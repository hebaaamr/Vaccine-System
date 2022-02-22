#include <iostream>
#include <stdlib.h>
#include <thread>
#include <string>
#include "Admin.h"
#include "Menus.h"
#include "Common.h"
using namespace std;

Menus menu;
Common commmon;

void Admin::signIn()
{
	system("CLS");
	cout << "Enter password, please.\nIf you want to go back enter 0.\nPassword: ";
	string pass;
	cin >> pass;
	if (pass == "0") {
		menu.welcomeMenu();
	}
	else if (pass == password) {
		menu.adminMenu();
	}
	else {
		cout << "Wrong password, try again.\nProcessing...";
		this_thread::sleep_for(3s);
		signIn();
	}
}

void Admin::viewUserData()
{
	system("CLS");
	long long NID;
	NID = commmon.check_ID();
	int userIndex = commmon.findUser(NID);
	while (userIndex == -1) {
		cout << "Wrong national ID. Please try again.\nNational ID: ";
		NID = commmon.check_ID();
		userIndex = commmon.findUser(NID);
	}
	commmon.displayUserData(NID);
}

void Admin::viewAllUsersData()
{
	User user;
	system("CLS");
	for (int i = 0; i < commmon.usersList.Length(); i++) {

		user = commmon.usersList.At(i);

		cout << "Name: " << user.name << endl;
		cout << "National ID: " << user.NID << endl;
		cout << "Age: " << user.age << endl;
		cout << "Country: " << user.country << endl;
		cout << "Governorate: " << user.gov << endl;
		cout << "Gender: " << user.gender << endl;
		cout << "Vaccination Status: ";
		if (user.isVaccined == true)
		{
			if (user.isFullyVaccinated == true) {
				cout << "Fully vaccinated." << endl;
			}
			else {
				cout << "On waiting list for the second dose." << endl;
			}
		}
		else {
			cout << "On waiting list for the first dose." << endl;
		}
		cout << "-----------------------------------------------\n";
	}
	cout << "Press 0 to go back. ";
	char back;
	cin >> back;
}

void Admin::deleteUser()
{
	system("CLS");
	long long NID;
	NID = commmon.check_ID();
	int userIndex = commmon.findUser(NID);
	while (userIndex == -1) {
		cout << "Wrong national ID. Please try again.\nNational ID: ";
		NID = commmon.check_ID();
		userIndex = commmon.findUser(NID);
	}
	User user = commmon.usersList.At(userIndex);
	if (!user.isFullyVaccinated)
	{
		commmon.removeFromWaitingList(user);
	}
	commmon.usersList.DeleteAt(userIndex);
	cout << "Deleting...";
	this_thread::sleep_for(3s);
}

void Admin::deleteAllUsers()
{
	for (int i = commmon.usersList.Length(); i > 0; i--)
	{
		commmon.usersList.DeleteAt(i - 1);
	}
	while (!commmon.dose1WaitingList.empty())
	{
		commmon.dose1WaitingList.dequeue();
	}
	while (!commmon.dose2WaitingList.empty())
	{
		commmon.dose2WaitingList.dequeue();
	}
	cout << "Deleting...";
	this_thread::sleep_for(1s);
}

void Admin::giveDose()
{
	system("CLS");
	cout << "\t\tGive Dose\n\n";
	cout << "1. First dose waiting list.\n2. Second dose waiting list.\n0. Go Back\nChoice: ";
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '0':
		menu.adminMenu();
		break;
	case '1':
		give1stDose();
		break;
	case '2':
		give2ndDose();
		break;
	default:
			cout << "Wrong choice, please enter valid choice.\nProcessing...";
			this_thread::sleep_for(3s);
			giveDose();
			break;
	}
}

void Admin::give1stDose()
{
	if (commmon.dose1WaitingList.empty())
	{
		cout << "\n\nThere is no one in first dose waiting list.";
		this_thread::sleep_for(3s);
		return;
	}
	system("CLS");
	cout << "\t\tGive Dose\n\n";
	long long NID = commmon.dose1WaitingList.Front();
	int userIndex = commmon.findUser(NID);
	cout << "Are you sure that " << commmon.usersList.At(userIndex).name << " has taken the first dose? (Y / N): ";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		commmon.dose2WaitingList.enqueue(NID);
		commmon.dose1WaitingList.dequeue();
		cout << "\n\n" << commmon.usersList.At(userIndex).name << " took the first dose and now in second dose waiting list.\n\nTake care of your health.";
		this_thread::sleep_for(5s);
	}
	editUserStatues(1, userIndex);
}

