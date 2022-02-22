#pragma once
#include <string>
#include "User.h"
using namespace std;

class Admin
{
public:
	const string password = "@bc123xyZ";

	void signIn();
	void viewUserData();
	void viewAllUsersData();
	void deleteUser();
	void deleteAllUsers();
	void giveDose();
	void give1stDose();
	void give2ndDose();
	void editUserStatues(int doseNo, int userIndex);
	void generalStatistics();
	void govStatistics();
	void checkLength();
};
