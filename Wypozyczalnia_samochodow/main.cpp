#include <iostream>
#include "rental.h"
#include "menu_auta.h"

int main(int argc, char * argv[])
{
	Menu menu(argv[1],argv[2], argv[3]);
	menu.main_menu();
	return 0;
}