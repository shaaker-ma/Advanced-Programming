#ifndef __COMMENTS_H__
#define __COMMENTS_H__

#include <iostream>
#include <string>
using namespace std ;

class Comment{
public:
	Comment(vector<string> wordsOfComment_ , bool correctnessOfComment_){
		wordsOfComment = wordsOfComment_;
		correctnessOfComment = correctnessOfComment_;
	}
	vector<string> getWordsOfComment() { return wordsOfComment; }
	bool getCorrectnessOfComment() { return correctnessOfComment; }
private:
	vector<string> wordsOfComment;
	bool correctnessOfComment;
};


#endif