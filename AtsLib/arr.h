#ifndef ATSARR_H
#define ATSARR_H

#include <stdio.h>
#include <stdlib.h>

enum Type
{
    INT,
    FLOAT,
    DOUBLE,
    CHAR
};
typedef enum Type type_t;

/*
    Prints the given array

    Parameters:
    void *arr -> The array to be printed
    int n -> The length of the array
    type_t type -> The type of the array 
    |->>(INT, FLOAT, DOUBLE, CHAR)

    Returns: None
*/
void arrprint(void *arr, int n, type_t type)
{
    if (type == INT)
    {
        printf("{ ");
        int *temp = (int *) arr;
        for (int i = 0; i<n; i++)
            printf("%d ", temp[i]);
        printf("}\n");
    }
    else if (type == FLOAT)
    {
        printf("{ ");
        float *temp = (float *) arr;
        for (int i = 0; i<n; i++)
            printf("%f ", temp[i]);
        printf("}\n");
    }
    else if (type == DOUBLE)
    {
        printf("{ ");
        double *temp = (double *) arr;
        for (int i = 0; i<n; i++)
            printf("%lf ", temp[i]);
        printf("}\n");
    }
    else if (type == CHAR)
    {
        char *temp = (char *) arr;
        for (int i = 0; i<n; i++)
            printf("%c", temp[i]);
        printf("\n");
    }
}

/*
    Initializes a 2D matrix of a given type

    Params:
    int row -> The number of rows
    int col -> The number of columns
    type_t type -> The type of the matrix 
    |->>(INT, FLOAT, DOUBLE, CHAR)

    Returns
    void *mat -> The matrix
*/
void *initmat(int row, int col, type_t type)
{
    int size;
    if (type == INT) size = sizeof(int);
    else if (type == FLOAT) size = sizeof(float);
    else if (type == DOUBLE) size = sizeof(double);
    else if (type == CHAR) size = sizeof(char);

    void **mat = (void **) malloc(sizeof(void *) * row);
    for (int i = 0; i<col; i++)
    {
        void *vec = malloc(size * col);
        mat[i] = vec;
    }
    return mat;
}

#endif