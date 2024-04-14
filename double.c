#include "double.h"

// Prints a double with no decimals if it is at least 1000.
// Otherwise, prints it with only four significant digits.
void print_double(double x)
{
    if (x >= 1000.0)
        printf("%.0lf", x);
    else
        printf("%.4g", x);
}

// Gets a random double between min and max (inclusive);
double random_double(double min, double max)
{
    double rand_max = (double)RAND_MAX;
    double x = (double)rand() + (double)rand() / (rand_max + 1.0);
    return x * (max - min) / rand_max + min;
}

// Tests whether x1 and x2 are approximately equal (within an error of epsilon).
bool doubles_are_equal(double x1, double x2, double epsilon)
{
    return fabs(x1 - x2) <= epsilon;
}

// Converts degrees to radians.
double degrees_to_radians(double a)
{
    return PI * a / 180.0;
}

// Converts radians to degrees.
double radians_to_degrees(double a)
{
    return 180.0 * a / PI;
}

// Returns x modulo m. Result will be positive, between 0 and |m|.
double fposmod(double x, double m)
{
    double y = fmod(x, m);
    return (y >= 0 ? y : y + fabs(m));
}

// Calculates the cosecant of x.
double csc(double x)
{
    return 1.0 / sin(x);
}

// Calculates the secant of x.
double sec(double x)
{
    return 1.0 / cos(x);
}

// Calculates the cotangent of x.
double cot(double x)
{
    double y = tan(x);
    if (isinf(y))
        return 0.0;
    else
        return 1.0 / y;
}
