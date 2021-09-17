#ifndef __TANK_H__
#define __TANK_H__

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include "powerUp.hpp"
using namespace std;

#define PI 3.14159265
#define PI_IN_DEGREE 180

enum State {SHIELD,SHOTGUN,DOLOL};
class Tank {
public:
    Tank(int xPos_, int yPos_, double angle_){
        xPos = xPos_;
        yPos = yPos_;
        angle = angle_;
        bulletsLeft = 5;
        alive = true;
        sheildOn = false;
        shotgunBullet = false;
        dololBullet = false;
    }
    bool moveForwardValid(vector<vector<int> > allWallsPos, Tank* otheTank, double radius);
    void moveForward(vector<vector<int> > allWallsPos, Tank* otherTank, double radius){
        if(moveForwardValid(allWallsPos, otherTank, radius)){
            xPos = xPos + floor(7*cos(angle*PI/PI_IN_DEGREE));
            yPos = yPos + floor(7*sin(angle*PI/PI_IN_DEGREE));            
        }
    }
    bool moveBackwardValid(vector<vector<int> > allWallsPos, Tank* otheTank, double radius);
    void moveBackward(vector<vector<int> > allWallsPos, Tank* otherTank , double radius){
        if(moveBackwardValid(allWallsPos, otherTank, radius)){
            xPos = xPos - floor(7*cos(angle*PI/PI_IN_DEGREE));
            yPos = yPos - floor(7*sin(angle*PI/PI_IN_DEGREE));   
        }
    }
    void rollCW(){ angle = angle - 7.5; }
    void rollCCW(){ angle = angle + 7.5; }
    int getXPos() { return xPos;}
    int getYPos() { return yPos;}
    double getAngle() { return angle;}
    bool getAlive() { return alive; }
    bool fire() {
        if(bulletsLeft > 0){
            bulletsLeft--;
            if(shotgunBullet || dololBullet) (power.front())->use();
            return true;
        }
        return false;
    }
    void load() {
        if (bulletsLeft < 5)
            bulletsLeft++;
    }
    void killTank() { 
        if(!sheildOn)
            alive = false;
     }
    void checkExpired(){
        if(power.empty())
            return;
        if(power.front()->isFinished()){
            delete power.front();
            power.pop();
        }
        checkPower();
    }
    queue<PowerUp*> getPower() { return power;}
    void addPower(PowerUp* newPower) {
        power.push(newPower); 
        newPower->refreshTime();
        checkPower();
    }

private:
    void checkPower() {
        sheildOn = false;
        shotgunBullet = false;
        dololBullet = false;
        if(power.empty()){
            return;
        }
        else{
            switch(power.front()->getPowerType()){
                case(PowerUp::type::SHIELD) :
                    sheildOn = true;
                    break;
                case(PowerUp::type::SHOTGUN) :
                    shotgunBullet = true;
                    break;
                case(PowerUp::type::DOLOL) :
                    dololBullet = true;
                    break;
            }
        }
    }
    int xPos;
    int yPos;
    double angle;
    int bulletsLeft;
    bool alive;
    bool sheildOn;
    bool shotgunBullet;
    bool dololBullet;
    queue<PowerUp*> power;

};

#endif