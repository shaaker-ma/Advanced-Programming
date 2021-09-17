#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
#include <unistd.h>
#include <stdlib.h>
#include <ctime>
#include "gameEngine.hpp"
#include "powerUp.hpp"
using namespace std;

#define PI 3.14159265
#define PI_IN_DEGREE 180
#define SCREEN_SIZE 720
#define WALL_LEFT_EXIST 2
#define WALL_UP_EXIST 1
#define WALL_LEFT_AND_UP_EXIST 3
#define WALL_LEFT_AND_UP_NOT_EXIST 0
#define SQRT3 1.73

void GameEngine::tankGetPower(Tank* tankPlayer1, Tank* tankPlayer2, double radius){
    for(uint i=0; i<allPowerUps.size(); i++){
        double Tank1AndPowerDistance;
        Tank1AndPowerDistance = sqrt( (tankPlayer1->getXPos() - allPowerUps[i]->getXPos())*(tankPlayer1->getXPos() - allPowerUps[i]->getXPos())  + (tankPlayer1->getYPos() - allPowerUps[i]->getYPos() )*(tankPlayer1->getYPos() - allPowerUps[i]->getYPos() ) );
        if(Tank1AndPowerDistance < 2 * radius){
            tankPlayer1->addPower(allPowerUps[i]);
            allPowerUps.erase(allPowerUps.begin()+i);
        }
        double Tank2AndPowerDistance;
        Tank2AndPowerDistance = sqrt( (tankPlayer2->getXPos() - allPowerUps[i]->getXPos())*(tankPlayer2->getXPos() - allPowerUps[i]->getXPos())  + (tankPlayer2->getYPos() - allPowerUps[i]->getYPos() )*(tankPlayer2->getYPos() - allPowerUps[i]->getYPos() ) );
        if(Tank2AndPowerDistance < 2 * radius){
            tankPlayer2->addPower(allPowerUps[i]);
            allPowerUps.erase(allPowerUps.begin()+i);
        }
    }
}

void GameEngine::showPowerUps(Window& window, double radius){
    for(uint i=0; i<allPowerUps.size(); i++){
        if(7 <= time(NULL) - allPowerUps[i]->getBeginTime()){
            allPowerUps.erase(allPowerUps.begin()+i);
            continue;
        }
        Rectangle powerRect( Point(allPowerUps[i]->getXPos()-radius,allPowerUps[i]->getYPos()-radius), 2*radius, 2*radius);
        switch(allPowerUps[i]->getPowerType()){
            case(PowerUp::type::SHIELD):
                window.draw_img("Assets/Shield-Pickup.png",powerRect);
                break;
            case(PowerUp::type::SHOTGUN):
                window.draw_img("Assets/Shotgun-Pickup.png",powerRect);
                break;
            case(PowerUp::type::DOLOL):
                window.draw_img("Assets/DoubleBarrel-Pickup.png",powerRect);
                break;
        }
    }
}

void GameEngine::createPowerUp(Tank* tankPlayer1, Tank* tankPlayer2, double radius, int row, int col, int heightCell, int widthCell, int& counter){
    if(counter >= 3000) {
        counter=0;
        int xCellOfTank1 = floor(tankPlayer1->getXPos()/ widthCell);
        int yCellOfTank1 = floor(tankPlayer1->getYPos()/ heightCell);
        int xCellOfTank2 = floor(tankPlayer2->getXPos()/ widthCell);
        int yCellOfTank2 = floor(tankPlayer2->getYPos()/ heightCell);
        int xCell, yCell;
        do{
             xCell = rand() % col;
             yCell = rand() % row;
        }while((xCell==xCellOfTank1 && yCell == yCellOfTank1) || (xCell==xCellOfTank2 && yCell == yCellOfTank2));
        int xPosPower = widthCell*xCell + widthCell/2;
        int yPosPower = heightCell*yCell + heightCell/2;
        int rndPower = rand() % 3;
        PowerUp* newPower;
        if(rndPower == 0)
            newPower = new Shield(xPosPower,yPosPower);
        else if(rndPower == 1)
            newPower = new Shotgun(xPosPower,yPosPower);
        else if(rndPower == 2)
            newPower = new Dolol(xPosPower,yPosPower);
        allPowerUps.push_back(newPower);
    }
}

