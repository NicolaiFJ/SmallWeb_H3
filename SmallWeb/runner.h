#pragma once

#include <iostream>
#include <WinSock2.h>
#include <string>
#include <string.h>
#include <chrono>
#include <random>

//#include "Users_get.cpp"
#include "UserManager.h"
#include "getSubUrl.h"
#include "getVarStringQuery.h"
#include "WebManager.h"
#include "BookingManager.h"



const int BUFFER_SIZE = 1080;


void runWebServer(SOCKET& wsocket,
	SOCKET& new_wsocket,
	WSADATA& wsaData,
	struct sockaddr_in& server,
	int& server_len,
	WebManager& webManager,
	UserManager& userManager,
	BookingManager& bookingManager);