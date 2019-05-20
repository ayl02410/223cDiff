//
//  File.c
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/12.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  With code sample from Professor William McCarthy.

#include "File.h"
#define BUFFERLEN 256

File* talloc() { return (File*)malloc(sizeof(File)); }
File* init_Paragraphs(STRING lines[], int lineCount, int start, int stop) {
   File* ptr = talloc();
   ptr->lines = lines;
   ptr->lineCount = lineCount;
   ptr->start = start;
   ptr->stop = stop;
   return ptr;
}

File* _1st_Line_Of(STRING lines[], int count) {
   File* p = init_Paragraphs(lines, count, 0, -1);
   return next_Paragraph_Of(p);
}

File* next_Paragraph_Of(File* p) {
   if (p == NULL || p->stop + 1 >= p->lineCount) { return NULL; }
   int brk;
   for (brk = p->stop + 1; brk < p->lineCount && 0 != strcmp(p->lines[brk], "\n"); ++brk) { }
   File* new_p = init_Paragraphs(p->lines, p->lineCount, p->stop + 1, brk);
   return new_p;
}

bool compare_Paragraph_Of(File* left, File* right) {
   if (left == NULL || right == NULL) { return false; }
   if (paragraph_Size(left) != paragraph_Size(right)) { return false; }
   if (left->start >= left->lineCount || right->start >= right->lineCount) { return false; }
   int lx = left->start, rx = right->start;
   while (0 == (strcmp(left->lines[lx++], right->lines[rx++]))) { }
   return true;
}

int compareFileOf(File* left, File* right) {
   printf("inside comp file\n");
   if (left->lineCount != right->lineCount) { return 1; }// Files have different line count.
   // Files have same line count, check if lines are same.
   int lineNum = 0, lineCount = left->lineCount;
   while (lineNum < lineCount) {
      if (strcmp(left->lines[lineNum], right->lines[lineNum]) != 0) { return 1; } // Files differ.
      ++lineNum;
   }
   return 0;
}

void print_Paragraph_ContextUnify(File* pgh, int indicator, void (*fp)(const STRING, const int)) {
   if (NULL == pgh) { return; }
   for (int ix = pgh->start; ix <= pgh->stop && ix != pgh->lineCount; ++ix)
   { fp(pgh->lines[ix], indicator); }
}

void print_Paragraph_Single(File* pgh, int column, void (*fp)(const STRING, const int)) {
   if (pgh == NULL) { return; }
   for (int i = pgh->start; i <= pgh->stop && i != pgh->lineCount; ++i)
   { fp(pgh->lines[i], column); }
}

void print_Paragraph_Double(File* left, File* right, void(*fp)(const STRING, const STRING)) {
   if (NULL == left || NULL == right) { return; }
   int lx = left->start, rx = right->start;
   for (int ix = 0; ix < (left->stop - left->start); ++ix) {
      fp(left->lines[lx++], right->lines[rx++]);
   }
}

STRING paragraph_Info(File* p) {
   static char buffer[BUFFERLEN];   // static for a reason
   snprintf(buffer, sizeof(buffer),
            "Lines: %p, fileSize: %d, start: %d, stop: %d\n",
            p->lines, p->lineCount, p->start, p->stop);
   return buffer;  // buf MUST be static
}

size_t wholeFileSize(File* p) { return p == NULL ? 0 : p->lineCount; }

void printFile(STRING lines[], int count, void (*fp)(const STRING, const int)) {
   File* pgh = _1st_Line_Of(lines, count);
   while (NULL != pgh) {
      print_Paragraph_Single(pgh, 0, fp);
      pgh = next_Paragraph_Of(pgh);
   }
   //printline();
}

size_t paragraph_Size(File* pgh) {
   return (NULL == pgh || pgh->stop < pgh->start) ? 0 : (pgh->stop - pgh->start + 1);
}

char** return_All_Lines_Of(File* pgh) { return pgh->lines; }
void destroy_File(File* p) { free(p); }
