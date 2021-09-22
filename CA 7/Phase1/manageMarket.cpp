#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std ;

#include "manageMarket.hpp"
#define SPLITOFTXT ' '
#define SPLITOFCSV ','
#define SUFFIX ".csv"

vector<string> ManageMarket::splitString(string str, char delim, vector<string> out){
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
	return out;
}

void ManageMarket::printCompare(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	int productId2 = stoi(commandVec[6]);
	string type; 
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			type = allProducts[i]->getType();
			for(int j=0; j < allProducts.size(); j++){
				if(allProducts[j]->getProductId() == productId2){
					cout << allProducts[i]->getProductName() << " | " << allProducts[j]->getProductName() << endl;

					if(type == "car"){
						cout << carFeatures[1] << ": " << ((Car*)allProducts[i])->getWeight() << " | " << ((Car*)allProducts[j])->getWeight() << endl;
						cout << carFeatures[2] << ": " << ((Car*)allProducts[i])->getSeatsNum() << " | " << ((Car*)allProducts[j])->getSeatsNum() << endl;
						cout << carFeatures[3] << ": " << ((Car*)allProducts[i])->getCylindersNum() << " | " << ((Car*)allProducts[j])->getCylindersNum() << endl;
						cout << carFeatures[4] << ": " << ((Car*)allProducts[i])->getEngineCapacity() << " | " << ((Car*)allProducts[j])->getEngineCapacity() << endl;
						cout << carFeatures[5] << ": " << ((Car*)allProducts[i])->getReverseParkingSensor() << " | " << ((Car*)allProducts[j])->getReverseParkingSensor() << endl;
					}
					else if(type == "tv"){
						cout << tvFeatures[1] << ": " << ((Tv*)allProducts[i])->getScreenSize() << " | " << ((Tv*)allProducts[j])->getScreenSize() <<  endl;
						cout << tvFeatures[2] << ": " << ((Tv*)allProducts[i])->getScreenType() << " | " << ((Tv*)allProducts[j])->getScreenType() <<  endl;
						cout << tvFeatures[3] << ": " << ((Tv*)allProducts[i])->getResolution() << " | " << ((Tv*)allProducts[j])->getResolution() <<  endl;
						cout << tvFeatures[4] << ": " << ((Tv*)allProducts[i])->getThreeD() << " | " << ((Tv*)allProducts[j])->getThreeD() <<  endl;
						cout << tvFeatures[5] << ": " << ((Tv*)allProducts[i])->getHDR() << " | " << ((Tv*)allProducts[j])->getHDR() <<  endl;
					}
					else if(type == "mobile"){
						cout << mobiileFeatures[1] << ": " << ((Mobile*)allProducts[i])->getWeight() << " | " << ((Mobile*)allProducts[j])->getWeight() << endl;
						cout << mobiileFeatures[2] << ": " << ((Mobile*)allProducts[i])->getCPUFrequency() << " | " << ((Mobile*)allProducts[j])->getCPUFrequency() << endl;
						cout << mobiileFeatures[3] << ": " << ((Mobile*)allProducts[i])->getBuiltInMemory() << " | " << ((Mobile*)allProducts[j])->getBuiltInMemory() << endl;
						cout << mobiileFeatures[4] << ": " << ((Mobile*)allProducts[i])->getRAM() << " | " << ((Mobile*)allProducts[j])->getRAM() << endl;
						cout << mobiileFeatures[5] << ": " << ((Mobile*)allProducts[i])->getDisplaySize() << " | " << ((Mobile*)allProducts[j])->getDisplaySize() << endl;
						cout << mobiileFeatures[6] << ": " << ((Mobile*)allProducts[i])->getCameraResolution() << " | " << ((Mobile*)allProducts[j])->getCameraResolution() << endl;
						cout << mobiileFeatures[7] << ": " << ((Mobile*)allProducts[i])->getOS() << " | " << ((Mobile*)allProducts[j])->getOS() << endl;
					}
					break;
				}
			}
		}
	}
}

bool ManageMarket::productsAreSameType(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	int productId2 = stoi(commandVec[6]);
	string type1;
	string type2;
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			type1 = allProducts[i]->getType();
			for(int j=0; j < allProducts.size(); j++){
				if(allProducts[j]->getProductId() == productId2){
					type2 = allProducts[j]->getType();
					if(type1 == type2) return true;
				}
			}
		}
	}
	return false;
}

bool ManageMarket::IdFoundForCompare(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	int productId2 = stoi(commandVec[6]);
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			for(int j=0; j < allProducts.size(); j++){
				if(allProducts[j]->getProductId() == productId2){
					return true;
				}
			}
		}
	}
	return false;
}

bool ManageMarket::validCommandForCompare(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="compare" && 
		commandVec[2] == "?" && commandVec[3] == "productId1" && commandVec[5] == "productId2") return true;
	return false;
}

void ManageMarket::addCommentToProduct(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			string name = onlineUser->getUserName();
			string comment;
			for(int j=6; j<commandVec.size(); j++){
				comment = comment + commandVec[j] + " " ;
			}
			comment.pop_back(); //to remove the last space
			string namePlusComment = name + " | " + comment;
			allProducts[i]->addToAllComments(namePlusComment);
		}
	}
}

bool ManageMarket::IdFoundForComment(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			return true;
		}
	}
	return false;
}

bool ManageMarket::validCommandForComment(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="comment" && 
		commandVec[2] == "?" && commandVec[3] == "productId" && commandVec[5] == "comment") return true;
	return false;
}

void ManageMarket::chargeWalletOfBuyer(vector<string> commandVec){
	float amoutOfMoney = stof(commandVec[4]);
	((Buyer*)onlineUser)->addToBuyerWallet(amoutOfMoney);
}

bool ManageMarket::validAmountForChargeWallet(vector<string> commandVec){
	if(stof(commandVec[4]) > 0) return true;
	return false;
}

bool ManageMarket::validCommandForChargeWallet(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="chargeWallet" && 
		commandVec[2] == "?" && commandVec[3] == "amount") return true;
	return false;
}

void ManageMarket::printBuyerWallet(vector<string> commandVec){
	vector<float>  CurrentBuyerWallet;
	CurrentBuyerWallet = ((Buyer*)onlineUser)->getBuyerWallet();
	cout << "credit" << endl;
	int mostStages = stoi(commandVec[4]);
	if(mostStages >= CurrentBuyerWallet.size()){
		int stage = CurrentBuyerWallet.size()-1;
		while(stage >= 0){
			cout << CurrentBuyerWallet[stage] << endl;
			stage = stage -1;
		}
	}
	else if(mostStages < CurrentBuyerWallet.size()){
		int stage = CurrentBuyerWallet.size()-1;
		while(mostStages > 0){ 
			cout << CurrentBuyerWallet[stage] << endl;
			stage = stage -1;
			mostStages = mostStages -1;
		}
	}
}

