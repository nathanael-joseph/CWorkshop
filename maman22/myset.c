/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/04/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 22 Question 1
-------------------------------------------------------------------------------
*/

#include "myset.h"

/* --- PRIVATE FUNCTION DECLARATIONS -------------------------------- */
/* --- MAIN --------------------------------------------------------- */
int main(int argc, char** argv) {

	String test = "		";
	/* Boolean b = string_tryParseInt(test, &i);
	
	 printf("success = [%d],  i = [%d] \n",b,i); */
	
	printf("trimmed = [%s]", string_trim(test));
	return 0;
}
/* --- FUNCTION DEFINITIONS ----------------------------------------- */

/* returns a pointer to the set with the specified name,
or null if the set name does not exist */
Set *getSet(String name) {
	static Boolean init = false;
	static Set *A, *B, *C, *D, *E, *F;
	if(!init) {
		A = set_init();
		B = set_init();
		C = set_init();
		D = set_init();
		E = set_init();
		F = set_init();
		init = true;
	}
	 /* TODO */
	return A;
}

/* Returns a pointer to the next line in stdin, without 
the ending '\n' character, or null if there are no more lines
to read. Exits if a line is too long.
Memory safe - no malloc/free required.
*/
String readLine() {

	static char str[MAX_LINE_LENGTH];
	char *newline;

	fgets(str, MAX_LINE_LENGTH,stdin);

	if((newline = strchr(str,'\n')) != NULL) {
		*newline = '\0';
	}

	return str;
}
