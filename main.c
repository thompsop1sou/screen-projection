#include <stdio.h>

#include "point.h"
#include "screen.h"

// Prints three example screens and showcases their mappings.
void print_example_screens();

// Helper for print_example_screens().
void print_screen_and_points(Screen s, Point ps[], int ps_size);

int main()
{
    print_example_screens();
    return 0;
}

// Prints three example screens and showcases their mappings.
void print_example_screens()
{
    const int PS_SIZE = 5;
    Point ps[PS_SIZE];
    Screen s;

    // Screen with no pairs of parallel lines
    ps[0] = (Point) {0, 2};
    ps[1] = (Point) {2, -2};
    ps[2] = (Point) {2, 2};
    ps[3] = (Point) {4, 0};
    ps[4] = (Point) {2, 1};
    s = (Screen) {ps[0], ps[1], ps[2], ps[3]};
    print_screen_and_points(s, ps, PS_SIZE);

    // Screen with one pair of parallel lines
    ps[0] = (Point) {-3, -3};
    ps[1] = (Point) {3, -3};
    ps[2] = (Point) {0, 0};
    ps[3] = (Point) {3, 0};
    ps[4] = (Point) {1, -1};
    s = (Screen) {ps[0], ps[1], ps[2], ps[3]};
    print_screen_and_points(s, ps, PS_SIZE);

    // Screen with two pairs of parallel lines
    ps[0] = (Point) {3, 0};
    ps[1] = (Point) {4, 3};
    ps[2] = (Point) {2, 2};
    ps[3] = (Point) {3, 5};
    ps[4] = (Point) {3, 2.5};
    s = (Screen) {ps[0], ps[1], ps[2], ps[3]};
    print_screen_and_points(s, ps, PS_SIZE);
}

// Helper for print_example_screens().
void print_screen_and_points(Screen s, Point ps[], int ps_size)
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
