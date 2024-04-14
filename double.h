#ifndef DOUBLE_H
#define DOUBLE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PI 3.14159265358979323846
#define E 2.71828182845904523536

void print_double(double x);

double random_double(double min, double max);

bool doubles_are_equal(double x1, double x2, double epsilon);

double degrees_to_radians(double a);

double radians_to_degrees(double a);

double fposmod(double x, double y);

double csc(double a);

double sec(double a);

double cot(double a);

#endif