#include "BookingManager.h"
#include <iostream>


void BookingManager::init()
{
    createBooking(1, "19:30", "Copenhagen", "Hair wash", "nodate");
    createBooking(1, "20:00", "Copenhagen", "Hair dye", "nodate");
}

void BookingManager::createBooking(int userID, std::string hour, std::string location, std::string service, std::string date)
{
	Booking booking;
	booking.userID = userID;
	booking.hour = hour;
	booking.location = location;
	booking.service = service;
    booking.date = date;

	m_bookings.push_back(booking);

	return;
}

std::string BookingManager::getBookingsAsJsonByUserID(int ID, UserManager* userMan)
{
    std::string json = "[";
    bool first = true;
    bool hasWorkerPerms = false;


    if (userMan->m_users.size() >= ID)
    {
        if (userMan->m_users[ID - 1].userType == UserManager::UserType::employee)
        {
            hasWorkerPerms = true;
        }
    }

    for (size_t i = 0; i < m_bookings.size(); ++i)
    {
        const Booking& booking = m_bookings[i];
        if (booking.userID == ID || hasWorkerPerms)
        {
            if (!first)
                json += ",";

            json += "{";
            json += "\"hour\":\"" + booking.hour + "\",";
            json += "\"userID\":" + std::to_string(booking.userID) + ",";
            json += "\"location\":\"" + booking.location + "\",";
            json += "\"service\":\"" + booking.service + "\",";
            json += "\"date\":\"" + booking.date + "\"";
            if (userMan->m_users.size() >= m_bookings[i].userID)
            {
                json += ",\"mail\":\"" + userMan->m_users[m_bookings[i].userID - 1].mail + "\"";
            }            
            json += "}";

            first = false;
        }
    }

    json += "]";
    return json;
}

bool BookingManager::isTimeDateTaken(std::string date, std::string hour)
{
    for (int i = 0; i < m_bookings.size(); i++)
    {
        if (m_bookings[i].date == date && m_bookings[i].hour == hour)
        {
            std::cout << "date: " << date << "\n";
            std::cout << "HHHHHHWHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n";
            return true;
        }

        std::cout << "date: " << m_bookings[i].date << "\n";
        std::cout << "hour: " << m_bookings[i].hour << "\n";
    }

    return false;


}
