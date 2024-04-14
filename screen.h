#ifndef SCREEN_H
#define SCREEN_H

#include <time.h>

#include "point.h"
#include "line.h"

typedef struct screen Screen;

// A struct representing a rectangular screen that has been warped due to projection.
struct screen
{
    // Top-left corner at (0, 0)
    Point p00;
    // Top-right corner at (1, 0)
    Point p10;
    // Bottom-left corner at (0, 1)
    Point p01;
    // Bottom-right corner at (1, 1)
    Point p11;
};

// Prints the four corners of a screen.
void print_screen(Screen s);

// Returns whether a screen is a valid convex quadrilateral.
bool screen_is_valid(Screen s);

// Maps the point p using a projection mapping. The mapping is based on the screen s in
// that it will map the four corners of the screen to (0, 0), (1, 0), (0, 1), and (1, 1).
Point map_point_to_screen_space(Point p, Screen s);

// Helper for map_point_to_screen_space(). Finds a single coordinate for a point between all non-parallel lines.
double map_point_coord_non_parallel_lines(Point p, Line l_lower, Line l_upper, Line l_hrzn);

// Helper for map_point_coord_non_parallel().
double non_parallel_helper(Line l1, Line l2);

// Helper for map_point_to_screen_space(). Finds a single coordinate for a point between parallel and non-parallel lines.
double map_point_coord_both_types_of_lines(Point p, Line l_lower, Line l_upper, Line l_hrzn);

// Helper for map_point_to_screen_space(). Finds a single coordinate for a point between all parallel lines.
double map_point_coord_parallel_lines(Point p, Line l_lower, Line l_upper);

// Test the screen mapping for a specified number of random screens.
void test_screen_mapping(unsigned int num_screens);

#endif