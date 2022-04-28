//
// Created by Alexander Townsend on 4/20/21.
//

#ifndef RUNNER_BIRD_H
#define RUNNER_BIRD_H

//
// Created by Alexander Townsend on 4/20/21.
//
#include "graphics.h"
#include "shape.h"
#include "rect.h"
#include "circle.h"
#include <vector>
#include <memory>
using namespace std;

class Bird{
private:
    bool isAlive=true;
    double scale=0.75;
    double jump=-0.1;
    int wing;
    point2D center = point2D(50,250);
    double angle = -0.0/180*3.1415926535;
    vector<Rect> parts;

    //saved points which later will be rotated and moved as necessary and stored in toCheck
    vector<point2D> checkPoints={point2D(32*scale,6*scale), point2D(12*scale,-24*scale),point2D(24*scale,-12*scale),
                                 point2D(24*scale,20*scale), point2D(4*scale,24*scale),point2D(-16*scale,24*scale)};

    //points to get checked by the pipe for overlap
    vector<point2D> toCheck={point2D(32*scale,6*scale), point2D(12*scale,-24*scale),point2D(24*scale,-12*scale),
                             point2D(24*scale,20*scale), point2D(4*scale,24*scale),point2D(-16*scale,24*scale)};

    //options for basic wings
    vector<vector<Rect>> wings={
            {Rect(1, 1, 0, 1, -22*scale, 4*scale, dimensions(20*scale, 8*scale)),
             Rect(0, 0, 0, 1, -22*scale, -2*scale, dimensions(20*scale, 4*scale)),
             Rect(0, 0, 0, 1, -22*scale, 10*scale, dimensions(20*scale, 4*scale)),
             Rect(0, 0, 0, 1, -34*scale, 4*scale, dimensions(4*scale, 8*scale)),
             Rect(0, 0, 0, 1, -10*scale, 2*scale, dimensions(4*scale, 12*scale))
            },
            {Rect(1, 1, 0, 1, -22*scale, 0.0001*scale, dimensions(20*scale,16*scale)),
             Rect(0, 0, 0, 1, -24*scale, -10*scale, dimensions(16*scale,4*scale)),
                    Rect(0, 0, 0, 1, -34*scale, -2*scale, dimensions(4*scale, 12*scale)),
                    Rect(0, 0, 0, 1, -30*scale, 6*scale, dimensions(4*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -22*scale, 10*scale, dimensions(12*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -14*scale, -6*scale, dimensions(4*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -14*scale, 6*scale, dimensions(4*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -10*scale, 0.0001*scale, dimensions(4*scale, 8*scale))
            },
            {
                    Rect(1, 1, 0, 1, -24*scale, 10*scale, dimensions(16*scale,12*scale)),
                    Rect(0, 0, 0, 1, -22*scale, 2*scale, dimensions(20*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -34*scale, 10*scale, dimensions(4*scale, 12*scale)),
                    Rect(0, 0, 0, 1, -24*scale, 18*scale, dimensions(16*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -18*scale, 14*scale, dimensions(4*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -14*scale, 10*scale, dimensions(4*scale, 4*scale)),
                    Rect(0, 0, 0, 1, -10*scale, 6*scale, dimensions(4*scale, 4*scale))
            }
    };

    //Basic bird
    vector<Rect> starter={Rect(1,0.5,0,1,-10*scale,14*scale,dimensions(28*scale,12*scale)),
                          Rect(1,0,0,1,14*scale,10*scale,dimensions(28*scale,12*scale)),
                          Rect(1,1,0,1,-14*scale,2*scale,dimensions(36*scale,12*scale)),
                          Rect(1,1,0,1,-16*scale,-8*scale,dimensions(24*scale,8*scale)),
                          Rect(1,1,0,1,-10*scale,-16*scale,dimensions(20*scale,8*scale)),
                          Rect(1,1,1,1,10*scale,-6*scale,dimensions(20*scale,12*scale)),
                          Rect(1,1,1,1,8*scale,-16*scale,dimensions(16*scale,8*scale)),
                          Rect(0,0,0,1,30*scale,6*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,26*scale,14*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,16*scale,10*scale,dimensions(24*scale,4*scale)),
                          Rect(0,0,0,1,14*scale,18*scale,dimensions(20*scale,4*scale)),
                          Rect(0,0,0,1,16*scale,2*scale,dimensions(24*scale,4*scale)),
                          Rect(0,0,0,1,2*scale,14*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,2*scale,6*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,-2*scale,10*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,2*scale,-2*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,2*scale,-18*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,14*scale,-18*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,18*scale,-14*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,22*scale,-6*scale,dimensions(4*scale,12*scale)),
                          Rect(0,0,0,1,-2*scale,-10*scale,dimensions(4*scale,12*scale)),
                          Rect(0,0,0,1,0.00001*scale,-22*scale,dimensions(24*scale,4*scale)),
                          Rect(0,0,0,1,14*scale,-8*scale,dimensions(4*scale,8*scale)),
                          Rect(0,0,0,1,-16*scale,-18*scale,dimensions(8*scale,4*scale)),
                          Rect(0,0,0,1,-22*scale,-14*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,-26*scale,-10*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,-30*scale,2*scale,dimensions(4*scale,20*scale)),
                          Rect(0,0,0,1,-26*scale,14*scale,dimensions(4*scale,4*scale)),
                          Rect(0,0,0,1,-20*scale,18*scale,dimensions(8*scale,4*scale)),
                          Rect(0,0,0,1,-6*scale,22*scale,dimensions(20*scale,4*scale))

    };
public:

    /**Constructor
     * Makes the bird
     */
    Bird();

    /* Destructor */
    virtual ~Bird() = default;

    /**
     * Resets angle to 0
     */
    void reset();

    /**
     * Set's angle to a certain angle, used for testing
     * @param a radian angle to be rotated to
     */
    void setAngle(double a);

    /**
     * Draws the bird with the right rotation
     */
    void draw();

    /**
     * Tells the bird to start a hop by setting jump to 1
     */
    void hop();

    /**
     * returns points for the pipe to check
     * @return a vector of points
     */
    vector<point2D> getCheck();

    /**
     * updates where the bird should be, run in a timer, updated every frame
     */
    void update();

    /**
     * kills the bird
     */
    void die();

    /**
     * returns if the bird is dead or alive
     * @return bool
     */
    bool isDead();
};


#endif //RUNNER_BIRD_H
