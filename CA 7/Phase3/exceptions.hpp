#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <iostream>
#include <string>
using namespace std ;

class Exception{
public:
	virtual void what() = 0; 
};

class NotFound : public Exception {
public:
	virtual void what(){
		cout << "Not Found" << endl;
	}
};

class BadRequest : public Exception {
public:
	virtual void what() {
		cout << "Bad Request" << endl;
	}
};

class PermissionDenied : public Exception {
public:
	virtual void what() {
		cout << "Permission Denied" << endl;
	}
};

#endif