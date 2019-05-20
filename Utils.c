//
//  Utils.c
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/10.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  With code sample from Professor William McCarthy.

#include "Utils.h"
#define BUFFERLEN 256

STRING stateStrOf(bool _) { return (_ == true) ? "✓" : " "; }

void printVersion() {
   printf("\n\nCPSC 223C - Diff Version Control 1.0.0\n");
   printf("\tCopyright (C) 2019 Alex Liao\n");
   printf("\tThis program is free software WITHOUT ANY WARRANTY: \n\tyou may redistribute it and/or modify it under the terms \n\tof the GNU General Public License as published by the Free \n\tSoftware Foundation ver. 3 of the License, or any later version.\n\tWith code samples by Professor William McCarthy.\n\n");
   exit(0);
}

void printConflictError(int error_code) {
   fprintf(stderr, "diff: conflicting output style options.\n");
   fprintf(stderr, "diff: Try `diff --help' for more information.)\n");
   exit(error_code);
}

void printDirNotSupportedError(int error_code) {
   fprintf(stderr, "Comparing directories is not supported\n");  exit(error_code);
}

void printOutputOptionNotSupportedError(int error_code) {
   fprintf(stderr, "Ouput option is not supported Currently.\n");  exit(error_code);
}

void printUnrecognizedOptionError(STRING error, int error_code) {
   fprintf(stderr, "Unrecognized option: %s\n", error);  exit(error_code);
}

FILE* openFile(const STRING filename, const STRING op_Mode) {
   FILE* tmp;
   if (NULL == (tmp = fopen(filename, op_Mode))) { printf("Can't open '%s'\n", filename); exit(1); }
   return tmp;
}

void printleft(const STRING left, const int twoColumn) {
   char buffer[BUFFERLEN];
   strncpy(buffer, left, BUFFERLEN);
   int bx = 0, len = (int)strlen(buffer) - 1;
   if (twoColumn) {
      for (; bx <= 48 - len; ++bx) { buffer[len + bx] = ' '; }
      buffer[len + bx++] = '<';
      buffer[len + bx++] = '\0';
   } else {
      printf("%s ", "<");
      buffer[len + bx++] = '\0';
   }
   printf("%s\n", buffer);
}

void printright(const STRING line, int twoColumn) {
   if (line == NULL) { return; }
   if (twoColumn) { printf("%50s %s", ">", line); }
   else { printf("%s %s", ">", line);}
   
}

void printboth(const STRING left, const STRING right) {
   //char left[BUFFERLEN];   /**/   size_t len = strlen(right);
   //if (len > 0) { strncpy(left, right, BUFFERLEN); }
   //left[len - 1] = '\0';
   printf("%-50s %s", left, right);
}

void printBrief(const STRING file1, const STRING file2) {
   printf("Files: %s and %s differ!\n\n", file1, file2); exit(0);
}

void printIdentical(const STRING file1, const STRING file2) {
   printf("Files: %s and %s are identical!\n\n", file1, file2); exit(0);
}

void printContextOrUnify(const STRING line, int indicator) {
   if ('!' == indicator) { printf("! %s", line); }
   else if ('+' == indicator) { printf("+ %s", line); }
   else if ('-' == indicator) { printf("- %s", line); }
}

void printline() {
   for (int i = 0; i < 11; ++i) { printf("======="); }
   printf("\n");
}

void printEndOfOperation() { printf("* * * * diff completes * * * *\n"); }

void prrintFileModTime(STRING file1, STRING file2) {
   struct stat file1_meta, file2_meta;
   stat(file1, &file1_meta);
   stat(file2, &file2_meta);
   char time1[50], time2[50];
   strftime(time1, 50, "%m %d %H:%M:%S %Y", localtime(&file1_meta.st_mtime));
   strftime(time2, 50, "%m %d %H:%M:%S %Y", localtime(&file2_meta.st_mtime));
   size_t alighBy = (strlen(file1) < strlen(file2)) ? strlen(file2) : strlen(file1);
   printf("*** %s %*s\n", file1, (int)alighBy + 20, time1);
   printf("--- %s %*s\n", file2, (int)alighBy + (int)(20 - (strlen(file2) - strlen(file1))), time2);
   printf("***************\n");
}