bool ManageMarket::validCommandForBuyerWallet(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="wallet" && 
		commandVec[2] == "?" && commandVec[3] == "count") return true;
	return false;
}

void ManageMarket::printBuyerOrders(vector<string> commandVec){
		cout << "productId | productName | offerId | sellerId | soldPrice | amount" << endl; 
		vector<Offer*> offersOfOnlineUser;
		vector<Offer*> currentSellerOffer;
		vector<int> quantities;
		vector<float> discountPercentage;
		vector<int> star;
		star = (((Buyer*)onlineUser)->getStarPrint());
		int currentOfferId;
		float totalPriceConsideringDiscount;
		// for(uint i=0; i<onlineUserCart.size(); i++){
		int i= (((Buyer*)onlineUser)->getBuyerCart()).size()-1;
		if(i< stoi(commandVec[4])){
			while(i>=0) {
				offersOfOnlineUser = onlineUserCart[i]->getOffersOfCart();
				quantities = onlineUserCart[i]->getQuantities();
				discountPercentage = onlineUserCart[i]->getDiscountPercentage();
				for(uint j=0; j< offersOfOnlineUser.size(); j++){
					cout << (offersOfOnlineUser[j]->getOfferProduct())->getProductId() << " | ";
					cout << (offersOfOnlineUser[j]->getOfferProduct())->getProductName() << " | ";
					cout << offersOfOnlineUser[j]->getOfferId() << " | ";
					currentOfferId = offersOfOnlineUser[j]->getOfferId();
					for(int k=0; k<allUsers.size(); k++){
						if(allUsers[k]->getType() == "seller"){
							currentSellerOffer = ((Seller*)allUsers[k])->getSellerOffers();
							for(int l=0; l<currentSellerOffer.size(); l++){
								if( currentSellerOffer[l]->getOfferId() ==  currentOfferId){
									cout << allUsers[k]->getUserId() << " | ";
									totalPriceConsideringDiscount = ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) - ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) * (discountPercentage[j]/100);
									cout << totalPriceConsideringDiscount << " | " << quantities[j] << endl;
								}
							}
						}
					}
				}
				if(star[i] == 1 && i != 0){
					cout << "****" << endl;
				}
				offersOfOnlineUser.clear();
				quantities.clear();
				discountPercentage.clear();
				currentSellerOffer.clear();
				i=i-1;
			}
		}
		else{
			while(i >= stoi(commandVec[4])) {
				offersOfOnlineUser = onlineUserCart[i]->getOffersOfCart();
				quantities = onlineUserCart[i]->getQuantities();
				discountPercentage = onlineUserCart[i]->getDiscountPercentage();
				for(uint j=0; j< offersOfOnlineUser.size(); j++){
					cout << (offersOfOnlineUser[j]->getOfferProduct())->getProductId() << " | ";
					cout << (offersOfOnlineUser[j]->getOfferProduct())->getProductName() << " | ";
					cout << offersOfOnlineUser[j]->getOfferId() << " | ";
					currentOfferId = offersOfOnlineUser[j]->getOfferId();
					for(int k=0; k<allUsers.size(); k++){
						if(allUsers[k]->getType() == "seller"){
							currentSellerOffer = ((Seller*)allUsers[k])->getSellerOffers();
							for(int l=0; l<currentSellerOffer.size(); l++){
								if( currentSellerOffer[l]->getOfferId() ==  currentOfferId){
									cout << allUsers[k]->getUserId() << " | ";
									totalPriceConsideringDiscount = ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) - ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) * (discountPercentage[j]/100);
									cout << totalPriceConsideringDiscount << " | " << quantities[j] << endl;
								}
							}
						}
					}
				}
				if(star[i] == 1 && i != 0){
					cout << "****" << endl;
				}
				offersOfOnlineUser.clear();
				quantities.clear();
				discountPercentage.clear();
				currentSellerOffer.clear();
				i=i-1;
			}
		}
}

bool ManageMarket::validCommandForBuyerOrders(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="orders" && 
		commandVec[2] == "?" && commandVec[3] == "count") return true;
	return false;
}

void ManageMarket::submitCart(){
	float onlineUserMoney = (((Buyer*)onlineUser)->getBuyerWallet())[((Buyer*)onlineUser)->getBuyerWallet().size()-1];
	float totalPriceConsideringDiscount;
	vector<Offer*> offersOfOnlineUser;
		vector<Offer*> currentSellerOffer;
		vector<int> quantities;
		vector<float> discountPercentage;
		int currentOfferId;
		for(uint i=0; i<onlineUserCart.size(); i++){
			offersOfOnlineUser = onlineUserCart[i]->getOffersOfCart();
			quantities = onlineUserCart[i]->getQuantities();
			discountPercentage = onlineUserCart[i]->getDiscountPercentage();
			for(uint j=0; j< offersOfOnlineUser.size(); j++){
				currentOfferId = offersOfOnlineUser[j]->getOfferId();
				for(int k=0; k<allUsers.size(); k++){
					if(allUsers[k]->getType() == "seller"){
						currentSellerOffer = ((Seller*)allUsers[k])->getSellerOffers();
						for(int l=0; l<currentSellerOffer.size(); l++){
							if( currentSellerOffer[l]->getOfferId() ==  currentOfferId){
								totalPriceConsideringDiscount = ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) - ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) * (discountPercentage[j]/100);
								((Seller*)allUsers[k])->addToSellerWallet(totalPriceConsideringDiscount);
							}
						}
					}
				}
			}
			offersOfOnlineUser.clear();
			quantities.clear();
			discountPercentage.clear();
			currentSellerOffer.clear();
		}
	((Buyer*)onlineUser)->addToBuyerWallet(onlineUserMoney-totalPriceConsideringDiscount);
	for(int m=0; m<onlineUserCart.size(); m++){
		((Buyer*)onlineUser)->addToBuyerCart(onlineUserCart[m]);
	}
	((Buyer*)onlineUser)->addToStarPrint(1);
	onlineUserCart.clear();
}

