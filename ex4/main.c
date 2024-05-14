/*
 * File:   main.c
 * Author: pyshe
 *
 * Created on May 17, 2019, 9:16 AM
 */

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "matrixop.h"
#include "iralg.h"
#include "config.h"

int openAllDocs(Document *docs, int numDocs, char *docsLocation);
int setAllDocsNames(Document *docs, int numDocs, char **docNames);
void printAllDocsNames(Document *docs, int numDocs);
void closeAllDocs(Document *docs, int numDocs);
int readAllTerms(FILE *input, char **terms, int numTerms);
void printAllTerms(char **terms, int numTerms);

/*
 *
 */
int main(int argc, char **argv) // expect path to text documents
{
    FILE *input;
    char **terms;
    Document *docs;

    IntMatrix termFreqMatrix;       // to store "f" values (term frequencies)
    FloatMatrix normTermFreqMatrix; // to store "tf" values (normalized term frequencies)
    IntVector docFreq;              // to store "df" (document frequencies)
    FloatVector invDocFreq;         // to store "idf" (inverse document frequencies)
    FloatMatrix termDocIncMatrix;   // to store "w" (term weights)

    Config config;
    loadConfig("config.txt", &config);

    docs = (Document *)malloc(config.numDocs * sizeof(Document));
    if (docs == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    if (setAllDocsNames(docs, config.numDocs, config.fileNames) != config.numDocs)
    {
        printf("Some document names are missing\n");
        exit(40);
    }

    if (openAllDocs(docs, config.numDocs, argv[1]) != config.numDocs)
    {
        printf("Some documents are missing\n");
        exit(40);
    }

    printf("Loaded documents:\n");
    printAllDocsNames(docs, config.numDocs);

    input = fopen("terms.txt", "rt");
    if (input == NULL)
    {
        printf("No input file found\n");
        exit(50);
    }
    // if (fscanf(input, "%d", &config.numTerms) != 1)
    // {
    //     printf("wrong input file format\n");
    //     exit(60);
    // }

    if (config.numTerms <= 0)
    {
        printf("illegal number of terms\n");
        exit(60);
    }

    terms = (char **)malloc(config.numTerms * sizeof(char *));
    if (terms == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    for (int ixTerm = 0; ixTerm < config.numTerms; ixTerm++)
    {
        terms[ixTerm] = (char *)malloc(MAX_LENGTH + 1);
        if (terms[ixTerm] == NULL)
        {
            printf("Memory allocation error\n");
            exit(20);
        }
    }

    if (readAllTerms(input, terms, config.numTerms) != config.numTerms)
    {
        printf("Some terms are missing in the input file\n");
        exit(70);
    }

    printf("\n");
    printf("Loaded terms:\n");
    printAllTerms(terms, config.numTerms);

    fclose(input);

    // In here, we have:
    // All the documents are open;
    // All the terms are in "terms"

    if (allocIntMatrix(&termFreqMatrix, config.numTerms, config.numDocs) == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillTermFreqMatrix(&termFreqMatrix, terms, docs);

    printf("\n");
    printf("Term frequencies:\n");
    printIntMatrix(&termFreqMatrix);

    if (allocFloatMatrix(&normTermFreqMatrix, config.numTerms, config.numDocs) == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillNormTermFreqMatrix(&normTermFreqMatrix, &termFreqMatrix);

    printf("\n");
    printf("Normalized term frequencies:\n");
    printFloatMatrix(&normTermFreqMatrix);

    if (allocIntVector(&docFreq, config.numTerms) == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillDocFreq(&docFreq, &termFreqMatrix);

    printf("\n");
    printf("Document frequencies:\n");
    printIntVector(&docFreq);

    if (allocFloatVector(&invDocFreq, config.numTerms) == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillInvDocFreq(&invDocFreq, &docFreq, config.numDocs);

    printf("\n");
    printf("Inverse document frequencies:\n");
    printFloatVector(&invDocFreq);

    if (allocFloatMatrix(&termDocIncMatrix, config.numTerms, config.numDocs) == NULL)
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillTermDocIncMatrix(&termDocIncMatrix, &normTermFreqMatrix, &invDocFreq);

    printf("\n");
    printf("Term Document Incidence:\n");
    printFloatMatrix(&termDocIncMatrix);

    freeIntMatrix(&termFreqMatrix);
    freeFloatMatrix(&normTermFreqMatrix);
    freeIntVector(&docFreq);
    freeFloatVector(&invDocFreq);
    freeFloatMatrix(&termDocIncMatrix);

    closeAllDocs(docs, config.numDocs);
    return (EXIT_SUCCESS);
}

int readAllTerms(FILE *input, char **terms, int numTerms)
{
    int ixTerm;
    for (ixTerm = 0; ixTerm < numTerms; ixTerm++)
    {
        int check = getWord(input, terms[ixTerm], MAX_LENGTH);
        if (check == EOF)
            return EOF;
        if (check != 1)
        {
            printf("wrong input file format\n");
            exit(60);
        }
    }
    return ixTerm;
}

void printAllTerms(char **terms, int numTerms)
{
    for (int ixTerm = 0; ixTerm < numTerms; ixTerm++)
    {
        printf("%s\n", terms[ixTerm]);
    }
}

int setAllDocsNames(Document *docs, int numDocs, char **docNames)
{
    int docCount = 0;
    for (int ixDoc = 0; ixDoc < numDocs; ixDoc++)
    {
        strcpy(docs[ixDoc].name, docNames[ixDoc]);
        docCount++;
    }
    return docCount;
}

int openAllDocs(Document *docs, int numDocs, char *docsLocation)
{
    int docCount = 0;

    for (int ixDoc = 0; ixDoc < numDocs; ixDoc++)
    {
        char path[512];
        sprintf(path, "%s/%s", docsLocation, docs[ixDoc].name);

        docs[ixDoc].source = fopen(path, "rt");
        if (docs[ixDoc].source == NULL)
        {
            printf("unable to open the document %s\n", path);
            exit(30);
        }
        docCount++;
    }
    return docCount;
}

void printAllDocsNames(Document *docs, int numDocs)
{
    for (int ixDoc = 0; ixDoc < numDocs; ixDoc++)
    {
        printf("%s\n", docs[ixDoc].name);
    }
}

void closeAllDocs(Document *docs, int numDocs)
{
    for (int ixDoc = 0; ixDoc < numDocs; ixDoc++)
    {
        fclose(docs[ixDoc].source);
    }
}
