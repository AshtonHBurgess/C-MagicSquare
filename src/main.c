
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/magicSquare.h"
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
    Line line;
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
                    fprintf( stderr,"invalid op\n");
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
                    fprintf( stderr,"invalid op\n");
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
            fprintf( stderr,"bad op ");
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
            fprintf( stderr,"bad op ");
            err = 1;
        }//else

        if ((inputFile = fopen(inFile, "r")) == NULL) {
            fprintf( stderr,"error: unable to open file!\n");
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
       char magic[81];
//        strcpy(magic,returnMagic(twoDMatrix,  rows, cols ));
        //For diagonal elements
        int isMagic;
        int sumDiag = 0;
        int sumRow = 0;
        int sumCol = 0;
      //  char magic[81];
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
            fprintf( stderr,"Error!");
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
        fprintf( stderr,"Error: %d", err);
    }//else if
    return err;
}//end of main









//        ATTEMPT #2


//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main(int argc, char *argv[]) {
//    setbuf(stdout,0);
//    FILE *inputFile;
//
////    int arraySize,*myArray;
////    myArray = (int*)malloc(sizeof(int)*arraySize);
////    for(int i=0; i<arraySize;i++){ printf("%i Vlaue %s",i,myArray[i]) }
//    int err = 0;
//    char op1[4];
//    char op2[4];
//    char inOp[4];
//    char outOp[4];
//    char file1[81];
//    char file2[81];
//    char inFile[81];
//    char outFile[81];
//    char *lineToRead;
//
////        FILE *file = fopen(file1, "r"); /* should check the result */
//        char line[256];
//        int count = 0;
//        int row = 0;
//        char array[5][81];//   need to make into a dynamic array
//
//
//    if (argc == 5) {
//        printf("Number of arguments:\t%i\n", argc); // number of arguements
//        for (int i = 0; i < argc; ++i) {
//            // printf("Argument: %s\n", argv[i]);
//            if (i == 1) {
//                strcpy(op1, argv[i]);
//                puts(op1);
//                if ((strcmp(op1, "-i")) == 0) {
//                    strcpy(inOp, op1);
//                    printf("in op");
//                    puts(inOp);
//                } else if ((strcmp(op1, "-o")) == 0) {
//                    strcpy(outOp, op1);
//                    printf("out op");
//                    puts(outOp);
//                } else {
//                    printf("invalid op\n");
//                    err = 1;
//                }
//
//
//
//
//                //   printf('%s', op1);
//            } else if (i == 2) {
//                strcpy(file1, argv[i]);
//
//                puts(file1);
//                //   printf('%s', file1);
//            } else if (i == 3) {
//                strcpy(op2, argv[i]);
//                puts(op2);
//                if ((strcmp(op2, "-i")) == 0) {
//                    strcpy(inOp, op2);
//                    printf("in op");
//                    puts(inOp);
//                } else if ((strcmp(op2, "-o")) == 0) {
//                    strcpy(outOp, op2);
//                    printf("out op");
//                    puts(outOp);
//                } else {
//                    printf("invalid op\n");
//                    err = 1;
//                }
//                //    printf('%s', op2);
//
//            } else if (i == 4) {
//                strcpy(file2, argv[i]);
//                puts(file2);
//                //printf('%s', file2);
//            }
//        }//for
//
////op + file 1
//        if ((strcmp(op1, "-i")) == 0) {
//            strcpy(inFile, file1);
//            printf("\ninfile =%s\n", inFile);
//        } else if ((strcmp(op1, "-o")) == 0) {
//            strcpy(outFile, file1);
//            printf("outfile =%s\n", outFile);
//        } else {
//            printf("bad op ");
//            err = 1;
//        }
//
////op + file 2
//        if ((strcmp(op2, "-i")) == 0) {
//            strcpy(inFile, file2);
//            printf("\ninfile =%s\n", inFile);
//        } else if ((strcmp(op2, "-o")) == 0) {
//            strcpy(outFile, file2);
//            printf("outfile =%s\n", outFile);
//        } else {
//            printf("bad op ");
//            err = 1;
//        }
//
//
//        if ((inputFile = fopen(inFile, "r")) == NULL) {
//            printf("error: unable to open file!\n");
//            err = 1;
//        } else printf("Opened file successfully \n");
//
//
//        while (fgets(line, sizeof(line), inputFile)) {
//
////            printf("%d Hello + %s ", count,line);
//
//
//            lineToRead = line;
//            printf(" %s ", lineToRead);
////            puts(lineToRead);
//            strcpy(array[count], lineToRead);
//
//            count++;
//
//        }//END OF WHILE
////        printf("\n\n %s ", array[3]);
//
//
//        printf("\n\n");
//        for (int i = 0; i < count; i++) {
//            printf(" %s ", array[i]);
//        }
//        fclose(inputFile);
//
//
//        int rows, cols, count2 = 0;
//
//
//        printf("\n\n %s ", array[0]);
//
//        int numList[(count * count)];
//        int twoDnumList[count][count];
//        for (int i = 0; i < count; i++) {
//
//            char *token1 = strtok(array[i], " ");
//            puts(token1);
//            while (token1 != NULL) {
//
//                int numFromChar = atoi(token1);   // convert ascii to int
//                if (i == 0 && count2 == 0) { rows = numFromChar; }
//
//                if (i == 0 && count2 == 1) { cols = numFromChar; }
//
//                if (i != 0) { numList[count2] = numFromChar; }
//
//
//                count2++;
//                token1 = strtok(NULL, " ");
//            }
//        }//for
//
//        printf(" yes    %d    %d\n", rows, cols);
//
//
//        int count3 = 0;
//        for (int i = 2; i < count2; i++) {
//            printf("%d ", numList[i]);
//        }
//
//        printf(" \n ");
//        int twoDList[rows][cols];
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//
//                twoDList[i][count3] = numList[count3];
//                printf(" %d ", twoDList[i][count3]);
//                count3++;
//
//
//                for (int i = 0; i < rows; i++) {
//
//                }
//            }
//
//        }
//
//        printf("\n\n");
//        int count4 = 2;
//        int matrix[rows][cols];
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                matrix[i][j] = numList[count4];
//                count4++;
//            }
//        }
//        int sumRows[rows];
//        for (int i = 0; i < rows; i++) { sumRows[i] = 0; }
//        int sumCols[cols];
//        for (int i = 0; i < rows; i++) { sumCols[i] = 0; }
//        int sumLeftDiag[rows];
//        for (int i = 0; i < rows; i++) { sumLeftDiag[i] = 0; }
//        int sumRightDiag[rows];
//        for (int i = 0; i < rows; i++) { sumRightDiag[i] = 0; }
//        int sum = 0;
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                printf("%d\t", matrix[i][j]);
//                if (i == 1) {
//                    sum = sum + matrix[i][j];
//                }//if
//                if (i == 2) {
//                    sumRows[0] = sumRows[0] + matrix[i][j];
//
//                }//if
//                if (i == 3) {
//                    sumRows[1] = sumRows[1] + matrix[i][j];
//                }//if
//                if (i == 4) {
//                    sumRows[2] = sumRows[2] + matrix[i][j];
//                }//if
//                if (i == 5) {
//                    sumRows[3] = sumRows[3] + matrix[i][j];
//                }//if
//                if (i == 6) {
//                    sumRows[4] = sumRows[4] + matrix[i][j];
//                }//if
////                if (i != 1 && i !=0) {
////
////
////
////                }//if
//
//            }//for
//            printf("\n");
//        }//for
//
//        printf("\nsum: %d   sumrows: %d\n", sum, sumRows[0]);
//
//
//        printf("\n\n");
//        int i, j, count;
//
//        int *ptr = malloc((rows * cols) * sizeof(int));
//
//        /* Putting 1 to 12 in the 1D array in a sequence */
//        for (int i = 0; i < rows * cols; i++)
//            //   ptr[i] = i + 1;
//            ptr[i] = numList[i + 2];
//        /* Accessing the array values as if it was a 2D array */
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++)
//                printf("%d\t", ptr[i * cols + j]);
//            printf("\n");
//        }
//
//        printf("\n");
//        for (int i = 0; i < rows * rows; i++) {
//
//
//            printf("%d\t", ptr[i]);
//
//
//        }
//
//
//        free(ptr);
//
//
//        printf("\n\nNext 2d \n");
//
//
//        char *line;
//        int **matrix2;
//        // maxrow and maxcol mimic count of lines from file
//        // for demo read x and y from terminal
////	int maxrow = 5; // used for debug
////	int maxcol = 4; // used for debug
//        int maxrow, maxcol;
////        printf("Please enter the number of rows: ");
////        scanf("%i", &maxrow);
////        printf("Please enter the number of columns: ");
////        scanf("%i", &maxcol);
//        maxrow = rows;
//        maxcol = cols;
//
//        // dynamically allocate an array
//        // maxrow = number of matrix rows
//        // maxcol = line length
//
//        matrix2 = (int **) malloc(sizeof(int *) * maxrow);
//
//        for (int count5 = 0; count5 < maxrow; count5++) {
//            matrix2[count5] = (int *) malloc(sizeof(int) * maxcol);
//        }
//        int count6 = 2;
//        // load the elements in to the matrix
//        printf("Now enter the element for the matrix...\n");
//        for (int row2 = 0; row2 < maxrow; row2++) {
//            for (int col2 = 0; col2 < maxcol; col2++) {
//                //printf("Row %d %d : ", (row2 + 1), (col2 + 1)*3);
//                matrix2[row2][col2] = numList[count6];
//                count6++;
//            }
//        }
//
//        // Write them back out
//        printf("Here is your matrix:\n");
//        for (int row2 = 0; row2 < maxrow; row2++) {
//            for (int col2 = 0; col2 < maxcol; col2++) {
//                printf("%3i ", matrix2[row2][col2]);
//
//            }
//            printf("\n");
//        }
//
//        //-------------------------------------------------------------------
//        //For diagonal elements
//        int flag;
//        int sumDiag = 0;
//        int sumRow = 0;
//        int sumCol = 0;
//        char magic[81];
//        for (int q = 0; q < rows; q++) {
//            for (int w = 0; w < cols; w++) {
//                if (q == w)
//                    sumDiag = sumDiag + matrix2[q][w];
//            }
//        }
//
//        //For Rows
//        for (int q = 0; q < rows; q++) {
//            sumRow = 0;
//            for (int w = 0; w < cols; w++) {
//                sumRow = sumRow + matrix2[q][w];
//            }
//            if (sumDiag == sumRow)
//                flag = 1;
//            else {
//                flag = 0;
//                break;
//            }
//        }
//
//        //For Columns
//        for (int q = 0; q < rows; q++) {
//            sumCol = 0;
//            for (int w = 0; w < cols; w++) {
//                sumCol = sumCol + matrix2[w][q];
//            }
//            if (sumDiag == sumCol)
//                flag = 1;
//            else {
//                flag = 0;
//                break;
//            }
//        }
//
//        if (flag == 1){
//            printf("\nMagic square\n");
//
//        sprintf(magic, "Is a magic square (the sums are all %d)", sum);
//    }//if
//        else {
//            printf("\nNo Magic square\n");
//            sprintf(magic, "Is not a magic square");
//        }
//        //---------------------------------------------------------------------
//
//        printf("Freeing the allocated matrix memory and terminating\n");
//
//        // To free the dynamically allocated memory
//        // Free each row pointer before freeing the array of pointers
//
//        printf("\nHERE1");
////        for (int row2 = 0; row2 < maxrow; row2++)
////        {
////            free(matrix2[row2]);
////        }
////        free(matrix2);
//
//        printf("\nHERE1");
//        int sentence;
//        FILE *fptr;
//
//
//        fptr = fopen(outFile, "w");
//
//        // exiting program
//        if (fptr == NULL) {
//            printf("Error!");
//            exit(1);
//        }
//
//        char endOfLine[3];
//        *endOfLine="\n";
//        for (int row2 = 0; row2 < maxrow; row2++)
//        {
//            for (int col2 = 0; col2 < maxcol; col2++)
//            {
//                printf("%3i ", matrix2[row2][col2]);
//                fprintf(fptr, "%3i ", matrix2[row2][col2]);
//            }
//            fprintf(fptr, "\n");
//            printf("\n");
//        }
//        fprintf(fptr,"%s",magic);
//
//
////        printf("Enter a sentence:\n");
////        fgets(sentence, sizeof(sentence), stdin);
//            sentence=1000;
////        fprintf(fptr, "%d", sentence);
//        fclose(fptr);
//
//
//        for (int row2 = 0; row2 < maxrow; row2++)
//        {
//            free(matrix2[row2]);
//        }
//        free(matrix2);
//
//    }//if argc
//    else if (argc != 5) {
//        err = 1;
//        printf("Error: %d", err);
//    }
//    return err;
//}//end of main










//          ATTEMPT #1
//
//        FILE *file = fopen(file1, "r"); /* should check the result */
//        char line[256];
//        int count = 0;
//        int row = 0;
//        char array[81][3];
//
//
//
//
//
//        inputFile= fopen()
//
//
//
//        while (fgets(line, sizeof(line), file)) {
//
//            printf("Hello + %s %d", line, count);
//
//            strcpy(array[count], line);
//
//            count = count + 1;
//
//        }//END OF WHILE
//        printf("\n\n");
//        fclose(file);
//        for (int i = 0; i <50;i++){
//           // printf("%s",array[i]);
//            strcpy(array[i],line);
//        }
//        printf("\n\n");
//        for (int i = 0; i <5;i++){
//            printf("%s",array[i]);
//        }



    //dynamyic mamory managment
    // command line arguements
    //file/ in and out

    //4test files to be used



    //steps   Read matrix from file,
    //determine if matrix is a migic square
    //how
    //read first line  AND dynamically create an appropriate 2D integer array and then read entries into the array
    //perform calculations on array to see if array is a magic square

    // say IS or Is not magic square
    // if is a magic square what the sums add up too
    //file inputs and outputs will be done via command line arguments







//magic square when every think equals to the same
