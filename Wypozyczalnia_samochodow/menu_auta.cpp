#include "menu_auta.h"



void Menu::main_menu()
{
	while (1)
	{
		int choice;
		system("cls");
		std::cout << "========================" << std::endl;
		std::cout << "WYPOZYCZALNIA SAMOCHODOW" << std::endl;
		std::cout << "========================" << std::endl << std::endl << std::endl;
		std::cout << "1. ZALOGUJ SIE" << std::endl << "2. ZAREJESTRUJ SIE" << std::endl << "3. WYJSCIE" << std::endl << "CO WYBIERASZ: "; std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			loging();
		}
		break;
		case 2:
		{
			system("cls");
			std::string login, password;
			std::cout << "LOGIN: "; std::cin >> login;
			std::cout << "HASLO: "; std::cin >> password;
			if (account.registering(login, password))
				std::cout << "ZAREJESTROWANO POMYSLNIE\n";
			else
				std::cout << "REJESTRACJA NIEUDANA\n";
			system("pause");
		}
		break;
		case 3:
		{
			return;
		}
		default:
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			}
		}
		break;
		}
	}
}



void Menu::loging()
{
	int choice;
	while (1)
	{
		system("cls");
		std::cout << "1. JESTEM UZYTKOWNIKIEM" << std::endl << "2. JESTEM ADMINISTRATOREM" << std::endl << "3. POWROT" << std::endl << "CO WYBIERASZ: "; std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			login_as_user();
		}
		break;
		case 2:
		{
			login_as_admin();
		}
		break;
		case 3:
		{
			return;
		}
		default:
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			}
		}
		break;
		}
	}
}



void Menu::login_as_user()
{
	system("cls");
	std::string login;
	std::cout << "PODAJ LOGIN: ";
	std::cin >> login;
	int login_data = account.loging(login);
	if (login_data == -1)
	{
		return;
	}
	int choice;
	while (1)
	{
		system("cls");
		std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
		std::cout << "ZALOGOWANO JAKO UZYTKOWNIK" << std::endl << "1. WYPOZYCZ AUTO" << std::endl << "2. ODDAJ AUTO" << std::endl << "3. WYLOGUJ" << std::endl << "CO WYBIERASZ?: "; std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			rental.print_cars();
			std::cout << "ABY WROCIC WPISZ '0'" << std::endl;
			std::cout << "KTORY NUMER AUTA WYBIERASZ?" << std::endl;
			std::cin >> choice;
			if (choice == 0)
			{
				return;
			}
			else if(account[login_data]->rent_car(rental.Rent_car(choice)))
				break;
			std::cout << "TO AUTO JEST JUZ ZAREZERWOWANE" << std::endl;
			system("pause");
			break;
		}
		break;
		case 2:
		{
			system("cls");
			account[login_data]->print_cars();
			std::cout << "ABY WROCIC WPISZ '0'" << std::endl;
			std::cout << "KTORE AUTO ODDAJESZ?: " << std::endl;
			std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			std::cin >> choice;
			if (choice == 0)
			{
				return;
			}
			else if (rental.return_car(account[login_data]->return_car(choice)))
			{
				account[login_data]->delete_from_rented(choice);
				break;
			}
			std::cout << "WYSTAPIL BLAD" << std::endl;
			system("pause");

		}
		break;
		case 3:
		{
			return;
		}
		default:

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			}
		}
		break;

	}
}



void Menu::login_as_admin(std::string login)
{
	system("cls");
	if (login == "")
	{
		std::cout << "PODAJ LOGIN: ";
		std::cin >> login;
		if (account.loging(login) == -1)
		{
			return;
		}
	}
	int choice;
	while (1)
	{
		system("cls");
		std::cout << "ZALOGOWANO JAKO ADMIN" << std::endl << "1. EDYTUJ AUTA" << std::endl << "2. DODAJ AUTO" << std::endl << "3. USUN AUTO" << std::endl << "4. WYLOGUJ" << std::endl << "CO WYBIERASZ?: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			int car_number, parameter_number;
			std::string new_parameter;
			system("cls");
			rental.print_cars();
			std::cout << "ABY WROCIC WPISZ '0'" << std::endl;
			std::cout << "KTORE AUTO WYBIERASZ?" << std::endl;
			std::cin >> car_number;
			if (car_number == 0)
			{
				return;
			}
			std::cout << "CO CHCESZ EDYTOWAC?" << std::endl << "1. MARKE" << std::endl << "2. MODEL" << std::endl << "3. ROCZNIK" << std::endl << "4. CENE" << std::endl;
			std::cout << "TWOJ WYBOR: ";
			std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			std::cin >> parameter_number;
			std::cout << "PODAJ NOWY PARAMETR: ";
			std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			std::getline(std::cin, new_parameter);
			for (int i = 0; i < new_parameter.size(); i++)
				if (new_parameter[i] == '*')
					new_parameter[i] = '&';
			Car car{ rental.Which_car(car_number) };
			if(rental.Edit_car_from_list(car_number, parameter_number, new_parameter))
			{
				account.edit_cars(parameter_number, new_parameter, car);
				break;
			}
			else
				std::cout << "BLAD" << std::endl;
			system("pause");
		}
		break;
		case 2:
		{
			std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			system("cls");
			std::string brand, model, price, year;
			std::cout << "PODAJ MARKE AUTA: "; std::getline(std::cin, brand);
			std::cout << "PODAJ MODEL AUTA: "; std::getline(std::cin, model);
			std::cout << "PODAJ ROCZNIK AUTA: "; std::getline(std::cin, year); 
			std::cout << "PODAJ CENE AUTA( W ZLOTOWKACH): "; std::getline(std::cin, price);
			for (int i = 0; i < brand.size(); i++)
				if (brand[i] == '*')
					brand[i] = '?';
			for (int i = 0; i < model.size(); i++)
				if (model[i] == '*')
					model[i] = '?';
			for (int i = 0; i < year.size(); i++)
				if (price[i] == '*')
					price[i] = '?';
			for (int i = 0; i < price.size(); i++)
				if (year[i] == '*')
					year[i] = '?';
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			}
			else if(rental.Add_car_to_list(brand, model, year, price))
					break;
			std::cout << "WYSTAPIL BLAD" << std::endl;
			system("pause");
		}
		break;
		case 3:
		{
			std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
			system("cls");
			int car_number;
			rental.print_cars();
			std::cout << "ABY WROCIC WPISZ '0'" << std::endl;
			std::cout << "KTORE AUTO CHCESZ USUNAC?" << std::endl;
			std::cin >> car_number;
			if (car_number == 0)
			{
				return;
			}
			Car car{ rental.Which_car(car_number) };
			if (rental.Delete_car_from_list(car_number))
			{
				account.delete_cars(car);
				break;
			}
			else
				std::cout << "BLAD" << std::endl;
			system("pause");
		}
		break;
		case 4:
			return;
			break;
		default:
			system("cls");
			return;
			break;
		}
	}

}
