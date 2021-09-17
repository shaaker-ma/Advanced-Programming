#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
#include <unistd.h>
#include "tank.hpp"
using namespace std;

bool Tank::moveForwardValid(vector<vector<int> > allWallsPos, Tank* otheTank , double radius){
    int xPosNew = xPos + floor(7*cos(angle*PI/PI_IN_DEGREE));
    int yPosNew = yPos + floor(7*sin(angle*PI/PI_IN_DEGREE));
    for(int i=0; i<allWallsPos.size(); i++){
        if(xPosNew> allWallsPos[i][0]-radius && xPosNew < allWallsPos[i][2]+radius && yPosNew> allWallsPos[i][1]-radius && yPosNew < allWallsPos[i][3]+radius)
            return false;
    }
    double TanksDistance;
    TanksDistance = sqrt( (xPosNew - otheTank->getXPos() )*(xPosNew - otheTank->getXPos() )  + (yPosNew - otheTank->getYPos() )*(yPosNew - otheTank->getYPos() ) );
    if(TanksDistance < 2 * radius) return false;
    return true;
}

bool Tank::moveBackwardValid(vector<vector<int> > allWallsPos, Tank* otheTank, double radius){
    int xPosNew = xPos - floor(7*cos(angle*PI/PI_IN_DEGREE));
    int yPosNew = yPos - floor(7*sin(angle*PI/PI_IN_DEGREE));
    for(int i=0; i<allWallsPos.size(); i++){
        if(xPosNew> allWallsPos[i][0]-radius && xPosNew < allWallsPos[i][2]+radius && yPosNew> allWallsPos[i][1]-radius && yPosNew < allWallsPos[i][3]+radius)
            return false;
    }
    double TanksDistance;
    TanksDistance = sqrt( (xPosNew - otheTank->getXPos() )*(xPosNew - otheTank->getXPos() )  + (yPosNew - otheTank->getYPos() )*(yPosNew - otheTank->getYPos() ) );
    if(TanksDistance < 2 * radius) return false;
    return true;
}