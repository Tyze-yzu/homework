// Reservation.cpp
// Member-function definitions for class Reservation.
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
#include "Reservation.h" // Reservation class definition

void Reservation::setReservation( unsigned int inputRoomType, unsigned int inputNumRooms,
                                  Date inputCheckInDate, Date inputCheckOutDate,
                                  string inputIDNumber, string inputName, string inputMobile )
{
   roomType = inputRoomType;
   numRooms = inputNumRooms;
   checkInDate = inputCheckInDate;
   checkOutDate = inputCheckOutDate;
   setIDNumber( inputIDNumber );
   setName( inputName );
   setMobile( inputMobile );
}

void Reservation::setIDNumber( string theIDNumber )
{
   strcpy_s( IDNumber, 12, theIDNumber.c_str() );
}

void Reservation::setName( string theName )
{
   strcpy_s( name, 12, theName.c_str() );
}

void Reservation::setMobile( string theMobile )
{
   strcpy_s( mobile, 12, theMobile.c_str() );
}

string Reservation::getIDNumber()
{
   return IDNumber;
}

unsigned int Reservation::getRoomType()
{
   return roomType;
}

unsigned int Reservation::getNumRooms()
{
   return numRooms;
}

Date Reservation::getCheckInDate()
{
   return checkInDate;
}

Date Reservation::getCheckOutDate()
{
   return checkOutDate;
}

bool Reservation::equalID( string id1, string id2 )
{
	return id1 == id2;
}

extern bool leapYear(unsigned int year);
void add(Date &d) {
	unsigned int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (leapYear(d.getYear()))
		days[2] = 29;

	if (d.getDay() != days[d.getMonth()]) 
		return d.setDay(d.getDay() + 1);

	d.setDay(1);
	if (d.getMonth() != 12) 
		return d.setMonth(d.getMonth() + 1);

	d.setMonth(1);
	d.setYear(d.getYear() + 1);
}

void Reservation::displayReservation()
{
	unsigned int day = 0;
	Date tmp = checkInDate;
	for (; !(tmp == checkOutDate); add(tmp), day++);

	string roomtypeName[6] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room", "Superior Suite", "Deluxe Suite" };
	unsigned int price[6] = { 0, 5390, 6270, 6270, 6820, 8470};
		cout << setw(12) << right << name
		<< setw(7) << right << price[roomType] * numRooms * day
		<< setw(12) << right << mobile
		<< setw(18) << right << roomtypeName[roomType]
		<< setw(16) << right << numRooms
		<< setw(15) << right << to_string(checkInDate.getYear()) + "-" + ((checkInDate.getMonth() < 10) ? "0" : "") + to_string(checkInDate.getMonth()) + "-" + ((checkInDate.getDay() < 10) ? "0" : "") + to_string(checkInDate.getDay())
		<< setw(15) << right << to_string(checkOutDate.getYear()) + "-" + ((checkOutDate.getMonth() < 10) ? "0" : "") + to_string(checkOutDate.getMonth()) + "-" + ((checkOutDate.getDay() < 10) ? "0" : "") + to_string(checkOutDate.getDay()) << endl;
}