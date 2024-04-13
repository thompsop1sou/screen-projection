#include "utils.h"

void print_double(double x)
{
    if (x >= 1000.0)
        printf("%.0lf", x);
    else
        printf("%.3g", x);
}

bool doubles_are_equal(double x1, double x2, double epsilon)
{
    return abs(x1 - x2) <= epsilon;
}

double degrees_to_radians(double a)
{
    return PI * a / 180.0;
}

double radians_to_degrees(double a)
{
    return 180.0 * a / PI;
}

double fposmod(double x, double y)
{
    double z = fmod(x, y);
    return (z >= 0 ? z : z + y);
}

double csc(double a)
{
    return 1.0 / sin(a);
}

double sec(double a)
{
    return 1.0 / cos(a);
}

double cot(double a)
{
    double x = tan(a);
    if (isinf(x))
        return 0.0;
    else
        return 1.0 / x;
}
