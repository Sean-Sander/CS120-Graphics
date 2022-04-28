#include "pipe.h"
#include "graphics.h"

#include <iostream>

Pipe::Pipe(double x, double y, double width, double height, double screenWidth, double screenHeight) : x(x), y(y), width(width), height(height), screenHeight(screenHeight), screenWidth(screenWidth){
    //set the class vars
    bottomHeight = screenHeight - height - y;
    topHeight = bottomHeight - GAP_HEIGHT;

}

void Pipe::setX(double x) {
    this->x = x;
}

void Pipe::moveX(double x) {
    this->x += x;
}

void Pipe::moveY(double y) {
    this->y += y;
    //update vars
    bottomHeight = screenHeight - height - y;
    topHeight = bottomHeight - GAP_HEIGHT;
}

void Pipe::setWidth(double width) {
    this->width = width;
}

void Pipe::setHeight(double height) {
    this->height = height;
    //update vars
    bottomHeight = screenHeight - height - y;
    topHeight = bottomHeight - GAP_HEIGHT;
}

void Pipe::setColor(color color) {
    pipeColor = color;
}

double Pipe::getX() {
    return x;
}

double Pipe::getWidth() {
    return width;
}

bool Pipe::isOverlapping(Bird &bird) {
    //check if the corner points are in any of the pipe zones
    for (point2D &p : bird.getCheck()) {
        //check if it is in the x range
        if (p.x > x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET && p.x < x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET) {
            //check if it is in the bottom y range
            if (p.y > bottomHeight - OUTLINE_OFFSET && p.y < screenHeight - y + OUTLINE_OFFSET)
                return true;
            //check if it is in the top y range
            else if (p.y > 0 - OUTLINE_OFFSET && p.y < topHeight + OUTLINE_OFFSET)
                return true;
        }
    }

    //if none of them are in a pillar, return false
    return false;
}

bool Pipe::passedPipe(Bird &bird) {
    //check if it is in the small sliver at the front of the pipe
    if (bird.getCheck()[0].x > x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET && bird.getCheck()[0].x < x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET + 1.1) {
        //check if it is in the gap
        if (bird.getCheck()[0].y < bottomHeight - OUTLINE_OFFSET && bird.getCheck()[0].y > topHeight + OUTLINE_OFFSET)
            return true;
    }

    return false;
}

void Pipe::makeRect(point2D topLeft, point2D bottomLeft, point2D bottomRight, point2D topRight) {
    //Draw rectangle as Quad
    glBegin(GL_QUADS);
    //set the 4 corners/vertices
    //top left
    glVertex2i(topLeft.x, topLeft.y);
    //bottom left
    glVertex2i(bottomLeft.x, bottomLeft.y);
    //bottom right
    glVertex2i(bottomRight.x, bottomRight.y);
    //top right
    glVertex2i(topRight.x, topRight.y);
    //End Quad
    glEnd();
}

