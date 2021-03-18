/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 18/03/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 11 Question 2
-------------------------------------------------------------------------------
*/

#include "my_sin.h"

int main() {

	double deg;
	int scannedSuccessfully;

	/* print start message */
	printf("Welcome to my sine calculator. \n");
	printf("This sine calculator is accurate within an error margin of E-6, \n");
	printf("for all angles in degrees. \n");

	/* scan double */
	printf("Enter an angle in degrees: \n >");
	scannedSuccessfully = scanf("%lf", &deg);
	while(scannedSuccessfully < 1) {	
		while(getchar() != '\n');
		printf("Could not parse a valid number.\n");
		printf("Please enter an angle in degrees: \n >");
		scannedSuccessfully = scanf("%lf", &deg);
	}

	/* Print result of my_sin(double d) and sin(double d) */
	printf("\nmy_sin of %.6f degrees is %.6f \n", deg, my_sin(toRadians(deg)));
	printf("math.h sin of %.6f degrees is %.6f \n \n \n", deg, sin(toRadians(deg)));

	return 0;
}


/* ------------------------- FUNCTION DEFINITIONS ------------------------ */

/* approximates sin(x) with an error margin less than E-6 */
double my_sin(double radians) {
	double result, nextMember, RADIANS_SQRD;
	int i, denominator;

	/* 
	to improve runtime and avoid overflow for arguments where |radians| > 2PI,
	sin(2kPI + x) = sin(x), where |x| < 2PI, k in Z.
	*/
	if (absolute(radians) > 2*DBL_PI) {
		radians = radians - ((int)(radians/(2*DBL_PI))*(2*DBL_PI));
	}

	/* this value remains constant */
	RADIANS_SQRD = radians*radians;

	/* the first memeber (i = 0) of the Taylor series is equal to the argument "radians" */
	result = radians;

	/* calculate the next memeber of the Taylor series */ 
	i = 1;
	denominator = (2*i)*((2*i) + 1);	
	nextMember = (result*RADIANS_SQRD)/denominator;

	/* The absolute value of the member i is always larger than the remainder R_i */
	while (absolute(nextMember) > DBL_ERROR_MARGIN) {
		/* if index is odd, subtract next memeber , else add the nest memeber */
		result += i % 2 == 1 ? -nextMember : nextMember;
		/* calculate the next memeber of the Taylor series */
		i++;
		denominator = (2*i)*((2*i) + 1);
		nextMember = (nextMember*RADIANS_SQRD)/denominator;
	}

	return result;
}

/* returns the absolute value of argument "x" */
double absolute(double x) {
	if(x < 0) {
		return -x;
	}
	return x;
}

/* returns the value of argument "degrees" in radians */
double toRadians(double degrees) {
	return degrees*(DBL_PI/180);
}