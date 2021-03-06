// Booking.cpp
// Member-function definitions for class Booking
#include <iostream>
#include <iomanip>
#include "Booking.h" // Booking class definition

extern char hours[17][8];
extern char movieNames[30][60];
extern char availableDates[10][12];
extern int numDates;

Booking::Booking()
{
}

void Booking::setEmail( string theEmail )
{
   int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

string Booking::getEmail()
{
   return string( email );
}

void Booking::setMovieCode( int theMovieCode )
{
   movieCode = ( theMovieCode > 0 ? theMovieCode : 0 );
}

int Booking::getMovieCode()
{
   return movieCode;
}

void Booking::setDateCode( int theDateCode )
{
   dateCode = ( theDateCode > 0 ? theDateCode : 0 );
}

int Booking::getDateCode()
{
   return dateCode;
}

void Booking::setSessionTimeCode( int theSessionTimeCode )
{
   sessionTimeCode = ( theSessionTimeCode > 0 ? theSessionTimeCode : 0 );
}

int Booking::getSessionTimeCode()
{
   return sessionTimeCode;
}

void Booking::setNumTickets( int theNumTickets[] )
{
   for( int i = 0; i < 4; i++ )
      numTickets[ i ] = ( theNumTickets[ i ] > 0 ? theNumTickets[ i ] : 0 );
}

int Booking::getNumTickets( int ticketType )
{
   return numTickets[ ticketType ];
}

void Booking::setSeletedSeats( string theSeletedSeats[], int numSeats )
{
   for( int i = 0; i < numSeats; i++ )
   {
      seletedSeats[ i ][ 0 ] = theSeletedSeats[ i ][ 0 ];
      seletedSeats[ i ][ 1 ] = theSeletedSeats[ i ][ 1 ];
	  seletedSeats[ i ][ 2 ] = '\0';
   }
}

string Booking::getSeletedSeat( int number )
{
   return seletedSeats[ number ];
}

void Booking::displayBooking( MovieDatabase &movieDatabase )
{
	cout << setw(7) << left << "" << setw(15) << right << "No. of Tickets" << setw(7) << right << "Price" << setw(10) << right << "Subtotal" << endl;
	string text[4] = { "Adult", "Concession", "Disability", "Elderly" };
	int total = 0;
	for (int i = 0; i < 4; i++) {
		if (numTickets[i] != 0) {
			int tmp = movieDatabase.getMovie(movieCode).getPrice(i) * numTickets[i];
			total += tmp;
			cout << setw(7) << left << text[i] << setw(15) << right << numTickets[i] << setw(7) << right << movieDatabase.getMovie(movieCode).getPrice(i) << setw(10) << right << tmp << endl;
		}
	}
	cout << endl << "Total Amount For Tickets: " << total << endl;
}