#include "Menus.h"
#include <iostream>
#include <stdlib.h>
#include <thread>
#include "User.h"
#include "Admin.h"
#include "Common.h"
using namespace std;

void Menus::welcomeMenu()
{
	system("CLS");
	cout << "\t\t\t\t\tWelcome in Egyption Vaccine System.\n";
	cout << "Continue as:\n1. User\n2. Admin\nChoice: ";
	cin >> choice;
	Admin admin;
	switch (choice)
	{
	case '1':
		user1stMenu();
		break;

	case '2':
		admin.signIn();
		break;

	default:
		cout << "Wrong choice, please enter valid choice.\nProcessing...";
		this_thread::sleep_for(3s);
		welcomeMenu();
		break;
	}
}

void Menus::adminMenu()
{
	Admin admin;
	system("CLS");
	cout << "1. View specific user's info.\n2. View all users' info.\n3. Delete specific user.\n4. Delete all users.\n5. Give a dose.\n6. View general statistics.\n7. View each Governorate statistics.\n0. Go Back.\nChoice: ";
	cin >> choice;
	switch (choice)
	{
	case '1':
		admin.checkLength();
		admin.viewUserData();
		adminMenu();
		break;

	case '2':
		admin.checkLength();
		admin.viewAllUsersData();
		adminMenu();
		break;

	case '3':
		admin.checkLength();
		admin.deleteUser();
		adminMenu();
		break;

	case '4':
		admin.checkLength();
		admin.deleteAllUsers();
		adminMenu();
		break;

	case '5':
		admin.giveDose();
		adminMenu();
		break;

	case '6':
		admin.generalStatistics();
		adminMenu();
		break;
		
	case '7':
		admin.govStatistics();
		adminMenu();
		break;

	case '0':
		welcomeMenu();
		break;

	default:
		cout << "Wrong choice, please enter valid choice.\nProcessing...";
		this_thread::sleep_for(3s);
		adminMenu();
		break;
	}
}

void Menus::user1stMenu()
{
	system("CLS");
	cout << "1. Sign up.\n2. Sign in.\nIf you want to go back enter 0.\nChoice: ";
	cin >> choice;
	User user;
	switch (choice)
	{
	case '0':
		welcomeMenu();
		break;

	case '1':
		user.signUp();
		user2ndMenu(user);
		break;

	case '2':
		user.signIn();
		user2ndMenu(user);
		break;

	default:
		cout << "Wrong choice, please enter valid choice.\nProcessing...";
		this_thread::sleep_for(3s);
		user1stMenu();
		break;
	}
}

void Menus::user2ndMenu(User user)
{
	system("CLS");
	cout << "1. Display data.\n2. Update data. \n3. Delete my account.\nIf you want to exit enter 0.\nChoice: ";
	cin >> choice;
	switch (choice)
	{
	case '0':
		user1stMenu();
		break;

	case '1':
		user.displayData();
		user2ndMenu(user);
		break;

	case '2':
		user.updateData();
		user2ndMenu(user);
		break;

	case '3':
		user.deleteAccount();
		user1stMenu();
		break;

	default:
		cout << "Wrong choice, please enter valid choice.\nProcessing...";
		this_thread::sleep_for(3s);
		user1stMenu();
		break;
	}
}
