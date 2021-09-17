#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

class PowerUp {
public:
    enum class type {SHIELD,SHOTGUN,DOLOL};
    PowerUp(int xPos_, int yPos_, type powerType_){
        xPos = xPos_;
        yPos = yPos_;
        powerType = powerType_;
        beginTime = time(NULL);
    }
    void refreshTime() {
        beginTime = time(NULL);
    }
    int getXPos() { return xPos; }
    int getYPos() { return yPos; }
    time_t getBeginTime() { return beginTime; }
    type getPowerType() { return powerType; }
    virtual bool isFinished() = 0;
    virtual void use() = 0;
protected:
    int xPos;
    int yPos;
    time_t beginTime;
    type powerType;
};

class Shield : public PowerUp{
public:
    Shield(int xPos_, int yPos_) : PowerUp(xPos_, yPos_, type::SHIELD) {}
    bool isFinished() {
        if(time(NULL)-beginTime>6){
            return true;
        }
        return false;
    }
    void use() {}
private:
};

class Shotgun : public PowerUp{
public:
    Shotgun(int xPos_, int yPos_) : PowerUp(xPos_, yPos_, type::SHOTGUN) {
        bulletsLeft = 3;
    }
    bool isFinished() {
        if(bulletsLeft<=0){
            return true;
        }
        return false;
    }
    void use(){
        bulletsLeft--;
    }
private:
    int bulletsLeft;
};

class Dolol : public PowerUp{
public:
    Dolol(int xPos_, int yPos_) : PowerUp(xPos_, yPos_, type::DOLOL) {
        bulletsLeft = 10;
    }
    bool isFinished() {
        if(bulletsLeft<=0){
            return true;
        }
        return false;
    }
    void use(){
        bulletsLeft--;
    }
private:
    int bulletsLeft;
};
#endif