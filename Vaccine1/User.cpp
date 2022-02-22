#include <iostream>
#include <stdlib.h>
#include <thread>
#include <string>
#include "User.h"
#include "Menus.h"
#include "Common.h"
using namespace std;

Menus menus;
Common common;

User::User()
{
	NID = 0;
	age = 0;
	gender = 'U';
}

User::User(string name, char gender, string password, string country, string gov, int age, long long NID, bool isVaccined, bool isFullyVaccinated)
{
	this->name = name;
	this->gender = gender;
	this->password = password;
	this->country = country;
	this->gov = gov;
	this->age = age;
	this->NID = NID;
	this->isVaccined = isVaccined;
	this->isFullyVaccinated = isFullyVaccinated;
	if (!isVaccined)
		common.dose1WaitingList.enqueue(NID);
	else if (!isFullyVaccinated)
		common.dose2WaitingList.enqueue(NID);
	common.usersList.Append(*this);
}

void User::signUp()
{
	system("CLS");
	cout << "\t\t\t\t\tSign Up\n";
	cout << "Name: ";
	cin >> name;
	NID = common.check_ID();
	int n = common.findUser(NID);
	if (n != -1) {
		cout << "National ID already has an account.\nProcessing...";
		this_thread::sleep_for(3s);
		menus.user1stMenu();
	}
	cout << "Password: ";
	cin >> password;
	cout << "Gender (F/M): ";
	cin >> gender;
	while (!((gender == 'F') || (gender == 'f') || (gender == 'M') || (gender == 'm')))
	{
		cout << "please insert a valid gender ";
		cin >> gender;

	}
	cout << "Age: ";
	cin >> age;
	cout << "Country: Egypt\n";
	country = "Egypt";
	chooseGov();
	cout << "Did you take 1st dose? (Y/N): ";
	char x;
	cin >> x;
	while (!(x == 'Y' || x == 'y' || x == 'N' || x == 'n'))
	{
		cout << "please insert a valid choice :  ";
		cin >> x;
	}
	if (x == 'Y' || x == 'y') {
		isVaccined = true;
		cout << "Did you take 2nd dose? (Y/N): ";
		cin >> x;
		while (!(x == 'Y' || x == 'y' || x == 'N' || x == 'n'))
		{
			cout << "please insert a valid choice :  ";
			cin >> x;
		}
		if (x == 'Y' || x == 'y') {
			isFullyVaccinated = true;
		}
		else if (x == 'N' || x == 'n') {
			common.dose2WaitingList.enqueue(NID);
		}
	}
	else {
		common.dose1WaitingList.enqueue(NID);
	}
	common.usersList.Append(*this);
}

void User::signIn()
{
	system("CLS");
	string pass;
	cout << "\t\t\t\t\tSign In\n";
	NID = common.check_ID();
	int n = common.findUser(NID);
	while (n == -1) {
		cout << "Wrong national ID. Please try again.\nNational ID: ";
		NID = common.check_ID();
		n = common.findUser(NID);
	}
	cout << "Password: ";
	cin >> pass;
	while (common.usersList.At(n).password != pass)
	{
		cout << "Wrong password. Please try again.\nPassword: ";
		cin >> pass;
	}
	*this = common.usersList.At(n);
}

void User::displayData()
{
	common.displayUserData(NID);
}

void User::updateData()
{
	system("CLS");
	string editString;
	int userInList = common.findUser(NID);

	int index = 0;
	system("CLS");
	cout << "\t\t\t\t\tUpdate Data\n";
	cout << "what would you like to edit?\n";
	cout << "1. Name\n2. Age\n3. Governate\n4. Password\n0. Back\nChoice: ";
	cin >> index;
	switch (index)
	{
	case 1:
		cout << "Enter new Name:\n";
		cin >> editString;
		name = editString;
		common.usersList.DeleteAt(userInList);
		common.usersList.Append(*this);
		break;

	case 2:
		cout << "Enter new Age:\n";
		int newAge;
		cin >> newAge;
		this->age = newAge;
		common.usersList.DeleteAt(userInList);
		common.usersList.Append(*this);
		break;

	case 3:
		chooseGov();
		common.usersList.DeleteAt(userInList);
		common.usersList.Append(*this);
		break;

	case 4:
		cout << "Enter new Password:\n";
		cin >> editString;
		this->password = editString;
		common.usersList.DeleteAt(userInList);
		common.usersList.Append(*this);
		break;

	case 0:
		break;
	default:
		cout << "Invalid choice";
		this_thread::sleep_for(750ms);
		updateData();
	}
}

void User::deleteAccount()
{
	system("CLS");

	int userIndex = common.findUser(NID);
	User user = common.usersList.At(userIndex);
	if (!user.isFullyVaccinated)
	{
		common.removeFromWaitingList(user);
	}
	common.usersList.DeleteAt(userIndex);
	cout << "Deleting...";
	this_thread::sleep_for(3s);
}

void User::chooseGov()
{
	cout << "Governorate:\n1. Cairo\n2. Alex\n3. Giza\nChoice: ";
	char choice;
	cin >> choice;
	while (!((choice == '1') || (choice == '2') || (choice == '3')))
	{
		cout << "Please insert a valid choice: ";
		cin >> choice;
	}
	switch (choice)
	{
	case '1':
		gov = "Cairo";
		break;
	case '2':
		gov = "Alex";
		break;
	case '3':
		gov = "Giza";
	default:
		break;
	}
}
