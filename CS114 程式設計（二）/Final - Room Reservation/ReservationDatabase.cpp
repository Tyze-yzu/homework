// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

void ReservationDatabase::loadFromReservations()
{
	ifstream file;
	file.open("Reservations.dat", ios::binary);
	Reservation tmp;
	while (file.read(reinterpret_cast<char *>(&tmp), sizeof(Reservation))) {
		reservations.push_back(tmp);
	}
	//cout << "reservation size: " << reservations.size() << endl;
	file.close();
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

unsigned int ReservationDatabase::numReservations( string IDNumber )
{
	unsigned int k = 0;
	for (unsigned int i = 0; i < reservations.size(); i++)
		if (reservations[i].getIDNumber() == IDNumber)
			k++;
	return k;
}

void ReservationDatabase::displayReservations( string IDNumber )
{
	if (numReservations(IDNumber) == 0) {
		cout << "Have no reservation." << endl;
		return;
	}

	cout << setw(12) << right << "Name"
		<< setw(7) << right << "Fare"
		<< setw(12) << right << "Mobile"
		<< setw(18) << right << "Room type"
		<< setw(16) << right << "Number of rooms"
		<< setw(15) << right << "Check in date"
		<< setw(15) << right << "Check out date" << endl;


	for (unsigned int i = 0; i < reservations.size(); i++)
		if (reservations[i].getIDNumber() == IDNumber)
			reservations[i].displayReservation();
}

void ReservationDatabase::saveToReservationFile()
{
	ofstream file;
	file.open("Reservations.dat", ios::binary);
	for (unsigned int i = 0; i < reservations.size(); i++)
		file.write(reinterpret_cast<char *>(&reservations[i]), sizeof(Reservation));
	file.close();
}