bool ManageMarket::enoughMoney(){
	float onlineUserMoney = (((Buyer*)onlineUser)->getBuyerWallet())[((Buyer*)onlineUser)->getBuyerWallet().size()-1];
	float totalPriceConsideringDiscount;
	vector<Offer*> offersOfOnlineUser;
		vector<Offer*> currentSellerOffer;
		vector<int> quantities;
		vector<float> discountPercentage;
		int currentOfferId;
		for(uint i=0; i<onlineUserCart.size(); i++){
			offersOfOnlineUser = onlineUserCart[i]->getOffersOfCart();
			quantities = onlineUserCart[i]->getQuantities();
			discountPercentage = onlineUserCart[i]->getDiscountPercentage();
			for(uint j=0; j< offersOfOnlineUser.size(); j++){
				currentOfferId = offersOfOnlineUser[j]->getOfferId();
				for(int k=0; k<allUsers.size(); k++){
					if(allUsers[k]->getType() == "seller"){
						currentSellerOffer = ((Seller*)allUsers[k])->getSellerOffers();
						for(int l=0; l<currentSellerOffer.size(); l++){
							if( currentSellerOffer[l]->getOfferId() ==  currentOfferId){
								totalPriceConsideringDiscount = ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) - ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) * (discountPercentage[j]/100);
							}
						}
					}
				}
			}
			offersOfOnlineUser.clear();
			quantities.clear();
			discountPercentage.clear();
			currentSellerOffer.clear();
		}
		if(onlineUserMoney >= totalPriceConsideringDiscount)
			return true;
		return false;
}

bool ManageMarket::validCommandForSubmitCart(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="submitCart") return true;
	return false;
}

void ManageMarket::printOnlineUserCart(){
	if(onlineUserCart.size() == 0){
		cout << "Empty" << endl;
	}
	else{
		cout << "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount" << endl; 
		vector<Offer*> offersOfOnlineUser;
		vector<Offer*> currentSellerOffer;
		vector<int> quantities;
		vector<float> discountPercentage;
		int currentOfferId;
		float totalPriceConsideringDiscount;
		for(uint i=0; i<onlineUserCart.size(); i++){
			offersOfOnlineUser = onlineUserCart[i]->getOffersOfCart();
			quantities = onlineUserCart[i]->getQuantities();
			discountPercentage = onlineUserCart[i]->getDiscountPercentage();
			for(uint j=0; j< offersOfOnlineUser.size(); j++){
				cout << (offersOfOnlineUser[j]->getOfferProduct())->getProductId() << " | ";
				cout << (offersOfOnlineUser[j]->getOfferProduct())->getProductName() << " | ";
				cout << offersOfOnlineUser[j]->getOfferId() << " | ";
				currentOfferId = offersOfOnlineUser[j]->getOfferId();
				for(int k=0; k<allUsers.size(); k++){
					if(allUsers[k]->getType() == "seller"){
						currentSellerOffer = ((Seller*)allUsers[k])->getSellerOffers();
						for(int l=0; l<currentSellerOffer.size(); l++){
							if( currentSellerOffer[l]->getOfferId() ==  currentOfferId){
								cout << allUsers[k]->getUserId() << " | ";
								totalPriceConsideringDiscount = ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) - ((currentSellerOffer[l]->getOfferPrice())*quantities[j]) * (discountPercentage[j]/100);
								cout << totalPriceConsideringDiscount << " | " << quantities[j] << endl;
							}
						}
					}
				}
			}
			offersOfOnlineUser.clear();
			quantities.clear();
			discountPercentage.clear();
			currentSellerOffer.clear();
		}
	}
}

bool ManageMarket::validCommandForCartOnlineUser(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="cart") return true;
	return false;
}

void ManageMarket::AddToCartWithDiscount(vector<string> commandVec){
	string discountCodeForCart = commandVec[8];
	int amountOfRequested = stoi(commandVec[6]);
	int offerIdForCart = stoi(commandVec[4]);
	float discountPercent ;
	for(uint i=0; i<allOffers.size(); i++){
		if( allOffers[i]->getOfferId() == offerIdForCart ){
			vector<pair <string,float> > DiscountCodeOnOffer;
			DiscountCodeOnOffer = allOffers[i]->getDiscountCodeOnOffer();
			for(uint j=0; j < DiscountCodeOnOffer.size(); j++){
				if(DiscountCodeOnOffer[j].first == discountCodeForCart) 
					discountPercent = DiscountCodeOnOffer[j].second;
			}
			// DiscountCodeOnOffer.clear();
		}
	}
	vector<Offer*> sellerOffers;
	for(int i=0; i< allUsers.size(); i++){
		if(allUsers[i]->getType() == "seller"){
			sellerOffers = ((Seller*)allUsers[i])->getSellerOffers();
			for(uint j=0; j< sellerOffers.size(); i++){
				if(sellerOffers[j]->getOfferId() == offerIdForCart){
					Cart* newCart = new Cart(sellerOffers[j],amountOfRequested,discountPercent);
					((Buyer*)onlineUser)->addToStarPrint(0);
					onlineUserCart.push_back(newCart);
				}
				break;
			}
		}
	}
}

bool ManageMarket::validDiscountCode(vector<string> commandVec){
	string discountCodeForCart = commandVec[8];
	int offerIdForCart = stoi(commandVec[4]);
	for(uint i=0; i<allOffers.size(); i++){
		if( allOffers[i]->getOfferId() == offerIdForCart ){
			vector<pair <string,float> > DiscountCodeOnOffer;
			DiscountCodeOnOffer = allOffers[i]->getDiscountCodeOnOffer();
			for(uint j=0; j < DiscountCodeOnOffer.size(); j++){
				if(DiscountCodeOnOffer[j].first == discountCodeForCart) 
					return true;
			}
			// DiscountCodeOnOffer.clear();
		}
	}
	return false;
}

void ManageMarket::AddToCartWithoutDiscount(vector<string> commandVec){	
	int amountOfRequested = stoi(commandVec[6]);
	int offerIdForCart = stoi(commandVec[4]);
	vector<Offer*> sellerOffers;
	for(int i=0; i< allUsers.size(); i++){
		if(allUsers[i]->getType() == "seller"){
			sellerOffers = ((Seller*)allUsers[i])->getSellerOffers();
			for(uint j=0; j< sellerOffers.size(); i++){
				if(sellerOffers[j]->getOfferId() == offerIdForCart){
					Cart* newCart = new Cart(sellerOffers[j],amountOfRequested,0); 
					((Buyer*)onlineUser)->addToStarPrint(0);
					onlineUserCart.push_back(newCart);
				}
				break;
			}
		}
	}
}

