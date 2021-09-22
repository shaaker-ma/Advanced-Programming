#ifndef __ManageMarket_H__
#define __ManageMarket_H__

#include <vector>
#include <iostream>
#include <string>
#include <random>
using namespace std ;

#include "product.hpp"
#include "user.hpp"
#include "offer.hpp"
#include "exceptions.hpp"
#include "cart.hpp"

class ManageMarket{
public:
	ManageMarket() {
		//motmaeen nistam vase admin!!!
		User* newUser = new Admin("admin@gmail.com","admin","admin",0,"admin");
		onlineUser = newUser;
		allUsers.push_back(newUser);
		countUserId =0;
		countProductId=0;
		countOfferId=0;
	}
	void manageCommands(string command);	
private:
	void printCompare(vector<string> commandVec);
	bool productsAreSameType(vector<string> commandVec);
	bool IdFoundForCompare(vector<string> commandVec);
	bool validCommandForCompare(vector<string> commandVec);
	void addCommentToProduct(vector<string> commandVec);
	bool IdFoundForComment(vector<string> commandVec);
	bool validCommandForComment(vector<string> commandVec);
	void chargeWalletOfBuyer(vector<string> commandVec);
	bool validAmountForChargeWallet(vector<string> commandVec);
	bool validCommandForChargeWallet(vector<string> commandVec);
	void printBuyerWallet(vector<string> commandVec);
	bool validCommandForBuyerWallet(vector<string> commandVec);

	void printBuyerOrders(vector<string> commandVec);
	bool validCommandForBuyerOrders(vector<string> commandVec);
	void submitCart();
	bool enoughMoney();
	bool validCommandForSubmitCart(vector<string> commandVec);
	void printOnlineUserCart();
	bool validCommandForCartOnlineUser(vector<string> commandVec);
	void AddToCartWithDiscount(vector<string> commandVec);
	bool validAmountForAddToCart(vector<string> commandVec);
	bool validDiscountCode(vector<string> commandVec);
	void AddToCartWithoutDiscount(vector<string> commandVec);
	bool validCommandForAddToCart(vector<string> commandVec);
	bool printCommentsOnProduct(vector<string> commandVec);
	bool IdFoundForComments(vector<string> commandVec);
	bool validCommandForComments(vector<string> commandVec);
	void printProductDetail(vector<string> commandVec);
	bool validCommandForProductDetail(vector<string> commandVec);
	void printOffersOnProduct(vector<string> commandVec);
	bool validCommandForOffersOnProduct(vector<string> commandVec);
	string random_string(std::size_t length);
	void generateDiscountCode(vector<string> commandVec);
	bool validCommandForGenerateDiscountCode(vector<string> commandVec);
	void printSellerWallet(vector<string> commandVec);
	bool validCommandForWalletSeller(vector<string> commandVec);
	void makeChangeOffer(vector<string> commandVec);
	bool validCommandForChangeOffer(vector<string> commandVec);
	void printMyOffers();
	bool validCommandForMyOffers(vector<string> commandVec);
	void makeOffer(vector<string> commandVec);
	bool firstTimeOffer(vector<string> commandVec);
	bool productIdExists(vector<string> commandVec);
	bool validCommandForOffer(vector<string> commandVec);
	void printProducts();
	bool userIsBuyer();
	bool userIsSeller();
	bool validCommandForGetProducts(vector<string> commandVec);
	void printOffersByAdmin(vector<string> commandVec);
	bool validCommandForOffers(vector<string> commandVec);
	void importProducts(string productType, vector<vector<string> > datas);
	vector<vector<string> > putDataIn2D(vector<string> commandVec);
	bool fileExists(vector<string> commandVec);
	bool userIsAdmin();
	bool validCommandForImportProducts(vector<string> commandVec);
	bool validCommandForLogout(vector<string> commandVec);
	User* findUser(vector<string> commandVec);
	bool correctUserPass(vector<string> commandVec);
	bool validCommandForLogin(vector<string> commandVec);
	bool userExists(string userName);
	bool validCommandForSignup(vector<string> commandVec);
	string decideOperation(vector<string> commandVec);
	vector<string> splitString(string str, char delim, vector<string> out);
	void printOffersByBuyer(vector<string> commandVec);
	void generateDiscountCodeWordHasher(vector<string> commandVec);
	User* onlineUser;
	int countUserId;
	int countProductId;
	int countOfferId;
	vector<string> carFeatures;
	vector<string> tvFeatures;
	vector<string> mobiileFeatures;
	vector<Product*> allProducts;
	vector<User*> allUsers;
	vector<Offer*> allOffers;
	vector<Cart*> onlineUserCart;
};


#endif