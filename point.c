#include "point.h"
#include "line.h"

void print_point(Point p)
{
    printf("(");
    print_double(p.x);
    printf(", ");
    print_double(p.y);
    printf(")");
}

bool point_is_valid(Point p)
{
    return isfinite(p.x) && isfinite(p.y);
}

bool points_are_equal(Point p1, Point p2, double epsilon)
{
    return doubles_are_equal(p1.x, p2.x, epsilon) && doubles_are_equal(p1.y, p2.y, epsilon);
}

double distance_between_points(Point p1, Point p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

double points_are_collinear(Point p1, Point p2, Point p3, double epsilon)
{
    if (points_are_equal(p1, p2, epsilon) || points_are_equal(p1, p3, epsilon) || points_are_equal(p2, p3, epsilon))
    {
        return true;
    }
    else
    {
        Line l = line_from_points(p1, p2);
        return point_is_on_line(p3, l, epsilon);
    }
}
