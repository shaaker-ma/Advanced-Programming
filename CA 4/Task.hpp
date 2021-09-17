#ifndef __Task_HPP__
#define __Task_HPP__


#include <string>
#include <vector>

using namespace std;

class Task {
	
	public:
	Task(string nameNew, unsigned int estimatedTimeNew, unsigned int priorityNew, string descriptionNew);
	string getName(){return name;}
	unsigned int getEstimatedTime(){return estimatedTime;}
	unsigned int getPriority(){return priority;}
	string getDescription(){return description;}
	bool getIsDone(){return isDone;}
	bool getIsAssigned(){return isAssigned;}

	void updateTaskFeatures(unsigned int estimatedTimeNew, unsigned int priorityNew, string descriptionNew);
	void updateStatusToDone();
	void updateToAssigned();

	private:
	string name;
	unsigned int estimatedTime;
	unsigned int priority;
	string description;
	bool isDone;
	bool isAssigned;
};


#endif