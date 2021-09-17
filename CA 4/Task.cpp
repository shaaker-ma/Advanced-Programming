#include <string>
#include <vector>

#include "Task.hpp"

using namespace std;


Task::Task(string nameNew, unsigned int estimatedTimeNew, unsigned int priorityNew, string descriptionNew){
	name = nameNew;
	estimatedTime = estimatedTimeNew;
	priority = priorityNew;
	description = descriptionNew;
	isDone= false;
	isAssigned = false;
}

void Task::updateTaskFeatures(unsigned int estimatedTimeNew, unsigned int priorityNew, string descriptionNew){
	estimatedTime = estimatedTimeNew;
	priority = priorityNew;
	description = descriptionNew;
}

void Task::updateStatusToDone(){
	isDone= true;
}

void Task::updateToAssigned(){
	isAssigned = true;
}


