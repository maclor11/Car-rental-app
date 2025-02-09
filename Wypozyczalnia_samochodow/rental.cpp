#include "rental.h"


bool Car::operator!()
{
	if (Availability)
	{
		ChangeAvailability();
		return true;
	}
	return false;
}


bool Car::operator==(const std::string& parameters) const
{
	std::string car{ Brand + '*' + Model + '*' + Year + '*' + Price + "\n" };
	if (car == parameters)
		return true;
	return false;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


RentalService::RentalService(const std::string& file_name)
{
	cars_filename = file_name;
	if (std::ifstream file{ file_name })
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::string Brand, Model, Year, Price;
			bool Availability;
			if (LoadCarInfo(line, Brand, Model, Year, Price, Availability))
				car_list.push_back(Car(Brand, Model, Year, Price));
			if (!Availability)
				car_list.back().ChangeAvailability();
		}
		file.close();
	}
}

bool RentalService::LoadCarInfo(const std::string& line, std::string& Brand, std::string& Model, std::string& Year, std::string& Price, bool& Availability)
{
	std::istringstream ss(line);
	std::getline(ss, Brand, '*');
	std::getline(ss, Model, '*');
	std::getline(ss, Year, '*');
	std::getline(ss, Price, '*');
	std::string IfAvailable;
	ss >> IfAvailable;
	if (IfAvailable == "1")
		Availability = true;
	else
		Availability = false;
	return true;
}

bool RentalService::Add_car_to_list(const std::string& Brand, const std::string& Model, const std::string& Year, const std::string& Price)
{
	car_list.push_back(Car(Brand, Model, Year, Price));
	return true;
}


