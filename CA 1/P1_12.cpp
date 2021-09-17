#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include<sstream>  // for converting int to string
#include <fstream> // file stream for open and close
using namespace std ;

#define FirstASCII_Num 48 
#define LastASCII_Num 57 
#define StaticCommand 8 

bool CheckStaticCommand(string data){
	if(data[0] == 's' && data[1] == 'h' && data[2] == 'o' 
		 && data[3] == 'w' && data[4] == '_' && data[5] == 'm'
			&& data[6] == 's' && data[7] == 'g' && data[8] == ' ' &&
			      FirstASCII_Num <= (int)data[9] && LastASCII_Num >= (int)data[9]){
		return true ;
	}
	return false ;
}

vector<string> Split(string to_be_splitted , char splitter) {
  vector<string> substrings;
  int char_iterator = 0 ;
  while(char_iterator < to_be_splitted.size()) {
  	string sub;
  	while(to_be_splitted[char_iterator] != splitter && char_iterator < to_be_splitted.size()) {
  		sub.push_back(to_be_splitted[char_iterator]);
  		char_iterator ++;
    }
   	substrings.push_back(sub);
    char_iterator ++;
  }
  return substrings;
}

vector<vector<string> > Relations(){
	vector<vector<string> >  file_people_within ;
	ifstream file_people ;
	file_people.open("people.txt") ;

	if (file_people.is_open()) {
		string line ;
		while (getline(file_people , line)) {
			char splitter = ' ' ;
			vector<string> save = Split(line,splitter) ;
			save.back().pop_back() ;
			file_people_within.push_back(save) ;			
		}
	}	
	file_people.close() ;	

	return file_people_within ;
}

bool IfInRel(vector<vector<string> > relation , string Send_ID , string Rec_ID){


	bool result = false ;
	for(int i =0 ; i< relation.size() ; i++){
			for(int j =0 ; j< relation[i].size() ; j++){
				if ( (relation [i][0] == Send_ID && relation [i][j] == Rec_ID) ||
				(relation [i][0] == Rec_ID  && relation [i][j] == Send_ID))
					{
						result = 1;
					}
			}
	}
	return result ;
}

void MakeUserFiles(vector<vector<string> > relation){
	int Num_Files ;
	Num_Files = relation.size() ;
	string File_Name , File_Name_txt ; 
	
	for(int i = 0 ; i < Num_Files ; i++ ){
		
		ofstream file ;
		stringstream ss;  
  		ss<< i;  
  		ss>> File_Name;
  		File_Name_txt = File_Name + ".txt" ;
		file.open(File_Name_txt.c_str()) ; 
		file.close() ;
	}
}

void SendMessages(vector<vector<string> > relation , string data){
	
	string Send_ID = "" ;
	string Rec_ID  = "" ;
	string message = "" ;
	
	int i =0 ;
	while(i < data.size()){
		while(data[i] != ' '){
			Send_ID = Send_ID + data[i] ;
			i++ ;
		}
		i++; //to skip the space between sender and receiver
		while(data[i] != ' '){
			Rec_ID = Rec_ID + data[i] ;
			i++ ;
		}
		i++; ////to skip the space between receiver and message 
		while(i < data.size()){
			message = message + data[i] ;
			i++ ;
		}
	}
	while(message.back() == ' '){
	 	message = message.substr(0, message.size()-1) ;
	}

	if (IfInRel(relation, Send_ID , Rec_ID)){
		cout << "sent" << endl ;

		ofstream WriteMessage ;
		string File_name = Rec_ID +".txt";
		WriteMessage.open(File_name.c_str(), ios :: app) ;
		WriteMessage << Send_ID << ' ' << message << '\n' ;
		WriteMessage.close() ;
	}
	else{
		cout << "failed" << endl;
	}
}

void ReadMessages(vector<vector<string> > relation , string data) {
	int i = StaticCommand +1 ;
	int DataSize = data.size();
	string ID = "" ;
	int ID_Int =0 ;
	while(i<DataSize){
		if(FirstASCII_Num <= (int)data[i] && LastASCII_Num >= (int)data[i]) {
			ID = ID + data[i] ;
		}
		i++ ;
	}
	int CheckInt = 0 ;
	int IDSize = ID.size() ;
	for(int j =0 ; j < IDSize ; j++) {
		if( (FirstASCII_Num <= (int)ID[j] && LastASCII_Num >= (int)ID[j]) ) CheckInt++ ;
	}
	if(CheckInt == IDSize){ 
	//we know it is a num
	// now we have to know if we have that ID
		 stringstream geek(ID);
		 geek >> ID_Int ; 
		 if(ID_Int <= relation.size()){
		 	//we know we have this ID
		 	string message , FileName;
		 	FileName = ID + ".txt" ;
  			ifstream myfile (FileName.c_str());
  			if (myfile.is_open()) {
    			while ( getline (myfile,message) ) {
      				cout << message << endl ;
    			}
    			myfile.close();
  			 }
		 }
	}
}

void Network(){	
	vector<vector<string> > relation ;
    relation =  Relations();
	MakeUserFiles(relation);	
	string data ;
	while(getline(cin , data)) {
		if ((FirstASCII_Num <= (int)data[0] && LastASCII_Num >= (int)data[0])){
			 SendMessages(relation , data) ;
		}
		else if (CheckStaticCommand(data)){
			ReadMessages(relation , data ) ;
		}	
		else {
    			cout << "failed" << endl ;
		}
	}
}

int main() {
	Network() ;
	return 0 ;
}