#include "Common.h"
#include <regex>
regex integer_expr("^[0-9]{13}$");

long long Common::check_ID()
{
	long long id;
	cout << "Enter national ID, please. *13 digits\nID : ";
	cin >> id;
	while (!(regex_match(to_string(id), integer_expr)))
	{
		cout << "Nationnal ID must be 13 digits.\nID: ";
		cin >> id;
	}
	return id;
}

int Common::findUser(long long NID)
{
	int n = -1;
	for (int i = 0; i < usersList.Length(); i++)
	{
		if (usersList.At(i).NID == NID)
		{
			n = i;
			break;
		}
	}
	return n;
}

void Common::displayUserData(long long NID)
{
	system("CLS");
	int userIndex = findUser(NID);
	User user = usersList.At(userIndex);
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
			cout << "Second dose is done." << endl;
		}
		else {
			cout << "First dose is done and in the waiting list of the second dose." << endl;
		}
	}
	else {
		cout << "In the waiting list of the first dose." << endl;
	}
	cout << "Press 0 to go back. ";
	char back;
	cin >> back;
}

void Common::removeFromWaitingList(User user)
{
	Queue <long long> templateQueue;
	if (!user.isVaccined)
	{
		while (!dose1WaitingList.empty())
		{
			if (dose1WaitingList.Front() != user.NID)
			{
				templateQueue.enqueue(dose1WaitingList.Front());
			}
			dose1WaitingList.dequeue();
		}
		dose1WaitingList.clear();
		dose1WaitingList = templateQueue;
	}
	else
	{
		while (!dose2WaitingList.empty())
		{
			if (dose2WaitingList.Front() != user.NID)
			{
				templateQueue.enqueue(dose2WaitingList.Front());
			}
			dose2WaitingList.dequeue();
		}
		dose2WaitingList.clear();
		dose2WaitingList = templateQueue;
	}
}
