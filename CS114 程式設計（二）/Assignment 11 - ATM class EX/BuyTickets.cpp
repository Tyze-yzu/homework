// BuyTickets.cpp
// Member-function definitions for class BuyTickets
#include <iostream>
#include <iomanip>
using namespace::std;
#include "BuyTickets.h" // BuyTickets class definition

extern char hours[ 17 ][ 8 ];
extern char movieNames[ 30 ][ 60 ];
extern char availableDates[ 10 ][ 12 ];
extern int numDates;
int inputAnInteger( int begin, int end );

// BuyTickets default constructor
BuyTickets::BuyTickets( MovieDatabase &theMovieDatabase, BookingDatabase &theBookingDatabase, string theEmail )
   : movieDatabase( theMovieDatabase ),
     bookingDatabase( theBookingDatabase )
{
   int length = theEmail.size();
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

void BuyTickets::execute()
{
	movieDatabase.displaySessionTimes(movieNames, availableDates);
	cout << "\n" << endl;
	Booking tmp;
	int moviecode, datecode, sessioncode;
	int arr[4] = {0};
	while (true)
	{
		printf("Enter movie code (0 - %d): ", 11 - 1);
		moviecode = inputAnInteger(0, 11 - 1);
		if (moviecode >= 0 && moviecode <= 11 - 1)
			break;
	}
	cout << endl;
	while (true)
	{
		printf("Enter date code (0 - %d): ", 17 - 1);
		datecode = inputAnInteger(0, numDates - 1);
		if (datecode >= 0 && datecode <= 17 - 1 )
			break;
	}
	cout << endl;
	while (true)
	{
		printf("Enter session time code (0 - %d): ", 16);
		sessioncode = inputAnInteger(0, 16);
		if (sessioncode >= 0 && sessioncode <= 16)
			break;
	}


	printf("\nMovie: %s\nDate: %s\nShow Time: %s\n\nPrice: Adult-270, Concession-270, Disability-160, Elderly-160\n\n", movieNames[moviecode], availableDates[datecode], hours[sessioncode]);

	while ((arr[0] + arr[1] + arr[2] + arr[3]) <= 0) {
		while (true)
		{
			printf("Enter the number of adult tickets (0 - 6): ");
			arr[0] = inputAnInteger(0, 6);
			if (arr[0] >= 0 && arr[0] <= 6)
				break;
		}
		while (true)
		{
			printf("Enter the number of concession tickets (0 - 6): ");
			arr[1] = inputAnInteger(0, 6);
			if (arr[1] >= 0 && arr[1] <= 6)
				break;
		}
		while (true)
		{
			printf("Enter the number of disability tickets (0 - 6): ");
			arr[2] = inputAnInteger(0, 6);
			if (arr[2] >= 0 && arr[2] <= 6)
				break;
		}
		while (true)
		{
			printf("Enter the number of elderly tickets (0 - 6): ");
			arr[3] = inputAnInteger(0, 6);
			if (arr[3] >= 0 && arr[3] <= 6)
				break;
		}
	}

	tmp.setMovieCode(moviecode);
	tmp.setEmail( string(email) );
	tmp.setNumTickets(arr);
	tmp.setDateCode(datecode);
	tmp.setSessionTimeCode(sessioncode);

	selectSeats(tmp);
	bookingDatabase.addBooking(tmp);
	tmp.displayBooking(movieDatabase);
}

void BuyTickets::selectSeats( Booking &newBooking )
{
	int movie = newBooking.getMovieCode();
	int date = newBooking.getDateCode();
	int sessionTime = newBooking.getSessionTimeCode();
	int sum = newBooking.getNumTickets(0) + newBooking.getNumTickets(1) + newBooking.getNumTickets(2) + newBooking.getNumTickets(3);
	cout << "\n  A B C D E F G H I J K L" << endl;
	for (int i = 0; i < 8; i++) {
		cout << i;
		for (int j = 0; j < 12; j++)
			(movieDatabase.getMovie(movie).getOccupiedSeat(date,sessionTime,i,j)) ? cout << " 1" : cout << " 0";
		cout << endl;
	}

	cout << "Select " << sum << " seats (e.g. 0A):\n";
	int i = 0;
	string arr[24];
	while (sum - i) {
		cout << "? ";
		char tmp_x, tmp_y;
		cin >> tmp_x >> tmp_y;
		int x, y;
		x = tmp_x - '0';
		y = tmp_y - 'A';
		if (x < 0 || x > 7 || y < 0 || y > 11) {
			cout << "\nInput error" << endl;
			continue;
		}
		if (movieDatabase.getMovie(movie).getOccupiedSeat(date, sessionTime, x, y)) {
			cout << "\nThis seat bas been occupied. Please select another seat." << endl;
			continue;
		}
		movieDatabase.getMovie(movie).setOccupiedSeat(date, sessionTime, x, y);
		
		arr[i].resize(3);
		arr[i][0] = tmp_x;
		arr[i][1] = tmp_y;
		arr[i][2] = '\0';
		i++;
	}
	newBooking.setSeletedSeats(arr, sum);
	cout << "\nSuccessful\n" << endl;
}
