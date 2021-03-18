/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 18/03/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 11 Question 2
-------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <math.h>

/* ------------------------------ CONSTANTS ------------------------------- */
#define DBL_ERROR_MARGIN (0.000001) /* E-6 */
#define DBL_PI (3.141592653589793) /* DBL_DIG = 15 */

/* ------------------------- FUNCTION DELCARATIONS ------------------------ */
/* returns the absolute value of argument "x" */
double absolute(double x);
/* returns the value of argument "degrees" in radians */
double toRadians(double degrees);
/* approximates sin(x) with an error margin less than E-6 */
double my_sin(double radians);