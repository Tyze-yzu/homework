// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "MakeReservation.h" // MakeReservation class definition

// extern bool legalID( const string &id );
extern void computeCurrentDate(Date &currentDate);
extern bool leapYear( unsigned int year );

// MakeReservation constructor initializes base-class data members
MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
                                  AvailableRoomsDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomsDatabase( theAvailableRoomsDatabase )
{
} // end MakeReservation constructor

// performs transaction
void MakeReservation::execute()
{
	Date checkInDate;
	Date checkOutDate;
	Date currentDate;
	Date availableMonths[6];
	unsigned int checkInYMCode;
	unsigned int firstDay;
	unsigned int lastDay;

	// calling tree
	computeCurrentDate(currentDate);
	computeAvailableMonths(currentDate, availableMonths);
	inputCheckInDates(checkInDate, currentDate, availableMonths, checkInYMCode, firstDay, lastDay);
	inputCheckOutDates(checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay);
	availableRoomsDatabase.displayAvailableRooms(checkInDate, checkOutDate);


	// check if all room's minimun is 0
	bool flag = ((availableRoomsDatabase.findMinNumRooms(1, checkInDate, checkOutDate) == 0) &&
		(availableRoomsDatabase.findMinNumRooms(2, checkInDate, checkOutDate) == 0) &&
		(availableRoomsDatabase.findMinNumRooms(3, checkInDate, checkOutDate) == 0) &&
		(availableRoomsDatabase.findMinNumRooms(4, checkInDate, checkOutDate) == 0) &&
		(availableRoomsDatabase.findMinNumRooms(5, checkInDate, checkOutDate) == 0));
	if (flag) {
		cout << "Have no room in this time selection. directing to home page." << endl;
		return;
	}

	cout << "Select Room Type¡G" << endl
		<< "1. Superior Room" << endl
		<< "2. Deluxe Room" << endl
		<< "3. Deluxe Twin Room" << endl
		<< "4. Superior Suite" << endl
		<< "5. Deluxe Suite" << endl;

	unsigned int roomtype = 0;
	while (roomtype < 1 || roomtype > 5) {
		cout << "? ";
		cin >> roomtype;
		if (availableRoomsDatabase.findMinNumRooms(roomtype, checkInDate, checkOutDate) == 0) {
			cout << "Have no room." << endl;
			roomtype = 0;
		}
	}

	unsigned int roomnum = 0;
	unsigned int min = availableRoomsDatabase.findMinNumRooms(roomtype, checkInDate, checkOutDate);
	while (roomnum < 1 || roomnum > min) {
		cout << "Number of rooms(" << min << " rooms available) :";
		cin >> roomnum;
	}

	availableRoomsDatabase.decreaseAvailableRooms(roomtype, roomnum, checkInDate, checkOutDate);

	cin.ignore();
	string id, name, mobile;
	cout << "ID Number: ";
	getline(cin, id);
	cout << "Name: ";
	getline(cin, name);
	cout << "Mobile Phone: ";
	getline(cin, mobile);

	Reservation *tmp = new Reservation();
	tmp->setReservation(roomtype, roomnum, checkInDate, checkOutDate, id, name, mobile);
	cout << setw(12) << right << "Name"
		<< setw(7) << right << "Fare"
		<< setw(12) << right << "Mobile"
		<< setw(18) << right << "Room type"
		<< setw(16) << right << "Number of rooms"
		<< setw(15) << right << "Check in date"
		<< setw(15) << right << "Check out date" << endl;
	tmp->displayReservation();
	reservationDatabase.pushBack(*tmp);
}

unsigned int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
void MakeReservation::computeAvailableMonths( Date currentDate, Date availableMonths[] )
{
	int j = 0;
	for (unsigned int i = currentDate.getMonth(); i <= currentDate.getMonth() + 5; i++, j++) {
		unsigned int year = currentDate.getYear() + (i>12);
		unsigned int month = ((i > 12) ? i - 12 : i);
		unsigned int day = ((month != 2) ? days[month] : (leapYear(year) ? 29 : 28));
		//cout << year << " " << month << " " << day << endl;
		availableMonths[j].setYear(year);
		availableMonths[j].setMonth(month);
		availableMonths[j].setDay(day);
	}
}

void MakeReservation::inputCheckInDates( Date &checkInDate, Date currentDate, Date availableMonths[], unsigned int &checkInYMCode, unsigned int &firstDay, unsigned int &lastDay )
{
	cout << "\nPlease Input Check In Date\n\n";
	cout << "Month:\n";
	for (int i = 0; i < 6; i++)
		cout << to_string(i + 1) << ". " << availableMonths[i].getYear() << "-" << ((availableMonths[i].getMonth() < 10) ? "0" + to_string(availableMonths[i].getMonth()) : to_string(availableMonths[i].getMonth())) << endl;

	unsigned int input = 0;
	while (input < 1 || input > 6) {
		cout << "? ";
		cin >> input;
	}
	checkInYMCode = input-1;

	checkInDate.setYear(availableMonths[checkInYMCode].getYear());
	checkInDate.setMonth(availableMonths[checkInYMCode].getMonth());


	firstDay = ((input == 1) ? currentDate.getDay() : 1);
	// ¯d¤@¤Ñ
	lastDay = ((input == 6)?availableMonths[input-1].getDay()-1: availableMonths[input - 1].getDay());

	input = 0;
	while (input < firstDay || input > lastDay) {
		cout << "Day(" << firstDay << " ~ " << lastDay << ") : ";
		cin >> input;
	}
	checkInDate.setDay(input);
	return;
}

void MakeReservation::inputCheckOutDates( Date &checkOutDate, Date checkInDate, Date availableMonths[],  unsigned int checkInYMCode, unsigned int firstDay, unsigned int lastDay )
{

	cout << "\nPlease Input Check Out Date\n\n";

	// if the first day is the last day of that month
	bool flag = false;
	unsigned int month = availableMonths[checkInYMCode].getMonth();
	unsigned int lastOfMonth = (month != 2) ? days[month] : (leapYear(availableMonths[checkInYMCode].getYear()) ? 29 : 28);

	flag = (checkInDate.getDay() == lastOfMonth);
	int count = 1;
	for (int i = 0; i < 6; i++) {
		if ((flag && i == 0) || (checkInYMCode > i) || checkInDate >=availableMonths[i]) {
			count++;
			continue;
		}
		cout << to_string(i + 1) << ". " << availableMonths[i].getYear() << "-" << ((availableMonths[i].getMonth() < 10) ? "0" + to_string(availableMonths[i].getMonth()) : to_string(availableMonths[i].getMonth())) << endl;
	}

	int input = 0;
	while (input < count || input > 6) {
		cout << "? ";
		cin >> input;
	}

	input--;
	Date tmp = availableMonths[input];
	//cout << "setyear " << tmp.getYear();
	//cout << "setmonth " << tmp.getMonth();
	checkOutDate.setYear(tmp.getYear());
	checkOutDate.setMonth(tmp.getMonth());

	unsigned int fd = (input > checkInYMCode) ? 1 : checkInDate.getDay() + 1;
	unsigned int ed = tmp.getDay();

	input = 0;
	while (input < fd || input > ed) {
		cout << "Day(" << fd << " ~ " << ed << ") : ";
		cin >> input;
	}
	checkOutDate.setDay(input);
	return;
}