bool RentalService::Edit_car_from_list(const int& car_number, const int& parameter_number, const std::string& new_parameter)
{
	if (car_number > 0 && car_number <= car_list.size())
	{
		switch (parameter_number)
		{
		case 1:
			car_list[car_number - 1].Brand_change(new_parameter);
			break;
		case 2:
			car_list[car_number - 1].Model_change(new_parameter);
			break;
		case 3:
			car_list[car_number - 1].Year_change(new_parameter);
			break;
		case 4:
			car_list[car_number - 1].Price_change(new_parameter);
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
}


bool RentalService::Delete_car_from_list(int car_number)
{
	if (car_number > 0 && car_number <= car_list.size())
	{
		car_list.erase(car_list.begin() + car_number - 1);
		return true;
	}
	return false;
}


void RentalService::print_cars()
{
	for (int i = 1; i <= car_list.size(); i++)
	{
		std::cout << i << ") " << car_list[i - 1].Brand_getter() + " * " + car_list[i - 1].Model_getter() + " * " + car_list[i - 1].Year_getter() + " * "
		+ car_list[i - 1].Price_getter()+ " ZLOTYCH " + " * " + (car_list[i - 1].IsAvailable() ? "DOSTEPNY" : "ZAREZERWOWANY ") + "\n";
	}
}

Car RentalService::Which_car(int car_number)
{
	car_number--;
	if (car_number >= 0 && car_number < car_list.size())
	{
		return Car(car_list[car_number]);
	}
	else
	{
		Car car(" ", " ", " ", " ");
		return car;
	}
}

Car RentalService::Rent_car(int car_number)
{
	car_number--;
	if (car_number >= 0 && car_number < car_list.size() && car_list[car_number].IsAvailable())
	{
		if (!car_list[car_number])
		{
			Car car(car_list[car_number]);
			return car;
		}
	}
	Car car(" ", " ", " ", " ");
	return car;
}

bool RentalService::return_car(const Car& car)
{
	if (car == " * * * ")
		return false;
	std::string tmp{ car.specification() };
	for (int i = 1; i <= car_list.size(); i++)
	{
		if (car_list[i - 1] == tmp)
		{
			car_list[i - 1].ChangeAvailability();
			return true;
		}
	}
	return false;
}


Car* RentalService::operator[](const int& n)
{
	return &car_list[n];
}

RentalService::~RentalService()
{
	std::ofstream file(cars_filename);
	for (const Car& car : car_list)
	{
		file << car.Brand_getter() << "*" << car.Model_getter() << "*" << car.Year_getter() << "*" << car.Price_getter() << "*" << (car.IsAvailable() ? "1" : "0") << "\n";
	}
	file.close();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool User::loging(const std::string& password)
{
	if (password == this->password)
		return true;
	return false;
}

bool User::rent_car(Car car)
{
	if (car.specification() == " * * * \n")
		return false;
	rented_cars_list.push_back(car);
	return true;
}

void User::edit_car(const int& parameter_number, const std::string& new_parameter, const Car& car)
{
	std::string tmp{ car.specification() };
	for (int i = 0; i < rented_cars_list.size(); i++)
	{
		if (rented_cars_list[i] == tmp)
		{
			switch (parameter_number)
			{
			case 1:
				rented_cars_list[i].Brand_change(new_parameter);
				break;
			case 2:
				rented_cars_list[i].Model_change(new_parameter);
				break;
			case 3:
				rented_cars_list[i].Year_change(new_parameter);
				break;
			case 4:
				rented_cars_list[i].Price_change(new_parameter);
				break;
			default:
				break;
			}
		}
	}
}

Car User::return_car(int car_number)
{
	car_number--;
	if (car_number >= 0 && car_number < rented_cars_list.size())
		return rented_cars_list[car_number];
	Car car(" ", " ", " ", " ");
	return car;
}

std::string User::rented_parameters()
{
	std::string parameters{};
	for (int i = 0; i < rented_cars_list.size(); i++)
		parameters += rented_cars_list[i].specification();
	return parameters;
}


void User::print_cars()
{
	for (int i = 1; i <= rented_cars_list.size(); i++)
		std::cout << i << ") " << rented_cars_list[i - 1].specification() << std::endl;
}



void User::delete_from_rented(int car_number)
{
	car_number--;
	if (car_number >= 0 && car_number < rented_cars_list.size())
		rented_cars_list.erase(rented_cars_list.begin() + car_number);
}

void User::delete_car(const Car& car)
{
	std::string tmp = car.specification();
	tmp.erase(tmp.rfind("|") + 1);
	std::cout << tmp << std::endl;
	int size = rented_cars_list.size();
	for (int i = 0, z = 0; i < size; i++)
	{
		if (rented_cars_list[i - z] == tmp)
		{
			rented_cars_list.erase(rented_cars_list.begin() + (i - z));
			z++;
		}
	}
}

bool User::operator==(const std::string& login)
{
	if (this->login == login)
	{
		return true;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Admin::loging(const std::string& password)
{
	if (password == "haslo")
		return true;
	else
		return false;
}

bool Admin::operator==(const std::string& login)
{
	if (this->login == login)
	{
		return true;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


UsersService::UsersService(std::string filename1, std::string filename2)
{
	users_filename = filename1;
	reservations_filename = filename2;
	if (std::ifstream file{ users_filename })
	{
		std::string login, password{};
		getline(file, login);
		all_users_list.push_back(new Admin(login));
		while (getline(file, login, '*'))
		{
			getline(file, password);
			all_users_list.push_back(new User(login, password));
		}
		file.close();
	}
	if (std::ifstream file{ reservations_filename })
	{
		std::string tmp{};
		std::string login;
		while (getline(file, tmp))
		{
			if (tmp[0] == '^')
				login = tmp.substr(1);
			else
				for (int i = 0; i < all_users_list.size(); i++)
					if (all_users_list[i]->return_login() == login)
					{
						std::string Brand, Model, Price, Year;
						size_t div1, div2;
						div1 = tmp.find('*');
						Brand = tmp.substr(0, div1);
						tmp[div1] = 'x';
						div2 = tmp.find('*');
						Model = tmp.substr(div1 + 1, div2 - div1 - 1);
						tmp[div2] = 'x';
						div1 = tmp.find('*');
						Year = tmp.substr(div2 + 1, div1 - div2 - 1);
						div2 = tmp.find('\n');
						Price = tmp.substr(div1 + 1, div2 - div1 - 1);
						all_users_list[i]->rent_car(Car(Brand, Model, Year, Price));
					}
		}
		file.close();
	}
}



bool UsersService::registering(std::string login, std::string password)
{
	bool user_occurence{ 1 };
	for (auto user : all_users_list)
	{
		if (*user == login)
			user_occurence = false;
	}
	if (user_occurence)
	{
		all_users_list.push_back(new User(login, password));
		return true;
	}
	return false;

}

int UsersService::loging(std::string login)
{
	int tmp = -1;
	for (int i = 0; i < all_users_list.size(); i++)
	{
		if (*all_users_list[i] == login)
		{
			tmp = i;
			break;
		}
	}
	if (tmp == -1)
		return -1;
	std::cout << "PODAJ HASLO: ";
	std::cin >> login;
	if (all_users_list[tmp]->loging(login))
		return tmp;
	return -1;
}

Someone* UsersService::operator[](int number)
{
	return all_users_list[number];
}

void UsersService::edit_cars(int parameter_number, std::string new_parameter, Car& car)
{
	for (int i = 1; i < all_users_list.size(); i++)
	{
		all_users_list[i]->edit_car(parameter_number, new_parameter, car);
	}
}

void UsersService::delete_cars(Car& car)
{
	for (int i = 1; i < all_users_list.size(); i++)
	{
		all_users_list[i]->delete_car(car);
	}
}

UsersService::~UsersService()
{
	std::ofstream file2(reservations_filename);
	for (auto car : all_users_list)
	{
		file2 << '^' << car->return_login() << '\n';
		file2 << car->rented_parameters();
	}
	file2.close();

	std::ofstream file1(users_filename);
	for (auto user : all_users_list)
		file1 << user->login_data();
	file1.close();

	for (int i = 0; i < all_users_list.size(); i++)
	{
		delete all_users_list[i];
	}
}

/////////////////////////////////////////////////////////////////////////////////








