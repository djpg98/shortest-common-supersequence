/*
Author: Diego Peña
Creation Date: 17-05-2020
Last Modified: 19-05-2020, 12:15 pm VET
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supersequence.h"

/*If a matrix is represented as a 1D array, in row major order, given the number of columns of the matrix and the coordinates
of an element, this function returns the index corresponding to the element in the 1D Array*/
int getMatrixIndex(int ncolumns, int row, int column){
    return ncolumns * row + column;
}

/*When recovering the supersequence, if the number of either the row or the column reaches zero, it means all the characters
in one of the two strings are already in the part of thesupersequence we have recovered, so we must finish reconstructing 
the rest by filling the remaining spots with the characters in the other string not yet in the sequence*/
void finish_supersequence(char * supersequence, char * str, int seq_index, int str_index){
    for(int i = str_index; i  > 0; i--){
        supersequence[seq_index] = str[str_index - 1];
        str_index--;
        seq_index--;
     }
}

/*Using the DP Matrix generated by shortest_common_supersequence, along with the strings for which we want to solve the 
problem, the size of the supersequence and the coordinates of the leftmost corner of the matrix, it reconstructs the
supersequence that anwers the problem and stores it in the supersequence variable
NOTE: I decided it was more convenient to pass the size of the supersequence as an argument to avoid searching for it
in the matrix for a second time, since shortest_common_subsequence does it a few lines before calling recover*/
void recover(char * supersequence, char * str1, char * str2, int * seq_table, int seq_index, int row, int col){
    int ncols,value1, value2;

    ncols = strlen(str2) + 1;

    while (seq_index >= 0){
        if (str1[row - 1] == str2[col - 1]){
            supersequence[seq_index] = str2[col - 1];
            row--;
            col--;
        } else{
            value1 = seq_table[getMatrixIndex(ncols, row, col - 1)];
            value2 = seq_table[getMatrixIndex(ncols, row - 1, col)];

            if (value1 <= value2){
                supersequence[seq_index] = str2[col - 1];
                col--;
            } else{
                supersequence[seq_index] = str1[row - 1];
                row--;
            }
        }

        seq_index--;

        if (row == 0){
            finish_supersequence(supersequence, str2, seq_index, col);
            return;
        }

        if (col == 0){
            finish_supersequence(supersequence, str1, seq_index, row);
            return;
        }
    }
}

/*Uses DP to determinate the shortest common subsequence between str1 and str2*/
char * shortest_common_supersequence(char * str1, char * str2){
    int * seq_table;
    char * supersequence;
    int rows, cols, value1, value2, seq_size, current_row, current_col;

    rows = strlen(str1) + 1;
    cols = strlen(str2) + 1;

    seq_table = (int *)malloc(sizeof(int) * cols * rows);

    for (int i = 0; i < rows; i++){
        seq_table[getMatrixIndex(cols, i, 0)] = i; 
    }

    for (int j = 0; j < cols; j++){
        seq_table[getMatrixIndex(cols, 0, j)] = j;
    }

    for (int i = 1; i < rows; i++){
        for (int j = 1; j < cols; j++){
            if (str1[i -1] == str2[j - 1]){
                seq_table[getMatrixIndex(cols, i, j)] = seq_table[getMatrixIndex(cols, i - 1, j - 1)] + 1;
            } else {
                value1 = seq_table[getMatrixIndex(cols, i, j - 1)];
                value2 = seq_table[getMatrixIndex(cols, i - 1, j)];
                if (value1 <= value2){
                    seq_table[getMatrixIndex(cols, i, j)] = value1 + 1;
                } else {
                    seq_table[getMatrixIndex(cols, i, j)] = value2 + 1;
                }
            }
        }
    }


    seq_size = seq_table[getMatrixIndex(cols, rows - 1, cols - 1)];

    supersequence = (char *)malloc(seq_size + 1);

    supersequence[seq_size] = '\0';

    recover(supersequence, str1, str2, seq_table, seq_size - 1, rows - 1, cols - 1);

    free(seq_table);

    return supersequence;
}