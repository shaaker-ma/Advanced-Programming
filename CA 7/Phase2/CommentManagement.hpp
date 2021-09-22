#ifndef __CommentManagement_H__
#define __CommentManagement_H__
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <limits>
using namespace std ;

#include "Word.hpp"
#include "Comment.hpp"

class CommentManagement{ 
public:
	void evaluate(string command);
	void getTrainContent(string filePath);
	void getTestContent(string filePath);
	vector<bool> giveCorrectnessOfAllComments(double givenProbCorrectness, double givenProbIncorrectness);
	bool wordExistsInTrain(string word);

private:
	vector<Comment*> comments;
	vector<Word*> words;
};

#endif