void Pipe::draw() {
    //draw the outlines
    //bottom pillar outline
    glColor3f(pipeColor.red, pipeColor.green, pipeColor.blue);
    makeRect({x - (width / 2) - OUTLINE_OFFSET, bottomHeight - OUTLINE_OFFSET},{x - (width / 2) - OUTLINE_OFFSET, screenHeight - y + OUTLINE_OFFSET},{x + (width / 2) + OUTLINE_OFFSET, screenHeight - y + OUTLINE_OFFSET},{x + (width / 2) + OUTLINE_OFFSET, bottomHeight - OUTLINE_OFFSET});

    //generate bottom pillar lip outline
    glColor3f(pipeColor.red, pipeColor.green, pipeColor.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, bottomHeight - OUTLINE_OFFSET},{x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, bottomHeight + LIP_OFFSET_Y + OUTLINE_OFFSET},{x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, bottomHeight + LIP_OFFSET_Y + OUTLINE_OFFSET},{x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, bottomHeight - OUTLINE_OFFSET});

    //generate the top pillar outline
    glColor3f(pipeColor.red, pipeColor.green, pipeColor.blue);
    makeRect({x - (width / 2) - OUTLINE_OFFSET, 0 - OUTLINE_OFFSET}, {x - (width / 2) - OUTLINE_OFFSET, topHeight + OUTLINE_OFFSET}, {x + (width / 2) + OUTLINE_OFFSET, topHeight + OUTLINE_OFFSET}, {x + (width / 2) + OUTLINE_OFFSET, 0 - OUTLINE_OFFSET});

    //generate top pillar lip outline
    glColor3f(pipeColor.red, pipeColor.green, pipeColor.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, topHeight - LIP_OFFSET_Y - OUTLINE_OFFSET}, {x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, topHeight + OUTLINE_OFFSET}, {x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, topHeight + OUTLINE_OFFSET}, {x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, topHeight - LIP_OFFSET_Y - OUTLINE_OFFSET});


    //generate the bottom pillar
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2), bottomHeight}, {x - (width / 2), screenHeight - y}, {x + (width / 2), screenHeight - y}, {x + (width / 2), bottomHeight});
    glColor3f(lightGreen.red, lightGreen.green, lightGreen.blue);
    makeRect({x - (width / 2), bottomHeight}, {x - (width / 2), screenHeight - y}, {x - (width / 2) + 20, screenHeight - y}, {x - (width / 2) + 20, bottomHeight});
    glColor3f(whiteGreen.red, whiteGreen.green, whiteGreen.blue);
    makeRect({x - (width / 2) + 4, bottomHeight}, {x - (width / 2) + 4, screenHeight - y}, {x - (width / 2) + 8, screenHeight - y}, {x - (width / 2) + 8, bottomHeight});
    glColor3f(darkGreen.red, darkGreen.green, darkGreen.blue);
    makeRect({x + (width / 2) - 12, bottomHeight}, {x + (width / 2) - 12, screenHeight - y}, {x + (width / 2), screenHeight - y}, {x + (width / 2), bottomHeight});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x + (width / 2) - 8, bottomHeight}, {x + (width / 2) - 8, screenHeight - y}, {x + (width / 2) - 5, screenHeight - y}, {x + (width / 2) - 5, bottomHeight});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2) + 14, bottomHeight}, {x - (width / 2) + 14, screenHeight - y}, {x - (width / 2) + 16, screenHeight - y}, {x - (width / 2) + 16, bottomHeight});


    //generate bottom pillar lip
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X, bottomHeight}, {x - (width / 2) - LIP_OFFSET_X, bottomHeight + LIP_OFFSET_Y}, {x + (width / 2) + LIP_OFFSET_X, bottomHeight + LIP_OFFSET_Y}, {x + (width / 2) + LIP_OFFSET_X, bottomHeight});
    glColor3f(lightGreen.red, lightGreen.green, lightGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X, bottomHeight},{x - (width / 2) - LIP_OFFSET_X, bottomHeight + LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 20, bottomHeight + LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 20, bottomHeight});
    glColor3f(whiteGreen.red, whiteGreen.green, whiteGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X + 4, bottomHeight},{x - (width / 2) - LIP_OFFSET_X + 4, bottomHeight + LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 8, bottomHeight + LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 8, bottomHeight});
    glColor3f(darkGreen.red, darkGreen.green, darkGreen.blue);
    makeRect({x + (width / 2) + LIP_OFFSET_X - 12, bottomHeight},{x + (width / 2) + LIP_OFFSET_X - 12, bottomHeight + LIP_OFFSET_Y},{x + (width / 2) + LIP_OFFSET_X, bottomHeight + LIP_OFFSET_Y},{x + (width / 2) + LIP_OFFSET_X, bottomHeight});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x + (width / 2) + LIP_OFFSET_X - 8, bottomHeight},{x + (width / 2) + LIP_OFFSET_X - 8, bottomHeight + LIP_OFFSET_Y},{x + (width / 2) + LIP_OFFSET_X - 5, bottomHeight + LIP_OFFSET_Y},{x + (width / 2) + LIP_OFFSET_X - 5, bottomHeight});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X + 14, bottomHeight},{x - (width / 2) - LIP_OFFSET_X + 14, bottomHeight + LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 16, bottomHeight + LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 16, bottomHeight});

    //generate the top pillar
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2), 0}, {x - (width / 2), topHeight}, {x + (width / 2), topHeight}, {x + (width / 2), 0});
    glColor3f(lightGreen.red, lightGreen.green, lightGreen.blue);
    makeRect({x - (width / 2), 0}, {x - (width / 2), topHeight}, {x - (width / 2) + 20, topHeight}, {x - (width / 2) + 20, 0});
    glColor3f(whiteGreen.red, whiteGreen.green, whiteGreen.blue);
    makeRect({x - (width / 2) + 4, 0}, {x - (width / 2) + 4, topHeight}, {x - (width / 2) + 8, topHeight}, {x - (width / 2) + 8, 0});
    glColor3f(darkGreen.red, darkGreen.green, darkGreen.blue);
    makeRect({x + (width / 2) - 12, 0}, {x + (width / 2) - 12, topHeight}, {x + (width / 2), topHeight}, {x + (width / 2), 0});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x + (width / 2) - 8, 0}, {x + (width / 2) - 8, topHeight}, {x + (width / 2) - 5, topHeight}, {x + (width / 2) - 5, 0});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2) + 14, 0}, {x - (width / 2) + 14, topHeight}, {x - (width / 2) + 16, topHeight}, {x - (width / 2) + 16, 0});


    //generate top pillar lip
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X, topHeight - LIP_OFFSET_Y}, {x - (width / 2) - LIP_OFFSET_X, topHeight}, {x + (width / 2) + LIP_OFFSET_X, topHeight}, {x + (width / 2) + LIP_OFFSET_X, topHeight - LIP_OFFSET_Y});
    glColor3f(lightGreen.red, lightGreen.green, lightGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X, topHeight - LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X, topHeight},{x - (width / 2) - LIP_OFFSET_X + 20, topHeight},{x - (width / 2) - LIP_OFFSET_X + 20, topHeight - LIP_OFFSET_Y});
    glColor3f(whiteGreen.red, whiteGreen.green, whiteGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X + 4, topHeight - LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 4, topHeight},{x - (width / 2) - LIP_OFFSET_X + 8, topHeight},{x - (width / 2) - LIP_OFFSET_X + 8, topHeight - LIP_OFFSET_Y});
    glColor3f(darkGreen.red, darkGreen.green, darkGreen.blue);
    makeRect({x + (width / 2) + LIP_OFFSET_X - 12, topHeight - LIP_OFFSET_Y},{x + (width / 2) + LIP_OFFSET_X - 12, topHeight},{x + (width / 2) + LIP_OFFSET_X, topHeight},{x + (width / 2) + LIP_OFFSET_X, topHeight - LIP_OFFSET_Y});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x + (width / 2) + LIP_OFFSET_X - 8, topHeight - LIP_OFFSET_Y},{x + (width / 2) + LIP_OFFSET_X - 8, topHeight},{x + (width / 2) + LIP_OFFSET_X - 5, topHeight},{x + (width / 2) + LIP_OFFSET_X - 5, topHeight - LIP_OFFSET_Y});
    glColor3f(normGreen.red, normGreen.green, normGreen.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X + 14, topHeight - LIP_OFFSET_Y},{x - (width / 2) - LIP_OFFSET_X + 14, topHeight},{x - (width / 2) - LIP_OFFSET_X + 16, topHeight},{x - (width / 2) - LIP_OFFSET_X + 16, topHeight - LIP_OFFSET_Y});




    //generate the lip separations
    //bottom one
    glColor3f(pipeColor.red, pipeColor.green, pipeColor.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, bottomHeight + LIP_OFFSET_Y}, {x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, bottomHeight + LIP_OFFSET_Y + OUTLINE_OFFSET}, {x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, bottomHeight + LIP_OFFSET_Y + OUTLINE_OFFSET}, {x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, bottomHeight + LIP_OFFSET_Y});

    //top one
    glColor3f(pipeColor.red, pipeColor.green, pipeColor.blue);
    makeRect({x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, topHeight - LIP_OFFSET_Y - OUTLINE_OFFSET}, {x - (width / 2) - LIP_OFFSET_X - OUTLINE_OFFSET, topHeight - LIP_OFFSET_Y}, {x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, topHeight - LIP_OFFSET_Y}, {x + (width / 2) + LIP_OFFSET_X + OUTLINE_OFFSET, topHeight - LIP_OFFSET_Y - OUTLINE_OFFSET});
}