bool ManageMarket::validAmountForAddToCart(vector<string> commandVec){
	int amountOfRequested = stoi(commandVec[6]);
	int offerIdForCart = stoi(commandVec[4]);
	vector<Offer*> sellerOffers;
	for(int i=0; i< allUsers.size(); i++){
		if(allUsers[i]->getType() == "seller"){
			sellerOffers = ((Seller*)allUsers[i])->getSellerOffers();
			for(uint j=0; j< sellerOffers.size(); i++){
				if(sellerOffers[j]->getOfferId() == offerIdForCart){
					if(amountOfRequested <= sellerOffers[j]->getOfferAmount())
						return true;
				}
			}
		}
	}
	return false;
}

bool ManageMarket::validCommandForAddToCart(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="addToCart" && 
		commandVec[2] == "?" && commandVec[3] == "offerId" && commandVec[5] == "amount") return true;
	return false;
}

bool ManageMarket::printCommentsOnProduct(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			cout << allProducts[i]->getProductName() << endl;
			for(int j=0; j< (allProducts[i]->getAllComments()).size(); j++ ){
				cout << (allProducts[i]->getAllComments())[j] << endl;
			}
		}
	}
}

bool ManageMarket::IdFoundForComments(vector<string> commandVec){
	int productId1 = stoi(commandVec[4]);
	for(int i=0; i < allProducts.size(); i++){
		if(allProducts[i]->getProductId() == productId1){
			return true;
		}
	}
	return false;
}

bool ManageMarket::validCommandForComments(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="comments" && 
		commandVec[2] == "?" && commandVec[3] == "productId") return true;
	return false;
}

void ManageMarket::printProductDetail(vector<string> commandVec){
	for(uint i=0; i<allProducts.size(); i++){
		if(allProducts[i]->getProductId() == stoi(commandVec[4])){
			if(allProducts[i]->getType() == "car"){
				cout << allProducts[i]->getProductName() << endl;
				cout << carFeatures[1] << ": " << ((Car*)allProducts[i])->getWeight() << endl;
				cout << carFeatures[2] << ": " << ((Car*)allProducts[i])->getSeatsNum() << endl;
				cout << carFeatures[3] << ": " << ((Car*)allProducts[i])->getCylindersNum() << endl;
				cout << carFeatures[4] << ": " << ((Car*)allProducts[i])->getEngineCapacity() << endl;
				cout << carFeatures[5] << ": " << ((Car*)allProducts[i])->getReverseParkingSensor() << endl;
			}
			else if(allProducts[i]->getType() == "tv"){
				cout << allProducts[i]->getProductName() << endl;
				cout << tvFeatures[1] << ": " << ((Tv*)allProducts[i])->getScreenSize() << endl;
				cout << tvFeatures[2] << ": " << ((Tv*)allProducts[i])->getScreenType() << endl;
				cout << tvFeatures[3] << ": " << ((Tv*)allProducts[i])->getResolution() << endl;
				cout << tvFeatures[4] << ": " << ((Tv*)allProducts[i])->getThreeD() << endl;
				cout << tvFeatures[5] << ": " << ((Tv*)allProducts[i])->getHDR() << endl;
			}
			else if(allProducts[i]->getType() == "mobile"){
				cout << allProducts[i]->getProductName() << endl;
				cout << mobiileFeatures[1] << ": " << ((Mobile*)allProducts[i])->getWeight() << endl;
				cout << mobiileFeatures[2] << ": " << ((Mobile*)allProducts[i])->getCPUFrequency() << endl;
				cout << mobiileFeatures[3] << ": " << ((Mobile*)allProducts[i])->getBuiltInMemory() << endl;
				cout << mobiileFeatures[4] << ": " << ((Mobile*)allProducts[i])->getRAM() << endl;
				cout << mobiileFeatures[5] << ": " << ((Mobile*)allProducts[i])->getDisplaySize() << endl;
				cout << mobiileFeatures[6] << ": " << ((Mobile*)allProducts[i])->getCameraResolution() << endl;
				cout << mobiileFeatures[7] << ": " << ((Mobile*)allProducts[i])->getOS() << endl;
			}
		}
	}
}

bool ManageMarket::validCommandForProductDetail(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="productDetail" && 
		commandVec[2] == "?" && commandVec[3] == "productId") return true;
	return false;
}

void ManageMarket::printOffersOnProduct(vector<string> commandVec){
	cout << "productId" << " | " << "productName" << " | " << "offerId" << " | " << "offerUnitPrice" << " | " << "offerAmount" << endl;
	int wantedProductId = stoi(commandVec[4]);
	for(uint i=0; i<allOffers.size(); i++){
		if((allOffers[i]->getOfferProduct())->getProductId() == wantedProductId){
			cout << (allOffers[i]->getOfferProduct())->getProductId() << " | " ;
			cout << (allOffers[i]->getOfferProduct())->getProductName() << " | " ;
			cout << allOffers[i]->getOfferId() << " | ";
			cout << allOffers[i]->getOfferPrice() << " | ";
			cout << allOffers[i]->getOfferAmount()<< endl;
		}
	}
}

bool ManageMarket::validCommandForOffersOnProduct(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="offersOnProduct" && 
		commandVec[2] == "?" && commandVec[3] == "productId") return true;
	return false;
}

string ManageMarket::random_string(std::size_t length){
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

void ManageMarket::generateDiscountCode(vector<string> commandVec){
	int offerIdGetsDiscount = stoi(commandVec[4]);
	float discountPercentOnOffer = stof(commandVec[6]);
	int discountNumberOnOffer = stoi(commandVec[8]);
	string randomDiscountCode;
	for(uint i=0; i<allOffers.size(); i++){
		if(allOffers[i]->getOfferId() == offerIdGetsDiscount){
			for(int j=0; j<discountNumberOnOffer; j++){
				allOffers[i]->addToDiscountCodeOnOffer(random_string(10),discountPercentOnOffer);
			}
			allOffers[i]->printDiscountCodeOnOffer();
		}
	}
}

bool ManageMarket::validCommandForGenerateDiscountCode(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="generateDiscountCode" && 
		commandVec[2] == "?" && commandVec[3] == "offerId" && 
		commandVec[5] == "discountPercent" && commandVec[7] == "discountNumber" ) return true;
	return false;
}