bool checkEndGame(Window& window, Tank* tankPlayer1, Tank* tankPlayer2){
    string message;
    Rectangle rectScreen(Point(0,0), Point(SCREEN_SIZE,SCREEN_SIZE)); //background screen
    if(!(tankPlayer1->getAlive())){
        message = "PLAYER 2 WINS";
        window.fill_rect(rectScreen, RGB(255,0,0));
    }
    else if(!(tankPlayer2->getAlive())){
        message = "PLAYER 1 WINS";
        window.fill_rect(rectScreen, RGB(0,255,0));
    }
    else return false;
    window.show_text(message, Point(270,360), RGB(0,0,0), "Assets/TankTrouble.ttf", 20);
    return true;
}

void GameEngine::showBullets(Window& window, double radius, Tank* tankPlayer1, Tank* tankPlayer2,const vector<vector<int> >& allWallsPos){
    for(uint i=0; i<allBullets.size(); i++){
        window.fill_circle(Point(allBullets[i]->getXPos(),allBullets[i]->getYPos()),0.1*radius,RGB(0,0,0));
        allBullets[i]->moveForward(allWallsPos, tankPlayer1, tankPlayer2, radius);
        int xPosNew = allBullets[i]->getXPos();
        int yPosNew = allBullets[i]->getYPos();
        double tank1AndBulletDistance, tank2AndBulletDistance;

        tank1AndBulletDistance = sqrt( (xPosNew - tankPlayer1->getXPos() )*(xPosNew - tankPlayer1->getXPos() )  + (yPosNew - tankPlayer1->getYPos() )*(yPosNew - tankPlayer1->getYPos() ) );
        if(tank1AndBulletDistance < radius + radius*0.1) {
            tankPlayer1->killTank();
            (allBullets[i]->getTankOfBullet())->load();
            delete allBullets[i];
            allBullets.erase(allBullets.begin()+i);
            continue;
        }
        tank2AndBulletDistance = sqrt( (xPosNew - tankPlayer2->getXPos() )*(xPosNew - tankPlayer2->getXPos() )  + (yPosNew - tankPlayer2->getYPos() )*(yPosNew - tankPlayer2->getYPos() ) );
        if(tank2AndBulletDistance < radius + radius*0.1) {
            tankPlayer2->killTank();
            (allBullets[i]->getTankOfBullet())->load();
            delete allBullets[i];
            allBullets.erase(allBullets.begin()+i);
            continue;
        }

        if(allBullets[i]->getStability() <= time(NULL) - allBullets[i]->getBeginTime()){
            (allBullets[i]->getTankOfBullet())->load();
            delete allBullets[i];
            allBullets.erase(allBullets.begin()+i);
        }
    }
}

void GameEngine::shootTank(Tank* tank, double radius){
    int bulletXPos = tank->getXPos()+ floor(1.5*cos(tank->getAngle()*PI/PI_IN_DEGREE)*(radius));
    int bulletYPos = tank->getYPos()+ floor(1.5*sin(tank->getAngle()*PI/PI_IN_DEGREE)*(radius));
    if((tank->getPower()).empty()){
        if((tank->fire())){
            Bullet* newBullet = new Bullet(bulletXPos, bulletYPos, tank->getAngle(), 5, tank, 0.5);
            allBullets.push_back(newBullet);
        }
    }
    else if(((tank->getPower()).front())->getPowerType() ==  PowerUp::type::SHIELD) {
        if((tank->fire())){
            Bullet* newBullet = new Bullet(bulletXPos, bulletYPos, tank->getAngle(), 5, tank, 0.5);
            allBullets.push_back(newBullet);
        }
    }
    else if(((tank->getPower()).front())->getPowerType() ==  PowerUp::type::SHOTGUN) {
        if((tank->fire())){
            double offset = -20;
            for(uint i=0; i<5; i++){
                Bullet* newBullet = new Bullet(bulletXPos, bulletYPos, tank->getAngle()+offset, 1, tank, 0.5*1.5);
                allBullets.push_back(newBullet);
                offset = offset +10;
            }
        }
    }
    else if(((tank->getPower()).front())->getPowerType() ==  PowerUp::type::DOLOL) {
        if((tank->fire())){
            double tankAngle = tank->getAngle();
            Bullet* newBullet1 = new Bullet(bulletXPos - 11*sin(tankAngle*PI/PI_IN_DEGREE), bulletYPos - 11*cos(tankAngle*PI/PI_IN_DEGREE), tankAngle, 3, tank, 0.5);
            Bullet* newBullet2 = new Bullet(bulletXPos + 11*sin(tankAngle*PI/PI_IN_DEGREE), bulletYPos + 11*cos(tankAngle*PI/PI_IN_DEGREE), tankAngle, 3, tank, 0.5);
            allBullets.push_back(newBullet1);
            allBullets.push_back(newBullet2);
        }
    }
}

