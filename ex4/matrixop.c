#include <stdio.h>
#include <stdlib.h>

#include "matrixop.h"

IntMatrix * allocIntMatrix( IntMatrix *pMatrix, int numRow, int numCol )
{
    pMatrix->numCol = numCol;
    pMatrix->numRow = numRow;
    
    pMatrix->body = (int**)malloc(pMatrix->numRow*sizeof(int*));
    if( pMatrix->body == NULL ) return NULL;
    
    for( int i = 0; i < pMatrix->numRow; i++ )
    {
        pMatrix->body[i] = (int*)malloc(pMatrix->numCol*sizeof(int));
        if(pMatrix->body[i]==NULL) return NULL;
    }
    
    return pMatrix;
}

void freeIntMatrix( IntMatrix *pMatrix )
{
    for( int i = 0; i < pMatrix->numRow; i++ ) free(pMatrix->body[i]);
    free(pMatrix->body);
}

void printIntMatrix( IntMatrix *pMatrix )
{
    for( int ixRow = 0; ixRow < pMatrix->numRow; ixRow++ )
    {
        for( int ixCol = 0; ixCol < pMatrix->numCol; ixCol++ )
        {
            printf("%4d ", pMatrix->body[ixRow][ixCol]);
        }
        printf("\n");
    }
}

FloatMatrix * allocFloatMatrix( FloatMatrix *pMatrix, int numRow, int numCol )
{
    pMatrix->numCol = numCol;
    pMatrix->numRow = numRow;
    
    pMatrix->body = (float**)malloc(pMatrix->numRow*sizeof(float*));
    if( pMatrix->body == NULL ) return NULL;
    
    for( int i = 0; i < pMatrix->numRow; i++ )
    {
        pMatrix->body[i] = (float*)malloc(pMatrix->numCol*sizeof(float));
        if(pMatrix->body[i]==NULL) return NULL;
    }
    
    return pMatrix;
}

void freeFloatMatrix( FloatMatrix *pMatrix )
{
    for( int i = 0; i < pMatrix->numRow; i++ ) free(pMatrix->body[i]);
    free(pMatrix->body);    
}

void printFloatMatrix( FloatMatrix *pMatrix )
{
   for( int ixRow = 0; ixRow < pMatrix->numRow; ixRow++ )
    {
        for( int ixCol = 0; ixCol < pMatrix->numCol; ixCol++ )
        {
            printf("%10.3e ", pMatrix->body[ixRow][ixCol]);
        }
        printf("\n");
    }    
}

int findMax( IntMatrix *pMatrix )
{
    int max = pMatrix->body[0][0];
    
    for( int ixRow = 0; ixRow < pMatrix->numRow; ixRow++ )
    {
        for( int ixCol = 0; ixCol < pMatrix->numCol; ixCol++ )
        {
            if(pMatrix->body[ixRow][ixCol]>max) max = pMatrix->body[ixRow][ixCol];
        }
    }  
    return max;
}

IntVector * allocIntVector(IntVector *pVector, int size)
{
	pVector->size = size;
	pVector->body = (int *)malloc(pVector->size * sizeof(int));
	if (pVector->body == NULL) return NULL;
	return pVector;
}

void freeIntVector(IntVector *pVector)
{
	free(pVector->body);
}

void printIntVector(IntVector *pVector)
{
	for (int ixVec = 0; ixVec < pVector->size; ++ixVec)
	{
		printf("%4d ", pVector->body[ixVec]);
	}
	printf("\n");
}
