#include "../inc/magicSquare.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


 int ReturnMagic(  int rows, int cols, int **twoDMatrix) {
     int sumDiag = 0;
     //  char magic[81];
     int isMagic;
     for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++) {
             if (i == j)// !!!!Where rows and cols match ONLY !!!!
                 sumDiag = sumDiag + twoDMatrix[i][j];// Diagonals
         }//for
     }//for

     int sumRow = 0;
     //For Rows
     for (int i = 0; i < rows; i++) {
         sumRow = 0;// resets for next iteration
         for (int j = 0; j < cols; j++) {
             sumRow = sumRow + twoDMatrix[i][j];// rows/ normal
         }//for
         if (sumDiag == sumRow)
             isMagic = 1;//     1== true Yes is magic ,     0== is not magic
         else {
             isMagic = 0;
             break;
         }//else
     }//for

     int sumCol = 0;
     //For Columns
     for (int i = 0; i < rows; i++) {
         sumCol = 0;// resets for next iteration
         for (int j = 0; j < cols; j++) {
             sumCol = sumCol + twoDMatrix[j][i]; //columns
         }//for
         if (sumDiag == sumCol)
             isMagic = 1;
         else {
             isMagic = 0;
             break;
         }//else
     }//for
return isMagic;

}
