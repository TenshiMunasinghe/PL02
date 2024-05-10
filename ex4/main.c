/*
 * File:   main.c
 * Author: pyshe
 *
 * Created on May 17, 2019, 9:16 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "matrixop.h"
#include "iralg.h"

int openAllDocs(Document *docs, int numDocs);
int setAllDocsNames( Document *docs, int numDocs, char** argv );
void printAllDocsNames( Document *docs, int numDocs );
void closeAllDocs(Document *docs, int numDocs);
int readAllTerms( FILE *input, char**terms, int numTerms);
void printAllTerms( char**terms, int numTerms);

/*
 *
 */
int main()
{
    int numTerms;
    FILE *input;
    char** terms;

    int numDocs;
    Document *docs;

    IntMatrix termFreqMatrix; // to store "f" values (term frequencies)
    FloatMatrix normTermFreqMatrix; // to store "tf" values (normalized term frequencies)
	IntVector docFrex; // to store "df" (document frequencies)

    if( argc <= 1 )
    {
        printf("No document collection defined\n");
        exit(10);
    }

    numDocs = argc - 1;

    docs = (Document *)malloc(numDocs*sizeof(Document));
    if( docs == NULL ) {
        printf("Memory allocation error\n");
        exit(20);
    }

    if( setAllDocsNames(docs,numDocs,argv) != numDocs )
    {
        printf("Some document names are missing\n");
        exit(40);
    }

    if( openAllDocs(docs,numDocs) != numDocs )
    {
        printf("Some documents are missing\n");
        exit(40);
    }

    printf("Loaded documents:\n");
    printAllDocsNames(docs,numDocs);

    input = fopen("input.txt", "rt");
    if( input == NULL )
    {
        printf("No input file found\n");
        exit(50);
    }

    if( fscanf(input, "%d", &numTerms ) != 1 )
    {
        printf("wrong input file format\n");
        exit(60);
    }

	if (numTerms <= 0)
	{
		printf("illegal number of terms\n");
		exit(60);
	}

    terms = (char**)malloc( numTerms*sizeof(char*));
    if( terms == NULL )
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    for( int ixTerm=0; ixTerm < numTerms; ixTerm++ )
    {
        terms[ixTerm] = (char *)malloc( MAX_LENGTH+1 );
        if( terms[ixTerm] == NULL )
        {
            printf("Memory allocation error\n");
            exit(20);
        }
    }

    if( readAllTerms( input, terms, numTerms ) != numTerms )
    {
        printf("Some terms are missing in the input file\n");
        exit(70);
    }

    printf("\n");
    printf("Loaded terms:\n");
    printAllTerms(terms,numTerms);

    fclose( input );

    // In here, we have:
	// All the documents are open;
	// All the terms are in "terms"

    if( allocIntMatrix(&termFreqMatrix,numTerms,numDocs) == NULL )
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillTermFrexMatrix(&termFreqMatrix, terms, docs );

    printf("\n");
    printf("Term frequencies:\n");
    printIntMatrix(&termFreqMatrix);

    if( allocFloatMatrix(&normTermFreqMatrix,numTerms,numDocs) == NULL )
    {
        printf("Memory allocation error\n");
        exit(20);
    }

    fillNormTermFreqMatrix(&normTermFreqMatrix, &termFreqMatrix);

    printf("\n");
    printf("Normalized term frequencies:\n");
    printFloatMatrix(&normTermFreqMatrix);

	if (allocIntVector(&docFrex, numTerms) == NULL)
	{
		printf("Memory allocation error\n");
		exit(20);
	}

	fillDocFrex(&docFrex, &termFreqMatrix);

	printf("\n");
	printf("Document frequencies:\n");
	printIntVector(&docFrex);

    freeIntMatrix(&termFreqMatrix);
    freeFloatMatrix(&normTermFreqMatrix);
	freeIntVector(&docFrex);

    closeAllDocs(docs,numDocs);
    return (EXIT_SUCCESS);
}

int readAllTerms( FILE *input, char**terms, int numTerms)
{
    int ixTerm;
    for( ixTerm = 0; ixTerm < numTerms; ixTerm++ )
    {
        int check = getWord(input,terms[ixTerm], MAX_LENGTH);
        if( check == EOF ) return EOF;
        if( check != 1 )
        {
            printf("wrong input file format\n");
            exit(60);
        }
    }
    return ixTerm;
}

void printAllTerms( char**terms, int numTerms)
{
    for( int ixTerm = 0; ixTerm < numTerms; ixTerm++ )
    {
        printf("%s\n",terms[ixTerm]);
    }
}

int setAllDocsNames( Document *docs, int numDocs, char** argv )
{
    int docCount = 0;

    for( int ixDoc = 0; ixDoc < numDocs; ixDoc++ )
    {
        strcpy( docs[ixDoc].name, argv[ ixDoc + 1] );
        docCount++;
    }
    return docCount;
}

int openAllDocs(Document *docs, int numDocs)
{
    int docCount = 0;

    for( int ixDoc = 0; ixDoc < numDocs; ixDoc++ )
    {
        docs[ixDoc].source = fopen( docs[ixDoc].name, "rt" );
        if( docs[ixDoc].source == NULL )
        {
            printf("unable to open the document %s\n", docs[ixDoc].name);
            exit(30);
        }
        docCount++;
    }
    return docCount;
}

void printAllDocsNames( Document *docs, int numDocs )
{
    for( int ixDoc = 0; ixDoc < numDocs; ixDoc++ )
    {
        printf("%s\n", docs[ixDoc].name);
    }
}

void closeAllDocs(Document *docs, int numDocs)
{
    for( int ixDoc = 0; ixDoc < numDocs; ixDoc++ )
    {
        fclose( docs[ixDoc].source);
    }
}
