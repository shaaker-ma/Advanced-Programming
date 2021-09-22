#ifndef __USER_H__
#define __USER_H__

#include <vector>
#include <iostream>
#include <string>
using namespace std ;
#include "offer.hpp"
#include "cart.hpp"

class User {
public:
	User(string userMail, string userUserName, string userPassword , int userUserId , string userType) {
		mail = userMail;
		userName = userUserName;
		password = userPassword;
		userId = userUserId;
		type = userType;
	}
	string getMail() { return mail; }
	string getUserName() { return userName; }
	string getPassword() { return password; }
	int getUserId() { return userId; }
	string getType() { return type; }
protected:
	string mail;
	string userName;
	string password;
	int userId;
	string type; //admin , seller , buyer
};

class Admin : public User {
public:
	Admin(string userMail, string userUserName, string userPassword , int userUserId , string userType) : User(userMail,userUserName,userPassword,userUserId,userType) {}
private:
	
};

class Buyer : public User {
public:
	Buyer(string userMail, string userUserName, string userPassword , int userUserId , string userType) : User(userMail,userUserName,userPassword,userUserId,userType) {
		buyerWallet.push_back(0);
	}
	void addToBuyerWallet(float money){
		buyerWallet.push_back(money);
	}
	void addToBuyerCart(Cart* newCart){
		buyerCart.push_back(newCart);
	}
	void addToStarPrint(int decide){
		starPrint.push_back(decide);
	}
	vector<int> getStarPrint() { return starPrint;}
	vector<float> getBuyerWallet() { return buyerWallet; }
	vector<Cart*> getBuyerCart() {return buyerCart; }
private:
	vector<float>  buyerWallet;
	vector<Cart*> buyerCart;
	vector<int> starPrint;
};

class Seller : public User {
public:
	Seller(string userMail, string userUserName, string userPassword , int userUserId , string userType) : User(userMail,userUserName,userPassword,userUserId,userType) {
		sellerWallet.push_back(0);
	}
	vector<Offer*> getSellerOffers() { return sellerOffers; }
	vector<float> getSellerWallet() { return sellerWallet; }
	void addTosellerOffers(Offer* newOffer){
		sellerOffers.push_back(newOffer);
	}
	void addToSellerWallet(float money){
		sellerWallet.push_back(money);
	}
private:
	vector<Offer*> sellerOffers;
	vector<float>  sellerWallet;
};

#endif