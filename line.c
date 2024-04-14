#include "line.h"

// Creates a new line that passes through p1 and p2.
Line line_from_points(Point p1, Point p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return (Line) {p1, dx, dy};
}

// Prints a line in the form "x = a" or "y = m * x + b".
void print_line(Line l)
{
    // Slope is invalid
    if (l.dx == 0.0 && l.dy == 0.0)
    {
        printf("<invalid line>");
    }
    // Vertical line
    else if (l.dx == 0.0)
    {
        printf("x = ");
        print_double(l.p.x);
    }
    // Horizontal line
    else if (l.dy == 0.0)
    {
        printf("y = ");
        print_double(l.p.y);
    }
    // Other line
    else
    {
        double m = slope_of_line(l);
        double b = y_val_of_line_at_x_val(l, 0.0);
        if (b > 0.0)
        {
            printf("y = ");
            print_double(m);
            printf(" * x + ");
            print_double(b);
        }
        else if (b < 0.0)
        {
            printf("y = ");
            print_double(m);
            printf(" * x - ");
            print_double(-b);
        }
        else
        {
            printf("y = ");
            print_double(m);
            printf(" * x");
        }
    }
}

// Returns whether l is a valid line (i.e. its point is valid and its slope is valid).
bool line_is_valid(Line l)
{
    return point_is_valid(l.p) && (l.dx != 0.0 || l.dy != 0.0);
}

// Returns the slope of a line (i.e. dy / dx).
double slope_of_line(Line l)
{
    return l.dy / l.dx;
}

// Returns the angle of a line with the x-axis.
double angle_of_line(Line l)
{
    if (l.dx == 0.0 && l.dy == 0.0)
        return NAN;
    else if (l.dx == 0.0)
        return PI / 2.0;
    else
        return fposmod(atan(l.dy / l.dx), PI);
}

// Returns whether l1 and l2 are equal (within an error of epsilon).
bool lines_are_equal(Line l1, Line l2, double epsilon)
{
    bool points_match = point_is_on_line(l1.p, l2, epsilon);
    bool are_parallel = lines_are_parallel(l1, l2, epsilon);
    return points_match && are_parallel;
}

// Returns whether l1 and l2 are parallel (within an error of epsilon).
bool lines_are_parallel(Line l1, Line l2, double epsilon)
{
    return doubles_are_equal(l1.dy * l2.dx, l2.dy * l1.dx, epsilon);
}

// Returns whether l1 and l2 are perpendicular (within an error of epsilon).
bool lines_are_perpendicular(Line l1, Line l2, double epsilon)
{
    return doubles_are_equal(l1.dy * l2.dy, -l1.dx * l2.dx, epsilon);
}

// Returns whether p lies on l (within an error of epsilon).
bool point_is_on_line(Point p, Line l, double epsilon)
{
    double lhs = l.dx * (l.p.y - p.y);
    double rhs = l.dy * (l.p.x - p.x);
    return doubles_are_equal(lhs, rhs, epsilon);
}

// Calculates the x-value of l at the provided y-value.
double x_val_of_line_at_y_val(Line l, double y)
{
    return (l.dx / l.dy) * (y - l.p.y) + l.p.x;
}

// Calculates the y-value of l at the provided x-value.
double y_val_of_line_at_x_val(Line l, double x)
{
    return (l.dy / l.dx) * (x - l.p.x) + l.p.y;
}

// Calculates the perpendicular distance between p and l.
double distance_between_point_and_line(Point p, Line l)
{
    Line l_perpendicular = {p, -l.dy, l.dx};
    Point p_intersection = intersection_of_lines(l, l_perpendicular);
    return distance_between_points(p, p_intersection);
}

// Calculates the intersection point of l1 and l2.
Point intersection_of_lines(Line l1, Line l2)
{
    double det1 = intersection_helper(l1);
    double det2 = intersection_helper(l2);
    double x_numer = -det2 * l1.dx + det1 * l2.dx;
    double x_denom = l2.dx * l1.dy - l1.dx * l2.dy;
    double y_numer = det2 * l1.dy - det1 * l2.dy;
    double y_denom = l2.dy * l1.dx - l1.dy * l2.dx;
    return (Point) {x_numer / x_denom, y_numer / y_denom};
}

// Helper for intersection_of_lines().
double intersection_helper(Line l)
{
    Point q = {l.p.x + l.dx, l.p.y + l.dy};
    return l.p.x * q.y - q.x * l.p.y;
}