void ManageMarket::printSellerWallet(vector<string> commandVec){
	vector<float>  CurrentSellerWallet;
	CurrentSellerWallet = ((Seller*)onlineUser)->getSellerWallet();
	cout << "credit" << endl;
	int mostStages = stoi(commandVec[4]);
	if(mostStages >= CurrentSellerWallet.size()){
		int stage = CurrentSellerWallet.size()-1;
		while(stage >= 0){
			cout << CurrentSellerWallet[stage] << endl;
			stage = stage -1;
		}
	}
	else if(mostStages < CurrentSellerWallet.size()){
		int stage = CurrentSellerWallet.size()-1;
		while(mostStages > 0){ 
			cout << CurrentSellerWallet[stage] << endl;
			stage = stage -1;
			mostStages = mostStages -1;
		}
	}
}

bool ManageMarket::validCommandForWalletSeller(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="wallet" && 
		commandVec[2] == "?" && commandVec[3] == "count") return true;
	return false;
}

void ManageMarket::makeChangeOffer(vector<string> commandVec){
	for(uint i=0; i < (((Seller*)onlineUser)->getSellerOffers()).size(); i++){
		if((((Seller*)onlineUser)->getSellerOffers())[i]->getOfferId() == stoi(commandVec[4])){
			(((Seller*)onlineUser)->getSellerOffers())[i]->changeOffer(stof(commandVec[6]), stoi(commandVec[8]));
		}
	}
	for(uint i=0; i < allOffers.size(); i++){
		if(allOffers[i]->getOfferId() == stoi(commandVec[4])){
			allOffers[i]->changeOffer(stof(commandVec[6]), stoi(commandVec[8]));
		}
	}
}

bool ManageMarket::validCommandForChangeOffer(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="changeOffer" && 
		commandVec[2] == "?" && commandVec[3] == "offerId" && 
		 commandVec[5] == "offerUnitPrice" && commandVec[7] == "offerAmount") return true;
	return false;
}

void ManageMarket::printMyOffers(){
	cout << "productId" << " | " << "offerId" << " | " << "offerUnitPrice" << " | " << "offerAmount" << endl;
	vector<Offer*> sellerOffersNow;
	sellerOffersNow = ((Seller*)onlineUser)->getSellerOffers();
	for(uint i=0; i< sellerOffersNow.size(); i++){
		cout << (sellerOffersNow[i]->getOfferProduct())->getProductId() << " | ";
		cout << sellerOffersNow[i]->getOfferId() << " | ";
		cout << sellerOffersNow[i]->getOfferPrice() << " | ";
		cout << sellerOffersNow[i]->getOfferAmount() << endl;
	}
}

bool ManageMarket::validCommandForMyOffers(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] == "myOffers") return true;
	return false;
}

void ManageMarket::makeOffer(vector<string> commandVec){
	int productIdOffered;
	for(uint i=0; i < allProducts.size(); i++){
		if(stoi(commandVec[4]) == allProducts[i]->getProductId()) 
			productIdOffered = i;
	}
	countOfferId = countOfferId+1;
	Offer* newOffer = new Offer(allProducts[productIdOffered],countOfferId,stof(commandVec[6]),stoi(commandVec[8]));
	((Seller*)onlineUser)->addTosellerOffers(newOffer);
	allOffers.push_back(newOffer);
}

bool ManageMarket::firstTimeOffer(vector<string> commandVec){
	vector<Offer*> sellerOffers;
	sellerOffers = ((Seller*)onlineUser)->getSellerOffers();

	int productIdOffered = stoi(commandVec[4]);
	for(uint j=0; j < sellerOffers.size(); j++){
		if((sellerOffers[j]->getOfferProduct())->getProductId() == productIdOffered) 
			return false;
	}
	return true;
}

bool ManageMarket::productIdExists(vector<string> commandVec){
	for(uint i=0; i < allProducts.size(); i++){
		if(stoi(commandVec[4]) == allProducts[i]->getProductId()) return true;
	}
	return false;
}

bool ManageMarket::validCommandForOffer(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="offer" && 
		commandVec[2] == "?" && commandVec[3] == "productId" && 
		 commandVec[5] == "offerUnitPrice" && commandVec[7] == "offerAmount") return true;
	return false;
}

void ManageMarket::printProducts(){
	cout << "productId" << " | " << "productName" << endl;
	for(uint i=1; i <= countProductId; i++){
		cout << i << " | " << allProducts[i-1]->getProductName() << endl;
	}
}

bool ManageMarket::userIsBuyer(){
	if(onlineUser->getType() == "buyer") return true;
	return false;
}

bool ManageMarket::userIsSeller(){
	if(onlineUser->getType() == "seller") return true;
	return false;
}

bool ManageMarket::validCommandForGetProducts(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="getProducts") return true;
	return false;
}

