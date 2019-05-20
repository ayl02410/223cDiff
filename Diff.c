//
//  Diff.c
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/4.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  With code sample from Professor William McCarthy.
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Utils.h"  // Utilities and helpers.
#include "File.h"   // Contains operations to perform on a file.
#include "Algos.h"  // Contains more complex diffing algorithms.

#define MAXLINES 1024
#define BUFFERLEN 256
#define MAXPARAGRAPHS 4096

// SWITCH macro Attribution: https://stackoverflow.com/posts/51816519/revisions
#ifndef SWITCH_CASE_INIT
#define SWITCH_CASE_INIT
#define SWITCH(X)   for (char* __switch_p__ = X, __switch_next__=1 ; __switch_p__ ; __switch_p__=0, __switch_next__=1) { {
#define CASE(X)         } if (!__switch_next__ || !(__switch_next__ = strcmp(__switch_p__, X))) {
#define DEFAULT           } {
#define END         }}
#endif

#define ARGC_ERROR 1
#define FILE_OPEN_ERROR 2
#define TOOMANYFILES_ERROR 3
#define UNRECOGNIZED_OPTION_ERROR 4
#define CONFLICTING_OPTIONS_ERROR 5
#define COMP_DIR_NOT_SUPPORTED_ERROR 6
#define OUTPUT_OPTION_NOT_SUPPORTED_ERROR 7

typedef char* STRING;
typedef struct files {STRING member[2];} FileNames; // Store files names

/* = = = = Output Option State = = = = */
bool Brief = false;                    //
bool Normal = false;                   //
bool Context = false;                  //
bool Unified = false;                  //
bool Identical = false;                //
bool SideBySide = false;               //
bool ShowVersion = false;              //
bool LeftColumnOnly = false;           //
bool Suppress_Common_Lines = false;    //
/*= = End of Output Option State = = = */

int numberOfUserRequestLines = 3; // For use in -c and -u

int file1LineCount = 0, file2LineCount = 0;
STRING file1Lines[MAXLINES], file2Lines[MAXLINES];

//= = Method Prototypes = = = = = = = = = = = = = =//
FileNames argvChecker(int, const STRING[]);        //
void loadFiles(const STRING, const STRING);        //
void summarizeFlags(const STRING, const STRING);   //
void analyzeFlags(void);                           //
void convertToInteger(STRING);                     //
//= = End of Method Prototypes = = = = = = = = = = //


int main(int argc, const STRING argv[]) {
   FileNames names = argvChecker(argc, argv);
   if (ShowVersion) { printVersion(); } // Print version, then exit.
   STRING name1 = names.member[0], name2 = names.member[1];
   loadFiles(name1, name2);
   analyzeFlags();
   summarizeFlags(name1, name2);
   File* left = _1st_Line_Of(file1Lines, file1LineCount);
   File* right = _1st_Line_Of(file2Lines, file2LineCount);
   
   int compResult = -1;
   if (Brief || Identical) { // -s and/or -q
      printf("comp file\n");
      compResult = compareFileOf(left, right); // 1 = files differ.
      printf("comp result: %d\n", compResult);
      if (Brief && Identical) {
         (compResult) ? printBrief(name1, name2) : printIdentical(name1, name2);
      } else if (Identical && 0 == compResult) { printIdentical(name1, name2);
      } else if (Brief && 1 == compResult) { printBrief(name1, name2); }
   }
   else if (Normal) { diffNormal(left, right); exit(0); }
   else if (LeftColumnOnly && SideBySide) { diff_SBS_LftCol(left, right); exit(0); }
   else if (Suppress_Common_Lines && SideBySide) { diff_SBS_SCmnLines(left, right); exit(0); }
   else if (SideBySide) { diffSideBySide(left, right); exit(0); }
   else if (Unified) {
      prrintFileModTime(name1, name2);
      diffUnified(left, right, numberOfUserRequestLines);
      exit(0);
   }
   else if (Context) {
      prrintFileModTime(name1, name2);
      diffContextual(left, right, numberOfUserRequestLines);
      exit(0);
   }
   else { printOutputOptionNotSupportedError(OUTPUT_OPTION_NOT_SUPPORTED_ERROR); }
   return 0;
}
// End of main = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void loadFiles(const STRING with_Name1, const STRING with_Name2) {
   char buffer[BUFFERLEN];
   memset(buffer, 0, sizeof(buffer));
   memset(file1Lines, 0, sizeof(file1Lines));
   memset(file2Lines, 0, sizeof(file2Lines));
   
   FILE *file1_Ptr = openFile(with_Name1, "r");
   FILE *file2_Ptr = openFile(with_Name2, "r");
   
   while (!feof(file1_Ptr) && NULL != fgets(buffer, BUFFERLEN, file1_Ptr))
   { file1Lines[file1LineCount++] = strdup(buffer); }
   fclose(file1_Ptr);
   
   while (!feof(file2_Ptr) && NULL != fgets(buffer, BUFFERLEN, file2_Ptr))
   { file2Lines[file2LineCount++] = strdup(buffer); }
   fclose(file2_Ptr);
}
// End of loadFiles = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void setFlagState(STRING arg) {
   SWITCH(arg)
      CASE("-r")
      CASE("--recursive")
         printDirNotSupportedError(COMP_DIR_NOT_SUPPORTED_ERROR);  break;
      CASE("--left-column")
         LeftColumnOnly = true;   break;
      CASE("--suppress-common-lines")
         Suppress_Common_Lines = true;   break;
      CASE("-q")
      CASE("--brief")
         printf("in q\n");
         Brief = true;   break;
      CASE("-s")
      CASE("--report-identical-files)")
         Identical = true;    break;
      CASE("--normal")
         Normal = true; break;
      CASE("-v")
      CASE("--version")
         ShowVersion = true;  break;
      CASE("-y")
      CASE("--side-by-side")
         printf("in y\n");
         SideBySide = true;   break;
      CASE("-c")
      CASE("-C")
      CASE("--context=")
         Context = true;   break;
      CASE("-u")
      CASE("-U")
      CASE("--unified=")
         Unified = true;   break;
      DEFAULT
         printUnrecognizedOptionError(arg, UNRECOGNIZED_OPTION_ERROR);
   END
}
// End of setFlagState = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void convertToInteger (STRING arg) {
   int ix = 0;
   while (!isdigit(arg[ix++])) { }
   while (isdigit(arg[ix])) { numberOfUserRequestLines = arg[ix] - '0';  ++ix; }
}
// End of convertToInteger = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


