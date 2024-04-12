#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define E 2.71828182845904523536

void print_double(double x);

bool doubles_are_equal(double x1, double x2, double epsilon);

double degrees_to_radians(double a);

double radians_to_degrees(double a);

double fposmod(double x, double y);

#endif