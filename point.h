#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "utils.h"

typedef struct point Point;

struct point
{
    double x;
    double y;
};

void print_point(Point p);

bool point_is_valid(Point p);

bool points_are_equal(Point p1, Point p2, double epsilon);

double distance_between_points(Point p1, Point p2);

double points_are_collinear(Point p1, Point p2, Point p3, double epsilon);

#endif
