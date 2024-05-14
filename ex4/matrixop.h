/*
 * File:   matrixop.h
 * Author: pyshe
 *
 * Created on May 17, 2019, 11:13 AM
 */

#pragma once

typedef struct
{
    int **body; // Jagged matrix of integers
    int numRow; // Number of rows
    int numCol; // Number of columns
} IntMatrix;    // (I'm using this for "Term Frequencies", because "f" are integers)

IntMatrix *allocIntMatrix(IntMatrix *pMatrix, int numRow, int numCol);
void freeIntMatrix(IntMatrix *pMatrix);

void printIntMatrix(IntMatrix *pMatrix);

typedef struct
{
    float **body;
    int numRow;
    int numCol;
} FloatMatrix; // (I'm using this for "Normalized Term Frequencies", because "tf" are floating-point values)

FloatMatrix *allocFloatMatrix(FloatMatrix *pMatrix, int numRow, int numCol);
void freeFloatMatrix(FloatMatrix *pMatrix);

void printFloatMatrix(FloatMatrix *pMatrix);

int findMax(IntMatrix *pMatrix);

typedef struct
{
    int *body;
    int size;
} IntVector;

IntVector *allocIntVector(IntVector *pVector, int size);
void freeIntVector(IntVector *pVector);
void printIntVector(IntVector *pVector);

typedef struct
{
    float *body;
    int size;
} FloatVector;

FloatVector *allocFloatVector(FloatVector *pVector, int size);
void freeFloatVector(FloatVector *pVector);
void printFloatVector(FloatVector *pVector);
