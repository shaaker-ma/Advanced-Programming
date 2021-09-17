#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "User.hpp"
#include "Task.hpp"
#include "List.hpp"
#include "Boss.hpp"

using namespace std;

#define LISTALREADYEXISTS "List already exists"
#define TASKALREADYEXISTS "Task already exists"
#define USERALREADYEXISTS "User already exists"

#define LISTDOESNOTEXIST  "List does not exist"
#define TASKDOESNOTEXIST  "Task does not exist"
#define USERDOESNOTEXIST  "User does not exist"

#define SUCCESS "Success"

Boss::Boss(){};

string Boss::addUser(string username){
	if(searchUser(username) == nullptr) {
		User userNew(username);
		allUsers.push_back(userNew);
		return SUCCESS; 
	}
	return USERALREADYEXISTS ;									
}

string Boss::addTask(string list, string name, unsigned int estimatedTime, unsigned int priority, string description){
	List* currentList = searchList(list);
	if(currentList == nullptr) 
		return LISTDOESNOTEXIST;   
	if(searchTasktInList(currentList,name))                           
		return TASKALREADYEXISTS;
	Task* taskNew = new Task(name,estimatedTime,priority,description);
	allTasks.push_back(taskNew);
	currentList->pushTaskToList(taskNew);
	return SUCCESS ;	
}

string Boss::editTask(string task, unsigned int estimatedTime, unsigned int priority, string description){
	for(int i=0; i<allTasks.size(); i++){
		if(allTasks[i]->getName() == task){
			allTasks[i]->updateTaskFeatures(estimatedTime,priority,description)  ; 
			return SUCCESS;
		}
	}
	return TASKDOESNOTEXIST;
}

string Boss::deleteTask(string task){
	Task* currentTask = searhTaskInAllTasks(task);
	if(currentTask != nullptr){
		for(uint i=0; i< allUsers.size(); i++){
			allUsers[i].deleteTaskFromUserIfExist(currentTask);
		}
		for(uint i=0; i< allLists.size(); i++){
			allLists[i].deleteTaskFromListIfExist(currentTask);
		}
		for(uint i=0; i< allTasks.size(); i++){
			if(allTasks[i] == currentTask)
				allTasks.erase(allTasks.begin() + i);
		}
		delete currentTask;
		return SUCCESS;
	}
	return TASKDOESNOTEXIST;
}

string Boss::assignTask(string task,string user){
	User* currentUser = searchUser(user);
	if(currentUser == nullptr)
		return USERDOESNOTEXIST;
	Task* currentTask = searhTaskInAllTasks(task);
	if(currentTask != nullptr){
		currentUser->pushTaskToUser(currentTask);
		currentTask->updateToAssigned();
		return SUCCESS;
	}
	return TASKDOESNOTEXIST;
}

string Boss::moveTask(string task, string list){
	List* listAim = searchList(list);
	if(listAim == nullptr)
		return LISTDOESNOTEXIST;
	Task* currentTask = searhTaskInAllTasks(task);
	if(currentTask != nullptr){
		//avval harja has delete she baad add she. 
		for(int i=0; i < allLists.size(); i++){
			allLists[i].deleteTaskFromListIfExist(currentTask);
		}
		listAim->pushTaskToList(currentTask);
		return SUCCESS;
	}
	return TASKDOESNOTEXIST;
}

string Boss::completeTask(string task){
	Task* currentTask = searhTaskInAllTasks(task); 
	if(currentTask != nullptr){
		currentTask->updateStatusToDone(); 
		return SUCCESS; 
	}
	return TASKDOESNOTEXIST;
}

string Boss::printTask(string task){
	Task* currentTask = searhTaskInAllTasks(task);
	bool taskExistsInUser = false;
	int indexUserIncludingTask;
	string taskInfo;
	if(currentTask == nullptr)
		return TASKDOESNOTEXIST;
	for(uint i=0; i<allUsers.size() ; i++){
		if(allUsers[i].TaskExistInUser(task)){
			taskExistsInUser = true;
			indexUserIncludingTask = i;
		}
	}
	if(taskExistsInUser == true){
		 taskInfo = currentTask->getName() + "\n" +
						  currentTask->getDescription() + "\n" +
						  "Priority: " + to_string(currentTask->getPriority()) + "\n" +
						  "Estimated Time: " + to_string(currentTask->getEstimatedTime()) + "\n" + 
						  "Assigned to " + allUsers[indexUserIncludingTask].getName() + "\n";

	}
	if(taskExistsInUser == false){
		 taskInfo = currentTask->getName() + "\n" +
						  currentTask->getDescription() + "\n" +
						  "Priority: " + to_string(currentTask->getPriority()) + "\n" +
						  "Estimated Time: " + to_string(currentTask->getEstimatedTime()) + "\n" + 
						  "Unassigned" + "\n";
	}
	return taskInfo;
}

