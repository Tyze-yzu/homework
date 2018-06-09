// BookingDatabase.cpp
// Member-function definitions for class BookingDatabase
#include <iostream>
#include <fstream>
#include "BookingDatabase.h" // BookingDatabase class definition

extern char hours[ 17 ][ 8 ];
extern char movieNames[ 30 ][ 60 ];
extern char availableDates[ 10 ][ 12 ];

// BookingDatabase default constructor loads bookings from the file Bookings.dat
BookingDatabase::BookingDatabase()
{
   loadBookings();
}

// BookingDatabase destructor saves bookings into the file Bookings.dat
BookingDatabase::~BookingDatabase()
{
   saveBookings();
}

void BookingDatabase::addBooking( Booking newBooking )
{
   bookings.push_back( newBooking );
}

// retrieve Booking object containing specified email
bool BookingDatabase::existingBooking( string email )
{
	for (unsigned int i = 0; i < bookings.size(); i++)
		if (bookings[i].getEmail() == email)
			return true;
	return false;
} // end function existingBooking

void BookingDatabase::displayBookings( string email, MovieDatabase &movieDatabase )
{
	bool isHaveBookings = false;
	for (unsigned int i = 0; i < bookings.size(); i++) {
		if (bookings[i].getEmail() == email) {
			isHaveBookings = true;
			break;
		}
	}
	if (!isHaveBookings) {
		cout << "\nNo Bookings!\n" << endl;
		return;
	}

	cout << "\nBooking History\n" << endl;
	for (unsigned int i = 0; i < bookings.size(); i++) {
		if (bookings[i].getEmail() == email) {
			Movie tmp = movieDatabase.getMovie(bookings[i].getMovieCode());
			cout << "Movie: " << movieNames[tmp.getMovieCode()] << endl;
			cout << "Date: " << availableDates[bookings[i].getDateCode()] << endl;
			cout << "Show Time: " << hours[bookings[i].getSessionTimeCode()] << endl;
			cout << "Seats:";
			int sum = bookings[i].getNumTickets(0) + bookings[i].getNumTickets(1) + bookings[i].getNumTickets(2) + bookings[i].getNumTickets(3);
			for (int j = 0; j < sum; j++)
				cout << " " << bookings[i].getSeletedSeat(j);
			cout << endl;

			bookings[i].displayBooking(movieDatabase);
			//display(movies, bookingHistories[i]);
			cout << "\n----------------------------------------------\n" << endl;
		}
	}
}

void BookingDatabase::loadBookings()
{
	ifstream file;
	file.open("Booking.dat", ios::in | ios::binary);
	while (file && !file.eof()) {
		Booking tmp;
		file.read(reinterpret_cast< char * >(&tmp), sizeof(Booking));
		bookings.push_back(tmp);
	}
	//bookings.pop_back(); // using while loop will get a empty item in the end, so need to fix it.
	file.close();
}

void BookingDatabase::saveBookings()
{
	ofstream file;
	file.open("Booking.dat", ios::out | ios::binary);
	for (unsigned int i = 0; i < bookings.size(); i++)
		file.write(reinterpret_cast< const char * >(&bookings[i]), sizeof(Booking));
	file.close();
}