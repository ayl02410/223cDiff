//
//  Algos.c
//  Diff_A_Liao
//
//  Created by Alex Liao on 2019/5/18.
//  Copyright © 2019年 Alex Liao. All rights reserved.
//  With code sample from Professor William McCarthy.

#include "Algos.h"
#define BUFFERLEN 256

void diffNormal(File* left, File* right) {
   int matchFound = -1;   /**/   int fromLineAt = 0;   /**/   File* lastRight = NULL;
   while (NULL != left) {
      lastRight = right;  /**/  matchFound = false;  /**/  fromLineAt = left->stop;
      while (NULL != right && (matchFound = compare_Paragraph_Of(left, right)) == false) {
         right = next_Paragraph_Of(right);
      }
      right = lastRight;
      if (matchFound) {
         while ((matchFound = compare_Paragraph_Of(left, right)) == false) {
            printf("%da%d,%d\n", left->start, right->start+1, right->stop+1);
            print_Paragraph_Single(right, 0, printright);
            right = next_Paragraph_Of(right);
            lastRight = right;
         }
         int lx = left->start, rx = right->start;
         for (int ix = 0; ix < (left->stop - left->start); ++ix) {
            if (strcmp(left->lines[lx], right->lines[rx]) != 0) {
               printf("%dc%d\n", lx + 1, rx + 1);
               printf("< %s ---\n", left->lines[lx]);
               printf("> %s", right->lines[rx]);
            }
            ++lx; ++rx;
         }
         left = next_Paragraph_Of(left);
         right = next_Paragraph_Of(right);
      } else {
         printf("%d,%dd%d\n", left->start+1, left->stop+1, right->start);
         print_Paragraph_Single(left, 0, printleft);
         left = next_Paragraph_Of(left);
      }
   }
   while (NULL != right) {
      int toLineAt = fromLineAt + (right->stop - right->start);
      printf("%da%d,%d\n", fromLineAt, toLineAt - 1, right->stop);
      print_Paragraph_Single(right, 0, printright);
      right = next_Paragraph_Of(right);
   }
   printEndOfOperation();
}
// End of diffNormal = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void diffSideBySide(File* left, File* right) {
   bool matchFound = false;   /**/   File* lastRight = NULL;
   while (NULL != left) {
      lastRight = right;  /**/  matchFound = false;
      while (NULL != right && (matchFound = compare_Paragraph_Of(left, right)) == false) {
         right = next_Paragraph_Of(right);
      }
      right = lastRight;
      
      if (matchFound) {
         while ((matchFound = compare_Paragraph_Of(left, right)) == false) {
            print_Paragraph_Single(right, 1, printright);
            right = next_Paragraph_Of(right);
            lastRight = right;
         }
         int lx = left->start, rx = right->start;
         
         for (int ix = 0; ix < (left->stop - left->start); ++ix) {
            char leftCopy[BUFFERLEN];   /**/   char rightCopy[BUFFERLEN];
            size_t len1 = strlen(left->lines[lx]);
            size_t len2 = strlen(right->lines[rx]);
            strncpy(leftCopy, left->lines[lx], BUFFERLEN);
            strncpy(rightCopy, right->lines[rx], BUFFERLEN);
            leftCopy[len1 - 1] = '\0';
            rightCopy[len2 - 1] = '\0';
            if (strcmp(left->lines[lx], right->lines[rx]) != 0) {
               printf("%-49s| %s\n", leftCopy, rightCopy);
            }
            else { printf("%-50s %s\n", leftCopy, rightCopy);}
            ++lx; ++rx;
         }
         printf("\n");
         left = next_Paragraph_Of(left);
         right = next_Paragraph_Of(right);
      } else {
         print_Paragraph_Single(left, 1, printleft);
         left = next_Paragraph_Of(left);
      }
   }
   while (NULL != right) {
      print_Paragraph_Single(right, 1, printright);
      right = next_Paragraph_Of(right);
   }
   printEndOfOperation();
}
// End of diffSideBySide = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void diff_SBS_LftCol(File* left, File* right) {
   bool matchFound = false;   /**/   File* lastRight = NULL;
   while (NULL != left) {
      lastRight = right;  /**/  matchFound = false;
      while (NULL != right && (matchFound = compare_Paragraph_Of(left, right)) == false) {
         right = next_Paragraph_Of(right);
      }
      right = lastRight;
      if (matchFound) {
         while ((matchFound = compare_Paragraph_Of(left, right)) == false) {
            print_Paragraph_Single(right, 1, printright);
            right = next_Paragraph_Of(right);
            lastRight = right;
         }
         int lx = left->start, rx = right->start;
         
         for (int ix = 0; ix < (left->stop - left->start); ++ix) {
            char leftCopy[BUFFERLEN];
            size_t len1 = strlen(left->lines[lx]);
            strncpy(leftCopy, left->lines[lx], BUFFERLEN);
            leftCopy[len1 - 1] = '\0';
            if (strcmp(left->lines[lx], right->lines[rx]) != 0) {
               char rightCopy[BUFFERLEN];
               size_t len2 = strlen(right->lines[rx]);
               strncpy(rightCopy, right->lines[rx], BUFFERLEN);
               rightCopy[len2 - 1] = '\0';
               printf("%-49s| %s\n", leftCopy, rightCopy);
            }
            else { printf("%-48s %s\n", leftCopy,"(");}
            ++lx; ++rx;
         }
         printf("\n");
         left = next_Paragraph_Of(left);
         right = next_Paragraph_Of(right);
      } else {
         print_Paragraph_Single(left, 1, printleft);
         left = next_Paragraph_Of(left);
      }
   }
   while (NULL != right) {
      print_Paragraph_Single(right, 1, printright);
      right = next_Paragraph_Of(right);
   }
   printEndOfOperation();
}
// End of diff_SBS_LftCol = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void diff_SBS_SCmnLines(File* left, File* right) {
   bool matchFound = false;   /**/   File* lastRight = NULL;
   while (NULL != left) {
      lastRight = right;  /**/  matchFound = false;
      while (NULL != right && (matchFound = compare_Paragraph_Of(left, right)) == false) {
         right = next_Paragraph_Of(right);
      }
      right = lastRight;
      if (matchFound) {
         while ((matchFound = compare_Paragraph_Of(left, right)) == false) {
            print_Paragraph_Single(right, 1, printright);
            right = next_Paragraph_Of(right);
            lastRight = right;
         }
         int lx = left->start, rx = right->start;
         
         for (int ix = 0; ix < (left->stop - left->start); ++ix) {
            if (strcmp(left->lines[lx], right->lines[rx]) != 0) {
               size_t len1 = strlen(left->lines[lx]);
               size_t len2 = strlen(right->lines[rx]);
               char leftCopy[BUFFERLEN];
               char rightCopy[BUFFERLEN];
               strncpy(leftCopy, left->lines[lx], BUFFERLEN);
               strncpy(rightCopy, right->lines[rx], BUFFERLEN);
               leftCopy[len1 - 1] = '\0';
               rightCopy[len2 - 1] = '\0';
               printf("%-49s| %s", leftCopy, rightCopy);
            }
            //else { printf("%-48s %s\n", leftCopy,"(");}
            ++lx; ++rx;
         }
         printf("\n");
         left = next_Paragraph_Of(left);
         right = next_Paragraph_Of(right);
      } else {
         print_Paragraph_Single(left, 1, printleft);
         left = next_Paragraph_Of(left);
      }
   }
   while (NULL != right) {
      print_Paragraph_Single(right, 1, printright);
      right = next_Paragraph_Of(right);
   }
   printEndOfOperation();
}
// End of diff_SBS_SCmnLines = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void diffContextual(File* left, File* right, const int numberOfUserRequestLines) {
   int matchFound = -1;   /**/   int fromLineAt = 0;   /**/   File* lastRight = NULL;
   int leftUnmatchLine = 1;   /**/   int rightUnmatchLine = 1;   /**/   File* lastLeft = left;
   while (NULL != left) {
      lastRight = right;  /**/  matchFound = false;  /**/  fromLineAt = left->stop;
      while (NULL != right && (matchFound = compare_Paragraph_Of(left, right)) == false) {
         right = next_Paragraph_Of(right);
      }
      right = lastRight;
      
      if (matchFound) {
         while ((matchFound = compare_Paragraph_Of(left, right)) == false) {
            printf("*** %d,%d ***\n", left->start + 1, numberOfUserRequestLines);
            printf("--- %d,%d ---\n", right->start + 1, right->stop + numberOfUserRequestLines + 1);
            print_Paragraph_ContextUnify(right, '+', printContextOrUnify);
            lastRight = right;
            right = next_Paragraph_Of(right);
         }
         
         left = next_Paragraph_Of(left);
         right = next_Paragraph_Of(right);
         
         if (NULL != left) {
            int nx = lastRight->stop + 1, contextStop = lastRight->stop + numberOfUserRequestLines;
            while (nx <= contextStop) { printf(" %s", lastRight->lines[nx++]); }
            printf("***************\n");
         }
      } else {
         lastLeft = left;
         lastLeft = next_Paragraph_Of(lastLeft);
         int ulx = lastLeft->start, urx = right->start;
         
         for (int ix = 0; ix < (lastLeft->stop - lastLeft->start); ++ix) {
            if (strcmp(left->lines[ulx], right->lines[urx]) != 0) {
               leftUnmatchLine += ulx;   rightUnmatchLine += urx;
            }
            ++ulx; ++urx;
         }
         int nlx = left->start - numberOfUserRequestLines;
         printf("*** %d,%d ***\n", nlx + 1, leftUnmatchLine + numberOfUserRequestLines);
         
         for ( ; nlx < left->start; ++nlx) { printf("  %s", left->lines[nlx]); }
         
         print_Paragraph_ContextUnify(left, '-', printContextOrUnify);
         
         left = next_Paragraph_Of(left);
         int ilx = left->start, irx = right->start;
         for (; ilx < leftUnmatchLine + numberOfUserRequestLines; ++ilx) {
            if (strcmp(left->lines[ilx], right->lines[irx]) != 0) {
               printf("! %s", left->lines[ilx]);
            } else { printf("  %s", left->lines[ilx]); }
            ++irx;
         }
         
         int nrx = right->start - numberOfUserRequestLines;
         printf("--- %d,%d ---\n", nrx + 1, rightUnmatchLine + numberOfUserRequestLines);
         for ( ; nrx < right->start; ++nrx) { printf("  %s", right->lines[nrx]); }
         
         int blx = left->start, brx = right->start;
         for ( ; brx < rightUnmatchLine + numberOfUserRequestLines; ++brx) {
            if (strcmp(left->lines[blx], right->lines[brx]) != 0) {
               printf("! %s", right->lines[brx]);
            } else { printf("  %s", right->lines[brx]); }
            ++blx;
         }
         printf("***************\n");
      }
   }
   while (NULL != right) {
      int crx = right->start - numberOfUserRequestLines;
      int clx = lastLeft->stop - numberOfUserRequestLines;
      printf("*** %d,%d ***\n", clx + 1, lastLeft->stop);
      printf("--- %d,%d ---\n", crx, right->stop);
      
      for ( ; clx < lastLeft->stop; ++clx) { printf("  %s", lastLeft->lines[clx]); }
      printf("+ %s", right->lines[right->start - 1]);
      print_Paragraph_ContextUnify(right, '+', printContextOrUnify);
      
      right = next_Paragraph_Of(right);
      printf("***************\n");
   }
   printEndOfOperation();
}
// End of diffContextual = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void diffUnified(File* left, File* right, const int numberOfUserRequestLines) {
   int matchFound = -1;   /**/   int fromLineAt = 0;   /**/   File* lastRight = NULL;
   int leftUnmatchLine = 1;   /**/   int rightUnmatchLine = 1;   /**/   File* lastLeft = left;
   while (NULL != left) {
      lastRight = right;  /**/  matchFound = false;  /**/  fromLineAt = left->stop;
      while (NULL != right && (matchFound = compare_Paragraph_Of(left, right)) == false) {
         right = next_Paragraph_Of(right);
      }
      right = lastRight;
      
      if (matchFound) {
         while ((matchFound = compare_Paragraph_Of(left, right)) == false) {
            printf("@@ -%d,%d ", left->start + 1, numberOfUserRequestLines);
            printf("+%d,%d @@\n", right->start + 1, right->stop + numberOfUserRequestLines + 1);
            print_Paragraph_ContextUnify(right, '+', printContextOrUnify);
            lastRight = right;
            right = next_Paragraph_Of(right);
         }
         
         left = next_Paragraph_Of(left);
         right = next_Paragraph_Of(right);
         
         if (NULL != left) {
            int nx = lastRight->stop + 1, contextStop = lastRight->stop + numberOfUserRequestLines;
            while (nx <= contextStop) { printf(" %s", lastRight->lines[nx++]); }
         }
      } else {
         lastLeft = left;
         lastLeft = next_Paragraph_Of(lastLeft);
         int ulx = lastLeft->start, urx = right->start;
         
         for (int ix = 0; ix < (lastLeft->stop - lastLeft->start); ++ix) {
            if (strcmp(left->lines[ulx], right->lines[urx]) != 0) {
               leftUnmatchLine += ulx;   rightUnmatchLine += urx;
            }
            ++ulx; ++urx;
         }
         int nlx = left->start - numberOfUserRequestLines;
         int nrx = right->start - numberOfUserRequestLines;
         
         printf("@@ -%d,%d ", nlx + 1, nrx);
         printf("+%d,%d @@\n", nrx + 1, rightUnmatchLine + numberOfUserRequestLines);
         
         for ( ; nlx < left->start; ++nlx) { printf("  %s", left->lines[nlx]); }
         
         print_Paragraph_ContextUnify(left, '-', printContextOrUnify);
         left = next_Paragraph_Of(left);
         
         int ilx = left->start, irx = right->start;
         for (; ilx < leftUnmatchLine + numberOfUserRequestLines; ++ilx) {
            if (strcmp(left->lines[ilx], right->lines[irx]) != 0) {
               printf("- %s", left->lines[ilx]);
               printf("+ %s", right->lines[irx]);
            } else { printf("  %s", left->lines[ilx]); }
            ++irx;
         }
      }
   }
   while (NULL != right) {
      int crx = right->start - numberOfUserRequestLines;
      int clx = lastLeft->stop - numberOfUserRequestLines;
      printf("@@ -%d,%d ", clx + 1, lastLeft->stop);
      printf("+%d,%d @@\n", crx, right->stop);
      
      for ( ; clx < lastLeft->stop; ++clx) { printf("  %s", lastLeft->lines[clx]); }
      printf("+ %s", right->lines[right->start - 1]);
      print_Paragraph_ContextUnify(right, '+', printContextOrUnify);
      
      right = next_Paragraph_Of(right);
   }
   printEndOfOperation();
}
// End of diffUnified = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
