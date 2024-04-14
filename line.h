#ifndef LINE_H
#define LINE_H

#include "double.h"
#include "point.h"

typedef struct line Line;

// A struct representing a 2D line.
struct line
{
    // The point that the line passes through.
    Point p;
    // The relative change in x and y, representing slope.
    double dx;
    double dy;
};

// Creates a new line that passes through p1 and p2.
Line line_from_points(Point p1, Point p2);

// Prints a line in the form "x = a" or "y = m * x + b".
void print_line(Line l);

// Returns whether l is a valid line (i.e. its point is valid and its slope is valid).
bool line_is_valid(Line l);

// Returns the slope of a line (i.e. dy / dx).
double slope_of_line(Line l);

// Returns the angle of a line with the x-axis.
double angle_of_line(Line l);

// Returns whether l1 and l2 are equal (within an error of epsilon).
bool lines_are_equal(Line l1, Line l2, double epsilon);

// Returns whether l1 and l2 are parallel (within an error of epsilon).
bool lines_are_parallel(Line l1, Line l2, double epsilon);

// Returns whether l1 and l2 are perpendicular (within an error of epsilon).
bool lines_are_perpendicular(Line l1, Line l2, double epsilon);

// Returns whether p lies on l (within an error of epsilon).
bool point_is_on_line(Point p, Line l, double epsilon);

// Calculates the x-value of l at the provided y-value.
double x_val_of_line_at_y_val(Line l, double y);

// Calculates the y-value of l at the provided x-value.
double y_val_of_line_at_x_val(Line l, double x);

// Calculates the perpendicular distance between p and l.
double distance_between_point_and_line(Point p, Line l);

// Calculates the intersection point of l1 and l2.
Point intersection_of_lines(Line l1, Line l2);

// Helper for intersection_of_lines().
double intersection_helper(Line l);

#endif
