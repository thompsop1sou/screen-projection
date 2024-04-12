#include "screen.h"

void print_screen(Screen s)
{
    printf("[");
    print_point(s.p00);
    printf(", ");
    print_point(s.p10);
    printf(", ");
    print_point(s.p01);
    printf(", ");
    print_point(s.p11);
    printf("]");
}

bool screen_is_valid(Screen s)
{
    return true;
}

// Point p is in wiimote coordinates. Will be mapped to screen-space coordinates and returned.
Point map_point_to_screen_space(Point p, Screen s)
{
    // Set up point to return
    Point p_mapped = {NAN, NAN};

    // Get upper and lower bounds
    Line l_x_lower = line_from_points(s.p00, s.p01); // y-axis
    Line l_x_upper = line_from_points(s.p10, s.p11);
    Line l_y_lower = line_from_points(s.p00, s.p10); // x-axis
    Line l_y_upper = line_from_points(s.p01, s.p11);

    // Check whether any lines are parallel
    bool l_x_are_parallel = lines_are_parallel(l_x_lower, l_x_upper, 0.000001);
    bool l_y_are_parallel = lines_are_parallel(l_y_lower, l_y_upper, 0.000001);

    // Both sets of lines are parallel
    if (l_x_are_parallel && l_y_are_parallel)
    {
        // Find mapped coordinates
        p_mapped.x = interpolate_point_between_lines_c(p, l_x_lower, l_x_upper);
        p_mapped.y = interpolate_point_between_lines_c(p, l_y_lower, l_y_upper);
    }
    // Only x lines are parallel
    else if (l_x_are_parallel)
    {
        // Find horizon
        Point p_hrzn_y = find_intersection_of_lines(l_y_lower, l_y_upper);
        Line l_hrzn = (Line) {p_hrzn_y, l_x_lower.dx, l_x_lower.dy};

        // Find mapped coordinates
        p_mapped.x = interpolate_point_between_lines_b(p, l_x_lower, l_x_upper, l_hrzn);
        p_mapped.y = interpolate_point_between_lines_a(p, l_y_lower, l_y_upper, l_hrzn);
    }
    // Only y lines are parallel
    else if (l_y_are_parallel)
    {
        // Find horizon
        Point p_hrzn_x = find_intersection_of_lines(l_x_lower, l_x_upper);
        Line l_hrzn = (Line) {p_hrzn_x, l_y_lower.dx, l_y_lower.dy};

        // Find mapped coordinates
        p_mapped.x = interpolate_point_between_lines_a(p, l_x_lower, l_x_upper, l_hrzn);
        p_mapped.y = interpolate_point_between_lines_b(p, l_y_lower, l_y_upper, l_hrzn);
    }
    // Bot sets of lines are NOT parallel
    else
    {
        // Find horizon
        Point p_hrzn_x = find_intersection_of_lines(l_x_lower, l_x_upper);
        Point p_hrzn_y = find_intersection_of_lines(l_y_lower, l_y_upper);
        Line l_hrzn = line_from_points(p_hrzn_x, p_hrzn_y);

        // Find mapped coordinates
        p_mapped.x = interpolate_point_between_lines_a(p, l_x_lower, l_x_upper, l_hrzn);
        p_mapped.y = interpolate_point_between_lines_a(p, l_y_lower, l_y_upper, l_hrzn);
    }

    return p_mapped;
}

// Helper for a point between non-parallel lines.
double interpolate_point_between_lines_a(Point p, Line l_lower, Line l_upper, Line l_hrzn)
{
    // Find the intersection point on the horizon of the upper and lower lines
    Point p_hrzn = find_intersection_of_lines(l_lower, l_upper);
    if (!point_is_on_line(p_hrzn, l_hrzn, 0.000001))
        return NAN;

    // Find angles of lines
    double a_hrzn = angle_of_line(l_hrzn);
    double a_lower = angle_of_line(l_lower);
    double a_upper = angle_of_line(l_upper);
    double da_lower = fposmod(a_lower - a_hrzn, PI);
    double da_upper = fposmod(a_upper - a_hrzn, PI);

    // Calculate constants for magic formula
    double k = 1 / (tan(da_upper - PI / 2.0) - tan(da_lower - PI / 2.0));
    double h = -tan(da_lower - PI / 2.0) * k;

    // Get the line and it's corresponding angle for the point
    Line l_p = line_from_points(p, p_hrzn);
    double a_p = angle_of_line(l_p);
    double da_p = fposmod(a_p - a_hrzn, PI);

    // Use magic formula to calculate final interpolated value
    return k * tan(da_p - PI / 2.0) + h;
}

// Helper for a point between parallel lines, with non-parallel lines on other sides.
double interpolate_point_between_lines_b(Point p, Line l_lower, Line l_upper, Line l_hrzn)
{
    // Get distances
    double d_lower = distance_between_point_and_line(l_lower.p, l_hrzn);
    double d_upper = distance_between_point_and_line(l_upper.p, l_hrzn);
    double d_point = distance_between_point_and_line(p, l_hrzn);

    // Calculate constants for magic formula
    double k = (d_upper * d_lower) / (d_upper - d_lower);
    double h = 1 / d_lower;

    // Use magic formula to calculate final interpolated value
    return k * (-(1 / d_point) + h);
}

// Helper for a point between parallel lines.
double interpolate_point_between_lines_c(Point p, Line l_lower, Line l_upper)
{
    // Make sure lines are parallel
    if (!lines_are_parallel(l_lower, l_upper, 0.000001))
        return NAN;

    // Get distances
    double d_lines = distance_between_point_and_line(l_upper.p, l_lower);
    double d_point_lower = distance_between_point_and_line(p, l_lower);

    // Return percentage
    return d_point_lower / d_lines;
}
