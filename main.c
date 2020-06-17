//
// Created by Maxi on 6/17/20.
//
#include "stdio.h"
#include "stdlib.h"

int **createMatrix(int row, int column);

void **createAnytypeMatrix(int size, int row, int column);

int readMatrix(FILE *filePointer, int **matrix, int row, int column);

int printMatrix(int **matrix, int row, int column);

int **matrixProduct(int **mat1rix, int **mat2, int row, int column, int column2);

int main(int argc, char *argv[])
{
    int **mat1, **mat2, **matProd;
    FILE *fp;
    int n, m, p;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <inFile>\n", argv[0]);
        exit(0);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("Could not open file ");
        exit(1);
    }
    fscanf(fp, "%d%d%d", &n, &m, &p);
//    mat1 = createMatrix(n, m);    // create an n X m matrix
    mat1 = (int **) createAnytypeMatrix(sizeof(int), n, m);
    readMatrix(fp, mat1, n, m); // read matrix mat1 from fp
    printMatrix(mat1, n, m);    // print mat1
//    mat2 = createMatrix(m, p);    // create an m X p matrix
    mat2 = (int **) createAnytypeMatrix(sizeof(int), m, p);
    readMatrix(fp, mat2, m, p); // read matrix mat2 from fp
    printMatrix(mat2, m, p);    // print mat2
    matProd = matrixProduct(mat1, mat2, n, m, p); // mat1 X mat2
    printMatrix(matProd, n, p); // print matrix matProd

    free(mat1);
    free(mat2);
    free(matProd);

    exit(0);
}

// Create a row * column empty matrix(int **)
int **createMatrix(int row, int column)
{
    // initialize a 2D array(int **) to store 1D array(int *)
    int **matrix = malloc(row * sizeof(int *));
    // Error handle
    if (matrix == NULL)
    {
        perror("matrix malloc Failed at createMatrix");
    }
    // initialize each 1D array(int *) in 2D array(int **) to store int
    for (int i = 0; i < row; i++)
    {
        matrix[i] = malloc(column * sizeof(int));
        // Error handle
        if (matrix[i] == NULL)
        {
            perror("matrix row malloc Failed at createMatrix");
        }
    }
    return matrix;
}

// Read a matrix from file and put it into matrix(int **) which is a row * column matrix.
int readMatrix(FILE *filePointer, int **matrix, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            int tmp = 0;
            fscanf(filePointer, "%d", &tmp);
            matrix[i][j] = tmp;
        }
    }
    return 0;
}

// Print matrix
int printMatrix(int **matrix, int row, int column)
{
    // Print the head of the matrix
    printf("%s %d %s %d\n", "Matrix", row, "*", column);
    // print each item inside the matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        // print proper link break
        printf("\n");
    }
    return 0;
}

// Calculate the product of two matrix(int **).
int **matrixProduct(int **matrix1, int **matrix2, int row, int column, int column2)
{
    // create a matrix
    int **result = createMatrix(row, column2);
    // store an element in the result matrix
    int resultItem = 0;

    // Matrix product calculate.
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column2; j++)
        {
            // Calculate one item in result
            for (int k = 0; k < column; k++)
            {
                // Calculate one part of the item and put it in resultItem.
                resultItem += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = resultItem;
            // reset resultItem
            resultItem = 0;
        }
    }
    // return result.
    return result;
}

// Create a row * column empty matrix(void **)
void **createAnytypeMatrix(int size, int row, int column)
{
    if (!(size > 0))
    {
        perror("error with size");
    }
    // initialize a 2D array(int **) to store 1D array(int *)
    void **matrix = malloc(row * sizeof(void *));
    // Error handle
    if (matrix == NULL)
    {
        perror("matrix malloc Failed at createMatrix");
    }
    // initialize each 1D array(int *) in 2D array(int **) to store int
    for (int i = 0; i < row; i++)
    {
        matrix[i] = malloc(column * size);
        // Error handle
        if (matrix[i] == NULL)
        {
            perror("matrix row malloc Failed at createMatrix");
        }
    }
    return matrix;
}