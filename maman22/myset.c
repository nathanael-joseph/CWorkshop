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
	String test = "-  405    ";
	Boolean b = string_tryParseInt(test, &i);

	printf("success = [%d],  i = [%d] \n",b,i);


	return 0;
}
/* --- FUNCTION DEFINITIONS ----------------------------------------- */

