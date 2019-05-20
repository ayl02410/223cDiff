//
//  File.h
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/12.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  With code sample from Professor William McCarthy.

#ifndef File_h
#define File_h

#include <stdio.h>
#include <stdbool.h>
#include "Utils.h"

typedef char* STRING;
typedef struct para {char** lines; int lineCount; int start; int stop;} File;

File* init_Paragraphs(STRING [], int, int, int);
File* _1st_Line_Of(STRING [], int);
File* next_Paragraph_Of(File*);
bool compare_Paragraph_Of(File*, File*);
int compareFileOf(File*, File*);
void print_Paragraph_ContextUnify(File*, int, void (*fp)(const STRING, int));
void print_Paragraph_Single(File*, int, void (*fp)(const STRING, const int));
void print_Paragraph_Double(File*, File*, void(*fp)(const STRING, const STRING));
char** return_All_Lines_Of(File*);
STRING paragraph_Info(File*);
size_t paragraph_Size(File*);
size_t wholeFileSize(File*);
void printFile(STRING [], int, void (*fp)(const STRING, const int));
void destroy_File(File*);
#endif /* File_h */
