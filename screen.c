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
    // Get diagonal lines
    Line l_diagonal_1 = line_from_points(s.p00, s.p11);
    Line l_diagonal_2 = line_from_points(s.p10, s.p01);

    // Find the intersection of the diagonal lines
    Point p_intersect = find_intersection_of_lines(l_diagonal_1, l_diagonal_2);

    // Ensure the intersection point is between p00 and p11
    bool p_is_between_diagonal_1 = point_is_between_points(p_intersect, s.p00, s.p11, 0.000001);

    // Ensure the intersection point is between p10 and p01
    bool p_is_between_diagonal_2 = point_is_between_points(p_intersect, s.p10, s.p01, 0.000001);

    // Only return true if it is between both pairs of diagonal points
    return p_is_between_diagonal_1 && p_is_between_diagonal_2;
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
        p_mapped.x = map_point_coord_parallel_lines(p, l_x_lower, l_x_upper);
        p_mapped.y = map_point_coord_parallel_lines(p, l_y_lower, l_y_upper);
    }
    // Only x lines are parallel
    else if (l_x_are_parallel)
    {
        // Find horizon
        Point p_hrzn_y = find_intersection_of_lines(l_y_lower, l_y_upper);
        Line l_hrzn = (Line) {p_hrzn_y, l_x_lower.dx, l_x_lower.dy};

        // Find mapped coordinates
        p_mapped.x = map_point_coord_both_types_of_lines(p, l_x_lower, l_x_upper, l_hrzn);
        p_mapped.y = map_point_coord_non_parallel_lines(p, l_y_lower, l_y_upper, l_hrzn);
    }
    // Only y lines are parallel
    else if (l_y_are_parallel)
    {
        // Find horizon
        Point p_hrzn_x = find_intersection_of_lines(l_x_lower, l_x_upper);
        Line l_hrzn = (Line) {p_hrzn_x, l_y_lower.dx, l_y_lower.dy};

        // Find mapped coordinates
        p_mapped.x = map_point_coord_non_parallel_lines(p, l_x_lower, l_x_upper, l_hrzn);
        p_mapped.y = map_point_coord_both_types_of_lines(p, l_y_lower, l_y_upper, l_hrzn);
    }
    // Both sets of lines are NOT parallel
    else
    {
        // Find horizon
        Point p_hrzn_x = find_intersection_of_lines(l_x_lower, l_x_upper);
        Point p_hrzn_y = find_intersection_of_lines(l_y_lower, l_y_upper);
        Line l_hrzn = line_from_points(p_hrzn_x, p_hrzn_y);

        // Find mapped coordinates
        p_mapped.x = map_point_coord_non_parallel_lines(p, l_x_lower, l_x_upper, l_hrzn);
        p_mapped.y = map_point_coord_non_parallel_lines(p, l_y_lower, l_y_upper, l_hrzn);
    }

    return p_mapped;
}

// Helper for helper function map_point_coord_non_parallel().
double non_parallel_helper(Line l1, Line l2)
{
    return (l1.dx * l2.dx + l1.dy * l2.dy) / (l1.dx * l2.dy - l1.dy * l2.dx);
}

// Helper for a point between non-parallel lines.
double map_point_coord_non_parallel_lines(Point p, Line l_lower, Line l_upper, Line l_hrzn)
{
    // Find the intersection point on the horizon of the upper and lower lines
    Point p_hrzn = find_intersection_of_lines(l_lower, l_upper);
    if (!point_is_on_line(p_hrzn, l_hrzn, 0.000001))
        return NAN;

    // Get the line for the point
    Line l_p = line_from_points(p, p_hrzn);

    // Use magic formula to calculate final interpolated value
    double k = 1 / (non_parallel_helper(l_upper, l_hrzn) - non_parallel_helper(l_lower, l_hrzn));
    double h = -non_parallel_helper(l_lower, l_hrzn) * k;
    return k * non_parallel_helper(l_p, l_hrzn) + h;
}

// Helper for a point between parallel lines, with non-parallel lines on other sides.
double map_point_coord_both_types_of_lines(Point p, Line l_lower, Line l_upper, Line l_hrzn)
{
    // Get distances
    double d_lower = distance_between_point_and_line(l_lower.p, l_hrzn);
    double d_upper = distance_between_point_and_line(l_upper.p, l_hrzn);
    double d_point = distance_between_point_and_line(p, l_hrzn);

    // Use magic formula to calculate final interpolated value
    double k = (d_upper * d_lower) / (d_upper - d_lower);
    double h = 1 / d_lower;
    return k * (-(1 / d_point) + h);
}

// Helper for a point between parallel lines.
double map_point_coord_parallel_lines(Point p, Line l_lower, Line l_upper)
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

// Test the mapping for a specified number of (valid) random screens.
void test_screen_mapping(unsigned int num_screens)
{
    srand(time(NULL));
    double max = 10.0;
    double min = -10.0;

    for (unsigned int i = 0; i < num_screens; i++)
    {
        // Get a valid screen
        Screen s;
        do
        {
            s.p00 = random_point(min, max, min, max);
            s.p10 = random_point(min, max, min, max);
            s.p01 = random_point(min, max, min, max);
            s.p11 = random_point(min, max, min, max);
        }
        while (!screen_is_valid(s));

        // Find the middle of the screen
        Point p_mid = find_intersection_of_lines(line_from_points(s.p00, s.p11), line_from_points(s.p10, s.p01));

        // Find the mapping of all the points we can access
        Point p00_mapped = map_point_to_screen_space(s.p00, s);
        Point p10_mapped = map_point_to_screen_space(s.p10, s);
        Point p01_mapped = map_point_to_screen_space(s.p01, s);
        Point p11_mapped = map_point_to_screen_space(s.p11, s);
        Point p_mid_mapped = map_point_to_screen_space(p_mid, s);

        // Check if the mapping of the points worked as expected
        bool test_succeeded = points_are_equal(p00_mapped, (Point) {0.0, 0.0}, 0.000001)
                            && points_are_equal(p10_mapped, (Point) {1.0, 0.0}, 0.000001)
                            && points_are_equal(p01_mapped, (Point) {0.0, 1.0}, 0.000001)
                            && points_are_equal(p11_mapped, (Point) {1.0, 1.0}, 0.000001)
                            && points_are_equal(p_mid_mapped, (Point) {0.5, 0.5}, 0.000001);
        if (!test_succeeded)
        {
            printf("\nFAILED");
            printf("\n  screen: ");
            print_screen(s);

            printf("\n  p00: ");
            print_point(s.p00);
            printf(" -> ");
            print_point(p00_mapped);

            printf("\n  p10: ");
            print_point(s.p10);
            printf(" -> ");
            print_point(p10_mapped);

            printf("\n  p01: ");
            print_point(s.p01);
            printf(" -> ");
            print_point(p01_mapped);

            printf("\n  p11: ");
            print_point(s.p11);
            printf(" -> ");
            print_point(p11_mapped);

            printf("\n  p_mid: ");
            print_point(p_mid);
            printf(" -> ");
            print_point(p_mid_mapped);

            printf("\n");
        }
    }
}
