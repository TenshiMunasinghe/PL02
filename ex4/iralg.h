/*
 * File:   iralg.h
 * Author: pyshe
 *
 * Created on May 17, 2019, 12:02 PM
 */

#pragma once

void fillTermFreqMatrix(IntMatrix *pTfMatrix, char **terms, Document *docs);
void fillNormTermFreqMatrix(FloatMatrix *pNormMatrix, IntMatrix *pTfMatrix);
void fillDocFreq(IntVector *pDocFreq, IntMatrix *pTfMatrix);
void fillInvDocFreq(FloatVector *pInvDocFreq, IntVector *pDocFreq, int numDocs);
void fillTermDocIncMatrix(FloatMatrix *pIncMatrix, FloatMatrix *pNormMatrix, FloatVector *pInvDocFreq);