void ManageMarket::printOffersByAdmin(vector<string> commandVec){
	if(commandVec[4] == "ASCEND"){
		if(commandVec[6] == "offerId"){
			cout << "productId" << " | " << "offerId" << " | " << "offerUnitPrice" << " | " << "offerAmount" << endl;
			for(uint i=0; i< allOffers.size(); i++){
				cout << (allOffers[i]->getOfferProduct())->getProductId() << " | ";
				cout << allOffers[i]->getOfferId() << " | ";
				cout << allOffers[i]->getOfferPrice() << " | ";
				cout << allOffers[i]->getOfferAmount() << endl;
			}
		}
		else if(commandVec[6] == "offerPrice"){
			vector<Offer*> tempASCEND;
			vector<Offer*> offerASCENDsorted;
			tempASCEND = allOffers;
			cout << "productId" << " | " << "offerId" << " | " << "offerUnitPrice" << " | " << "offerAmount" << endl;
			int indexOfMinPrice=0;
			int count =tempASCEND.size()-1;
			while(count>=0){
				for(uint j=0; j< tempASCEND.size(); j++){
					if(tempASCEND[j]->getOfferPrice() <= tempASCEND[indexOfMinPrice]->getOfferPrice())
						indexOfMinPrice = j;
				}
				offerASCENDsorted.push_back(tempASCEND[indexOfMinPrice]);
				tempASCEND.erase(tempASCEND.begin()+ indexOfMinPrice);
				indexOfMinPrice = 0;
				count = count-1;
			}
			for(uint k=0; k< offerASCENDsorted.size()-1; k++){
				if(offerASCENDsorted[k]->getOfferPrice() == offerASCENDsorted[k+1]->getOfferPrice()){
					if(offerASCENDsorted[k]->getOfferId() >  offerASCENDsorted[k+1]->getOfferId()){
						swap(offerASCENDsorted[k],offerASCENDsorted[k+1]);
					}
				}
			}
			for(uint l=0; l< offerASCENDsorted.size(); l++){
				cout << (offerASCENDsorted[l]->getOfferProduct())->getProductId() << " | ";
				cout << offerASCENDsorted[l]->getOfferId() << " | ";
				cout << offerASCENDsorted[l]->getOfferPrice() << " | ";
				cout << offerASCENDsorted[l]->getOfferAmount() << endl;
			}
		}
	}
	else if(commandVec[4] == "DESCEND"){
		if(commandVec[6] == "offerId"){
			cout << "productId" << " | " << "offerId" << " | " << "offerUnitPrice" << " | " <<  "offerAmount" << endl;
			int counter = allOffers.size()-1; //DESCEND
			while(counter >= 0){
				cout << (allOffers[counter]->getOfferProduct())->getProductId() << " | ";
				cout << allOffers[counter]->getOfferId() << " | ";
				cout << allOffers[counter]->getOfferPrice() << " | ";
				cout << allOffers[counter]->getOfferAmount() << endl;
				counter = counter-1;
			}

		}
		else if(commandVec[6] == "offerPrice"){
			vector<Offer*> tempDESCEND;
			vector<Offer*> offerDESCENDsorted;
			tempDESCEND = allOffers;
			cout << "productId" << " | " << "offerId" << " | " << "offerUnitPrice" << " | "<< "offerAmount" << endl;
			int indexOfMinPrice=0;
			int count =tempDESCEND.size()-1;
			while(count>=0){
				for(uint j=0; j< tempDESCEND.size(); j++){
					if(tempDESCEND[j]->getOfferPrice() <= tempDESCEND[indexOfMinPrice]->getOfferPrice())
						indexOfMinPrice = j;
				}
				offerDESCENDsorted.push_back(tempDESCEND[indexOfMinPrice]);
				tempDESCEND.erase(tempDESCEND.begin()+ indexOfMinPrice);
				indexOfMinPrice = 0;
				count = count-1;
			}
			for(uint k=0; k< offerDESCENDsorted.size()-1; k++){
				if(offerDESCENDsorted[k]->getOfferPrice() == offerDESCENDsorted[k+1]->getOfferPrice()){
					if(offerDESCENDsorted[k]->getOfferId() >  offerDESCENDsorted[k+1]->getOfferId()){
						swap(offerDESCENDsorted[k],offerDESCENDsorted[k+1]);
					}
				}
			}
			int l = offerDESCENDsorted.size()-1;
			while(l>=0){
				cout << (offerDESCENDsorted[l]->getOfferProduct())->getProductId() << " | ";
				cout << offerDESCENDsorted[l]->getOfferId() << " | ";
				cout << offerDESCENDsorted[l]->getOfferPrice() << " | ";
				cout << offerDESCENDsorted[l]->getOfferAmount() << endl;
				l = l-1;
			}
		}
	}
}

bool ManageMarket::validCommandForOffers(vector<string> commandVec){
	if(commandVec[0] == "GET" && commandVec[1] =="offers" && 
		commandVec[2] == "?" && commandVec[3] == "order" && 
		 commandVec[5] == "field") {
			if(commandVec[4] == "ASCEND" || commandVec[4] == "DESCEND"){
				if(commandVec[6] == "offerId" || commandVec[6] == "offerPrice"){
					return true;
				}
			}
	}
	return false;
}

void ManageMarket::importProducts(string productType, vector<vector<string> > datas){
	if(productType == "car"){
		carFeatures.clear(); 
		for(uint j=0; j<datas[0].size();j++){
			carFeatures.push_back(datas[0][j]);
		}
		carFeatures[5].pop_back(); 
		for(uint i=1; i<datas.size(); i++){
			countProductId = countProductId+1;
			Product* newProduct = new Car(datas[i][0], countProductId, productType, stof(datas[i][1]), stoi(datas[i][2]), stoi(datas[i][3]), stof(datas[i][4]), stoi(datas[i][5]));
			allProducts.push_back(newProduct);
		}
	}
	else if(productType == "tv"){
		tvFeatures.clear();
		for(uint j=0; j<datas[0].size();j++){
			tvFeatures.push_back(datas[0][j]);
		}
		tvFeatures[5].pop_back(); 
		for(uint i=1; i<datas.size(); i++){
			countProductId = countProductId+1;
			Product* newProduct = new Tv(datas[i][0], countProductId, productType, stof(datas[i][1]), datas[i][2], datas[i][3], stoi(datas[i][4]), stoi(datas[i][5]));
			allProducts.push_back(newProduct);
		}
	}
	else if(productType == "mobile"){
		mobiileFeatures.clear();
		for(uint j=0; j<datas[0].size();j++){
			mobiileFeatures.push_back(datas[0][j]);
		}
		mobiileFeatures[7].pop_back(); 
		for(uint i=1; i<datas.size(); i++){
			countProductId = countProductId+1;
			Product* newProduct = new Mobile(datas[i][0], countProductId, productType, stof(datas[i][1]), stof(datas[i][2]), stof(datas[i][3]), stof(datas[i][4]), stof(datas[i][5]), stof(datas[i][6]), datas[i][7]);
			allProducts.push_back(newProduct);
		}
	}
}

vector<vector<string> > ManageMarket::putDataIn2D(vector<string> commandVec){
	ifstream dataRead ;
	string filePath = commandVec[6];
	string productType = commandVec[4];
	string productTypeFileName;
	if(productType == "car"){
		productTypeFileName = "Car";
	}
	else if(productType == "tv"){
		productTypeFileName = "Tv";
	}
	else if(productType == "mobile"){
		productTypeFileName = "Mobile";
	}
	string fileName = filePath;
	dataRead.open(fileName.c_str());
	string line;
	vector<vector<string> > datas;
	vector<string> lineContent;
	while(getline(dataRead,line)){
		lineContent = splitString(line,SPLITOFCSV,lineContent);
		datas.push_back(lineContent);
		line.erase();
		lineContent.clear();
	}	
	dataRead.close();
	return datas;
}

bool ManageMarket::fileExists(vector<string> commandVec){
	ifstream dataRead ;
	string filePath = commandVec[6];
	string productType = commandVec[4];
	string productTypeFileName;
	if(productType == "car"){
		productTypeFileName = "Car";
	}
	else if(productType == "tv"){
		productTypeFileName = "Tv";
	}
	else if(productType == "mobile"){
		productTypeFileName = "Mobile";
	}
	string fileName = filePath;
	dataRead.open(fileName.c_str());
	if(dataRead.is_open()){
		return true;
	}
	else{
		return false;
	}
}

bool ManageMarket::userIsAdmin(){
	if(onlineUser->getType() == "admin") return true;
	return false;
}

