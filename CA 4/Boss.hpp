#ifndef __BOSS_HPP__
#define __BOSS_HPP__

#include <string>
#include <vector>

#include "User.hpp"
#include "Task.hpp"
#include "List.hpp"

class Boss
{
public:
	Boss();

	std::string addUser(std::string username);
	std::string addTask(std::string list, std::string name, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string deleteTask(std::string task);
	std::string assignTask(std::string task, std::string user);
	std::string moveTask(std::string task, std::string list);
	std::string completeTask(std::string task);
	std::string printTask(std::string task);

	std::string addList(std::string name);
	std::string deleteList(std::string list);
	std::string printList(std::string list);

	std::string printUserTasks(std::string user);
	std::string printUserUnfinishedTasks(std::string user);

	int printTotalEstimatedTime();
	int printTotalRemainingTime();

    int printUserWorkload(std::string user);

	std::string printUsersByWorkload();
	std::string printUsersByPerformance();

    std::string printAllLists();
  	std::string printUnassignedTasksByPriority();
	std::string printAllUnfinishedTasksByPriority();

	string infoOfTaskToPrint(Task* currentTask);
	User* searchUser(string userName);
	bool searchTasktInList(List* currentList, string name);
	List* searchList(string name);
	Task* searhTaskInAllTasks(string task);

private:
	vector <User> allUsers;
	vector <Task*> allTasks;
	vector <List> allLists;
};

#endif