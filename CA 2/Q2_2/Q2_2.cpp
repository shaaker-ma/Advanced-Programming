#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 
#include <cmath>
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
void PrepareVector(vector<string>& given_string){
	string str , temp_str ;
	temp_str = "" ;
    getline(cin , str);
	str.push_back(' '); 
    int beging_with = 0 ;
    int repeat = str.size()+2 ;
    int ResFillVector = FillVector(given_string , str , temp_str , repeat , beging_with) ;
    return ;
}
void FillIntVector(vector<string>& given_string , vector<int>& given_num , int size, int step ){
	if(size - step == 0) return ;
	given_num.push_back(stoi(given_string[step])) ;
	FillIntVector(given_string ,given_num , size, step +1) ;
}

void Insert(vector<int>& given_num , int Saved){
	if(given_num.back() <= Saved){
		given_num.push_back(Saved);
	}
	else{
	int here = given_num.back();
	given_num.pop_back();
	Insert(given_num , Saved);
	//becouse here > saved so it has to  push back later
	given_num.push_back(here);
	}

}

void Sort(vector<int>& given_num){
	if(given_num.size() == 1) return ;
	else{
	int Saved = given_num.back();
	given_num.pop_back();
	Sort(given_num);
	Insert(given_num , Saved) ;
	}
}

void PrintOutput(vector<int> given_num ,int size , int current){
	if(size == current) return ; 
   	cout << given_num[current] << ' ';
   	current = current+1 ;
   	PrintOutput(given_num , size , current);
}

int main() {
	vector<string> given_string ;
	PrepareVector(given_string) ;
	vector<int> given_num ;
	int begin = 0 ;
	FillIntVector(given_string , given_num , given_string.size(), begin) ;
	Sort(given_num);
	PrintOutput(given_num , given_num.size() , begin) ;
}