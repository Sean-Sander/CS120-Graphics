#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "bird.h"
#include <iostream>
#include <memory>
#include <vector>
#include <ctime>
#include "pipe.h"
#include "score.h"
#include "button.h"
using namespace std;

GLdouble width, height;
int wd;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color lightGrassGreen(36/255.0, 186/255.0, 66/255.0);
const color darkGrassGreen(6/255.0, 156/255.0, 36/255.0);
const color white(1, 1, 1);
const color grey(0.75, 0.75, 0.75);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);

const dimensions GRASS_BLOCK(10, 26);

vector<unique_ptr<Shape>> clouds;
vector<unique_ptr<Shape>> grassBlocks;
vector<Score> scoreVec;
Rect grass;
vector<Pipe> pipes;
vector<int> digits;
Rect user;
Bird bird;
Button newGame({.5, .7, 1}, {250, 225}, {100, 50}, "Try Again");
int score;
double angle;
bool pipeScroll = false;
bool grassScroll = true;

void initClouds() {
    //randomizing the positions
    double randX;
    double randY;
    //clouds
    clouds.clear();
    dimensions cloudBottom(30, 30);
    for (int i = 0; i < 10; ++i) {
        // First cloud
        //anywhere between screen width
        randX = rand() % (int) (width - 30);
        //anywhere between 0 and height/4
        randY = (rand() % (int) (height / 4) + 30);
        clouds.push_back(make_unique<Circle>(grey, randX + 50 * i, randY + 10 * i, 20));
        clouds.push_back(make_unique<Circle>(grey, randX + 30 + 50 * i, randY + 10 * i, 20));
        clouds.push_back(make_unique<Circle>(grey, randX + 20 + 50 * i, randY - 10 + 10 * i, 20));
        clouds.push_back(make_unique<Rect>(grey, randX + 15 + 50 * i, randY + 5 + 10 * i, cloudBottom));
    }

}

void initGrass() {
    grassBlocks.clear();
    grass.setCenter(width/2, height-5);
    grass.setSize(width, 25);
    dimensions grassBlock(10, 26);
    for (int i = 0; i <= width; i++) {
        if (i % 20 == 0) {
            grassBlocks.push_back(make_unique<Rect>(darkGrassGreen,
                                                    i,
                                                    height - 5,
                                                    GRASS_BLOCK));
        }
    }
    grass.setColor(lightGrassGreen);
}

void initPipes() {
    pipes.clear();
    int totalPipeWidth = 0;
    double pipeHeight, pipeWidth;
    //populate vector
    while (totalPipeWidth < width + 50) {
        //get random pipe height between 50 and 350
        pipeHeight = rand() % 301 + 50;
        pipeWidth = 50;
        pipes.push_back(Pipe(totalPipeWidth + (pipeWidth/2) + 200 + width, 20, pipeWidth, pipeHeight, width, height));
        totalPipeWidth += pipeWidth + 200;
    }
}

void initUser() {
    bird=Bird();
}

void initScore() {
    Score::init(score);
}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
    initClouds();
    initGrass();
    initPipes();
    initUser();
    initScore();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE
    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    
    /*
     * Draw here
     */

    for (unique_ptr<Shape> &s : clouds) {
        s->draw();
    }

    for (Pipe &p : pipes) {
        if (p.isOverlapping(bird)) {
            p.setColor(brickRed);
            bird.die();
            pipeScroll = false;
            grassScroll = false;
        }
        else {
            p.setColor(black);
        }

        p.draw();
    }

    for (Score &s : Score::calculateScore(score, width, height)) {
        s.draw();
    }



    grass.draw();

    for (unique_ptr<Shape> &s : grassBlocks) {
        s->draw();
    }

    bird.draw();

    //draw the button if the game is over
    if (bird.isDead())
        newGame.draw();

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    //space bar (wrap this in an if screen == game)
    if (key == 32 && !bird.isDead()) {
        bird.hop();
        pipeScroll = true;
        grassScroll = true;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
        case GLUT_KEY_RIGHT:
            
            break;
        case GLUT_KEY_UP:
            
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    if (newGame.isOverlapping(x,y)){
        newGame.hover();
    }
    else{
        newGame.release();
    }
    glutPostRedisplay();
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && newGame.isOverlapping(x, y))
        newGame.pressDown();
    else
        newGame.release();

    //ensure the bird is dead so you cant click an invisible button and reset the game
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && newGame.isOverlapping(x, y) && bird.isDead())
        init();

    glutPostRedisplay();
}

void cloudTimer(int dummy) {

    for (unique_ptr<Shape> &s : clouds) {
        // Move all the clouds to the left
        s->moveX(-1);
        // If a shape has moved off the screen
        if (s->getCenterX() < -20) {
            // Set it to the right of the screen so that it passes through again
            s->setCenterX(520);
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(50, cloudTimer, dummy);
}


void pipeTimer(int dummy) {
    //bird info
    bird.update();


    //make sure the user has started playing
    if (pipeScroll) {
        int pipeOnLeft;
        for (int i = 0; i < pipes.size(); ++i) {
            //scroll pipes to left
            pipes[i].moveX(-2);
            //if a pipe has moved off the screen
            if (pipes[i].getX() < -(pipes[i].getWidth() / 2)) {
                //set it to the right of the screen and randomize the height
                pipeOnLeft = (i == 0) ? pipes.size() - 1 : i - 1;
                pipes[i].setX(
                        pipes[pipeOnLeft].getX() + pipes[pipeOnLeft].getWidth() / 2 + pipes[i].getWidth() / 2 + 200);
                pipes[i].setHeight(rand() % 301 + 50);
            }
            //to increment score
            if (pipes[i].passedPipe(bird)) {
                score++;
            }
        }
        //if the bird died somehow stop scrolling
        if (bird.isDead())
            pipeScroll = false;
    }

    glutPostRedisplay();
    glutTimerFunc(30, pipeTimer, dummy);
}

void grassTimer(int dummy) {

    if (grassScroll) {
        for (int i = 0; i < grassBlocks.size(); i++) {
            grassBlocks[i]->moveX(-2);
            if (grassBlocks[i]->getCenterX() < -(GRASS_BLOCK.width) / 2) {
                // reset grass blocks
                grassBlocks[i]->setCenterX(width + GRASS_BLOCK.width * 1.5);
            }
        }
        if (bird.isDead())
            grassScroll = false;
    }
    glutPostRedisplay();
    glutTimerFunc(30, grassTimer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Very Interesting Bird" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, cloudTimer, 0);
    glutTimerFunc(0, pipeTimer, 0);
    glutTimerFunc(0, grassTimer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
