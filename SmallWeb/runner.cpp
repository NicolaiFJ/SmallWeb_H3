#pragma comment(lib, "ws2_32.lib")
#include "runner.h"


void runWebServer(SOCKET &wsocket,
SOCKET &new_wsocket,
WSADATA &wsaData,
struct sockaddr_in & server,
int &server_len,
WebManager& webManager,
UserManager& userManager,
BookingManager& bookingManager)
{

while (true)
{
	new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
	if (new_wsocket == INVALID_SOCKET)
	{
		continue;
	}

	char buff[BUFFER_SIZE] = { 0 };
	int bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);

	if (bytes < 0)
	{
		continue;
	}




	char* sub = getSubUrl(buff, bytes);
	if (sub == NULL)
	{
		continue;
	}

	std::string subS = sub;

	if (subS.compare("/bookings") == 0)
	{
		std::string body = "{\"id\":\"" + std::to_string(rand() % 156) + "\"}";
		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (subS.compare("/randData") == 0)
	{
		std::string body = "{\"id\":\"" + std::to_string(rand() % 156) + "\"}";
		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (subS.compare("/Users/get/count") == 0)
	{
		std::string body = "{\"count\":" + std::to_string(userManager.getNumberUsers()) + "}";

		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);

	}
	else if (std::string("/Users/get").size() <= subS.size() && subS.substr(0, std::string("/Users/get").size()).compare("/Users/get") == 0)
	{
		std::string idQuery = getVarStringQuery(sub, subS.size(), "ID");
		bool isIDNumber = true;
		for (int i = 0; i < idQuery.size(); i++)
		{
			if (std::isdigit(idQuery[i]) == false)
			{
				isIDNumber = false;
				break;
			}
		}
		std::string body;
		if (isIDNumber && idQuery.size())
		{
			body = userManager.getUserAsJson(std::stoi(getVarStringQuery(sub, subS.size(), "ID")));
		}
		else
		{
			body = userManager.getUserAsJson(0);
		}
		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (subS.compare("/bookings/book") == 0)
	{



		std::string body = "{\"id\":" + std::to_string(rand() % 156) + ",\n\"price\":" + std::to_string(rand() % 40 * 4) + "}";
		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (std::string("/bookings/user").size() <= subS.size() && subS.substr(0, std::string("/bookings/user").size()).compare("/bookings/user") == 0)///bookings/user/{USER_ID}/day/{DAY}
	{
		std::string body;

		if (rand() % 10 > 2)
		{
			body = "{\"is_booked\": false }";
		}
		else
		{
			body = "{\"is_booked\": true }";
		}

		std::string a = "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (webManager.isMatch(subS, "/bookings/get"))
	{

		std::string idQuery = getVarStringQuery(sub, subS.size(), "userID");
		if (idQuery.size() <= 0) { continue; }

		bool isIDNumber = true;
		for (int i = 0; i < idQuery.size(); i++)
		{
			if (std::isdigit(idQuery[i]) == false)
			{
				isIDNumber = false;
				break;
			}
		}

		if (isIDNumber == false)
		{
			continue;
		}

		int id = std::stoi(idQuery);

		std::string body = bookingManager.getBookingsAsJsonByUserID(id, &userManager);



		std::string a = webManager.getWebHeadders(body.size()) + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (webManager.isMatch(subS, "/bookings/add"))
	{
		if (bookingManager.isTimeDateTaken(getVarStringQuery(sub, subS.size(), "date"), getVarStringQuery(sub, subS.size(), "hour")))
		{
			std::string body = "{\"isDateTaken\":\"True\"}";
			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
			continue;
		}

		std::string idQuery = getVarStringQuery(sub, subS.size(), "userID");
		if (idQuery.size() <= 0)
		{
			std::string body = "{\"ERROR\":\"Size of id is empty\"}";
			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
		}

		bool isIDNumber = true;
		for (int i = 0; i < idQuery.size(); i++)
		{
			if (std::isdigit(idQuery[i]) == false)
			{
				std::string body = "{\"ERROR\":\"Id query is not a number" + idQuery + "\"}";
				std::string a = webManager.getWebHeadders(body.size()) + body;
				send(new_wsocket, a.c_str(), a.length(), 0);

				isIDNumber = false;
				continue;
			}
		}

		if (isIDNumber == false)
		{
			std::string body = "{\"ERROR\":\"Id query is not a number" + idQuery + "\"}";
			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
			continue;
		}

		

		int id = std::stoi(idQuery);

		std::string body = bookingManager.getBookingsAsJsonByUserID(id, &userManager);

		bookingManager.createBooking(id, getVarStringQuery(sub, subS.size(), "hour"), getVarStringQuery(sub, subS.size(), "location"), getVarStringQuery(sub, subS.size(), "service"), getVarStringQuery(sub, subS.size(), "date"));

		std::string a = webManager.getWebHeadders(body.size()) + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (webManager.isMatch(subS, "/bookings/isdatetaken"))
	{
		if (bookingManager.isTimeDateTaken(getVarStringQuery(sub, subS.size(), "date"), getVarStringQuery(sub, subS.size(), "time")))
		{
			std::string body = "{\"isTaken\":\"True\"}";
			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
		}
		else
		{
			std::string body = "{\"isTaken\":\"False\"}";
			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
		}
	}
	else if (webManager.isMatch(subS, "/users/login"))
	{
		std::string mail = getVarStringQuery(sub, subS.size(), "email");
		std::string password = getVarStringQuery(sub, subS.size(), "password");

		std::string body;


		body = "{\"userID\":" + std::to_string(userManager.login(mail, password)) + "}";

		std::string a = webManager.getWebHeadders(body.size()) + body;
		send(new_wsocket, a.c_str(), a.length(), 0);

	}
	else if (webManager.isMatch(subS, "/employees/get"))
	{
		std::string body = userManager.getEmployeesAsJson();

		std::string a = webManager.getWebHeadders(body.size()) + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	else if (webManager.isMatch(subS, "/users/signup"))
	{
		std::string mail = getVarStringQuery(sub, subS.size(), "email");
		std::string password = getVarStringQuery(sub, subS.size(), "password");

		if (userManager.doesUserExist(mail, password))
		{
			std::string body = "{\"error\":\"Failed to create user\" }";



			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
		}


		UserManager::User user;
		user.mail = mail;
		user.password = password;
		user.userType = UserManager::UserType::standard;
		userManager.m_users.push_back(user);


		std::string body;
		body = "{\"userID\":" + std::to_string(userManager.m_users.size()) + "}";



		std::string a = webManager.getWebHeadders(body.size()) + body;
		send(new_wsocket, a.c_str(), a.length(), 0);

	}
	else if (webManager.isMatch(subS, "/users/create/employee"))
	{
		std::string mail = getVarStringQuery(sub, subS.size(), "mail");
		std::string password = getVarStringQuery(sub, subS.size(), "password");

		if (!password.size() || !mail.size())
		{
			std::string body = "{\"createdUser\":\"False\"}";
			std::string a = webManager.getWebHeadders(body.size()) + body;
			send(new_wsocket, a.c_str(), a.length(), 0);
			continue;
		}

		userManager.createUser(mail, password, UserManager::UserType::employee);

		std::string body = "{\"createdUser\":\"True\"}";
		std::string a = webManager.getWebHeadders(body.size()) + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}
	/*else if (subS.size() > 1)
	{
		std::string body = "{\"id\":" + std::to_string(rand() % 156) + "}";
		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nContent-type: application/json\r\nContent-Length: " + std::to_string(body.length()) + "\r\n" + "Connection: close\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);
	}*/
	else
	{
		std::string body = "<html>|" + subS + "| not found " + std::to_string(subS.length()) + "</html>";
		std::string a = "HTTP/1.1 200 OK \r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Headers: *\r\nContent-type: text/html\r\nContent-Length: " + std::to_string(body.length()) + "\r\n\r\n" + body;
		send(new_wsocket, a.c_str(), a.length(), 0);


	}

	closesocket(new_wsocket);

	free(sub);



	std::cout << buff << '\n';

}
	 }