FileNames argvChecker(int argc, const STRING argv[]) {
   int index = 0;   /**/   STRING arg;   /**/   static FileNames fileNames;
   ++argv; --argc;
   while (argc-- && (arg = *argv++)) {
      
      if ('-' == arg[0]) { setFlagState(arg); }
      else if (isdigit(arg[0])) {  convertToInteger(arg); }
      else {
         if (2 != index) { fileNames.member[index++] = arg;}
         else {
            fprintf(stderr, "This ver. of diff accepts only two files!\n");
            fprintf(stderr, "Usage: ./diff [options...] file1 file2\n");
            exit(TOOMANYFILES_ERROR);
         }
      } // End of 1st-else
   } // End of while
   return fileNames;
}
// End of argvChecker = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void printFlagState(bool _) { (_) ? printf("%s\n", stateStrOf(_)) : printf("x\n"); }

// End of printFlagState = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void summarizeFlags(const STRING file1, const STRING file2) {
   printf("\nDiff Output Options for file: %s and %s \n", file1, file2);
   printf("  Legend: ✓ = Selected\n");
   printf("  Brief:                  "); printFlagState(Brief);
   printf("  Normal:                 "); printFlagState(Normal);
   printf("  Context:                "); printFlagState(Context);
   printf("  Unified:                "); printFlagState(Unified);
   printf("  Side by side:           "); printFlagState(SideBySide);
   printf("  Show version:           "); printFlagState(ShowVersion);
   printf("  Left Column:            "); printFlagState(LeftColumnOnly);
   printf("  Suppress Common Line:   "); printFlagState(Suppress_Common_Lines);
   printf("  Report Identical Files: "); printFlagState(Identical);
   printline();
}
// End of summarizeFlags = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void analyzeFlags() {
   if ( (Unified & (Normal || Context || SideBySide))  ||
        (Normal && (Context || Unified || SideBySide)) ||
        (SideBySide && (Normal || Context || Unified)) ||
        (Context && (Normal || Unified || SideBySide)) )
   { printConflictError(CONFLICTING_OPTIONS_ERROR); printf("6\n");}
   
   if (Brief || Identical) {
      printf("in brief\n");
      Normal = Context = Unified = SideBySide =
      LeftColumnOnly = Suppress_Common_Lines = false;
      printf("brief %d\n", Brief);
      printf("identical %d\n", Identical);
   } else if (false == Context && false == Unified && false == SideBySide) {
      printf("1~\n");
      Normal = true;
   } else if (LeftColumnOnly && (Context || Unified)) {
      printf("2\n");
      LeftColumnOnly = false;
   } else if (Suppress_Common_Lines && (Context || Unified)) {
      printf("3\n");
      Suppress_Common_Lines = false;
   } else if (LeftColumnOnly && Suppress_Common_Lines) {
      printf("4\n");
      Normal = true;
      LeftColumnOnly = Suppress_Common_Lines = false;
   } else if (Normal && (LeftColumnOnly || Suppress_Common_Lines)) {
      printf("5\n");
      LeftColumnOnly = Suppress_Common_Lines = false;
   }
}
// End of analyzeFlags = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
