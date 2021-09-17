#include <string>
#include <iostream>
#include "utrello_interface.hpp"
#include "Boss.hpp"

using namespace std;

Boss boss;

UTrelloInterface::UTrelloInterface(){};

string UTrelloInterface::addUser(string username){
	return boss.addUser(username);
}
string UTrelloInterface::addTask(string list, string name, unsigned int estimatedTime, unsigned int priority, string description){
	return boss.addTask(list, name, estimatedTime, priority, description);
}
string UTrelloInterface::editTask(string task, unsigned int estimatedTime, unsigned int priority, string description){
	return boss.editTask(task, estimatedTime, priority, description);
}
string UTrelloInterface::deleteTask(string task){
	return boss.deleteTask(task);
}
string UTrelloInterface::assignTask(string task, string user){
	return boss.assignTask(task, user);
}
string UTrelloInterface::moveTask(string task, string list){
	return boss.moveTask(task, list);
}
string UTrelloInterface::completeTask(string task){
	return boss.completeTask(task);
}
string UTrelloInterface::printTask(string task){
	return boss.printTask(task);
}
string UTrelloInterface::addList(string name){
	return boss.addList(name);
}
string UTrelloInterface::deleteList(string list){
	return boss.deleteList(list);
}
string UTrelloInterface::printList(string list){
	return boss.printList(list);
}
string UTrelloInterface::printUserTasks(string user){
	return boss.printUserTasks(user);
}
string UTrelloInterface::printUserUnfinishedTasks(string user){
	return boss.printUserUnfinishedTasks(user);
}
int UTrelloInterface::printTotalEstimatedTime(){
	return boss.printTotalEstimatedTime();
}
int UTrelloInterface::printTotalRemainingTime(){
	return boss.printTotalRemainingTime();
}
int UTrelloInterface::printUserWorkload(string user){
	return boss.printUserWorkload(user);
}

string UTrelloInterface::printUsersByWorkload(){
	return boss.printUsersByWorkload();
}
string UTrelloInterface::printUsersByPerformance(){
	return boss.printUsersByPerformance();
}
string UTrelloInterface::printAllLists(){
	return boss.printAllLists();
}

string UTrelloInterface::printUnassignedTasksByPriority(){
	return boss.printUnassignedTasksByPriority();
}

string UTrelloInterface::printAllUnfinishedTasksByPriority(){
	return boss.printAllUnfinishedTasksByPriority();
}

