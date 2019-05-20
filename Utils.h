//
//  Utils.h
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/10.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  With code sample from Professor William McCarthy.

#ifndef Utils_h
#define Utils_h

#include <time.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef char* STRING;

STRING stateStrOf(bool);
void printVersion();
void printConflictError(int);
void printDirNotSupportedError(int);
void printOutputOptionNotSupportedError(int);
void printUnrecognizedOptionError(STRING, int);

FILE* openFile(const STRING, const STRING);

void printleft(const STRING, const int);
void printright(const STRING, const int);
void printboth(const STRING, const STRING);
void printBrief(const STRING, const STRING);
void printIdentical(const STRING, const STRING);
void printContextOrUnify(const STRING, int);
void printline(void);
void printEndOfOperation();
void prrintFileModTime(STRING, STRING);
#endif /* Utils_h */
