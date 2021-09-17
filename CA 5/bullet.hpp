#ifndef __BULLET_H__
#define __BULLET_H__

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <ctime>
#include "tank.hpp"
using namespace std;

#define PI 3.14159265
#define PI_IN_DEGREE 180

class Bullet{
public:
    Bullet(int xPos_, int yPos_, double angle_, double stability_, Tank* tank, double speed_){
        xPos = xPos_;
        yPos = yPos_;
        angle = angle_;
        speed = speed_;
        beginTime = time(NULL);
        stability = stability_;
        tankOfBullet = tank;
    }
    void moveForward(const vector<vector<int> >& allWallsPos, Tank* tankPlayer1, Tank* tankPlayer2, double radius);
    int getXPos() { return xPos; }
    int getYPos() { return yPos; }
    Tank* getTankOfBullet() { return tankOfBullet; }
    time_t getBeginTime() { return beginTime; }
    double getStability() { return stability; }
private:
    int xPos;
    int yPos;
    double angle;
    double speed;
    time_t beginTime;
    double stability;
    Tank* tankOfBullet;
};

#endif