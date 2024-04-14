#ifndef SCREEN_H
#define SCREEN_H

#include "point.h"
#include "line.h"

typedef struct screen Screen;

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

void print_screen(Screen s);

bool screen_is_valid(Screen s);

Point map_point_to_screen_space(Point p, Screen s);

double non_parallel_helper(Line l1, Line l2);

double map_point_coord_non_parallel_lines(Point p, Line l_lower, Line l_upper, Line h);

double map_point_coord_both_types_of_lines(Point p, Line l_lower, Line l_upper, Line h);

double map_point_coord_parallel_lines(Point p, Line l_lower, Line l_upper);

void test_screen_mapping(unsigned int num_screens);

#endif