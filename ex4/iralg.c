#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrixop.h"
#include "common.h"

int countFreq(char *term, FILE *f );

void fillTermFrexMatrix(IntMatrix *pTfMatrix, char** terms, Document* docs )
{
    for( int ixTerm = 0; ixTerm < pTfMatrix->numRow; ixTerm++ )
    {
            
        for( int ixDoc = 0; ixDoc < pTfMatrix->numCol; ixDoc++)
        {
        
            pTfMatrix->body[ixTerm][ixDoc] = countFreq(terms[ixTerm],docs[ixDoc].source);
        }
    }
}


void fillNormTermFreqMatrix(FloatMatrix *pNormMatrix, IntMatrix *pTfMatrix)
{
    int max = findMax(pTfMatrix);
    
    for( int ixTerm = 0; ixTerm < pTfMatrix->numRow; ixTerm++ )
    {        
        for( int ixDoc = 0; ixDoc < pTfMatrix->numCol; ixDoc++)
        {    
            pNormMatrix->body[ixTerm][ixDoc] = (float) pTfMatrix->body[ixTerm][ixDoc] / max;
        }
    }
}

int countFreq(char *term, FILE *f )
{
    rewind(f);
    
    int termCount = 0;
    
    for( ; ; )
    {
        char word[MAX_LENGTH];
        
        int check = getWord(f, word, MAX_LENGTH);
        if( check == EOF ) break;
        if( check != 1 ) 
        {
            printf("wrong doscument file format\n");
            exit(60);
        }
        
        if(strcmp(term,word)==0) termCount++;
    }
    return termCount;
}

void fillDocFrex(IntVector *pDocFrex, IntMatrix *pTfMatrix)
{
	for (int ixTerm = 0; ixTerm < pDocFrex->size; ++ixTerm)
	{
		int docCount = 0;
		for (int ixDoc = 0; ixDoc < pTfMatrix->numCol; ++ixDoc)
		{
			if (pTfMatrix->body[ixTerm][ixDoc] > 0) docCount++;
		}
		pDocFrex->body[ixTerm] = docCount;
	}
}