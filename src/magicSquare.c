
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    setbuf(stdout,0);
    FILE *inputFile;
    FILE *outGoingFile;
    int err = 0;
    char op1[4];
    char op2[4];
    char inOp[4];
    char outOp[4];
    char file1[81];
    char file2[81];
    char inFile[81];
    char outFile[81];
    char *lineToRead;
    char line[256];
    int count = 0;
    char array[10][81];  //temp array


    if (argc == 5) {
        for (int i = 0; i < argc; ++i) {
            if (i == 1) {
                strcpy(op1, argv[i]);
                if ((strcmp(op1, "-i")) == 0) {
                    strcpy(inOp, op1);
                }//if
                else if ((strcmp(op1, "-o")) == 0) {
                    strcpy(outOp, op1);
                }//else if
                else {
                    printf("invalid op\n");
                    err = 1;
                }//else
            }//if
            else if (i == 2) {
                strcpy(file1, argv[i]);
            }//else if
            else if (i == 3) {
                strcpy(op2, argv[i]);
                if ((strcmp(op2, "-i")) == 0) {
                    strcpy(inOp, op2);
                }//if
                else if ((strcmp(op2, "-o")) == 0) {
                    strcpy(outOp, op2);
                }//else if
                else {
                    printf("invalid op\n");
                    err = 1;
                }//else
            }//else if
            else if (i == 4) {
                strcpy(file2, argv[i]);
            }//else if
        }//for

//op + file 1
        if ((strcmp(op1, "-i")) == 0) {
            strcpy(inFile, file1);

        }//else if
        else if ((strcmp(op1, "-o")) == 0) {
            strcpy(outFile, file1);
        }//else
        else {
            printf("bad op ");
            err = 1;
        }//else
//op + file 2
        if ((strcmp(op2, "-i")) == 0) {
            strcpy(inFile, file2);

        }//else if
        else if ((strcmp(op2, "-o")) == 0) {
            strcpy(outFile, file2);

        }//else if
        else {
            printf("bad op ");
            err = 1;
        }//else

        if ((inputFile = fopen(inFile, "r")) == NULL) {
            printf("error: unable to open file!\n");
            err = 1;
        }//if
        else printf("Opened file successfully \n");

        while (fgets(line, sizeof(line), inputFile)) {
            lineToRead = line;
            strcpy(array[count], lineToRead);
            count++;
        }//END OF WHILE

        fclose(inputFile);

        int rows, cols, count2 = 0;
        int numList[(count * count)];
        for (int i = 0; i < count; i++) {
            char *token1 = strtok(array[i], " ");
            while (token1 != NULL) {
                int numFromChar = atoi(token1);   // convert ascii to int
                if (i == 0 && count2 == 0) { rows = numFromChar; }//if
                if (i == 0 && count2 == 1) { cols = numFromChar; }//if
                if (i != 0) { numList[count2] = numFromChar; }//if
                count2++;
                token1 = strtok(NULL, " ");}
        }//for

        char *line;
        int **twoDMatrix;
        twoDMatrix = (int **) malloc(sizeof(int *) * rows);

        for (int count5 = 0; count5 < rows; count5++) {
            twoDMatrix[count5] = (int *) malloc(sizeof(int) * cols);
        }//for
        int count6 = 2;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                twoDMatrix[i][j] = numList[count6];
                count6++;
            }//for
        }//for

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

        if (isMagic == 1){
            sprintf(magic, "Is a magic square (the sums are all %d)", sumRow);
        }//if
        else {
            sprintf(magic, "Is not a magic square");
        }//else

        outGoingFile = fopen(outFile, "w");

        // exiting program
        if (outGoingFile == NULL) {
            printf("Error!");
            exit(1);
        }//if

        char endOfLine[3];
        *endOfLine="\n";
        for (int row2 = 0; row2 < rows; row2++){
            for (int col2 = 0; col2 < cols; col2++){
                fprintf(outGoingFile, "%3i ", twoDMatrix[row2][col2]);
            }//for
            fprintf(outGoingFile, "\n");
        }//for
        fprintf(outGoingFile,"%s",magic);

        fclose(outGoingFile);

        for (int row2 = 0; row2 < rows; row2++){
            free(twoDMatrix[row2]);
        }//for
        free(twoDMatrix);

    }//if argc
    else if (argc != 5) {
        err = 1;
        printf("Error: %d", err);
    }//else if
    return err;
}//end of main