bool ManageMarket::validCommandForImportProducts(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="importProducts" && 
		commandVec[2] == "?" && commandVec[3] == "type" && 
		 commandVec[5] == "filePath") return true;
	return false;
}

bool ManageMarket::validCommandForLogout(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="logout") return true;
	return false;
}

User* ManageMarket::findUser(vector<string> commandVec){
	for(uint i=0; i< allUsers.size(); i++){
		if(allUsers[i]->getMail() == commandVec[4]){
			if(allUsers[i]->getPassword() == commandVec[6])
		 		return allUsers[i];
		}
	}
	return nullptr;
}

bool ManageMarket::correctUserPass(vector<string> commandVec) {
	for(uint i=0; i< allUsers.size(); i++){
		if(allUsers[i]->getMail() == commandVec[4]){
			if(allUsers[i]->getPassword() == commandVec[6])
		 		return true;
		}
	}
	return false;
}

bool ManageMarket::validCommandForLogin(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] =="login" && 
		commandVec[2] == "?" && commandVec[3] == "email" && 
		 commandVec[5] == "password") return true;
	return false;
}

bool ManageMarket::userExists(string userName){
	for(uint i=0; i< allUsers.size(); i++){
		if(allUsers[i]->getUserName() == userName) return true;
	}
	return false;
}

bool ManageMarket::validCommandForSignup(vector<string> commandVec){
	if(commandVec[0] == "POST" && commandVec[1] == "signup" &&
		commandVec[2] == "?" && commandVec[3] == "email" &&
		 commandVec[5] == "username" && commandVec[7] =="password") return true;
	return false;
}

string ManageMarket::decideOperation(vector<string> commandVec){
	return commandVec[1];
}

void ManageMarket::printOffersByBuyer(vector<string> commandVec){
	cout << "productId" << " | " << "offerId" << " | " << "offerUnitPrice" << " | " << "offerAmount" << endl;
	for(uint i=0; i< allOffers.size(); i++){
		cout << (allOffers[i]->getOfferProduct())->getProductId() << " | ";
		cout << allOffers[i]->getOfferId() << " | ";
		cout << allOffers[i]->getOfferPrice() << " | ";
		cout << allOffers[i]->getOfferAmount() << endl;
	}
}


bool notFoundState(vector<string> commandVec){
	if(commandVec[0] == "POST" ||  commandVec[0] == "GET")
	{
		if( commandVec[1] != "signup" || commandVec[1] != "login" ||
		    commandVec[1] != "logout" || commandVec[1] != "importProducts" ||
		    commandVec[1] != "offers" || commandVec[1] != "getProducts" ||
			commandVec[1] != "offer" || commandVec[1] != "myOffers" ||
			commandVec[1] != "changeOffer" || commandVec[1] != "wallet" ||
			commandVec[1] != "generateDiscountCode" || commandVec[1] != "getProducts" ||
			commandVec[1] != "offersOnProduct" || commandVec[1] != "productDetail" ||
			commandVec[1] != "comments" || commandVec[1] != "submitCart" ||
			commandVec[1] != "addToCart" || commandVec[1] != "cart" ||
			commandVec[1] != "orders" || commandVec[1] != "wallet" ||
			commandVec[1] != "chargeWallet" || commandVec[1] != "comment" ||
			commandVec[1] != "compare")
		{
			return true;
		}
	}
	return false;
}


//emtiazi
size_t wordHasher(string word){
	    hash<string> hasher;
	    size_t result = hasher(word);
	    return result;
}
//emtiazi
void ManageMarket::generateDiscountCodeWordHasher(vector<string> commandVec){
	int offerIdGetsDiscount = stoi(commandVec[4]);
	float discountPercentOnOffer = stof(commandVec[6]);
	int discountNumberOnOffer = stoi(commandVec[8]);
	string randomDiscountCode;
	for(uint i=0; i<allOffers.size(); i++){
		if(allOffers[i]->getOfferId() == offerIdGetsDiscount){
			for(int j=0; j<discountNumberOnOffer; j++){
				allOffers[i]->addToDiscountCodeOnOffer(to_string(wordHasher(random_string(10))),discountPercentOnOffer);
			}
			allOffers[i]->printDiscountCodeOnOffer();
		}
	}
}


