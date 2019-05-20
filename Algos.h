//
//  Algos.h
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/18.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  More complex diffing algorithms

#ifndef Algos_h
#define Algos_h
#include "File.h"

#include <stdio.h>
void diffNormal(File*, File*);
void diffUnified(File*, File*, const int);
void diffContextual(File*, File*, const int );
void diffSideBySide(File*, File*);
void diff_SBS_LftCol(File*, File*);
void diff_SBS_SCmnLines(File*, File*);
#endif /* Algos_h */
