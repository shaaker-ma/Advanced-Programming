#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <ctime>
#include "bullet.hpp"
using namespace std;

#define PI 3.14159265
#define PI_IN_DEGREE 180

void Bullet::moveForward(const vector<vector<int> >& allWallsPos, Tank* tankPlayer1, Tank* tankPlayer2, double radius){
    int xPosNew = xPos + floor(speed*5*cos(angle*PI/PI_IN_DEGREE));
    int yPosNew = yPos + floor(speed*5*sin(angle*PI/PI_IN_DEGREE));
    for(int i=0; i<allWallsPos.size(); i++){
        if(xPosNew> allWallsPos[i][0]-radius*0.1 && xPosNew < allWallsPos[i][2]+radius*0.1 && yPosNew> allWallsPos[i][1]-radius*0.1 && yPosNew < allWallsPos[i][3]+radius*0.1){
            if(allWallsPos[i][0] == allWallsPos[i][2]){
                angle = 180 - angle;
            }
            if(allWallsPos[i][1] == allWallsPos[i][3]){
                angle = -1*angle;
            }
            break;
        }
    }
    xPos = xPos + floor(speed*5*cos(angle*PI/PI_IN_DEGREE));
    yPos = yPos + floor(speed*5*sin(angle*PI/PI_IN_DEGREE));
}