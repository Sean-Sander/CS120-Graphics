//
// Created by Sean on 4/23/2021.
//

#ifndef FLAPPYBIRD_SCORE_H
#define FLAPPYBIRD_SCORE_H

#include <vector>
#include "rect.h"

using namespace std;

class Score {
private:

    int num;

    double width, height;

    //position
    double x, y;



public:
    Score() = default;
    Score(int num, double x, double y, double width, double height);

    static vector<Score> calculateScore(int score, double width, double height);

    static void init(int& score);

    void draw();

};


#endif //FLAPPYBIRD_SCORE_H