void ManageMarket::manageCommands(string command){
	vector<string> commandVec;
	commandVec = splitString(command,SPLITOFTXT,commandVec);
	Exception* exception;
	if(commandVec.size() == 1 ){
		exception = new BadRequest();
		throw exception;
	}
	
	string operation = decideOperation(commandVec);

    if(commandVec.size() >= 9 && operation == "signup") {
		if(validCommandForSignup(commandVec) && userExists(commandVec[6]) == false){
			if(commandVec.size() == 9){
				countUserId = countUserId+1;
				User* newUser = new Buyer(commandVec[4],commandVec[6],commandVec[8],countUserId , "buyer");
				onlineUser = newUser;
				allUsers.push_back(newUser);
				cout << "OK"<< endl;
			}
			else{
				if(commandVec[10] == "buyer"){
					countUserId = countUserId+1;
					User* newUser = new Buyer(commandVec[4],commandVec[6],commandVec[8],countUserId , "buyer");
					onlineUser = newUser;
					allUsers.push_back(newUser);
					cout << "OK"<< endl;
				}
				if(commandVec[10] == "seller"){
					countUserId = countUserId+1;
					User* newUser = new Seller(commandVec[4],commandVec[6],commandVec[8],countUserId , "seller");
					onlineUser = newUser;
					allUsers.push_back(newUser);
					cout << "OK" << endl;
				}
			}
		}	
		else {
			exception = new BadRequest();
			throw exception;
		}
	}
	else if( commandVec.size() ==7 && operation == "login"){
		if( validCommandForLogin(commandVec) && correctUserPass(commandVec) && onlineUser == nullptr){
			onlineUser = findUser(commandVec);
			cout << "OK" << endl;
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 2 && operation == "logout"){
		if( validCommandForLogout(commandVec)){ 
			if(onlineUser != nullptr){
				onlineUserCart.clear();
				onlineUser = nullptr;
				cout << "OK" << endl;
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
				exception = new BadRequest();
				throw exception;
		}
	}
	else if(commandVec.size() == 7 && operation == "importProducts"  && onlineUser != nullptr){ //admin
		if(validCommandForImportProducts(commandVec)) {
			if(userIsAdmin()){
				if(fileExists(commandVec)){
					vector<vector<string> > datas;
					datas = putDataIn2D(commandVec);
					importProducts(commandVec[4],datas);
					cout << "OK" << endl;
				}
				else {
					exception = new NotFound();
					throw exception;
				}
			}
			else {
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 7 && operation == "offers"  && onlineUser != nullptr){ //admin
		if(validCommandForOffers(commandVec)) {
			if(userIsAdmin()){
				printOffersByAdmin(commandVec);
			}
			else {
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
				throw exception;
		}
	}
	else if(commandVec.size() == 2 && operation == "getProducts"  && onlineUser != nullptr){ //seller
		if(validCommandForGetProducts(commandVec)){
			if(userIsSeller() || userIsBuyer()){
				printProducts();
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 9 && operation == "offer"  && onlineUser != nullptr){ //seller
		if( validCommandForOffer(commandVec)){
			if(userIsSeller()){
				if(productIdExists(commandVec) && firstTimeOffer(commandVec)){
					makeOffer(commandVec);
					cout << "OK" << endl;
				}
				else{
					exception = new BadRequest();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 2 && operation == "myOffers"  && onlineUser != nullptr){ //seller
		if( validCommandForMyOffers(commandVec)){
			if(userIsSeller()){
				printMyOffers();
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 9 && operation == "changeOffer"  && onlineUser != nullptr){ //seller
		if( validCommandForChangeOffer(commandVec)){
			if(userIsSeller()){
				if(productIdExists(commandVec)){
					makeChangeOffer(commandVec);
					cout << "OK" << endl;
				}
				else{
					exception = new BadRequest();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 5 && operation == "wallet"  && onlineUser != nullptr && onlineUser->getType() == "seller" ){ //seller
		if(validCommandForWalletSeller(commandVec)){
			if(userIsSeller()){
				printSellerWallet(commandVec);
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 9 && operation == "generateDiscountCode" && onlineUser != nullptr ){ //seller
		if(validCommandForGenerateDiscountCode(commandVec)){
			if(userIsSeller()){
				generateDiscountCode(commandVec);
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 2 && operation == "getProducts" && onlineUser != nullptr ){ //buyer
		if(validCommandForGetProducts(commandVec)){
			if(userIsSeller() || userIsBuyer()){
				printProducts();
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 5  && operation == "offersOnProduct" && onlineUser != nullptr ){ //buyer
		
		if(validCommandForOffersOnProduct(commandVec)){
			if(userIsBuyer()){
				printOffersOnProduct(commandVec);
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 5  && operation == "productDetail" && onlineUser != nullptr ){ //buyer
		if(validCommandForProductDetail(commandVec)){
			if(userIsBuyer()){
				printProductDetail(commandVec);
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 5 && operation == "comments" && onlineUser != nullptr){ //buyer
		if(validCommandForComments(commandVec)){
			
			if(userIsBuyer()){
				if(IdFoundForComments(commandVec)){
					printCommentsOnProduct(commandVec);
				}
				else{
					exception = new NotFound();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(operation == "addToCart" && onlineUser != nullptr){ //buyer
		if(validCommandForAddToCart(commandVec)){
			if(userIsBuyer()){
				if(commandVec.size() == 7 && validAmountForAddToCart(commandVec)){
					
					AddToCartWithoutDiscount(commandVec);
					cout << "OK" << endl;
				}
				else if(commandVec.size() == 9 && commandVec[7] == "discountCode" && validAmountForAddToCart(commandVec) && validDiscountCode(commandVec)){
					AddToCartWithDiscount(commandVec);
					cout << "OK" << endl;
				}
				else{
					exception = new BadRequest();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 2 && operation == "cart" && onlineUser != nullptr){ //buyer
		if(validCommandForCartOnlineUser(commandVec)){
			if(userIsBuyer()){
				printOnlineUserCart();
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		
		}
	}
	else if(commandVec.size() == 2 && operation == "submitCart" && onlineUser != nullptr){ //buyer
		if(validCommandForSubmitCart(commandVec)){
			if(userIsBuyer()){
				if(enoughMoney()){
					submitCart();
					cout << "OK" << endl;
				}
				else{
					exception = new BadRequest();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		
		}
	}
	else if(commandVec.size() == 5 && operation == "orders" && onlineUser != nullptr ){ //buyer
		if(validCommandForBuyerOrders(commandVec)){
			if(userIsBuyer()){
				if((((Buyer*)onlineUser)->getBuyerCart()).size() != 0){
					printBuyerOrders(commandVec);
				}
				else{
					exception = new NotFound();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		
		}
	}
	else if(commandVec.size() == 5 && operation == "wallet" && onlineUser != nullptr && onlineUser->getType() == "buyer" ){ //buyer
		if(validCommandForBuyerWallet(commandVec)){
			if(userIsBuyer()){
				printBuyerWallet(commandVec);
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}
	else if(commandVec.size() == 5 && operation == "chargeWallet" && onlineUser != nullptr){ //buyer
		if(validCommandForChargeWallet(commandVec)){
			if(userIsBuyer()){
				if(validAmountForChargeWallet(commandVec)){
					chargeWalletOfBuyer(commandVec);
					cout << "OK" << endl;
				}
				else{
					exception = new BadRequest();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}

	}
	else if(operation == "comment" && onlineUser != nullptr ){ //buyer
		if(validCommandForComment(commandVec)){
			if(userIsBuyer()){
				if(IdFoundForComment(commandVec)){
					addCommentToProduct(commandVec);
					cout << "OK" << endl;
				}
				else{
					exception = new NotFound();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}

	}
	else if(commandVec.size() == 7 && operation == "compare" && onlineUser != nullptr ){ //buyer
		if(validCommandForCompare(commandVec)){
			if(userIsBuyer()){
				if(IdFoundForCompare(commandVec)){
					if(productsAreSameType(commandVec)){
						printCompare(commandVec);
					}
					else {
						exception = new BadRequest();
						throw exception;
					}
				}
				else{
					exception = new NotFound();
					throw exception;
				}
			}
			else{
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
			throw exception;
		}
	}

	//Emtiazi
	else if(commandVec.size() == 2 && operation == "offers"  && onlineUser != nullptr && onlineUser->getType() == "buyer" ){ //admin
		if(commandVec[0] == "GET" && commandVec[1] == "offers") {
			if(userIsBuyer()){
				printOffersByBuyer(commandVec);
			}
			else {
				exception = new PermissionDenied();
				throw exception;
			}
		}
		else{
			exception = new BadRequest();
				throw exception;
		}
	}


	else if(notFoundState(commandVec) && commandVec[1] != "signup" ){
		exception = new NotFound();
		throw exception;
	}
	else {
		exception = new BadRequest();
		throw exception;
	}

}