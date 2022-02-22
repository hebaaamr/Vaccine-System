#pragma once
#include "User.h"

class Menus
{
	char choice;
public:
	void welcomeMenu();
	void adminMenu();
	void user1stMenu();
	void user2ndMenu(User user);
};
