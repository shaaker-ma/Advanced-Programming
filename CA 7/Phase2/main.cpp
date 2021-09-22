#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std ;

#include "CommentManagement.hpp"

int main(){
	CommentManagement cm;
	string command;
	getline(cin,command);
	if(command == "POST evaluateModel"){
		cm.evaluate(command);
	}
	return 0;
}