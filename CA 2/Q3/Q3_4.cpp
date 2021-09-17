#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 
using namespace std;


int StringToInt(string str) {
	int intOfstr = atoi(str.c_str());
	return intOfstr ;
}

int FillVector(vector<string>& given , string str , string& temp_str , int repeat , int beging_with) {
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
 
void PrepareNumVector(vector<string>& given){
	string str , temp_str ;
	temp_str = "" ;
    getline(cin , str);
	str.push_back(' '); 
    int beging_with = 0 ;
    int repeat = str.size()+2 ;
    int ResFillVector = FillVector(given , str , temp_str , repeat , beging_with) ;
    return ;
}

int MakeTableCells(vector<vector<char> >& Table, string RestLines , int row , int col ,int ActualRows , int ActualCols ){
 	
 	if(col == 0 ) return 1 ;
 	else {
 		Table[ActualRows-row][ActualCols-col] = RestLines[ActualCols-col];
 		col = col -1 ;
 		return MakeTableCells(Table , RestLines , row  , col , ActualRows , ActualCols );
	 }
	
 }

void MakeTable(vector<vector<char> >& Table, int row ,  int col ,int ActualRows , int ActualCols ) {
	if(row == 0) return  ; 
	else{
		string RestLines ;
  		getline(cin , RestLines) ;
  		int TableMadeCell = MakeTableCells(Table , RestLines , row  , col , ActualRows , ActualCols ) ;
  		RestLines.erase();
  		row = row-1 ; 
   		MakeTable(Table, row , col , ActualRows , ActualCols ) ;
   }
}

int CountMines(int SelectedRow , int SelectedCol , vector<vector<char> >& Table , int TableRows , int TableCols) {
	
	int Num_Mines = 0 ;
	if(SelectedRow + 1 <=  TableRows && SelectedCol + 1 <= TableCols ){
		if(Table[SelectedRow+1][SelectedCol+1] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if(SelectedRow + 1 <=  TableRows && SelectedCol - 1 >= 0 ){
		if(Table[SelectedRow+1][SelectedCol-1] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if(SelectedRow + 1 <=  TableRows ){
		if(Table[SelectedRow+1][SelectedCol] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if(SelectedCol + 1 <= TableCols ){
		if(Table[SelectedRow][SelectedCol+1] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if( SelectedCol - 1 >= 0 ){
		if(Table[SelectedRow][SelectedCol-1] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if(SelectedRow - 1 >= 0 && SelectedCol + 1 <= TableCols ){
		if(Table[SelectedRow-1][SelectedCol+1] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if(SelectedRow - 1 >= 0  && SelectedCol - 1 >=0 ){
		if(Table[SelectedRow-1][SelectedCol-1] == 'M') Num_Mines = Num_Mines+1 ;
	}
	if(SelectedRow - 1 >= 0 ){
		if(Table[SelectedRow-1][SelectedCol] == 'M') Num_Mines = Num_Mines+1 ;
	}
	
	return Num_Mines ; 
}

//...................
int RightAvailable(vector<vector<char> >& Solve ,vector<vector<char> >& Table ,  int CurrentRow ,  int CurrentCol ,int TableRows , int TableCols){
	if(CurrentCol +1 <= TableCols && Table[CurrentRow][CurrentCol +1] != 'M' && Solve[CurrentRow][CurrentCol+1] == '*') {
		return 1 ;
		
	}
	return 0 ;
}

int UpAvailable(vector<vector<char> >& Solve , vector<vector<char> >& Table , int CurrentRow ,  int CurrentCol ,int TableRows , int TableCols){
	if(CurrentRow -1 >= 0 && Table[CurrentRow-1][CurrentCol] != 'M' && Solve[CurrentRow-1][CurrentCol] == '*') {
		return 1 ;
	}
	return 0 ;
}

int LeftAvailable(vector<vector<char> >& Solve , vector<vector<char> >& Table , int CurrentRow ,  int CurrentCol ,int TableRows , int TableCols){
	if(CurrentCol -1 >= 0 && Table[CurrentRow][CurrentCol -1] != 'M' && Solve[CurrentRow][CurrentCol-1] == '*') {
		return 1 ;
	}
	return 0 ;
}

int DownAvailable(vector<vector<char> >& Solve , vector<vector<char> >& Table , int CurrentRow ,  int CurrentCol ,int TableRows , int TableCols){
	if(CurrentRow +1 <= TableRows && Table[CurrentRow+1][CurrentCol] != 'M' && Solve[CurrentRow+1][CurrentCol] == '*') {
		return 1 ;
	}
	return 0 ;
}
 
void MakeResponce(vector<vector<char> >& Solve , int SelectedRow , int SelectedCol , vector<vector<char> >& Table , int CurrentRow ,  int CurrentCol ,int TableRows , int TableCols ) {

	if(CountMines(CurrentRow,CurrentCol,Table,TableRows,TableCols) > 0) 
	{
		Solve[CurrentRow][CurrentCol] = CountMines(CurrentRow,CurrentCol,Table,TableRows,TableCols) + '0';
		return ;
	}

	else 
	{
		if(RightAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			// CurrentCol = CurrentCol +1 ;
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow ,  CurrentCol+1 , TableRows , TableCols ) ; 

		}

		if(RightAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols) && UpAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			cout <<"up and right" << endl;
			cout << CurrentRow << CurrentCol << endl ;
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow -1 ,  CurrentCol +1 , TableRows , TableCols ) ; 
		}

		if(UpAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			// CurrentRow = CurrentRow -1 ; 
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow-1 ,  CurrentCol , TableRows , TableCols ) ; 
		}

		if(UpAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols) && LeftAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			cout <<"up , left" << endl;
			cout << CurrentRow << CurrentCol << endl ;
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow-1 ,  CurrentCol-1 , TableRows , TableCols ) ; 
		}

		if(LeftAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			// CurrentCol = CurrentCol -1 ;		
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow ,  CurrentCol-1 , TableRows , TableCols ) ; 
		}
		
		if(DownAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols) && LeftAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			cout <<"down and left" << endl;
			cout << CurrentRow << CurrentCol << endl ;
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow +1,  CurrentCol-1 , TableRows , TableCols ) ; 
		}
		
		if(DownAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			//CurrentRow = CurrentRow +1 ; 
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow +1 ,  CurrentCol , TableRows , TableCols ) ; 
		}
		
		if(DownAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols) && RightAvailable(Solve,Table,CurrentRow , CurrentCol ,TableRows , TableCols)){
			Solve[CurrentRow][CurrentCol] = 0 + '0';
			cout <<"down and right" << endl;
			cout << CurrentRow << CurrentCol << endl ;
			MakeResponce(Solve , SelectedRow , SelectedCol , Table , CurrentRow+1 ,  CurrentCol+1 , TableRows , TableCols ) ;
		}

	}

}

void PrintResponce(vector<vector<char> > Solve){
	for(int i =0 ; i < Solve.size() ; i++) {
	    for(int j = 0 ; j < Solve[i].size() ; j++) {
			cout << Solve[i][j] ;
		}
		cout << endl ; 
	}
}

void MineSweeper(){
	vector<string> given_num ;
	PrepareNumVector(given_num) ;
	
    int rows = StringToInt(given_num[0]) ; 
    int cols = StringToInt(given_num[1]) ;
    int SelectedCol = StringToInt(given_num[2])-1;
    int SelectedRow = StringToInt(given_num[3])-1;
    vector<char> VectTable(cols, '.') ; 
  	vector<vector<char> > Table(rows,VectTable ) ;
  	vector<char> VectSolve(cols, '*') ; 
	vector<vector<char> > Solve(rows,VectSolve ) ;  
  	
  	MakeTable(Table, rows , cols , rows , cols ) ; 
	MakeResponce(Solve ,SelectedRow, SelectedCol  , Table , SelectedRow , SelectedCol , rows , cols) ;
	PrintResponce(Solve);
}

int main() {
	MineSweeper() ;
  	return 0; 
}
