#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrixop.h"
#include "common.h"

int countFreq(char *term, FILE *f);

void fillTermFreqMatrix(IntMatrix *pTfMatrix, char **terms, Document *docs)
{
    for (int ixTerm = 0; ixTerm < pTfMatrix->numRow; ixTerm++)
    {

        for (int ixDoc = 0; ixDoc < pTfMatrix->numCol; ixDoc++)
        {

            pTfMatrix->body[ixTerm][ixDoc] = countFreq(terms[ixTerm], docs[ixDoc].source);
        }
    }
}

void fillNormTermFreqMatrix(FloatMatrix *pNormMatrix, IntMatrix *pTfMatrix)
{
    int max = findMax(pTfMatrix);

    for (int ixTerm = 0; ixTerm < pTfMatrix->numRow; ixTerm++)
    {
        for (int ixDoc = 0; ixDoc < pTfMatrix->numCol; ixDoc++)
        {
            pNormMatrix->body[ixTerm][ixDoc] = (float)pTfMatrix->body[ixTerm][ixDoc] / max;
        }
    }
}

int countFreq(char *term, FILE *f)
{
    rewind(f);

    int termCount = 0;

    for (;;)
    {
        char word[MAX_LENGTH];

        int check = getWord(f, word, MAX_LENGTH);
        if (check == EOF)
            break;
        if (check != 1)
        {
            printf("wrong doscument file format\n");
            exit(60);
        }

        if (strcmp(term, word) == 0)
            termCount++;
    }
    return termCount;
}

void fillDocFreq(IntVector *pDocFreq, IntMatrix *pTfMatrix)
{
    for (int ixTerm = 0; ixTerm < pDocFreq->size; ++ixTerm)
    {
        int docCount = 0;
        for (int ixDoc = 0; ixDoc < pTfMatrix->numCol; ++ixDoc)
        {
            if (pTfMatrix->body[ixTerm][ixDoc] > 0)
                docCount++;
        }
        pDocFreq->body[ixTerm] = docCount;
    }
}

void fillInvDocFreq(FloatVector *pInvDocFreq, IntVector *pDocFreq, int numDocs)
{
    for (int ixTerm = 0; ixTerm < pInvDocFreq->size; ++ixTerm)
    {
        if (pDocFreq->body[ixTerm] == 0)
            pInvDocFreq->body[ixTerm] = INFINITY; // outputs infinity as division by 0 causes an error
        else
            pInvDocFreq->body[ixTerm] = log(numDocs / pDocFreq->body[ixTerm]);
    }
}

void fillTermDocIncMatrix(FloatMatrix *pIncMatrix, FloatMatrix *pNormMatrix, FloatVector *pInvDocFreq)
{
    for (int ixTerm = 0; ixTerm < pNormMatrix->numRow; ixTerm++)
    {
        for (int ixDoc = 0; ixDoc < pNormMatrix->numCol; ixDoc++)
        {
            if (pInvDocFreq->body[ixTerm] == INFINITY) // no occurrence of the term in any document
                pIncMatrix->body[ixTerm][ixDoc] = NAN; // therefore outputs 0
            else
                pIncMatrix->body[ixTerm][ixDoc] = pNormMatrix->body[ixTerm][ixDoc] * pInvDocFreq->body[ixTerm];
        }
    }
}