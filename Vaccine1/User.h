#pragma once
#include <string>
using namespace std;

class User
{
public:
	string name, password, country, gov;
	char gender;
	int age;
	long long NID;
	bool isVaccined = false, isFullyVaccinated = false;

	User();
	User(string name, char gender, string password, string country, string gov, int age, long long NID, bool isVaccined, bool isFullyVaccinated);
	void signUp();
	void signIn();
	void displayData();
	void updateData();
	void deleteAccount();
	void chooseGov();
};