void Admin::give2ndDose()
{
	if (commmon.dose2WaitingList.empty())
	{
		cout << "\n\nThere is no one in second dose waiting list.";
		this_thread::sleep_for(3s);
		return;
	}
	system("CLS");
	cout << "\t\tGive Dose\n\n";
	long long NID = commmon.dose2WaitingList.Front();
	int userIndex = commmon.findUser(NID);
	cout << "Are you sure that " << commmon.usersList.At(userIndex).name << " has taken the Second dose? (Y / N): ";
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		commmon.dose2WaitingList.dequeue();
		cout << "\n\n" << commmon.usersList.At(userIndex).name << " is now fully Vaccinated.\n\nTake care of your health.";
		this_thread::sleep_for(3s);
	}
	editUserStatues(2, userIndex);
}

void Admin::editUserStatues(int doseNo, int userIndex)
{
	User user = commmon.usersList.At(userIndex);
	if (doseNo == 1)
	{
		user.isVaccined = true;
	}
	else
	{
		user.isFullyVaccinated = true;
	}
	commmon.usersList.DeleteAt(userIndex);
	commmon.usersList.Append(user);
}

void Admin::generalStatistics()
{
	system("CLS");
	float unvaccinated, atleastOneDose, fully;
	unvaccinated = (float(commmon.dose1WaitingList.length()) / commmon.usersList.Length()) * 100;
	atleastOneDose = (float((commmon.usersList.Length()) - commmon.dose1WaitingList.length()) / commmon.usersList.Length()) * 100;
	fully = (float((commmon.usersList.Length()) - commmon.dose1WaitingList.length() - commmon.dose2WaitingList.length()) / commmon.usersList.Length()) * 100;
	cout << "Percentage of the unvaccinated: " << unvaccinated << " %\n";
	cout << "Percentage of those who received at least one dose: " << atleastOneDose << " %\n";
	cout << "Percentage of those who got fully vaccinated: " << fully << " %\n";
	cout << "Press 0 to go back. ";
	char back;
	cin >> back;
}

void Admin::govStatistics()
{
	system("CLS");
	float C[6] = { 0 }, A[6] = { 0 }, G[6] = { 0 };
	for (int i = 0; i < commmon.usersList.Length(); i++)
	{
		User user = commmon.usersList.At(i);
		if (user.gov == "Cairo")
		{
			C[0]++; //Total in Cairo
			if (!user.isVaccined)
			{
				C[1]++; //1st waiting list in Cairo
			}
			else if (user.isFullyVaccinated)
			{
				C[2]++; //Fully vaccinated in Cairo
			}
		}
		else if (user.gov == "Alex")
		{
			A[0]++; //Total in Alex
			if (!user.isVaccined)
			{
				A[1]++; //1st waiting list in Alex
			}
			else if (user.isFullyVaccinated)
			{
				A[2]++; //Fully vaccinated in Alex
			}
		}
		else
		{
			G[0]++; //Total in Giza
			if (!user.isVaccined)
			{
				G[1]++; //1st waiting list in Giza
			}
			else if (user.isFullyVaccinated)
			{
				G[2]++; //Fully vaccinated in Giza
			}
		}
	}
	C[3] = (C[1] / C[0]) * 100; //Unvaccinated in Cairo
	C[4] = (C[0] - C[1]) / C[0] * 100; //At least one dose in Cairo
	C[5] = (C[2] / C[0]) * 100; //Fully vaccinated in Cairo

	A[3] = (A[1] / A[0]) * 100; //Unvaccinated in Alex
	A[4] = (A[0] - A[1]) / A[0] * 100; //At least one dose in Alex
	A[5] = (A[2] / A[0]) * 100; //Fully vaccinated in Alex

	G[3] = (G[1] / G[0]) * 100; //Unvaccinated in Giza
	G[4] = (G[0] - G[1]) / G[0] * 100; //At least one dose in Giza
	G[5] = (G[2] / G[0]) * 100; //Fully vaccinated in Giza

	cout << "Percentage of the unvaccinated in Cairo: " << C[3] << " %\n";
	cout << "Percentage of those who received at least one dose in Cairo: " << C[4] << " %\n";
	cout << "Percentage of those who got fully vaccinated in Cairo: " << C[5] << " %\n";
	cout << "-----------------------------------------------\n";
	cout << "Percentage of the unvaccinated in Alex: " << A[3] << " %\n";
	cout << "Percentage of those who received at least one dose in Alex: " << A[4] << " %\n";
	cout << "Percentage of those who got fully vaccinated in Alex: " << A[5] << " %\n";
	cout << "-----------------------------------------------\n";
	cout << "Percentage of the unvaccinated in Giza: " << G[3] << " %\n";
	cout << "Percentage of those who received at least one dose in Giza: " << G[4] << " %\n";
	cout << "Percentage of those who got fully vaccinated in Giza: " << G[5] << " %\n";
	cout << "-----------------------------------------------\n";
	cout << "Press 0 to go back. ";
	char back;
	cin >> back;
}

void Admin::checkLength()
{
	if (commmon.usersList.Length() == 0 )
	{
		cout << "\nThere is no users yet.";
		this_thread::sleep_for(2s);
		menu.adminMenu();
	}
}
