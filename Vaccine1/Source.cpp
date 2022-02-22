#include <iostream>
#include "Menus.h"
#include "Common.h"
#include "User.h"
using namespace std;

void insertUsers();

LinkedList <User> Common::usersList;
Queue <long long> Common::dose1WaitingList;
Queue <long long> Common::dose2WaitingList;

int main() {
	system("Color F0");
	insertUsers();
	Menus menus;
	menus.welcomeMenu();
	return 0;
}

void insertUsers()
{
	User user1("user1", 'M', "123", "Egypt", "Cairo", 25, 1111111111111, true, false);
	User user2("user2", 'M', "456", "Egypt", "Alex", 19, 2222222222222, true, true);
	User user3("user3", 'M', "789", "Egypt", "Giza", 31, 3333333333333, false, false);
	User user4("user4", 'F', "321", "Egypt", "Cairo", 36, 4444444444444, true, true);
	User user5("user5", 'F', "654", "Egypt", "Alex", 18, 5555555555555, false, false);
	User user6("user6", 'F', "987", "Egypt", "Giza", 21, 666666666666, true, false);
}
