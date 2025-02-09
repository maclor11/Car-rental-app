#ifndef MENU
#define MENU

#include "rental.h"
#include <iostream>

class Menu
{
private:
	RentalService rental;
	UsersService account;
public:
	Menu(){}
	Menu(std::string filename1, std::string filename2, std::string filename3) :rental(filename1), account(filename2, filename3) {}
	void main_menu();
	void loging();
	void login_as_user();
	void login_as_admin(std::string login = "");
};

#endif