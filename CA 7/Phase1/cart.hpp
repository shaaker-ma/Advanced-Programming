#ifndef __CART_H__
#define __CART_H__

#include <iostream>
#include <vector>
#include <string>
#include "offer.hpp"
class Cart{
public:
	Cart(Offer* offer, int quantities_, float discountPercentage_){
		offersOfCart.push_back(offer);
		quantities.push_back(quantities_);
		discountPercentage.push_back(discountPercentage_);
	}
	vector<Offer*> getOffersOfCart(){ return offersOfCart; }
	vector<int> getQuantities(){ return quantities; }
	vector<float> getDiscountPercentage(){ return discountPercentage; }
	void addToCart(Offer* offer, int quantities_, float discountPercentage_){
		offersOfCart.push_back(offer);
		quantities.push_back(quantities_);
		discountPercentage.push_back(discountPercentage_);
	}
private:
	vector<Offer*> offersOfCart;
	vector<int> quantities;
	vector<float> discountPercentage;
};

#endif