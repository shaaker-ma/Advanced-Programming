#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <unistd.h>
#include "rsdl.hpp"
#include "tank.hpp"
#include "bullet.hpp"
#include "powerUp.hpp"
using namespace std;

#define PI 3.14159265
#define PI_IN_DEGREE 180
#define SCREEN_SIZE 720
#define WALL_LEFT_EXIST 2
#define WALL_UP_EXIST 1
#define WALL_LEFT_AND_UP_EXIST 3
#define WALL_LEFT_AND_UP_NOT_EXIST 0

class GameEngine {
public:
    GameEngine(){
            gameStarts = true;
        }
    void buildWalls(Window& window, vector<vector<int> >& allWallsStatus, int heightCell, int widthCell);
    void gameRun();
    bool gameIsOn();
    void shootTank(Tank* tank, double radius);
    void showBullets(Window& window, double radius, Tank* tankPlayer1, Tank* tankPlayer2,const vector<vector<int> >& allWallsPos);
    void createPowerUp(Tank* tankPlayer1, Tank* tankPlayer2, double radius, int row, int col, int heightCell, int widthCell, int& counter);
    void showPowerUps(Window& window, double radius);
    void tankGetPower(Tank* tankPlayer1, Tank* tankPlayer2, double radius);

private:
    bool gameStarts; //for pause
    vector<Bullet*> allBullets;
    vector<PowerUp*> allPowerUps;
};

#endif