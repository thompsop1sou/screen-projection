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

double interpolate_point_between_lines_a(Point p, Line l_lower, Line l_upper, Line h);

double interpolate_point_between_lines_b(Point p, Line l_lower, Line l_upper, Line h);

double interpolate_point_between_lines_c(Point p, Line l_lower, Line l_upper);

#endif