#include "UserManager.h"

static std::string urlDecode(const std::string& str) {
	std::string result;
	for (size_t i = 0; i < str.length(); ++i) {
		if (str[i] == '%' && i + 2 < str.length()) {
			std::string hex = str.substr(i + 1, 2);
			char ch = static_cast<char>(std::stoi(hex, nullptr, 16));
			result += ch;
			i += 2; // skip the next two characters
		}
		else if (str[i] == '+') {
			result += ' '; // optional: convert '+' to space
		}
		else {
			result += str[i];
		}
	}
	return result;
}

void UserManager::init()
{
	User user;
	user.mail = "mail%40mail.mail";
	user.password = "Kode1234!";
	user.userType = UserType::employee;

	m_users.push_back(user);

	user.mail = "mail%40gmail.com";
	user.password = "Kode1234!";
	user.userType = UserType::employee;

	m_users.push_back(user);

	user.mail = "mail%40yahhooo.com";
	user.password = "Man";
	user.userType = UserType::standard;

	m_users.push_back(user);
}

std::string UserManager::getUserAsJson(int id)
{
	if (id < 0 || id >= m_users.size())
		return "{}"; // user not found, return empty JSON

	const User& user = m_users[id];

	std::string json = "{";
	json += "\"mail\":\"" + user.mail + "\",";
	json += "\"password\":\"" + user.password + "\",";

	switch (user.userType)
	{
	case UserType::standard:  json += "\"userType\":\"standard\""; break;
	case UserType::employee:  json += "\"userType\":\"employee\""; break;
			//case UserType::    json += "\"userType\":\"Admin\""; break;
	}

	json += "}";
	return json;
}

int UserManager::getNumberUsers()
{
	return m_users.size();
}

std::string UserManager::getEmployeesAsJson()
{
	std::string json = "[";
	bool first = true;

	for (const auto& user : m_users)
	{
		if (user.userType == UserType::employee)
		{
			if (!first)
				json += ",";

			json += "{";
			json += "\"mail\":\"" + user.mail + "\"";
			json += ",\"password\":\"" + user.password + "\"";
			json += "}";

			first = false;
		}
	}

	json += "]";
	return json;
}

int UserManager::login(std::string mail, std::string password)
{
	for (int i = 0; i < m_users.size(); i++)
	{
		if (urlDecode(m_users[i].mail) == urlDecode(mail))
		{
			if (urlDecode(m_users[i].password) == urlDecode(password))
			{
				return i+1;
			}
		}
	}

	return 0;
}

void UserManager::createUser(std::string mail, std::string password, UserType userType)
{
	User newUser;
	newUser.mail = urlDecode(mail);
	newUser.password = urlDecode(password);
	newUser.userType = userType;

	m_users.push_back(newUser);
}

bool UserManager::doesUserExist(std::string mail, std::string password)
{
	for (int i = 0; i < m_users.size(); i++)
	{
		if (m_users[i].mail == mail && m_users[i].password == password)
		{
			return true;
		}
	}

	return false;
}


/*

*/
/*
	std::string body = "";
	body += "{";
	body += "\"1\":{";
	body += "\"id\":" + std::to_string(rand() % 156) +
		",\n\"name\":" + "\"Mar\"" +
		",\n\"email\":" + "\"mail@mail.mail\"";
	body += "},";
	body += "\"2\":{";
	body += "\"id\":" + std::to_string(rand() % 156) +
		",\n\"name\":" + "\"Carl Jim\"" +
		",\n\"email\":" + "\"carl@mail.mail\"";
	body += "}";
	body += "}";
	return body;

	return std::string();
	*/