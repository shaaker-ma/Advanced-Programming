#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <unistd.h>
using namespace std;

#define PI 3.14159265
#define PI_IN_DEGREE 180


int main() {

	// float x=180+30;
	// int pos = 50;
	// pos = pos + floor(5*sin(x*PI/PI_IN_DEGREE));
	// usleep(1000);
	// cout << pos << endl;
	int digit;
	int y = 3111;
	while (y > 0)
	{
	cout << "ha"
    digit = y%10;
    y /= 10;
    cout << digit << endl;
	}


	return 0;
}