string Boss::addList(string name){
	if(searchList(name) != nullptr) 
		return LISTALREADYEXISTS; 						
	List listNew(name);
	allLists.push_back(listNew);
	return SUCCESS ;							
}

string Boss::deleteList(string list){
	List* currentList = searchList(list);
	if(currentList != nullptr) {
		for(int i=0 ; i<allLists.size(); i++){
			if(allLists[i].getName() ==  list){
				allLists.erase(allLists.begin()+i);
				return SUCCESS ;
			}
		}
	}
	return LISTDOESNOTEXIST;
}

string Boss::printList(string list){
	List* currentList = searchList(list);
	bool taskExistsInUser = false;
	int indexUserIncludingTask;
	string listInfo = "";
	if(currentList != nullptr) {
		listInfo = listInfo + "List " + currentList->getName() + "\n";
		vector<Task*> TasksInGivenList;
		TasksInGivenList = currentList->getTaskOfList();
		for(uint i=0; i< TasksInGivenList.size() ; i++){
			listInfo = listInfo + to_string(TasksInGivenList[i]->getPriority()) + " | ";
			listInfo = listInfo + TasksInGivenList[i]->getName() + " | ";
			//search if task exists in any user's tasks
			for(uint j=0; j<allUsers.size() ; j++){				
				if(allUsers[j].TaskExistInUser(TasksInGivenList[i]->getName())){
					taskExistsInUser = true;
					indexUserIncludingTask = j;
					break;
				}
				else
				{
					taskExistsInUser = false;
					//indexUserIncludingTask = j;
				}
			}
			if(taskExistsInUser == true){
				listInfo = listInfo + allUsers[indexUserIncludingTask].getName() + " | ";
				listInfo = listInfo + to_string(TasksInGivenList[i]->getEstimatedTime()) + "h" + "\n";
			}
			if(taskExistsInUser == false){
				listInfo = listInfo + "Unassigned" + " | ";
				listInfo = listInfo + to_string(TasksInGivenList[i]->getEstimatedTime()) + "h" + "\n";
			}
		}
		return listInfo;
	}
	return LISTDOESNOTEXIST;
}

string Boss::printUserTasks(string user){
	User* currentUser = searchUser(user);
	string userInfo = "";
	if(currentUser != nullptr){
		vector<Task*> TasksOfGivenUser;
		TasksOfGivenUser = currentUser->getTaskOfUser();
		for(uint i=0; i< TasksOfGivenUser.size(); i++){
			userInfo = userInfo + to_string(TasksOfGivenUser[i]->getPriority()) + " | ";
			userInfo = userInfo + TasksOfGivenUser[i]->getName() + " | ";
			userInfo = userInfo + currentUser->getName() + " | ";
			userInfo = userInfo + to_string(TasksOfGivenUser[i]->getEstimatedTime()) + "h" + "\n";
		}
		return userInfo;	
	}
	return USERDOESNOTEXIST;
}


string Boss::printUserUnfinishedTasks(string user){
	User* currentUser = searchUser(user);
	string unfinishedTasks = "";
	if(currentUser != nullptr){
		vector<Task*> TasksOfGivenUser;
		TasksOfGivenUser = currentUser->getTaskOfUser();
		for(uint i=0; i< TasksOfGivenUser.size(); i++){
			if(TasksOfGivenUser[i]->getIsDone() == false ){
			unfinishedTasks = unfinishedTasks + to_string(TasksOfGivenUser[i]->getPriority()) + " | ";
			unfinishedTasks = unfinishedTasks + TasksOfGivenUser[i]->getName() + " | ";
			unfinishedTasks = unfinishedTasks + currentUser->getName() + " | ";
			unfinishedTasks = unfinishedTasks + to_string(TasksOfGivenUser[i]->getEstimatedTime()) + "h" + "\n";
			}
		}
		return unfinishedTasks;
	}
	return USERDOESNOTEXIST;
}

