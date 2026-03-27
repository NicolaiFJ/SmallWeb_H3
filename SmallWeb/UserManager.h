#pragma once
#include <vector>
#include <string>
class UserManager
{
public:
	enum UserType
	{
		standard,
		employee,
	};

	struct User
	{
		std::string mail;
		std::string password;
		UserType userType;
	};

	std::vector<User> m_users;


	void init();
	std::string getUserAsJson(int id);
	int getNumberUsers();
	std::string getEmployeesAsJson();
	int login(std::string mail, std::string password);
	void createUser(std::string mail, std::string password, UserType userType);
	bool doesUserExist(std::string mail, std::string password);

};

