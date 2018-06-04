/*
 * Name: Tickets System
 * Author: 張彥成
 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct MemberRecord
{
	char email[ 40 ];
	char password[ 24 ];
	char IDNumber[ 12 ];
	char name[ 12 ];
	char phone[ 12 ];
};

struct Movie
{
	int movieCode;
	int prices[ 4 ]; // prices[0]:adult, prices[1]:concession, prices[2]:disability, prices[3]:elderly
	bool dates[ 9 ];
	bool sessionTimes[ 17 ];
	bool occupiedSeats[ 9 ][ 17 ][ 8 ][ 12 ]; // occupiedSeats[i][j] is the occupied Seats for all accounts
};                                           // at j-th session time on i-th date

struct BookingInfo
{
	char email[ 40 ];
	int movieCode;
	int dateCode;
	int sessionTimeCode;
	int numTickets[ 4 ]; // numTickets[0]: the number of adult tickets,
						// numTickets[1]: the number of concession tickets,
						// numTickets[2]: the number of disability tickets,
						// numTickets[3]: the number of elderly tickets
	char seletedSeats[ 24 ][ 4 ]; // seleted seats for the user with the specified email
};

char hours[ 17 ][ 8 ] = { "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00",
						  "18:00", "19:00", "20:00", "21:00", "22:00", "23:00", "00:00", "01:00" };

void loadMemberInfo( MemberRecord memberDetails[], int &numMembers );
int inputAnInteger( int begin, int end );
void signIn( MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][ 60 ], int numMovies,
			 BookingInfo bookingHistories[], int &numBookings, char availableDates[][ 12 ], int numDates );
bool illegal( char email[], char password[], MemberRecord memberDetails[], int numMembers, int &recordNumber );
void accountInfor( MemberRecord memberDetails[], int numMembers, int recordNumber );
void newMember( MemberRecord memberDetails[], int &numMembers );
bool existingID( char newIDNumber[], MemberRecord memberDetails[], int &numMembers );
bool existingEmail( char newEmail[], MemberRecord memberDetails[], int &numMembers );

void loadBookingHistories( BookingInfo bookingHistories[], int &numBookings );
void loadAvailableDates( char availableDates[][ 12 ], int &numDates );
void loadMovies( Movie movies[], int &numMovies );
void loadMovieNames( char movieNames[][ 60 ], int numMovies );
void buyTickets( BookingInfo bookingHistories[], int &numBookings, Movie movies[], char movieNames[][ 60 ],
				 int numMovies, char availableDates[][ 12 ], int numDates, char email[] );
void selectSeats( BookingInfo bookingHistories[], int numBookings, Movie movies[] );
void display( Movie movies[], BookingInfo bookingHistory );
void displaySessionTimes( Movie movies[], char movieNames[][ 60 ], int numMovies,
						  char availableDates[][ 12 ], int numDates );
void displayBookingHistory( BookingInfo bookingHistories[], int numBookings, Movie movies[],
							char movieNames[][ 60 ], char availableDates[][ 12 ], char email[] );
void saveMemberInfo( MemberRecord memberDetails[], int numMembers );
void saveMovies( Movie movies[], int numMovies );
void saveBookingHistories( BookingInfo bookingHistories[], int numBookings );

int main()
{
	MemberRecord memberDetails[ 100 ] = {};
	int numMembers = 0;
	loadMemberInfo( memberDetails, numMembers );

	BookingInfo bookingHistories[ 1000 ] = {};
	int numBookings = 0;
	loadBookingHistories( bookingHistories, numBookings );

	Movie movies[ 30 ] = {};
	int numMovies = 0;
	loadMovies( movies, numMovies );

	char movieNames[ 30 ][ 60 ] = {};
	loadMovieNames( movieNames, numMovies );

	char availableDates[ 10 ][ 12 ];
	int numDates = 0;
	loadAvailableDates( availableDates, numDates );

	cout << "Welcome to Vieshow Cinemas Taipei QSquare system\n\n";

	int choice;

	while( true )
	{
		cout << "Enter your choice:" << endl;
		cout << "1. Sign In\n";
		cout << "2. New Member\n";
		cout << "3. End\n? ";

		choice = inputAnInteger( 1, 3 );
		cout << endl;

		switch ( choice ) {
			case 1:
				signIn( memberDetails, numMembers, movies, movieNames, numMovies, bookingHistories, numBookings, availableDates, numDates );
				break;

			case 2:
				newMember( memberDetails, numMembers );
				break;

			case 3:
				saveMemberInfo( memberDetails, numMembers );
				saveMovies( movies, numMovies );
				saveBookingHistories(  bookingHistories, numBookings );
				cout << "Thank you...\n\n";
				system( "pause" );
				return 0;
			default:
				cout << "Input Error!\n\n";
				break;
		}
	}

	system( "pause" );
}
void loadMemberInfo( MemberRecord memberDetails[], int &numMembers ){
	ifstream inMemberFile;
	inMemberFile.open( "Member Info.dat", ios::in | ios::binary );
	while( inMemberFile && !inMemberFile.eof() ){
		inMemberFile.read( reinterpret_cast< char * >( &memberDetails[numMembers] ), sizeof(MemberRecord) );
		numMembers++;		
	}
	inMemberFile.close();
}
int inputAnInteger( int begin, int end ){
	char input[3];
	cin >> input;
	for(int i = 0; i < 3; i++){
		// make sure the input in range of 0 to 9
		if( ((int)input[i] < 48 || (int)input[i] > 57) && (int)input[i] != 0 ) return -1;
		if( (int)input[i] == 0 ) break;
	}
	if( atoi(input) >= begin && atoi(input) <= end)
		return atoi(input);
	else
		return -1;
}
void signIn( MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][ 60 ], int numMovies, BookingInfo bookingHistories[], int &numBookings, char availableDates[][ 12 ], int numDates ){
	char email[ 40 ];
	char password[ 24 ];
	cout << "Enter email address: ";
	cin >> email;
	cout << "Enter password: ";
	cin >> password;
	int tmp_recordNum = 0;
	if( !illegal(email, password, memberDetails, numMembers, tmp_recordNum) ) {
		int choice;
		cout << endl;
		while( true )
		{
			cout << "Enter your choice:" << endl;
			cout << "1. Account Information\n";
			cout << "2. Buy Tickets\n";
			cout << "3. My Bookings\n";
			cout << "4. Sign Out\n? ";

			choice = inputAnInteger( 1, 4 );
			cout << endl;

			switch ( choice )
			{
				case 1:
					accountInfor( memberDetails, numMembers, tmp_recordNum);
					break;
				case 2:
					buyTickets( bookingHistories, numBookings, movies, movieNames, numMovies, availableDates, numDates, email );
					break;
				case 3:
					displayBookingHistory( bookingHistories, numBookings, movies, movieNames, availableDates, email );
					break;
				case 4:
					return;
				default:
					cout << "Input Error!\n\n";
					break;
			}
		}
	}
	else{
		cout << "\nSorry, unrecognized email or password.\n" << endl;
		return;
	}
}
bool illegal( char email[], char password[], MemberRecord memberDetails[], int numMembers, int &recordNumber ){
	// if email and password are match, return false. 'cause not illegal is legal
	for(int i = 0; i < numMembers; i++){
		if( strcmp(email, memberDetails[i].email) == 0 && strcmp(password, memberDetails[i].password) == 0 ){
			recordNumber = i;
			return false;
		}
	}
	return true;
}
void accountInfor( MemberRecord memberDetails[], int numMembers, int recordNumber ){
	// you can fix your user information here.
	cout << "1. Name: "          << memberDetails[recordNumber].name << endl;
	cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
	cout << "3. Phone Number: "  << memberDetails[recordNumber].phone << endl;
	cout << "4. ID Number: "     << memberDetails[recordNumber].IDNumber << endl;
	cout << "5. Password: "      << memberDetails[recordNumber].password << endl;
	cout << "\nWhich one do you want to modify (0 – not modify)? ";
	int choice;
	while( true )
	{
		choice = inputAnInteger( 0, 5 );
		cout << endl;

		switch ( choice )
		{
			case 1:
				cout << "Enter correct data: ";
				cin >> memberDetails[recordNumber].name;
				cout << "Successful!\n\n";
				return;
			case 2:
				char tmp_email[40];
				cout << "Enter correct data: ";
				cin >> tmp_email;
				while(existingEmail(tmp_email, memberDetails, numMembers)){
					cout << "This email is existing. Please input another one: ";
					cin >> tmp_email;
				}
				memcpy(memberDetails[ recordNumber ].email, tmp_email, sizeof(tmp_email));
				cout << "Successful!\n\n";
				return;
			case 3:
				cout << "Enter correct data: ";
				cin >> memberDetails[recordNumber].phone;
				cout << "Successful!\n\n";
				return;
			case 4:
				char tmp_ID[12];
				cout << "Enter correct data: ";
				cin >> tmp_ID;
				while(existingID(tmp_ID, memberDetails, numMembers)){
					cout << "This ID is existing. Please input another one: ";
					cin >> tmp_ID;
				}
				memcpy(memberDetails[ recordNumber ].IDNumber, tmp_ID, sizeof(tmp_ID));
				cout << "Successful!\n\n";
				return;
			case 5:
				cout << "Enter correct data: ";
				cin >> memberDetails[recordNumber].password;
				cout << "Successful!\n\n";
				return;
			case 0:
				return;
			default:
				cout << "Input Error! Please try again: ";
				break;
		}
	}
}
void newMember( MemberRecord memberDetails[], int &numMembers ){
	// create new member, and numMembers have to be added in this function!!!!!!!!!
	cout << "Enter your ID number: ";
	cin >> memberDetails[ numMembers ].IDNumber;
	while(existingID(memberDetails[ numMembers ].IDNumber, memberDetails, numMembers)){
		cout << "This ID is existing. Please input another one: ";
		cin >> memberDetails[ numMembers ].IDNumber;
	}
	cout << "Enter your name: ";
	cin >> memberDetails[ numMembers ].name;
	cout << "Enter an email address: ";
	cin >> memberDetails[ numMembers ].email;
	while(existingEmail(memberDetails[ numMembers ].email, memberDetails, numMembers)){
		cout << "This email is existing. Please input another one: ";
		cin >> memberDetails[ numMembers ].email;
	}
	cout << "Enter a password: ";
	cin >> memberDetails[ numMembers ].password;
	cout << "Enter your phone number: ";
	cin >> memberDetails[ numMembers ].phone;
	cout << "\nSuccessful!\n" << endl;
	numMembers++;
}
bool existingID( char newIDNumber[], MemberRecord memberDetails[], int &numMembers ){
	for(int i = 0; i < numMembers; i++){
		if( strcmp(memberDetails[i].IDNumber, newIDNumber) == 0 )
			return true;
	}
	return false;
}
bool existingEmail( char newEmail[], MemberRecord memberDetails[], int &numMembers ){
	for(int i = 0; i < numMembers; i++){
		if( strcmp(memberDetails[i].email, newEmail) == 0 )
			return true;
	}
	return false;
}
void loadBookingHistories( BookingInfo bookingHistories[], int &numBookings ){
	ifstream file;
	file.open( "Booking Histories.dat", ios::in | ios::binary );
	while( file && !file.eof() ){
		file.read( reinterpret_cast< char * >( &bookingHistories[numBookings] ), sizeof(BookingInfo) );
		numBookings++;
	}
	numBookings--; // using while loop will get a empty item in the end, so need to fix it.
	file.close();
}
void loadAvailableDates( char availableDates[][ 12 ], int &numDates ){
	ifstream file;
	file.open( "Available Dates.txt", ios::in );
	while( !file.eof() ){
		file.getline(availableDates[numDates], 12);
		numDates++;
	}
	numDates--; // using while loop will get a empty item in the end, so need to fix it.
	file.close();
}
void loadMovies( Movie movies[], int &numMovies ){
	ifstream file;
	file.open( "Movies.dat", ios::in | ios::binary );
	while( file && !file.eof() ){
		file.read( reinterpret_cast< char * >( &movies[numMovies] ), sizeof(Movie) );
		numMovies++;		
	}
	numMovies--; // using while loop will get a empty item in the end, so need to fix it.
	file.close();
}
void loadMovieNames( char movieNames[][ 60 ], int numMovies ){
	ifstream file;
	file.open( "Movie Names.txt", ios::in );
	for(int i = 0; i < numMovies; i++)
		file.getline(movieNames[i], 60);
	file.close();
}
void buyTickets( BookingInfo bookingHistories[], int &numBookings, Movie movies[], char movieNames[][ 60 ], int numMovies, char availableDates[][ 12 ], int numDates, char email[] ){
	//bookingHistories[numBookings].email = email;
	memcpy(bookingHistories[numBookings].email, email, 40);
	displaySessionTimes( movies, movieNames, numMovies, availableDates, numDates );
	cout << "\n" << endl;
	while( true )
	{
		printf("Enter movie code (0 - %d): ", numMovies-1);
		bookingHistories[numBookings].movieCode = inputAnInteger( 0, numMovies-1 );
		if( bookingHistories[numBookings].movieCode >= 0 && bookingHistories[numBookings].movieCode <= numMovies-1 )
			break;
	}
	cout << endl;
	while( true )
	{
		printf("Enter date code (0 - %d): ", numDates-1);
		bookingHistories[numBookings].dateCode = inputAnInteger( 0, numDates-1 );
		if( movies[ bookingHistories[numBookings].movieCode ].dates[ bookingHistories[numBookings].dateCode ] ) 
			break;
	}
	cout << endl;
	while( true )
	{
		printf("Enter session time code (0 - %d): ", 16);
		bookingHistories[numBookings].sessionTimeCode = inputAnInteger( 0, 16 );
		if( movies[ bookingHistories[numBookings].movieCode ].sessionTimes[ bookingHistories[numBookings].sessionTimeCode ] )
			break;
	}


	printf("\nMovie: %s\nDate: %s\nShow Time: %s\n\nPrice: Adult-270, Concession-270, Disability-160, Elderly-160\n\n", movieNames[bookingHistories[numBookings].movieCode], availableDates[bookingHistories[numBookings].dateCode], hours[bookingHistories[numBookings].sessionTimeCode]);

	while((bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1] + bookingHistories[numBookings].numTickets[2] + bookingHistories[numBookings].numTickets[3]) <= 0){
		//bookingHistories[numBookings].numTickets[4] = {0,0,0,0};
		//cout << endl;
		while( true )
		{
			printf("Enter the number of adult tickets (0 - 6): ");
			bookingHistories[numBookings].numTickets[0] = inputAnInteger( 0, 6 );
			if( bookingHistories[numBookings].numTickets[0] >= 0 && bookingHistories[numBookings].numTickets[0] <= 6 )
				break;			
		}
		while( true )
		{
			printf("Enter the number of concession tickets (0 - 6): ");
			bookingHistories[numBookings].numTickets[1] = inputAnInteger( 0, 6 );
			if( bookingHistories[numBookings].numTickets[1] >= 0 && bookingHistories[numBookings].numTickets[1] <= 6 )
				break;			
		}
		while( true )
		{
			printf("Enter the number of disability tickets (0 - 6): ");
			bookingHistories[numBookings].numTickets[2] = inputAnInteger( 0, 6 );
			if( bookingHistories[numBookings].numTickets[2] >= 0 && bookingHistories[numBookings].numTickets[2] <= 6 )
				break;			
		}
		while( true )
		{
			printf("Enter the number of elderly tickets (0 - 6): ");
			bookingHistories[numBookings].numTickets[3] = inputAnInteger( 0, 6 );
			if( bookingHistories[numBookings].numTickets[3] >= 0 && bookingHistories[numBookings].numTickets[3] <= 6 )
				break;			
		}
	}

	display( movies, bookingHistories[numBookings] );

	selectSeats(bookingHistories, numBookings, movies);
	numBookings++;   // Because selectSeats have no pass by reference so need to add 1 at here

	//displayBookingHistory(bookingHistories, numBookings, movies, movieNames, availableDates, email);
}
void selectSeats( BookingInfo bookingHistories[], int numBookings, Movie movies[] ){
	int movie = bookingHistories[numBookings].movieCode;
	int date = bookingHistories[numBookings].dateCode;
	int sessionTime = bookingHistories[numBookings].sessionTimeCode;
	int sum = bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1] + bookingHistories[numBookings].numTickets[2] + bookingHistories[numBookings].numTickets[3];
	//bool (*seats)[8][12] = &movies[movie].occupiedSeats[date][sessionTime];
	cout << "\n  A B C D E F G H I J K L" << endl;
	for(int i = 0; i < 8; i++){
		cout << i ;
		for(int j = 0; j < 12; j++)
			(movies[movie].occupiedSeats[date][sessionTime][i][j]) ? cout << " 1" : cout << " 0" ;		
		cout << endl;
	}

	cout << "Select " << sum << " seats (e.g. 0A):\n";
	int i = 0;
	while(sum-i){
		cout << "? ";
		char tmp_x, tmp_y;
		cin >> tmp_x >> tmp_y;
		//cin.get(tmp_x);
		//cin.get(tmp_y);
		int x, y;
		x = tmp_x - '0';
		y = tmp_y - 'A';
		//cin >> x >> y;
		if( x < 0 || x > 7 || y < 0 || y > 11 ){
			cout << "\nInput error" << endl;
			continue;
		}
		if(movies[movie].occupiedSeats[date][sessionTime][x][y]){
			cout << "\nThis seat bas been occupied. Please select another seat." << endl;
			continue;
		}
		movies[movie].occupiedSeats[date][sessionTime][x][y] = true;
		bookingHistories[numBookings].seletedSeats[i][0] = tmp_x;
		bookingHistories[numBookings].seletedSeats[i][1] = tmp_y;
		bookingHistories[numBookings].seletedSeats[i][2] = '\0';
		i++;
	}

	cout << "\nSuccessful\n" << endl;
}
void display( Movie movies[], BookingInfo bookingHistory ){
	cout << endl;
	cout << setw(27) << right << "No. of Tickets" << setw(10) << right << "Price" << setw(10) << right << "Subtotal" << endl;
	if(bookingHistory.numTickets[0] > 0)
		cout << setw(17) << left << "Adult" << setw(10) << right << bookingHistory.numTickets[0] << setw(10) << right << "270" << setw(10) << right << bookingHistory.numTickets[0]*270 << endl;
	if(bookingHistory.numTickets[1] > 0)
		cout << setw(17) << left << "Concession" << setw(10) << right << bookingHistory.numTickets[1] << setw(10) << right << "270" << setw(10) << right << bookingHistory.numTickets[1]*270 << endl;
	if(bookingHistory.numTickets[2] > 0)
		cout << setw(17) << left << "Disability" << setw(10) << right << bookingHistory.numTickets[2] << setw(10) << right << "160" << setw(10) << right << bookingHistory.numTickets[2]*160 << endl;
	if(bookingHistory.numTickets[3] > 0)
		cout << setw(17) << left << "Elderly" << setw(10) << right << bookingHistory.numTickets[3] << setw(10) << right << "160" << setw(10) << right << bookingHistory.numTickets[3]*160 << endl;
	cout << "\nTotal Amount For Tickets: " << (bookingHistory.numTickets[0]*270+bookingHistory.numTickets[1]*270+bookingHistory.numTickets[2]*160+bookingHistory.numTickets[3]*160) << endl;
}
void displaySessionTimes( Movie movies[], char movieNames[][ 60 ], int numMovies, char availableDates[][ 12 ], int numDates ){
	for(int i = 0; i < numMovies; i++){
		cout << "\n" << i << ". Movie: " << movieNames[i] << "\n    Date:";

		for(int j = 0; j < numDates; j++)
			if(movies[i].dates[j]) printf("  %d. %s,", j, availableDates[j]);

		printf("\n    Session Time:");

		for(int j = 0; j < 17; j++)
			if(movies[i].sessionTimes[j]) printf("  %d. %s,", j, hours[j]);
	}
}
void displayBookingHistory( BookingInfo bookingHistories[], int numBookings, Movie movies[],
							char movieNames[][ 60 ], char availableDates[][ 12 ], char email[] ){
	bool isHaveBookings = false;
	for(int i = 0; i < numBookings; i++){
		if( strcmp( bookingHistories[i].email, email ) == 0 ){
			isHaveBookings = true;
			break;
		}
	}
	if(!isHaveBookings){
		cout << "\nNo Bookings!\n" << endl;
		return;
	}

	cout << "\nBooking History\n" << endl;
	for(int i = 0; i < numBookings; i++){
		if(strcmp( bookingHistories[i].email, email ) == 0){
			cout << "Movie: " << movieNames[ bookingHistories[i].movieCode ] << endl;
			cout << "Date: " << availableDates[ bookingHistories[i].dateCode ] << endl;
			cout << "Show Time: " << hours[ bookingHistories[i].sessionTimeCode ]  << endl;
			cout << "Seats:";
			int sum = bookingHistories[i].numTickets[0] + bookingHistories[i].numTickets[1] + bookingHistories[i].numTickets[2] + bookingHistories[i].numTickets[3];
			for(int j = 0; j < sum; j++)
				cout << " " << bookingHistories[i].seletedSeats[j];
			cout << endl;
			display(movies, bookingHistories[i]);
			cout << "\n----------------------------------------------\n" << endl;
		}
	}
}
void saveMemberInfo( MemberRecord memberDetails[], int numMembers ){
	ofstream file;
	file.open("Member Info.dat", ios::out | ios::binary);
	for (int i = 0; i < numMembers; i++)
		file.write(reinterpret_cast< const char * >( &memberDetails[i] ), sizeof( MemberRecord ) );
	file.close();
}
void saveMovies( Movie movies[], int numMovies ){
	ofstream file;
	file.open("Movies.dat", ios::out | ios::binary);
	for (int i = 0; i < numMovies; i++)
		file.write(reinterpret_cast< const char * >( &movies[i] ), sizeof( Movie ) );
	file.close();
}
void saveBookingHistories( BookingInfo bookingHistories[], int numBookings ){
	ofstream file;
	file.open("Booking Histories.dat", ios::out | ios::binary);
	for (int i = 0; i < numBookings; i++)
		file.write(reinterpret_cast< const char * >( &bookingHistories[i] ), sizeof( BookingInfo ) );
	file.close();	
}