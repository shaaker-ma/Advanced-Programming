#include "CommentManagement.hpp"
using namespace std ;
#define SPLITOFTXT ' '
#define SPLITOFCSV ','
#define GETTEST ""
#define TEST_FILE_PATH "test.csv"
#define TRAIN_FILE_PATH "train.csv"
#define TRAIN_FILE_PATH "train.csv"
#define CLASS_PROB "class probabilities"

vector<string> splitString(string str, char delim, vector<string> out){
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
	return out;
}

void CommentManagement::getTestContent(string filePath){
	ifstream dataRead;
	string fileName = filePath;
	dataRead.open(fileName.c_str());
	string line;
	int correctnessInComment;
	vector<string> lineContent;
	vector<string> allWordsOfOneComment;
	int forgetFirstLine =0;
	while(getline(dataRead,line)){
		if(forgetFirstLine == 1){
			lineContent = splitString(line,SPLITOFCSV,lineContent);
			allWordsOfOneComment = splitString(lineContent[0], SPLITOFTXT, allWordsOfOneComment);
			if(stoi(lineContent[1]) == 1 ) {
				correctnessInComment = 0;
			}
			else if(stoi(lineContent[1]) == 0){
				correctnessInComment = 1;
			}
			Comment* newComment = new Comment(allWordsOfOneComment,correctnessInComment);
			comments.push_back(newComment);
			line.erase();
			lineContent.clear();
			allWordsOfOneComment.clear();
		}
		forgetFirstLine=1;
	}	
	dataRead.close();
}

double giveCorrectnessFromFile(){
	float correctness;
	ifstream dataRead;
	string fileName = CLASS_PROB;
	dataRead.open(fileName.c_str());
	dataRead >> correctness;
	dataRead.close();
	return correctness;
}

void CommentManagement::getTrainContent(string filePath){
	ifstream dataRead;
	string fileName = filePath;
	dataRead.open(fileName.c_str());
	string line;
	vector<string> lineContent;
	int forgetFirstLine =0;
	while(getline(dataRead,line)){
		if(forgetFirstLine == 1){
		lineContent = splitString(line,SPLITOFCSV,lineContent);
		Word* newWord = new Word(lineContent[0], stod(lineContent[1]), stod(lineContent[2]));
		words.push_back(newWord);
		line.erase();
		lineContent.clear();
		}
		forgetFirstLine=1;
	}	
	dataRead.close();
}

bool CommentManagement::wordExistsInTrain(string word){
	for(int i=0; i<words.size(); i++){
		if(words[i]->getName() == word)
			return true;
	}
	return false;
}

vector<bool> CommentManagement::giveCorrectnessOfAllComments(double givenProbCorrectness, double givenProbIncorrectness){
	vector<string> wordsOfEachComment;
	vector<bool> results;
	double epsilon = std::numeric_limits<double>::min();
	double logProbOfCorrectness;
	double logProbOfIncorrectness;
	for(int i=0; i<comments.size();i++){
		wordsOfEachComment = comments[i]->getWordsOfComment();
		 logProbOfCorrectness =0;
		 logProbOfIncorrectness =0;
		for(int j=0; j<wordsOfEachComment.size();j++){
			if(wordExistsInTrain(wordsOfEachComment[j])){
				for(int k=0; k<words.size(); k++){
					if(words[k]->getName() == wordsOfEachComment[j]){
						logProbOfCorrectness = logProbOfCorrectness + log10(epsilon+words[k]->getCorrectness());
						logProbOfIncorrectness = logProbOfIncorrectness +log10(epsilon+words[k]->getIncorrectness());
						break;
					}
				}
			}
		}
		logProbOfCorrectness = logProbOfCorrectness + log10(givenProbCorrectness);
		logProbOfIncorrectness = logProbOfIncorrectness + log10(givenProbIncorrectness);

		if(logProbOfCorrectness >= logProbOfIncorrectness){
			results.push_back(1);
		}
		else if(logProbOfCorrectness < logProbOfIncorrectness){
			results.push_back(0);
		}
		wordsOfEachComment.clear();
	}
	return results;
} 


void CommentManagement::evaluate(string command){
	getTestContent(TEST_FILE_PATH);
	double givenProbCorrectness = giveCorrectnessFromFile();
	double givenProbIncorrectness = 1 - givenProbCorrectness;
	getTrainContent(TRAIN_FILE_PATH);
	vector<bool> correctnessOfAllComments;
	correctnessOfAllComments = giveCorrectnessOfAllComments(givenProbCorrectness, givenProbIncorrectness);

	double allGoodsGiven=0;
	double allGoodTaken=0;
	double goodAndCorrect=0;
	double allCorrect;
	double allComments = comments.size();
	for(int i=0; i<comments.size() ; i++){
		if(comments[i]->getCorrectnessOfComment() == 1){
			allGoodsGiven = allGoodsGiven +1;
		}
	}
	for(int i=0; i<correctnessOfAllComments.size() ; i++){
		if(correctnessOfAllComments[i] == 1){
			allGoodTaken = allGoodTaken +1;
		}
	}
	for(int i=0; i<comments.size() ; i++){
		if(correctnessOfAllComments[i] == 1){
			if(comments[i]->getCorrectnessOfComment() == correctnessOfAllComments[i] )
				goodAndCorrect = goodAndCorrect+1;
		}
	}
	for(int i=0; i<comments.size() ; i++){
			if(comments[i]->getCorrectnessOfComment() == correctnessOfAllComments[i] )
				allCorrect = allCorrect+1;
	}
	fstream myfile;
	myfile.open("output.txt",ios::out);
	myfile << "   ";
	double recall = (goodAndCorrect/allGoodsGiven) * 100;
	myfile << "Recall: " << recall << endl;
	double precision = (goodAndCorrect/allGoodTaken) * 100;
	myfile << "Precision: " << precision << endl;
	double accuracy = (allCorrect/allComments) * 100;
	myfile << "Accuracy: " << accuracy << endl;
	myfile.close();
}