int Boss::printTotalEstimatedTime(){
	vector<Task*> TasksOfUser;
	int totalEstimatedTime = 0;
	int currentEstimatedTime = 0; 
	for(uint i=0; i< allUsers.size(); i++){
		TasksOfUser = allUsers[i].getTaskOfUser();
		for(uint j=0; j< TasksOfUser.size(); i++){
			currentEstimatedTime = TasksOfUser[j]->getEstimatedTime();
			if(currentEstimatedTime > totalEstimatedTime) totalEstimatedTime = currentEstimatedTime;
		}
		TasksOfUser.clear();
	}
	return totalEstimatedTime;
}


//eyyyyyyyyyne balaee amma check she aya isDone ?
int Boss::printTotalRemainingTime(){
	vector<Task*> TasksOfUser;
	int TotalRemainingTime = 0;
	int currentRemainingTime ; 
	bool taskIsDone ;
	for(uint i=0; i< allUsers.size(); i++){
		TasksOfUser = allUsers[i].getTaskOfUser();
		for(uint j=0; j< TasksOfUser.size(); i++){
			taskIsDone = TasksOfUser[j]->getIsDone();
			currentRemainingTime = TasksOfUser[j]->getEstimatedTime();
			if((currentRemainingTime > TotalRemainingTime) && taskIsDone == false) TotalRemainingTime = currentRemainingTime;
		}
		TasksOfUser.clear();
	}
	return TotalRemainingTime;
}

int Boss::printUserWorkload(string user){
	User* currentUser = searchUser(user);
	int userNotFound = 0 ;
	int workLoad = 0;
	if(currentUser != nullptr ){
		vector<Task*> TasksOfGivenUser;
		TasksOfGivenUser = currentUser->getTaskOfUser();
		for(uint i=0; i< TasksOfGivenUser.size(); i++){
			workLoad = workLoad + TasksOfGivenUser[i]->getEstimatedTime();
		}
		return workLoad;
	}
	return userNotFound;
}

string Boss::printUsersByWorkload(){
	vector<User> currentAllUsers = allUsers;
	int firstUserWorkload , secondUserWorkload ; 
	string userNamesByWorkload = "";
	for(uint j=0; j< currentAllUsers.size(); j++){
		for(uint i=0; i< currentAllUsers.size()-1; i++){
			 firstUserWorkload =  printUserWorkload(currentAllUsers[i].getName());
			 secondUserWorkload = printUserWorkload(currentAllUsers[i+1].getName());
			if(secondUserWorkload < firstUserWorkload){
				swap(currentAllUsers[i],currentAllUsers[i+1]);
			}
		}
	}
		for(uint i=0; i< currentAllUsers.size(); i++){
			userNamesByWorkload = userNamesByWorkload + currentAllUsers[i].getName() + "\n";
		}
	return userNamesByWorkload;
}

string Boss::printUsersByPerformance(){
	vector<User> currentAllUsers = allUsers;
	int performanceFirst =0 ;
	int performanceSecond=0 ; 
	int firstUserPerformance , secondUserPerformance; 
	string userNamesByPerformance = "";
	for(uint l=0; l<currentAllUsers.size(); l++ ){
		for(uint i=0; i< currentAllUsers.size()-1; i++) {
			vector<Task*> TasksOfUserFirst;
			TasksOfUserFirst = currentAllUsers[i].getTaskOfUser();
			for(uint j=0; j < TasksOfUserFirst.size(); j++){
				if(TasksOfUserFirst[j]->getIsDone() == true) {
					performanceFirst = performanceFirst + TasksOfUserFirst[j]->getEstimatedTime();
				}
			}
			vector<Task*> TasksOfUserSecond;
			TasksOfUserSecond = currentAllUsers[i+1].getTaskOfUser();
			for(uint k=0; k< TasksOfUserSecond.size(); k++){
				if(TasksOfUserSecond[k]->getIsDone() == true) {
					performanceSecond = performanceSecond + TasksOfUserSecond[k]->getEstimatedTime();
				}	
			}
			firstUserPerformance =  performanceFirst;
			secondUserPerformance = performanceSecond;
			performanceFirst =0 ;
		    performanceSecond=0 ; 
		    TasksOfUserFirst.clear();
		    TasksOfUserSecond.clear();

			if(secondUserPerformance > firstUserPerformance){
				swap(currentAllUsers[i],currentAllUsers[i+1]);
			}
		}
	}

	for(uint i=0; i< currentAllUsers.size(); i++){
		  userNamesByPerformance = userNamesByPerformance + currentAllUsers[i].getName() + "\n";
	}
	return userNamesByPerformance;
}

