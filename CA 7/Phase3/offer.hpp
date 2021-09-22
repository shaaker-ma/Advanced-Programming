#ifndef __OFFER_H__
#define __OFFER_H__

class Product;
#include "product.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Offer {
public:
	Offer(Product* offerProduct_, int  offerId_, float offerPrice_, int offerAmount_){
		offerProduct = offerProduct_;
		offerId = offerId_;
		offerPrice = offerPrice_;
		offerAmount = offerAmount_;
	}
	Product* getOfferProduct() { return offerProduct;}
	int getOfferId() { return offerId; }
	float getOfferPrice() { return offerPrice; }
	int getOfferAmount() { return offerAmount; }
	vector<pair <string,float> > getDiscountCodeOnOffer() { return DiscountCodeOnOffer;}
	void changeOffer(float offerPrice_, int offerAmount_){
		offerPrice = offerPrice_;
		offerAmount = offerAmount_;
	}
	void addToDiscountCodeOnOffer(string discountCode, float discountPercent){
		DiscountCodeOnOffer.push_back(make_pair(discountCode,discountPercent) );
	}
	void printDiscountCodeOnOffer(){
		for(int k=0; k< DiscountCodeOnOffer.size(); k++){
		cout << DiscountCodeOnOffer[k].first << endl;
		}
	}
	size_t wordHasher(string word){
	    hash<string> hasher;
	    size_t result = hasher(word);
	    return result;
	}
private:
	Product* offerProduct;
	int  offerId;
	float offerPrice;
	int offerAmount;
	vector<pair <string,float> > DiscountCodeOnOffer;
};

#endif