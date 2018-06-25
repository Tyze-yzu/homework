// AvailableRoomsDatabase.cpp
// Member-function definitions for class AvailableRoomsDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

extern void computeCurrentDate(Date &currentDate);
extern bool leapYear( unsigned int year );

void AvailableRoomsDatabase::loadAvailableRooms()
{
	ifstream file;
	file.open("Available Rooms.dat", ios::binary);
	AvailableRooms tmp;
	while (file.read(reinterpret_cast<char *>(&tmp), sizeof(AvailableRooms)))
		availableRooms.push_back(tmp);

	file.close();
	if (availableRooms.size() == 0)
		initilizeAvailableRooms();
	else
		adjustAvailableRooms();
	//cout << "Available Rooms size: " << availableRooms.size() << endl;
	return;
}

void AvailableRoomsDatabase::initilizeAvailableRooms()
{
	Date currentDate;
	computeCurrentDate(currentDate);
	int j = 0;
	unsigned int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	for (unsigned int i = currentDate.getMonth(); i <= currentDate.getMonth() + 5; i++, j++) {
		unsigned int year = currentDate.getYear() + (i >= 13);
		unsigned int month = i % 12;
		unsigned int day = ((month != 2) ? days[month] : (leapYear(year) ? 29 : 28));
		for (unsigned int k = 1; k <= day; k++) {
			AvailableRooms* tmp = new AvailableRooms();
			tmp->setDate(year, month, k);
			availableRooms.push_back(*tmp);
			//cout << "·s¼W: " << tmp->getDate().getYear() << "-" << tmp->getDate().getMonth() << "-" << tmp->getDate().getDay() << endl;
		}
	}
}

void AvailableRoomsDatabase::adjustAvailableRooms()
{
	Date currentDate;
	computeCurrentDate(currentDate);
	auto it = availableRooms.begin();
	if (currentDate < it->getDate()) {
		cout << "Available Rooms.dat must have problem. pleace delete it." << endl;
		system("PAUSE");
		exit(0);
	}
	for (; it != availableRooms.end(); ++it) {
		if (currentDate == it->getDate())
			break;
	}
	availableRooms.erase(availableRooms.begin(), it);
}

void AvailableRoomsDatabase::displayAvailableRooms(  Date &checkInDate, Date &checkOutDate )
{
	vector< AvailableRooms >::iterator it1, it2;
	findIterators(checkInDate, checkOutDate, it1, it2);

	cout << setw(10) << right << "Date"
		<< setw(16) << right << "Superior Room"
		<< setw(14) << right << "Deluxe Room"
		<< setw(19) << right << "Deluxe Twin Room"
		<< setw(17) << right << "Superior Suite"
		<< setw(15) << right << "Deluxe Suite" << endl;

	for (; it1 != it2+1; ++it1)
		cout << setw(10) << right << to_string(it1->getDate().getYear()) + "-" + ((it1->getDate().getMonth() < 10) ? "0" : "") + to_string(it1->getDate().getMonth()) + "-" + ((it1->getDate().getDay() < 10) ? "0" : "") + to_string(it1->getDate().getDay())
		<< setw(16) << right << it1->getAvailableRooms()[1]
		<< setw(14) << right << it1->getAvailableRooms()[2]
		<< setw(19) << right << it1->getAvailableRooms()[3]
		<< setw(17) << right << it1->getAvailableRooms()[4]
		<< setw(15) << right << it1->getAvailableRooms()[5] << endl;
/*
with out find iterator
	
	cout << setw(10) << right << "Date"
		<< setw(16) << right << "Superior Room"
		<< setw(14) << right << "Deluxe Room"
		<< setw(19) << right << "Deluxe Twin Room"
		<< setw(17) << right << "Superior Suite"
		<< setw(15) << right << "Deluxe Suite" << endl;
//	cout << to_string(checkInDate.getYear()) + "-" + to_string(checkInDate.getMonth()) + "-" + to_string(checkInDate.getDay()) << endl;
//	cout << to_string(checkOutDate.getYear()) + "-" + to_string(checkOutDate.getMonth()) + "-" + to_string(checkOutDate.getDay()) << endl;
	for (unsigned int i = 0; i < availableRooms.size(); i++) {
//		cout << to_string(availableRooms[i].getDate().getYear()) + "-" + to_string(availableRooms[i].getDate().getMonth()) + "-" + to_string(availableRooms[i].getDate().getDay()) << endl;
		if ((availableRooms[i].getDate() >= checkInDate) && (availableRooms[i].getDate() <= checkOutDate)) {
			unsigned int *arr = availableRooms[i].getAvailableRooms();
			Date tmp = availableRooms[i].getDate();
			cout << setw(10) << right << to_string(tmp.getYear()) + "-" + ((tmp.getMonth()<10) ? "0" : "") + to_string(tmp.getMonth()) + "-" + ((tmp.getDay()<10)?"0" : "")+to_string(tmp.getDay())
				<< setw(16) << right << arr[1]
				<< setw(14) << right << arr[2]
				<< setw(19) << right << arr[3]
				<< setw(17) << right << arr[4]
				<< setw(15) << right << arr[5] << endl;
		}
	}
*/
}

unsigned int AvailableRoomsDatabase::findMinNumRooms( unsigned int roomType,
                             const Date &checkInDate, const Date &checkOutDate )
{
	unsigned int min = -1;
	vector<AvailableRooms>::iterator it1, it2;
	findIterators(checkInDate, checkOutDate, it1, it2);
	for (; it1 != it2+1; ++it1)
		min = (it1->getAvailableRooms()[roomType] > min) ? min : it1->getAvailableRooms()[roomType];
	return min;
/*
with out find iterator

	unsigned int min = -1;
	for (unsigned int i = 0; i < availableRooms.size(); i++) {
		if ((availableRooms[i].getDate() >= checkInDate) && (availableRooms[i].getDate() <= checkOutDate)) {
			min = (availableRooms[i].getAvailableRooms()[roomType] > min)? min: availableRooms[i].getAvailableRooms()[roomType];
		}
	}
	return min;

*/
}

void AvailableRoomsDatabase::decreaseAvailableRooms( unsigned int roomType, unsigned int numRooms,
                                                     const Date &checkInDate, const Date &checkOutDate )
{
	vector<AvailableRooms>::iterator it1, it2;
	findIterators(checkInDate, checkOutDate, it1, it2);
	for (; it1 != it2+1; ++it1)
		it1->decreaseAvailableRooms(roomType, numRooms);
}

void AvailableRoomsDatabase::saveAvailableRooms()
{
	ofstream file;
	file.open("Available Rooms.dat", ios::binary);
	for (unsigned int i = 0; i < availableRooms.size(); i++)
		file.write(reinterpret_cast<char *>(&availableRooms[i]), sizeof(AvailableRooms));
	file.close();
}

void AvailableRoomsDatabase::findIterators( const Date &checkInDate, const Date &checkOutDate,
                                            vector< AvailableRooms >::iterator &checkInIterator,
                                            vector< AvailableRooms >::iterator &checkOutIterator )
{
	for (vector< AvailableRooms >::iterator it = availableRooms.begin(); it != availableRooms.end(); ++it) {
		if (it->getDate() == checkInDate)
			checkInIterator = it;
		if (it->getDate() == checkOutDate) {
			checkOutIterator = it;
			return;
		}
	}
}