string Boss::printAllLists(){
	string printOfAllLists = "";
	for(uint i=0; i < allLists.size(); i++){
		printOfAllLists = printOfAllLists + printList(allLists[i].getName());
	}
	return printOfAllLists;
}

string Boss::infoOfTaskToPrint(Task* currentTask){
	bool taskExistsInUser = false;
	int indexUserIncludingTask;
	string taskInfo;
	
	for(uint i=0; i<allUsers.size() ; i++){
		if(allUsers[i].TaskExistInUser(currentTask->getName())){
			taskExistsInUser = true;
			indexUserIncludingTask = i;
		}
	}
	if(taskExistsInUser == true){
		 taskInfo = 
						  
						   to_string(currentTask->getPriority()) + " | " +
						  currentTask->getName() + " | " +
						   allUsers[indexUserIncludingTask].getName() + " | " +
						   to_string(currentTask->getEstimatedTime()) + "h" +  "\n";

	}
	if(taskExistsInUser == false){
		taskInfo = 
						  
						   to_string(currentTask->getPriority()) + " | " +
						  currentTask->getName() + " | " +
						   "Unassigned" + " | " +
						   to_string(currentTask->getEstimatedTime()) + "h" +  "\n";
	}
	return taskInfo;
}


string Boss::printUnassignedTasksByPriority(){
	string printOfAllUnassignedTasksByPriority = "";
	vector<Task*> currentTasks;
	for(uint i=0; i< allTasks.size(); i++){
		if(allTasks[i]->getIsAssigned() == false)
			currentTasks.push_back(allTasks[i]);
	}
	for(uint j=0; j< currentTasks.size(); j++){
		for(uint k=0; k< currentTasks.size()-1; k++){
			if(currentTasks[k+1]->getPriority() <  currentTasks[k]->getPriority())
				swap(currentTasks[k],currentTasks[k+1]);
		}
	}
	for(uint i=0; i < currentTasks.size(); i++){
		printOfAllUnassignedTasksByPriority = printOfAllUnassignedTasksByPriority + infoOfTaskToPrint(currentTasks[i]);
	}
	return printOfAllUnassignedTasksByPriority;
}

string Boss::printAllUnfinishedTasksByPriority(){
	string printOfAllUnfinishedTasksByPriority = "";
	vector<Task*> currentTasks; 
	for(uint i=0; i< allTasks.size(); i++){
		if(allTasks[i]->getIsDone() == false)
			currentTasks.push_back(allTasks[i]);
	}
	for(uint j=0; j< currentTasks.size(); j++){
		for(uint k=0; k< currentTasks.size()-1; k++){
			if(currentTasks[k+1]->getPriority() <  currentTasks[k]->getPriority())
				swap(currentTasks[k],currentTasks[k+1]);
		}
	}
	for(uint i=0; i < currentTasks.size(); i++){
		printOfAllUnfinishedTasksByPriority = printOfAllUnfinishedTasksByPriority + infoOfTaskToPrint(currentTasks[i]);
	}
	return printOfAllUnfinishedTasksByPriority;
}



User* Boss::searchUser(string userName){
	for(uint i=0 ; i< allUsers.size() ; i++){
		if(userName == allUsers[i].getName()) 
			return &allUsers[i];
	}
	return nullptr;
}

bool Boss::searchTasktInList(List* currentList, string name){
	if(currentList->givenTaskExists(name)) 
		return true;
	return false;
}


List* Boss::searchList(string name){
	for(uint i=0; i < allLists.size(); i++){
		if(name == allLists[i].getName()) 
			return &allLists[i];
	}
	return nullptr;
}

Task* Boss::searhTaskInAllTasks(string task){
	for(uint i=0; i< allTasks.size(); i++){
		if(task == allTasks[i]->getName()) 
			return allTasks[i];
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////



