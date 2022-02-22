#pragma once
#include "User.h"
#include "LinkedList.cpp"
#include "Queue.cpp"

class Common
{
public:
	static LinkedList<User> usersList;
	static Queue <long long> dose1WaitingList, dose2WaitingList;

	long long check_ID();
	int findUser(long long NID);
	void displayUserData(long long NID);
	void removeFromWaitingList(User user);
};
