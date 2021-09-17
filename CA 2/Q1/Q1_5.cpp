#include<iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#define AllPossibleNumbers 9

void Build_ASCII_Vectro(vector<int> &ASCIINums,int current_stage){
		if(current_stage >= 0 ) {
			ASCIINums.push_back(current_stage) ;
			Build_ASCII_Vectro(ASCIINums,current_stage-1) ;
		}
}

int ReturnInt(char given_char , vector<int> ASCIINums ){
	int int_of_given_char = (given_char - '0' ) ;
	if(ASCIINums[ASCIINums.size()-1] == int_of_given_char) return ASCIINums[ASCIINums.size()-1] ;
	ASCIINums.pop_back(); 
	return ReturnInt(given_char , ASCIINums) ;
}

int CONVERTED(string s , int converted , int  power ,vector<int>  ASCIINums){
	if(s.empty()) return  converted ;
	int current_num ;
	current_num = ReturnInt(s[s.size()-1] , ASCIINums) ;
	converted = converted  + current_num * (pow(6,power)) ; 
	s.erase(s.size()-1);
	return CONVERTED(s , converted , power +1 , ASCIINums) ;
}


int convertBase6ToBase10(string s)
{
	int converted = 0  , power = 0 ;
	vector<int> ASCIINums ;
	Build_ASCII_Vectro(ASCIINums , AllPossibleNumbers);
	return CONVERTED(s ,converted , power , ASCIINums);
}

int main()
{
	string s;
	while(cin>>s)
		cout << convertBase6ToBase10(s ) << endl;
	return 0;
}
















