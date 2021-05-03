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
int main() {

	int i;
	String test = "o n e, two ,,four   ,";
	String *result;
	int resultLength = string_split(test,',',&result);

	for(i = 0; i < resultLength; i++) {
		printf("result[%d] is: [%s] , len is [%d]\n",i,result[i], strlen(result[i]));
	}


	return 0;
}
/* --- FUNCTION DEFINITIONS ----------------------------------------- */

