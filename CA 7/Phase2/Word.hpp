#ifndef __WORDS_H__
#define __WORDS_H__

#include <iostream>
#include <string>
using namespace std ;

class Word{
public:
	Word(string name_, double correctness_, double incorrectness_){
		name = name_;
		correctness = correctness_;
		incorrectness = incorrectness_;
	}
	string getName() { return name; }
	double getCorrectness() { return correctness; }
	double getIncorrectness() { return incorrectness; }
private:
	string name;
	double correctness;
	double incorrectness;
};


#endif