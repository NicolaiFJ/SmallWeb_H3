#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <string.h>
#include <thread>
#include <random>

//#include "Users_get.cpp"
#include "UserManager.h"
#include "getSubUrl.h"
#include "getVarStringQuery.h"
#include "WebManager.h"
#include "BookingManager.h"
#include <functional> // IMPORTANT
#include "runner.h"

int main() {
	
	

	SOCKET wsocket;
	SOCKET new_wsocket;
	WSADATA wsaData;
	struct sockaddr_in server;
	int server_len;
	const int BUFFER_SIZE = 1080;

	

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "FAILED_1\n";
		return 1;
	}

	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET)
	{
		std::cout << "FAILED_2\n";
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(4090);
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, server_len) != 0)
	{
		std::cout << "FAILED_3\n";
		return 1;
	}

	if (listen(wsocket, 20) != 0) {
		std::cout << "FAILED_4\n";
		return 1;
	}

	WebManager webManager;
	UserManager userManager;
	BookingManager bookingManager;

	userManager.init();
	bookingManager.init();

	std::thread t_1(
		runWebServer,
		std::ref(wsocket),
		std::ref(new_wsocket),
		std::ref(wsaData),
		std::ref(server),
		std::ref(server_len),
		std::ref(webManager),
		std::ref(userManager),
		std::ref(bookingManager)
	);


	std::thread t_2(
		runWebServer,
		std::ref(wsocket),
		std::ref(new_wsocket),
		std::ref(wsaData),
		std::ref(server),
		std::ref(server_len),
		std::ref(webManager),
		std::ref(userManager),
		std::ref(bookingManager)
	);

	std::thread t_3(
		runWebServer,
		std::ref(wsocket),
		std::ref(new_wsocket),
		std::ref(wsaData),
		std::ref(server),
		std::ref(server_len),
		std::ref(webManager),
		std::ref(userManager),
		std::ref(bookingManager)
	);

	while(true)
	{ }

	return 0;
}