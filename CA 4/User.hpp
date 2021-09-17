#ifndef __User_HPP__
#define __User_HPP__

#include <string>
#include <vector>

#include "Task.hpp"

using namespace std;

class User{
	
	public:
	User(string userName);
	string getName(){return name;}
	void pushTaskToUser(Task* taskNew);
	void deleteTaskFromUserIfExist(Task* task);
	bool TaskExistInUser(string task);
	vector<Task*> getTaskOfUser(){return taskOfUser;}
	private:
	string name;
	vector<Task*> taskOfUser;
};

#endif