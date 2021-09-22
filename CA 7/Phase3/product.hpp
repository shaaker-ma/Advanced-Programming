#ifndef __PRODUCTS_H__
#define __PRODUCTS_H__

#include <iostream>
#include <vector>
#include <string>
#include "user.hpp"

using namespace std ;

class Product {
public:
	Product(string productName_, int productId_, string type_) {
		productName = productName_;
		productId = productId_;
		type = type_;
	}
	string getProductName(){ return productName; }
	int getProductId(){ return productId; }
	vector<string> getAllComments(){ return allComments; }
	string getType() { return type; }
	void addToAllComments(string namePlusComment){
		allComments.push_back(namePlusComment);
	}
protected:
	string productName;
	int productId;
	vector<string> allComments;
	string type;
};

class Mobile : public Product {
public:
	Mobile(string productName_, int productId_, string type_, float weight_, float CPUFrequency_, float builtInMemory_, float RAM_, float displaySize_, float cameraResolution_,string OS_) : Product(productName_,productId_,type_) {
		weight = weight_;
		CPUFrequency = CPUFrequency_;
		builtInMemory = builtInMemory_;
		RAM = RAM_;
		displaySize = displaySize_;
		cameraResolution = cameraResolution_;
		OS = OS_;
	}
	float getWeight() { return weight; }
	float getCPUFrequency() { return CPUFrequency; }
	float getBuiltInMemory() { return builtInMemory; }
	float getRAM() { return RAM; }
	float getDisplaySize() { return displaySize; }
	float getCameraResolution() { return cameraResolution; }
	string getOS() {return OS;}
private:
	float weight;
	float CPUFrequency;
	float builtInMemory;
	float RAM;
	float displaySize;
	float cameraResolution;
	string OS;
};

class Tv : public Product {
public:
	Tv(string productName_, int productId_, string type_, float screenSize_, string screenType_, string resolution_, bool threeD_, bool HDR_) : Product(productName_,productId_,type_){
		screenSize = screenSize_;
		screenType = screenType_;
		resolution = resolution_;
		threeD = threeD_;
		HDR = HDR_;
	}
	float getScreenSize() { return screenSize; }
	string getScreenType() { return screenType;}
	string getResolution() { return resolution;}
	bool getThreeD() { return threeD; }
	bool getHDR() { return HDR; }
private:
	float screenSize;
	string screenType;
	string resolution;
	bool threeD;
	bool HDR;
};

class Car : public Product {
public:
	Car(string productName_, int productId_, string type_, float weight_, int seatsNum_, int cylindersNum_, float engineCapacity_, bool reverseParkingSensor_) : Product(productName_,productId_,type_) {
		weight = weight_;
		seatsNum = seatsNum_;
		cylindersNum = cylindersNum_;
		engineCapacity = engineCapacity_;
		reverseParkingSensor = reverseParkingSensor_;
	}
	float getWeight() { return weight; }
	int getSeatsNum() { return seatsNum; }
	int getCylindersNum() { return cylindersNum; }
	float getEngineCapacity() { return engineCapacity; }
	bool getReverseParkingSensor() { return reverseParkingSensor; }
private:
	float weight;
	int seatsNum;
	int cylindersNum;
	float engineCapacity;
	bool reverseParkingSensor;
};


#endif