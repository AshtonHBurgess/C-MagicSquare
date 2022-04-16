#include "../inc/magicSquare.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char returnMagic( int **twoDMatrix, int rows, int cols ) {

//For diagonal elements
    int isMagic;
    int sumDiag = 0;
    int sumRow = 0;
    int sumCol = 0;
    char magic[81];
    for (int q = 0; q < rows; q++) {
        for (int w = 0; w < cols; w++) {
            if (q == w)
                sumDiag = sumDiag + twoDMatrix[q][w];
        }//for
    }//for

//For Rows
    for (int i = 0; i < rows; i++) {
        sumRow = 0;// resets for next iteration
        for (int j = 0; j < cols; j++) {
            sumRow = sumRow + twoDMatrix[i][j];
        }//for
        if (sumDiag == sumRow)
            isMagic = 1;
        else {
            isMagic = 0;
            break;
        }//else
    }//for

//For Columns
    for (int i = 0; i < rows; i++) {
        sumCol = 0;// resets for next iteration
        for (int j = 0; j < cols; j++) {
            sumCol = sumCol + twoDMatrix[j][i];
        }//for
        if (sumDiag == sumCol)
            isMagic = 1;
        else {
            isMagic = 0;
            break;
        }//else
    }//for

    if (isMagic == 1) {
        sprintf(magic, "Is a magic square (the sums are all %d)", sumRow);
    }//if
    else {
        sprintf(magic, "Is not a magic square");
    }//else

return magic;
}//end of magic
