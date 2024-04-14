#ifndef POINT_H
#define POINT_H

#include "double.h"

typedef struct point Point;

// A struct representing a 2D point.
struct point
{
    double x;
    double y;
};

// Prints a point in the form "(x, y)".
void print_point(Point p);

// Gets a random point where x is between x_min and x_max (inclusive) and
// y is between y_min and y_max (inclusive).
Point random_point(double x_min, double x_max, double y_min, double y_max);

// Returns whether both the x- and y-values are valid, finite numbers.
bool point_is_valid(Point p);

// Returns whether p1 and p2 are approximately equal (within an error of epsilon).
bool points_are_equal(Point p1, Point p2, double epsilon);

// Returns whether p_mid is on the line formed by p1 and p2 and between p1 and p2.
bool point_is_between_points(Point p_mid, Point p1, Point p2, double epsilon);

// Calculates the distance between p1 and p2.
double distance_between_points(Point p1, Point p2);

#endif