void showTank2(Window& window, Tank* tankPlayer2, int heightCell, int widthCell){
    Rectangle tankRect( Point( (tankPlayer2->getXPos())-0.5*(widthCell/SQRT3), (tankPlayer2->getYPos())-0.5*(heightCell/SQRT3) ), widthCell/SQRT3, heightCell/SQRT3);
    if((tankPlayer2->getPower()).empty()){
        window.draw_img("Assets/Tank2-Normal.png",tankRect,NULL_RECT,tankPlayer2->getAngle());
    }
    else if(((tankPlayer2->getPower()).front())->getPowerType() ==  PowerUp::type::SHIELD) {
        window.draw_img("Assets/Tank2-Shield.png",tankRect,NULL_RECT,tankPlayer2->getAngle());
    }
    else if(((tankPlayer2->getPower()).front())->getPowerType() ==  PowerUp::type::SHOTGUN) {
        window.draw_img("Assets/Tank2-Shotgun.png",tankRect,NULL_RECT,tankPlayer2->getAngle());
    }
    else if(((tankPlayer2->getPower()).front())->getPowerType() ==  PowerUp::type::DOLOL) {
        window.draw_img("Assets/Tank2-DoubleBarrel.png",tankRect,NULL_RECT,tankPlayer2->getAngle());
    }
}

void showTank1(Window& window, Tank* tankPlayer1, int heightCell, int widthCell){ //important to know the size of tank based on row & col (S* 1/3)
    Rectangle tankRect( Point( (tankPlayer1->getXPos())-0.5*(widthCell/SQRT3), (tankPlayer1->getYPos())-0.5*(heightCell/SQRT3) ), widthCell/SQRT3, heightCell/SQRT3);
    if((tankPlayer1->getPower()).empty()){
        window.draw_img("Assets/Tank1-Normal.png",tankRect,NULL_RECT,tankPlayer1->getAngle());
    }
    else if(((tankPlayer1->getPower()).front())->getPowerType() ==  PowerUp::type::SHIELD) {
        window.draw_img("Assets/Tank1-Shield.png",tankRect,NULL_RECT,tankPlayer1->getAngle());
    }
    else if(((tankPlayer1->getPower()).front())->getPowerType() ==  PowerUp::type::SHOTGUN) {
        window.draw_img("Assets/Tank1-Shotgun.png",tankRect,NULL_RECT,tankPlayer1->getAngle());
    }
    else if(((tankPlayer1->getPower()).front())->getPowerType() ==  PowerUp::type::DOLOL) {
        window.draw_img("Assets/Tank1-DoubleBarrel.png",tankRect,NULL_RECT,tankPlayer1->getAngle());
    }
}

int makeFirstYPosTank2(int firstYCellTank2, int heightCell, int widthCell){
    int firstYPosTank2;
    firstYPosTank2 = (heightCell*firstYCellTank2)+floor(heightCell/2);
    return firstYPosTank2;
}

int makeFirstXPosTank2(int firstXCellTank2, int heightCell, int widthCell){
    int firstXPosTank2;
    firstXPosTank2 = (widthCell*firstXCellTank2)+floor(widthCell/2);
    return firstXPosTank2;
}

int makeFirstYPosTank1(int firstYCellTank1, int heightCell, int widthCell){
    int firstYPosTank1;
    firstYPosTank1 = (heightCell*firstYCellTank1)+floor(heightCell/2);
    return firstYPosTank1;
}

int makeFirstXPosTank1(int firstXCellTank1, int heightCell, int widthCell){
    int firstXPosTank1;
    firstXPosTank1 = (widthCell*firstXCellTank1)+floor(widthCell/2);
    return firstXPosTank1;
}

