# Introduction
This is a C library that was built to compensate for and remove perspective warping from a set of 2D points. The scenario it was built for involved a rectangular game board that was being monitored by a video feed. The desire was to be able to tell where on the game board a particular piece was located. The positions of the game piece and the four corners of the game board were marked, so their 2D coordinates from the perspective of the camera were all known. The issue was that the camera was not directly above the game board, so the image was slightly warped due to perspective. This library got rid of that perspective warping and found the exact 2D location of the piece on the game board.

# How to Use
First, make sure to include both [point.h](point.h) and [screen.h](screen.h).

Next, create a screen by creating four points to represent the four corners:
```c
Point p_1 = (Point) {0, 2};
Point p_2 = (Point) {2, -2};
Point p_3 = (Point) {2, 2};
Point p_4 = (Point) {4, 0};
Screen s = (Screen) {p_1, p_2, p_3, p_4);
```
> **Note:** The points should be provided in the order: top-left, top-right, bottom-left, bottom-right.

Next, create a point that we will find the "unprojected" coordinates for:
```c
Point p = (Point) {2, 1};
```

Finally, use the function `map_point_to_screen_space()` to find the "unprojected" coordinates of our point:
```c
// The "unprojected" point will be (0.5, 0.5)
Point p_unprojected = map_point_to_screen_space(p, s);
```

> **Note:** The "unprojected" coordinates are expressed in a UV coordinate space. This means the top-left corner takes on the value (0.0, 0.0), and the bottom-right corner takes on the value (1.0, 1.0).

Screens can be printed with `print_screen()` and points can be printed with `print_point()`:
```c
print_screen(s);
print_point(p);
print_point(p_unprojected);
```
