#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// GET WORD from file
int getWord(FILE *f, char *word, int limit)
{
	char ch = fgetc(f);
	int  ixLit = 0;

	// Skip leading spaces
	while (isspace(ch)) ch = fgetc(f);
	if (ch == EOF) return EOF;
	// Reading a word of letters
	while (!isspace(ch) && ch != EOF)
	{
		if (!isalpha(ch)) return 0;

		if (ixLit < limit) word[ixLit++] = ch;

		ch = fgetc(f);
	}
	word[ixLit] = '\0';

	return 1;
}
