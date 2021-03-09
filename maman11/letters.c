

#include "letters.h"

int main() 
{
	/* flags: 1 -> true, 0 -> false */
	short int isInQuotations = 0;
	short int isStartOfSentence = 1;

	/* input character */
	char c;

	while((c = getchar()) != EOF) {


		if(!isNumber(c)) {
			
			if(!isWhitespace(c)) {
				if (c == FULLSTOP && !isInQuotations) {
					flipFlag(&isStartOfSentence);
				} 
				else if (c == DOUBLEQUOTE) {
					flipFlag(&isInQuotations);
					isStartOfSentence = 0;
				} 
				else if (isInQuotations || isStartOfSentence ) {
					c = toUpper(c);
					isStartOfSentence = 0;
				}
				else {
					c = toLower(c);
				}
			}
			
			putchar(c);
		}
	} 

	return 0;
}



/* returns an Upper Case char of the same letter if applicable, otherwise, returns the argument */
char toUpper(char c) {
	if(isLowerCase(c)) {
		c += UPPERCASE_START - LOWERCASE_START;
	}
	return c;
}

/* returns a lower case char of the same letter if applicable, otherwise, returns the argument */
char toLower(char c) {
	if(isUpperCase(c)) {
		c += LOWERCASE_START - UPPERCASE_START;
	}
	return c;
}


/* flips a short int flag from 1 to 0, or from 0 to 1 */
void flipFlag(short int* flag) {
	static const short int TRUE = 1;
	*flag = TRUE ^ *flag;
}

/* returns 1 if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'} 0 otherwise */
short int isWhitespace(char c) {
	int i;
	for( i = 0; i < WHITESPACES_ARR_LEN; i++) {
		if (c == WHITESPACES_ARR[i])
			return 1;
	}
	return 0;
}

/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
short int isLowerCase(char c) {
	if(c >= LOWERCASE_START && c <= LOWERCASE_END) 
		return 1;
	return 0;
}

/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
short int isUpperCase(char c) 
{
	if(c >= UPPERCASE_START && c <= UPPERCASE_END) 
		return 1;
	return 0;
}

/* returns 1 if c is in the range '0' -'9', 0 otherwise */
short int isNumber(char c) 
{
	if(c >= NUMBERS_START && c <= NUMBERS_END)
		return 1;
	return 0;
}

