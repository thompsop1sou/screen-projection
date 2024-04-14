#include "point.h"
#include "line.h"

// Prints a point in the form "(x, y)".
void print_point(Point p)
{
    printf("(");
    print_double(p.x);
    printf(", ");
    print_double(p.y);
    printf(")");
}

// Gets a random point where x is between x_min and x_max (inclusive) and
// y is between y_min and y_max (inclusive).
Point random_point(double x_min, double x_max, double y_min, double y_max)
{
    return (Point) {random_double(x_min, x_max), random_double(y_min, y_max)};
}

// Returns whether both the x- and y-values are valid, finite numbers.
bool point_is_valid(Point p)
{
    return isfinite(p.x) && isfinite(p.y);
}

// Returns whether p1 and p2 are approximately equal (within an error of epsilon).
bool points_are_equal(Point p1, Point p2, double epsilon)
{
    return doubles_are_equal(p1.x, p2.x, epsilon) && doubles_are_equal(p1.y, p2.y, epsilon);
}

// Returns whether p_mid is on the line formed by p1 and p2 and between p1 and p2.
bool point_is_between_points(Point p_mid, Point p1, Point p2, double epsilon)
{
    // Make sure the three points are collinear
    if (!point_is_on_line(p_mid, line_from_points(p1, p2), epsilon))
        return false;

    // Check if the x or y coordinate of p_mid is between p0 and p1
    if (p1.x < p2.x)
        return p1.x < p_mid.x && p_mid.x < p2.x;
    else if (p2.x < p1.x)
        return p2.x < p_mid.x && p_mid.x < p1.x;
    else if (p1.y < p2.y)
        return p1.y < p_mid.y && p_mid.y < p2.y;
    else if (p2.y < p1.y)
        return p2.y < p_mid.y && p_mid.y < p1.y;
}

// Calculates the distance between p1 and p2.
double distance_between_points(Point p1, Point p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}
