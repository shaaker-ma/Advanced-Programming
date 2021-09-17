#ifndef __List_HPP__
#define __List_HPP__


#include <string>
#include <vector>

#include "Task.hpp"

using namespace std;

class List{
	
	public:
	List(string nameNew);
	string getName(){return name;}
	bool givenTaskExists(string nameTask);
	void pushTaskToList(Task* taskNew);
	void deleteTaskFromListIfExist(Task* task);
	vector<Task*> getTaskOfList(){return taskOfList;}
	private:

	string name;
	vector<Task*> taskOfList;
};

#endif