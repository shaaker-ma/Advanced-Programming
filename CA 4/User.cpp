#include <string>
#include <vector>

#include "User.hpp"
#include "Task.hpp"

using namespace std;

User::User(string userName) {
	name = userName;
}

void User::pushTaskToUser(Task* taskNew){
	taskOfUser.push_back(taskNew);
}

void User::deleteTaskFromUserIfExist(Task* task){
	for(uint i=0; i< taskOfUser.size(); i++){
		if(task->getName() == taskOfUser[i]->getName())
			taskOfUser.erase(taskOfUser.begin() + i);
	} 
}

bool User::TaskExistInUser(string task){
	for(uint i=0; i<taskOfUser.size(); i++){
		if(task == taskOfUser[i]->getName())
			return true;
	}
	return false;
}
