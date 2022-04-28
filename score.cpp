//
// Created by Sean on 4/23/2021.
//

#include "score.h"
#include <iostream>

Score::Score(int num, double x, double y,
             double width, double height) : num(num), x(x), y(y),
                                            width(width), height(height) {

}

void Score::init(int& score) {
    score = 0;
}

vector<Score> Score::calculateScore(int score, double width, double height) {
    vector<Score> scoreVec;
    vector<uint16_t> digits;
    int scoreTmp = score;
    while (scoreTmp > 0) {
        int digit = scoreTmp % 10;
        scoreTmp /= 10;
        digits.push_back(digit);
    }
    int offset = 0;
    int gap = 10;
    if (digits.size() > 1) {
        //gross corner-casing -- need to fix
        if (digits.size() % 2 == 0) {
            offset -= ((digits.size() * 40) / 2) + gap / 2;
        } else
            offset -= ((digits.size() * 40) / 2) + 20 + gap;
    } else {
        Score tmp(score, width / 2, height / 4, 40, 80);
        scoreVec.push_back(tmp);
    }
    for (int i = digits.size() - 1; i >= 0; i--) {
        //somehow left-skewed
        Score tmp(digits.at(i), (width / 2) + offset, height / 4, 40, 80);
        scoreVec.push_back(tmp);
        offset += 40 + gap;
    }
    while (!digits.empty()) {
        digits.pop_back();
        offset = 0;
    }
    return scoreVec;
}

void Score::draw() {
    Rect topSeg ({1, 1, 1},
                 x,
                 y - 2*(height/6),
                 {width, height/6});
    Rect midSeg ({1, 1, 1},
                 x,
                 y,
                 {width, height/6});
    Rect botSeg ({1, 1, 1},
                 x,
                 y + 2*(height/6),
                 {width, height/6});
    Rect topRSeg ({1, 1, 1},
                  x + 1*(height/6),
                  y - 1*(height/6),
                  {height/6, width});
    Rect botRSeg ({1, 1, 1},
                  x + 1*(height/6),
                  y + 1*(height/6),
                  {height/6, width});
    Rect topLSeg ({1, 1, 1},
                  x - 1*(height/6),
                  y - 1*(height/6),
                  {height/6, width});
    Rect botLSeg ({1, 1, 1},
                  x - 1*(height/6),
                  y + 1*(height/6),
                  {height/6, width});

    if (num == 0) {
        topSeg.draw();
        topLSeg.draw();
        topRSeg.draw();
        botLSeg.draw();
        botRSeg.draw();
        botSeg.draw();
    }
    else if (num == 1) {
        Rect specialSeg1 ({1, 1, 1},
                          x - width/3,
                          y - 2*(height/6),
                          {width/3, height/6});
        Rect specialSeg2 ({1, 1, 1},
                          x,
                          y,
                          {height/6, width + 2*(height/6)});
        specialSeg1.draw();
        specialSeg2.draw();
    }
    else if (num == 2) {
        topSeg.draw();
        topRSeg.draw();
        midSeg.draw();
        botLSeg.draw();
        botSeg.draw();
    }
    else if (num == 3) {
        topSeg.draw();
        topRSeg.draw();
        midSeg.draw();
        botRSeg.draw();
        botSeg.draw();
    }
    else if (num == 4) {
        topLSeg.draw();
        topRSeg.draw();
        midSeg.draw();
        botRSeg.draw();
    }
    else if (num == 5) {
        topSeg.draw();
        topLSeg.draw();
        midSeg.draw();
        botRSeg.draw();
        botSeg.draw();
    }
    else if (num == 6) {
        topSeg.draw();
        topLSeg.draw();
        midSeg.draw();
        botLSeg.draw();
        botRSeg.draw();
        botSeg.draw();
    }
    else if (num == 7) {
        topSeg.draw();
        topRSeg.draw();
        botRSeg.draw();
    }
    else if (num == 8) {
        topSeg.draw();
        topLSeg.draw();
        topRSeg.draw();
        midSeg.draw();
        botLSeg.draw();
        botRSeg.draw();
        botSeg.draw();
    }
    else if (num == 9) {
        topSeg.draw();
        topLSeg.draw();
        topRSeg.draw();
        midSeg.draw();
        botRSeg.draw();
        botSeg.draw();
    }
}
