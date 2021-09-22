#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
// #include <sstream> 
#include <fstream>
#include <cmath>
// #include <iomanip>
using namespace std;
#include "exceptions.hpp"
#include "manageMarket.hpp"

int main(){
	string command;
	ManageMarket manageJomeBazar;
	while(getline(cin,command)){
		// Exception* Ex;
		try{
			manageJomeBazar.manageCommands(command);
		}catch(Exception* Ex){
			Ex->what();
		}
		command.erase();
	}
}