/* 
 * File:   iralg.h
 * Author: pyshe
 *
 * Created on May 17, 2019, 12:02 PM
 */

#pragma once

void fillTermFrexMatrix(IntMatrix *pTfMatrix, char** terms, Document* docs );
void fillNormTermFreqMatrix(FloatMatrix *pNormMatrix, IntMatrix *pTfMatrix);
void fillDocFrex(IntVector *pDocFrex, IntMatrix *pTfMatrix);
