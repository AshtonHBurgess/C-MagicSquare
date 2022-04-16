
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/magicSquare.h"
int main(int argc, char *argv[]) {
    setbuf(stdout,0);
    FILE *inputFile;
    FILE *outGoingFile;
    int err = 0;
    LittleChar op1,op2, inOp, outOp;
    char next[3];
    BigChar file1, file2, inFile, outFile, line;
    char *lineToRead;
    int **twoDMatrix;
    int isMagic;
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
                    fprintf( stderr,"Invalid command line argument usage.");
//                    err = 1;
                    exit(1);
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
                    fprintf( stderr,"Invalid command line argument usage.");
//                    err = 1;
                    exit(1);
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
            fprintf( stderr,"Invalid command line argument usage.");
//            err = 1;
            exit(1);
        }//else
//op + file 2
        if ((strcmp(op2, "-i")) == 0) {
            strcpy(inFile, file2);

        }//else if
        else if ((strcmp(op2, "-o")) == 0) {
            strcpy(outFile, file2);

        }//else if
        else {
            fprintf( stderr,"Invalid command line argument usage.");
//            err = 1;
            exit(1);
        }//else

        if ((inputFile = fopen(inFile, "r")) == NULL) {
            fprintf( stderr,"Cannot open %s for reading.", inFile);
//            err = 1;
            exit(1);
        }//if f
        //else printf("Opened file successfully \n");

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
       BigChar magic;

        int sumDiag = 0;
      //  char magic[81];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == j)// !!!!Where rows and cols match ONLY !!!!
                    sumDiag = sumDiag + twoDMatrix[i][j];// Diagonals
            }//for
        }//for

            isMagic = ReturnMagic(rows,cols,twoDMatrix);
        if (isMagic == 1){

        sprintf(magic, "Is a magic square (the sums are all %d)", sumDiag);// concat num to string, strcpy, on steroids
    }//if
        else {
            sprintf(magic, "Is not a magic square");
        }//else
//        sprintf(magic, "%s",(returnMagic(isMagic, sumRow)));


        outGoingFile = fopen(outFile, "w");
        if (outGoingFile == NULL) {
            fprintf( stderr,"Cannot open %s for writing.", outFile);
            exit(1);
//           err=1;
        }//if
        sprintf(next, "\n");
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                fprintf(outGoingFile, "%3i ", twoDMatrix[i][j]);
            }//for
            fprintf(outGoingFile, "\n");
        }//for
        fprintf(outGoingFile,"%s",magic);

        fclose(outGoingFile);

        for (int i = 0; i < rows; i++){
            free(twoDMatrix[i]);
        }//for
        free(twoDMatrix);

    }//if argc
    else if (argc != 5) {
        fprintf( stderr,"Invalid number of command line arguments.");
        exit(1);
    }//else if
    return err;
}//end of main
