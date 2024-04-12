#include <stdio.h>

#include "point.h"
#include "line.h"
#include "screen.h"

void test_points_and_lines();
void test_screens();
void test_screen(Screen s, Point ps[], int ps_size);

int main()
{
    //test_points_and_lines();
    test_screens();
    return 0;
}

void test_points_and_lines()
{
    // Line l between (0, 2) and (1, 0)
    Point a = {0, 2};
    Point b = {1, 0};
    Line l = line_from_points(a, b);
    printf("\npoint a: ");
    print_point(a);
    printf("\npoint b: ");
    print_point(b);
    printf("\nline l: ");
    print_line(l);
    printf("\nangle of l: ");
    print_double(radians_to_degrees(angle_of_line(l)));
    printf("\n");

    // Line m between (2, 0) and (3, 2)
    Point c = {2, 0};
    Point d = {3, 2};
    Line m = line_from_points(c, d);
    printf("\npoint c: ");
    print_point(c);
    printf("\npoint d: ");
    print_point(d);
    printf("\nline m: ");
    print_line(m);
    printf("\nangle of m: ");
    print_double(radians_to_degrees(angle_of_line(m)));
    printf("\n");

    // Intersection of l and m
    Point p = find_intersection_of_lines(l, m);
    printf("\nintersection of l and m: ");
    print_point(p);
    printf("\n");
}

void test_screens()
{
    const int SIZE = 5;
    Point ps[5];
    Screen s;

    // No sets of parallel lines
    ps[0] = (Point) {0, 2};
    ps[1] = (Point) {2, -2};
    ps[2] = (Point) {2, 2};
    ps[3] = (Point) {4, 0};
    ps[4] = (Point) {2, 1};
    s = (Screen) {ps[0], ps[1], ps[2], ps[3]};
    test_screen(s, ps, SIZE);

    // One set of parallel lines
    ps[0] = (Point) {-3, -3};
    ps[1] = (Point) {3, -3};
    ps[2] = (Point) {0, 0};
    ps[3] = (Point) {3, 0};
    ps[4] = (Point) {1, -1};
    s = (Screen) {ps[0], ps[1], ps[2], ps[3]};
    test_screen(s, ps, SIZE);

    // Two sets of parallel lines
    ps[0] = (Point) {3, 0};
    ps[1] = (Point) {4, 3};
    ps[2] = (Point) {2, 2};
    ps[3] = (Point) {3, 5};
    ps[4] = (Point) {3, 2.5};
    s = (Screen) {ps[0], ps[1], ps[2], ps[3]};
    test_screen(s, ps, SIZE);
}

void test_screen(Screen s, Point ps[], int ps_size)
{
    // Print screen
    printf("\nscreen: ");
    print_screen(s);

    // Loop through and print points
    for (int i = 0; i < ps_size; i++)
    {
        printf("\npoint %d: ", i);
        print_point(ps[i]);
        printf(" -> ");
        print_point(map_point_to_screen_space(ps[i], s));
    }
    
    printf("\n");
}