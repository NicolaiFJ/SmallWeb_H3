#pragma once
#include <vector>
#include <string>
#include "UserManager.h"

class BookingManager
{
	struct Booking
	{
		std::string hour;
		int userID;
		std::string location;
		std::string service;
		std::string date;
	};

	std::vector<Booking> m_bookings;

public:
	void init();
	void createBooking(int userID, std::string hour, std::string location, std::string service, std::string date);
	std::string getBookingsAsJsonByUserID(int ID,UserManager * userMan);
	bool isTimeDateTaken(std::string date, std::string hour);

};