void GameEngine::buildWalls(Window& window, vector<vector<int> >& allWallsStatus, int heightCell, int widthCell){
    for(uint i=0; i<allWallsStatus.size(); i++){
        for(uint j=0; j<allWallsStatus[i].size(); j++){
            if(allWallsStatus[i][j] == WALL_LEFT_AND_UP_NOT_EXIST){
                continue;
            }
            else if(allWallsStatus[i][j] == WALL_UP_EXIST){
                window.draw_line(Point(j*widthCell,i*heightCell),Point((j+1)*widthCell,i*heightCell),RGB(255,0,0));
            }
            else if(allWallsStatus[i][j] == WALL_LEFT_EXIST){
                window.draw_line(Point(j*widthCell,i*heightCell),Point(j*widthCell,(i+1)*heightCell),RGB(255,0,0));
            }
            else if(allWallsStatus[i][j] == WALL_LEFT_AND_UP_EXIST){
                window.draw_line(Point(j*widthCell,i*heightCell),Point((j+1)*widthCell,i*heightCell),RGB(255,0,0));
                window.draw_line(Point(j*widthCell,i*heightCell),Point(j*widthCell,(i+1)*heightCell),RGB(255,0,0));
            }
        }
    }
    window.draw_line(Point(SCREEN_SIZE-1,0),Point(SCREEN_SIZE-1,SCREEN_SIZE-1),RGB(255,0,0));
    window.draw_line(Point(0,SCREEN_SIZE-1),Point(SCREEN_SIZE-1,SCREEN_SIZE-1),RGB(255,0,0));
}

void saveWallsPos(vector<vector<int> >&  allWallsPos, vector<vector<int> >& allWallsStatus, int heightCell, int widthCell){
    int wallQuantity=0;
    for(uint i=0; i<allWallsStatus.size(); i++){
        for(uint j=0; j<allWallsStatus[i].size(); j++){
            if(allWallsStatus[i][j] == WALL_LEFT_AND_UP_NOT_EXIST){
                continue;
            }
            else if(allWallsStatus[i][j] == WALL_UP_EXIST){
                wallQuantity = wallQuantity+1;
            }
            else if(allWallsStatus[i][j] == WALL_LEFT_EXIST){
                wallQuantity = wallQuantity+1;
            }
            else if(allWallsStatus[i][j] == WALL_LEFT_AND_UP_EXIST){
                wallQuantity = wallQuantity+2;
            }
        }
    }
    vector<int> tempWall;
        for(uint i=0; i<allWallsStatus.size(); i++){
            for(uint j=0; j<allWallsStatus[i].size(); j++){
                if(allWallsStatus[i][j] == WALL_LEFT_AND_UP_NOT_EXIST){
                    continue;
                }
                else if(allWallsStatus[i][j] == WALL_UP_EXIST){
                    tempWall.push_back(j*widthCell);
                    tempWall.push_back(i*heightCell);
                    tempWall.push_back((j+1)*widthCell);
                    tempWall.push_back(i*heightCell);
                    allWallsPos.push_back(tempWall);
                    tempWall.clear();
                }
                else if(allWallsStatus[i][j] == WALL_LEFT_EXIST){
                    tempWall.push_back(j*widthCell);
                    tempWall.push_back(i*heightCell);
                    tempWall.push_back(j*widthCell);
                    tempWall.push_back((i+1)*heightCell);
                    allWallsPos.push_back(tempWall);
                    tempWall.clear();
                }
                else if(allWallsStatus[i][j] == WALL_LEFT_AND_UP_EXIST){
                    tempWall.push_back(j*widthCell);
                    tempWall.push_back(i*heightCell);
                    tempWall.push_back((j+1)*widthCell);
                    tempWall.push_back(i*heightCell);
                    allWallsPos.push_back(tempWall);
                    tempWall.clear();
                    tempWall.push_back(j*widthCell);
                    tempWall.push_back(i*heightCell);
                    tempWall.push_back(j*widthCell);
                    tempWall.push_back((i+1)*heightCell);
                    allWallsPos.push_back(tempWall);
                    tempWall.clear();
                }
            }
        }
    tempWall.push_back(SCREEN_SIZE);
    tempWall.push_back(0);
    tempWall.push_back(SCREEN_SIZE);
    tempWall.push_back(SCREEN_SIZE);
    allWallsPos.push_back(tempWall);
    tempWall.clear();
    tempWall.push_back(0);
    tempWall.push_back(SCREEN_SIZE);
    tempWall.push_back(SCREEN_SIZE);
    tempWall.push_back(SCREEN_SIZE);
    allWallsPos.push_back(tempWall);
    tempWall.clear();
}

