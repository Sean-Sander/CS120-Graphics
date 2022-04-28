# Flappy Bird

## Authors:
* David Melkumov
* Sean Sander
* Alexander Townsend

## Directions:
1. Download/clone the repository
   - Take any necessary steps to get GLUT and OpenGL working on your device
2. Run it and enjoy the game

## Summary:
### Game info:
Our project is a game of flappy bird. You are a bird
that can only fly in hops and you are constantly moving 
to the right. The goal is to not hit any pipes and get
as high of a score as you can. You can try to fly above
the pipes but the pipes go up forever, so you will not 
have any luck with that. You also can't go under the pipes
as you die if you touch the ground.

### How it works:
Our game uses multiple classes to represent the bird, pipes, and score respectively. At the start of the game, the
bird will hover up and down/slowly drift to the ground if not provided with any input, which ends the game. To control
the bird, we use the space bar. Once pressed, you will need to keep pressing space to have the bird hop, and the 
pipes/grass will begin scrolling using timers. The bird also flaps its wings by displaying a different vector of wings
through logic in its draw function. If any of the designated points in the bird overlap with a pipe, the bird will die
which sets some flags in the form of booleans to stop scrolling. If the bird reaches the gap of the pipes successfully,
the pipes will increment the score with logic inside the pipe's timer function. Upon reaching the left edge of the 
screen, the pipes are sent to the other side with a new randomized height. The bird is also able to rotate depending on 
how long it has been falling for. The score functions by using some predefined bars (rects) to create a 7 segment 
display for each number from 0 to 9, which is placed in the top middle section of the screen. Upon losing a game, a 
button is drawn which allows the user to restart the game by calling the initialization methods.

## Keyboard/Mouse input:
* ESC key to close the window
* Space Bar key to make the bird hop/play the game
* Mouse Left Click for new game button

## Citations:
Built off the runner guided project and its classes such as rect, shape, and circle. Also adapted the scrolling from
runner for pipes and grass. Used the clouds provided in runner but with some slight additions such as randomization.