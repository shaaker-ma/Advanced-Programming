#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 
using namespace std;

int FillVector(vector<string>& given , string str , string& temp_str , int repeat , int beging_with){
	if(beging_with == repeat) {
		int res = 0  ;
		return res ;
	}
	else if(str[beging_with] != ' '){
		temp_str = temp_str + str[beging_with] ;
		return FillVector(given , str , temp_str , repeat , beging_with + 1 );
	}
	else if(str[beging_with] == ' ' ){
		given.push_back(temp_str);
		temp_str.erase();
		return FillVector(given , str , temp_str , repeat , beging_with + 1 );

	}
}

void GoToFirst(vector<string>& given , int size , int& SecPOP , string FirstToBePushed , string SecondaryPushBack){
	if(size == 1 && SecPOP == 1) {
		// given.push_back(FirstToBePushed);
		SecPOP = 0 ; 
		return ;
	}
	if(SecPOP == 1){
		FirstToBePushed = given.back();
		given.pop_back();
		SecondaryPushBack = given.back();
		given.pop_back();
		given.push_back(FirstToBePushed);
		GoToFirst(given , given.size() , SecPOP , FirstToBePushed , SecondaryPushBack );
	}
	if(SecPOP == 0){
		given.push_back(SecondaryPushBack);
	}
}

void  ReverseVector(vector<string>& given , int size , int& POP , string NeedsToBePushed){
	string temp2 , temp3 ;
	if(size == 2 && POP == 1 ){
		temp2 = given.back();
		given.pop_back();
		temp3 = given.back();
		given.pop_back();
		given.push_back(temp2);
		given.push_back(temp3);
		POP = 0 ; 
		return  ;
	}

	if(POP == 1){
	NeedsToBePushed = given.back() ;
	given.pop_back();
	int SizeGiven = given.size() ; 
	ReverseVector(given , SizeGiven , POP , NeedsToBePushed);
	}

	if(POP == 0){
		int SecPOP = 1 ;
		string empty = "" ; 
		given.push_back(NeedsToBePushed);
		GoToFirst(given , given.size() , SecPOP , empty , empty ) ;
	}
}

void PrepareVector(vector<string>& given){
	string str , temp_str ;
	temp_str = "" ;
    getline(cin , str);
	str.push_back(' '); 
    int beging_with = 0 ;
    int repeat = str.size()+2 ;
    int ResFillVector = FillVector(given , str , temp_str , repeat , beging_with) ;
    return ;
}

void ReverseOperation(vector<string>& given){
	string temp_str = "" ;
	int SizeGiven = given.size() ; 
	int POP = 1 ; 
	ReverseVector(given , SizeGiven , POP, temp_str) ;
}

void PrintOutput(vector<string>& given ,int size , int current){
	if(size == current) return ; 
   	cout << given[current] << ' ';
   	current = current+1 ;
   	PrintOutput(given , size , current);
}

int main() {
	vector<string> given ;
	PrepareVector(given) ;
	ReverseOperation(given);
	PrintOutput(given, given.size() , 0);
}


