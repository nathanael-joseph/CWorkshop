/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 17/03/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 11 Question 2
-------------------------------------------------------------------------------
*/

#include "my_sin.h"

int main() {

	/* print start message */

	/* scan double */

	/* result of my_sin(double d) and sin(double d) */


	double deg, rads;
	while(1) {
		scanf("%lf", &deg);
		printf("  %.10f degrees is %.10f in radians \n ", deg, toRadians(deg));
		printf(" sin of  %.10f degrees is %.10f \n", deg, my_sin(toRadians(deg)));
	}

	return 0;
}

/* returns the value of argument "degrees" in radians */
double toRadians(double degrees) {
	return degrees*(DBL_PI/180);
}
/* approximates sin(x) with an error margin less than E-6 */
double my_sin(double radians) {

	int i = 1;
	int denominator = 6;

	/* the first memeber of the summation is radians */
	double result = radians;

	/* remainder is the absolute value of the next member in the sumation */
	/* this is always larger than the actual remainder in Legrange form */
	double remainder = (result*radians*radians)/denominator;

	while (remainder > (double)DBL_ERROR_MARGIN) {

		if (i % 2 == 1) {
			result -= remainder;
		} 
		else {
			result += remainder;
		}

		i++;
		denominator *= (2*i)*((2*i) + 1);


		remainder = (result*radians*radians)/denominator;
		printf(" remainder is %.10f \n", remainder);

	}


	return result;
}