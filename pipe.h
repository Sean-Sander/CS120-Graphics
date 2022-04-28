
#ifndef FLAPPYBIRD_PIPE_H
#define FLAPPYBIRD_PIPE_H

#include "shape.h"
#include <iostream>
#include <vector>
#include "bird.h"

class Pipe{
private:
    //vars for pipe info
    double x, y, width, height, topHeight, bottomHeight, screenWidth, screenHeight;
    const double GAP_HEIGHT = 120;
    const double LIP_OFFSET_X = 5;
    const double LIP_OFFSET_Y = 10;
    const double OUTLINE_OFFSET = 2;

    //to change the outline color
    color pipeColor = {0, 0, 0};

    //other pipe colors
    color normGreen = {.5, .95, 0};
    color lightGreen = {.5, 1, .5};
    color whiteGreen = {.8, .93, .8};
    color darkGreen = {0, .7, 0};

    /**
     * Helper function to draw the pipe
     * @param point2D topLeft corner
     * @param point2D bottomLeft corner
     * @param point2D bottomRight corner
     * @param point2D topRight corner
     */
    void makeRect(point2D topLeft, point2D bottomLeft, point2D bottomRight, point2D topRight);

public:
    /**
     * Constructor
     * @param double x for x pos
     * @param double y for y offset from bottom of screen
     * @param double width for width of pipe
     * @param double height for height of pipe gap area
     * @param double screenWidth the screen's width
     * @param double screenHeight the screen's height
     */
    Pipe(double x, double y, double width, double height, double screenWidth, double screenHeight);

    /**
     * Destructor
     */
    virtual ~Pipe() = default;

    /**
     * Sets the x pos
     * @param double x to set it to
     */
    void setX(double x);

    /**
     * Shifts the x pos
     * @param double x to shift it by
     */
    void moveX(double x);

    /**
     * Shifts the y pos
     * @param double y to shift it by
     */
    void moveY(double y);

    /**
     * Sets the width of the pipe
     * @param double width to set to
     */
    void setWidth(double width);

    /**
     * Sets the height of the pipe
     * @param double height for where the gap should be
     */
    void setHeight(double height);

    /**
     * Sets the outline color
     * @param struct color to set it to
     */
    void setColor(color color);

    /**
     * Gets the x pos
     * @return double x position
     */
    double getX();

    /**
     * Gets the width of the pipe
     * @return double width
     */
    double getWidth();

    /**
     * Checks if the bird is overlapping
     * @param Bird bird to check
     * @return bool if it is overlapping or not
     */
    bool isOverlapping(Bird &bird);

    /**
     * Checks if the bird has passed through the gap
     * @param Bird bird to check
     * @return bool if it has cleared the start of the pipe/made it through the gap
     */
    bool passedPipe(Bird &bird);

    /**
     * Draws the pipe
     */
    void draw();
};


#endif //FLAPPYBIRD_PIPE_H
