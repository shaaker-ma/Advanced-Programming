#include <string>
#include <vector>

#include "List.hpp"
#include "Task.hpp"

using namespace std;

List::List(string nameNew){
	name = nameNew;
}

bool List::givenTaskExists(string nameTask){
	for(int i =0 ; i<taskOfList.size() ; i++){
		if(nameTask == taskOfList[i]->getName()) 
			return true;
	}
	return false;
}

void List::pushTaskToList(Task* taskNew){
	taskOfList.push_back(taskNew);
}

void List::deleteTaskFromListIfExist(Task* task){
	for(uint i=0; i< taskOfList.size(); i++){
		if(task->getName() == taskOfList[i]->getName())
			taskOfList.erase(taskOfList.begin() + i);
	} 
}

