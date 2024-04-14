#ifndef DOUBLE_H
#define DOUBLE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define E 2.71828182845904523536

// Prints a double with no decimals if it is at least 1000.
// Otherwise, prints it with only four significant digits.
void print_double(double x);

// Gets a random double between min and max (inclusive);
double random_double(double min, double max);

// Tests whether x1 and x2 are approximately equal (within an error of epsilon).
bool doubles_are_equal(double x1, double x2, double epsilon);

// Converts degrees to radians.
double degrees_to_radians(double a);

// Converts radians to degrees.
double radians_to_degrees(double a);

// Returns x modulo m. Result will be positive, between 0 and |m|.
double fposmod(double x, double m);

// Calculates the cosecant of x.
double csc(double x);

// Calculates the secant of x.
double sec(double x);

// Calculates the cotangent of x.
double cot(double x);

#endif
