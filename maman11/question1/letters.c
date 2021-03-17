/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/03/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 11 Question 1
-------------------------------------------------------------------------------
*/

#include "letters.h"

int main() 
{
	/* flags: 1 -> true, 0 -> false */
	int isInQuotations;
	int isStartOfSentence;

	/* input character */
	char c;

	/* process the input */

	clearFlag(&isInQuotations);
	setFlag(&isStartOfSentence);

	while((c = getchar()) != EOF) {

		if (!isWhitespace(c)) {
			if (c == FULLSTOP) {
				/* whether or not the full stop is in quotations or not does not change the logic, 
				   either way, the next letter will be changed to uppercase, and the flag will be cleared */
				setFlag(&isStartOfSentence);
			}
			else {

				if (c == DOUBLEQUOTE) {
					flipFlag(&isInQuotations);
				}
				else if (isInQuotations || isStartOfSentence ) {
					c = toUpper(c);
				}
				else {
					c = toLower(c);
				}

				clearFlag(&isStartOfSentence);
			}
		}

		if(!isNumber(c)) {
			putchar(c);
		}

	} /* ebd while loop */

	return 0;
}



/* --- FUNCTION DEFINITIONS -------------------------------- */


/* flips an int flag from 1 to 0, or from 0 to 1 */
void flipFlag(int* flag) {
	*flag = !*flag;
}

/* sets an int flag to 1 */
void setFlag(int* flag) {
	*flag = 1;
}

/* sets an int flag to 0 */
void clearFlag(int* flag) {
	*flag = 0;
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

/* returns 1 if c is any of the following {' ', '\t', '\r', '\n', '\v', '\f'}, 0 otherwise */
int isWhitespace(char c) {
	int i;
	for( i = 0; i < WHITESPACES_ARR_LEN; i++) {
		if (c == WHITESPACES_ARR[i])
			return 1;
	}
	return 0;
}

/* returns 1 if c is in the range 'a' -'z', 0 otherwise */
int isLowerCase(char c) {
	if(c >= LOWERCASE_START && c <= LOWERCASE_END) 
		return 1;
	return 0;
}

/* returns 1 if c is in the range 'A' -'Z', 0 otherwise */
int isUpperCase(char c) 
{
	if(c >= UPPERCASE_START && c <= UPPERCASE_END) 
		return 1;
	return 0;
}

/* returns 1 if c is in the range '0' -'9', 0 otherwise */
int isNumber(char c) 
{
	if(c >= NUMBERS_START && c <= NUMBERS_END)
		return 1;
	return 0;
}