void buildAllWallsStatus(vector<vector<int> >& allWallsStatus, int row, int col){
    vector<int> eachwallsReverse;
    vector<int> eachwall;
    int state,last;
    for(uint i=0; i<row; i++){
        cin >> state;
        while (state != 0) {
            last = state % 10;
            eachwallsReverse.push_back(last);
            state = (state - last) / 10;
        }
        for(uint l=0; l<eachwallsReverse.size(); l++)
    	    eachwall.push_back(eachwallsReverse[eachwallsReverse.size()-1-l]);
        allWallsStatus.push_back(eachwall);
        eachwallsReverse.clear();
        eachwall.clear();
    }
}

void GameEngine::gameRun() {
    int col,row, wallStatus, counter=0;
    cin >> row >> col;
    int heightCell,widthCell;
    heightCell = floor(SCREEN_SIZE/row);
    widthCell = floor(SCREEN_SIZE/col);

    vector<vector<int> > allWallsStatus;
    vector<vector<int> > allWallsPos;
    buildAllWallsStatus(allWallsStatus,row,col);
    saveWallsPos(allWallsPos, allWallsStatus, heightCell, widthCell);

    int firstXCellTank1,firstYCellTank1,firstXCellTank2,firstYCellTank2;
    cin >> firstXCellTank1 >> firstYCellTank1 >> firstXCellTank2 >> firstYCellTank2;
    int firstXPosTank1,firstYPosTank1,firstXPosTank2,firstYPosTank2;
    firstXPosTank1 = makeFirstXPosTank1(firstXCellTank1, heightCell, widthCell);
    firstYPosTank1 = makeFirstYPosTank1(firstYCellTank1, heightCell, widthCell);
    firstXPosTank2 = makeFirstXPosTank2(firstXCellTank2, heightCell, widthCell);
    firstYPosTank2 = makeFirstYPosTank2(firstYCellTank2, heightCell, widthCell);
    
    Tank* tankPlayer1 = new Tank(firstXPosTank1, firstYPosTank1, 0);
    Tank* tankPlayer2 = new Tank(firstXPosTank2, firstYPosTank2, 0);
    double radius = min(0.5*(widthCell/SQRT3),0.5*(heightCell/SQRT3));

    Window window(SCREEN_SIZE,SCREEN_SIZE,"$Truble Tank$");
    Rectangle rectScreen(Point(0,0), Point(SCREEN_SIZE,SCREEN_SIZE));

    while(true){
        counter++;
        window.fill_rect(rectScreen, RGB(255,255,255));
        buildWalls(window, allWallsStatus, heightCell, widthCell);
        showTank1(window, tankPlayer1, heightCell, widthCell);
        showTank2(window, tankPlayer2, heightCell, widthCell);
        showBullets(window, radius, tankPlayer1, tankPlayer2, allWallsPos);
        createPowerUp(tankPlayer1, tankPlayer2, radius, row, col, heightCell, widthCell, counter);
        showPowerUps(window, radius);
        tankGetPower(tankPlayer1, tankPlayer2, radius);
        tankPlayer1->checkExpired();
        tankPlayer2->checkExpired();
        if (window.has_pending_event()) {
			Event event = window.poll_for_event();
                switch (event.get_pressed_key()) {
                    case 'i':
                    case 'I':
                        tankPlayer1->moveForward(allWallsPos, tankPlayer2 , radius);
                        break;
                    case 'j':
                    case 'J':
                        tankPlayer1->rollCW();
                        break;
                    case 'k':
                    case 'K':
                        tankPlayer1->moveBackward(allWallsPos, tankPlayer2, radius);
                        break;
                    case 'l':
                    case 'L':
                        tankPlayer1->rollCCW();
                        break;
                    case 'u':
                    case 'U':
                        shootTank(tankPlayer1, radius);
                        break;
                    case 'w':
                    case 'W':
                        tankPlayer2->moveForward(allWallsPos, tankPlayer1, radius);
                        break;
                    case 'a':
                    case 'A':
                        tankPlayer2->rollCW();
                        break;
                    case 's':
                    case 'S':
                        tankPlayer2->moveBackward(allWallsPos, tankPlayer1, radius);
                        break;
                    case 'd':
                    case 'D':
                        tankPlayer2->rollCCW();
                        break;
                    case 'q':
                    case 'Q':
                        shootTank(tankPlayer2, radius);
                        break;
                }
		}
        if(checkEndGame(window, tankPlayer1, tankPlayer2)){
            window.update_screen();
            usleep(5000000);
            exit(1);
        }
        window.update_screen();
        usleep(2500);
    }
}
    bool GameEngine::gameIsOn(){
        return gameStarts ;
}