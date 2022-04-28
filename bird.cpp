//
// Created by Alexander Townsend on 4/20/21.
//
#include "graphics.h"
#include "bird.h"
#include <cmath>
#include <vector>


Bird::Bird(){
    parts=starter;
    isAlive=true;
}

void Bird::reset() {
    angle=-20/180*3.1415926535;
}

void Bird::draw() {
    for(Rect &r : parts){
        Rect temp = Rect(r);
        point2D o = r.getCenter();
        double d=sqrt(o.x*o.x+o.y*o.y);
        double a1=acos(o.x/d);
        double a2=asin(-o.y/d);
        if(o.x<0 && o.y>0){
            a1+=angle;
            a2+=angle;
        }else if(o.x>0 && o.y>0) {
            a1 += angle;
            a2 -= angle;
        }else if(o.x>0 && o.y<0) {
            a1 -= angle;
            a2 -= angle;
        }else if(o.x<0 && o.y<0) {
            a1 -= angle;
            a2 += angle;
        }
        temp.setCenter(cos(a1)*d, -sin(a2)*d);
        temp.move(center.x,center.y);
        temp.draw(-angle);
    }

    int wingType = wing/4;
    if(wingType==3){
        wingType=1;
    }

    if(!isAlive){
        wingType=0;
    }

    for(Rect &r : wings[wingType]){
        Rect temp = Rect(r);
        point2D o = r.getCenter();
        double d=sqrt(o.x*o.x+o.y*o.y);
        double a1=acos(o.x/d);
        double a2=asin(-o.y/d);
        if(o.x<0 && o.y>0){
            a1+=angle;
            a2+=angle;
        }else if(o.x>0 && o.y>0) {
            a1 += angle;
            a2 -= angle;
        }else if(o.x>0 && o.y<0) {
            a1 -= angle;
            a2 -= angle;
        }else if(o.x<0 && o.y<0) {
            a1 -= angle;
            a2 += angle;
        }
        temp.setCenter(cos(a1)*d, -sin(a2)*d);
        temp.move(center.x,center.y);
        temp.draw(-angle);
    }

    for(int i=0;i<checkPoints.size();i++){
        point2D o = checkPoints[i];
        double d = sqrt(o.x * o.x + o.y * o.y);
        double a1 = acos(o.x / d);
        double a2 = asin(-o.y / d);
        if(o.x<0 && o.y>0){
            a1+=angle;
            a2+=angle;
        }else if(o.x>0 && o.y>0) {
            a1 += angle;
            a2 -= angle;
        }else if(o.x>0 && o.y<0) {
            a1 -= angle;
            a2 -= angle;
        }else if(o.x<0 && o.y<0) {
            a1 -= angle;
            a2 += angle;
        }
        toCheck[i]=point2D(cos(a1)*d+center.x, ((-sin(a2)*d+center.y<0)?5:-sin(a2)*d+center.y));
    }

}

void Bird::setAngle(double a) {
    angle=a;
}

vector<point2D> Bird::getCheck() {
    return toCheck;
}

void Bird::hop() {
    jump=1;
}

void Bird::update(){
    if(jump<=0 && jump>=-5 && isAlive) {
        center.y += (jump/10);
        jump-=0.1;
    }else if(jump<-5 && jump>=-11 && isAlive) {
        center.y += (-4 - jump)/10;
        jump-=0.1;
    }else if(jump<-10 && isAlive){
        jump=-0.1;
    }else if(jump>0 && jump<=13){
        center.y-=(7-jump)*2;
        jump+=1;
        angle=(-20.0/180*3.1415926535);
    }else if(jump>13){
        center.y+=jump;
        jump+=1;
        if(jump>14 && angle<3.1415926535/2 && center.y<480){
            angle+=0.15;
        }
    }

    if(center.y>480){
        center.y=480;
        die();
    }
    wing=(wing+1)%12;
}

void Bird::die() {
    isAlive=false;
}

bool Bird::isDead() {
    if(isAlive){
        return false;
    }
    return true;
}