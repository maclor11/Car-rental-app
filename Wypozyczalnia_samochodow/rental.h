#ifndef RENTAL_H
#define RENTAL_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



class Car
{
private:
	std::string Brand;
	std::string Model;
	std::string Year;
	std::string Price;
	bool Availability;
public:
	Car(const std::string& brand, const std::string& model, const std::string& year, const std::string& price)
		:Brand{ brand }, Model{ model }, Year{ year }, Price{ price }, Availability{ true } {}
	const std::string  specification() const
	{
		return Brand + '*' + Model + '*' + Year + '*' + Price + "\n";
	}
	std::string Brand_getter() const { return Brand; }
	std::string Model_getter() const { return Model; }
	std::string Year_getter() const { return Year; }
	std::string Price_getter() const { return Price; }
	void Brand_change(const std::string& Brand)
	{
		this->Brand = Brand;
	}
	void Model_change(const std::string& Model)
	{
		this->Model = Model;
	}
	void Year_change(const std::string& Year)
	{
		this->Year = Year;
	}
	void Price_change(const std::string& Price)
	{
		this->Price = Price;
	}
	bool IsAvailable() const
	{
		return Availability;
	}
	void ChangeAvailability()
	{
		Availability = !Availability;
	}
	bool operator!();
	bool operator==(const std::string& parameters) const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RentalService
{
private:
	std::vector <Car> car_list;
	std::string cars_filename;
public:
	RentalService() {}
	RentalService(const std::string& file_name);
	bool LoadCarInfo(const std::string& line, std::string& Brand, std::string& Model, std::string& Year, std::string& Price, bool& Availability);
	bool Add_car_to_list(const std::string& Brand, const std::string& Model, const std::string& Year, const std::string& Price);
	bool Delete_car_from_list(int car_number);
	bool Edit_car_from_list(const int& car_number, const int& parameter_number, const std::string& new_parameter);
	void print_cars();
	Car Rent_car(int car_number);
	bool return_car(const Car& car);
	Car Which_car(int car_number);
	Car* operator[](const int& n);
	~RentalService();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Someone
{
public:
	Someone() {}
	virtual bool loging(const std::string& password) = 0;
	virtual bool rent_car(Car car) = 0;
	virtual void edit_car(const int& pararameter_number, const std::string& new_parameter, const Car& car) = 0;
	virtual void delete_car(const Car& car) = 0;
	virtual void print_cars() = 0;
	virtual Car return_car(int car_number) = 0;
	virtual void delete_from_rented(int car_number) = 0;
	virtual std::string rented_parameters() = 0;
	virtual std::string return_login() = 0;
	virtual std::string login_data() = 0;
	virtual bool operator==(const std::string& login) = 0;
	virtual ~Someone() {};
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class User : public Someone
{
private:
	std::string login;
	std::string password;
	std::vector<Car> rented_cars_list;
public:
	User() {}
	User(std::string login, std::string password)
	{
		this->login = login;
		this->password = password;
	}
	std::string login_data()
	{
		return login + '*' + password + '\n';
	}
	std::string return_login()
	{
		return login;
	}
	bool loging(const std::string& password);
	void edit_car(const int& parameter_number, const std::string& new_parameter, const Car& car);
	std::string rented_parameters();
	void delete_car(const Car& car);
	bool rent_car(Car car);
	void print_cars();
	Car return_car(int car_number);
	void delete_from_rented(int car_number);
	bool operator==(const std::string& login);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Admin : public Someone
{
private:
	std::string login;
public:
	Admin() {}
	Admin(std::string login)
	{
		this->login = login;
	}
	bool loging(const std::string& password);
	void edit_car(const int& parameter_number, const std::string& new_parameter, const Car& car) {}
	std::string rented_parameters()
	{
		std::string nothing{};
		return nothing;
	}
	bool operator==(const std::string& login);
	std::string login_data()
	{
		return login + '\n';
	}
	std::string return_login()
	{
		return " ";
	}
	bool rent_car(Car car)
	{
		return false;
	}
	void print_cars() {}
	Car return_car(int car_number)
	{
		return Car(" ", " ", " ", " ");
	}
	void delete_from_rented(int car_number) {}
	void delete_car(const Car& car) {}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class UsersService
{
private:
	std::vector <Someone*> all_users_list;
	std::string users_filename;
	std::string reservations_filename;
public:
	UsersService() {}
	UsersService(std::string filename1, std::string filename2);
	bool registering(std::string login, std::string password);
	int loging(std::string login);
	Someone* operator[](int number);
	void edit_cars(int pararameter_number, std::string new_parameter, Car& car);
	void delete_cars(Car& car);
	~UsersService();
};

#endif