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
	String test = "		";
	/* Boolean b = string_tryParseInt(test, &i);
	
	 printf("success = [%d],  i = [%d] \n",b,i); */
	
	printf("trimmed = [%s]", string_trim(test));
	return 0;
}
/* --- FUNCTION DEFINITIONS ----------------------------------------- */

