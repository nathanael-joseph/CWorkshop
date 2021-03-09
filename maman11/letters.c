#include "letters.h"

int main() 
{
	/* flags: 1 -> true, 0 -> false */
	short int isInQuotations = 0;
	short int isStartOfSentence = 1;

	/* input character */
	char c;

	while((c = getchar()) != EOF) {
		/* process input */
		
		if(!isNumber(c)) {

			if (c == FULLSTOP && !isInQuotations) {
				flipFlag(&isStartOfSentence);
			} 
			else if (c == DOUBLEQUOTE) {
				flipFlag(&isInQuotations);
			} 
			else if (isInQuotations || isStartOfSentence ) {
				c = toUpper(c);
			}
			else {
				c = toLower(c);
			}
			
			printf("%c",c);
		}
	} 

	return 0;
}

/* TODO */
char toUpper(char c);

char toLower(char c);


/* flips a short int flag from 1 to 0, or from 0 to 1 */
void flipFlag(short int* flag) {
	static const short int one = 1;
	*flag = one ^ *flag;
	printf("*flag -> %d ", one ^ *flag);
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

