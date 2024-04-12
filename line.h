#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "utils.h"
#include "point.h"

typedef struct line Line;

struct line
{
    Point p;
    double dx;
    double dy;
};

Line line_from_points(Point p1, Point p2);

void print_line(Line l);

bool line_is_valid(Line l);

double distance_between_point_and_line(Point p, Line l);

double x_val_of_line_at_y_val(Line l, double y);

double y_val_of_line_at_x_val(Line l, double x);

double determinant_of_line(Line l);

bool point_is_on_line(Point p, Line l, double epsilon);

bool lines_are_equal(Line l1, Line l2, double epsilon);

bool lines_are_parallel(Line l1, Line l2, double epsilon);

bool lines_are_perpendicular(Line l1, Line l2, double epsilon);

Point find_intersection_of_lines(Line l1, Line l2);

double slope_of_line(Line l);

double angle_of_line(Line l);

#endif
