// MovieDatabase.cpp
// Member-function definitions for class MovieDatabase
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace::std;
#include "MovieDatabase.h" // MovieDatabase class definition

extern char hours[ 17 ][ 8 ];

// MovieDatabase default constructor loads movies from the file Movies.dat
MovieDatabase::MovieDatabase()
{
   loadMovies();
}

// MovieDatabase destructor saves movies into the file Movies.dat
MovieDatabase::~MovieDatabase()
{
   saveMovies();
}

int MovieDatabase::getNumMovies()
{
   return movies.size();
}

Movie& MovieDatabase::getMovie( int movieCode )
{
   return movies[ movieCode ];
}

void MovieDatabase::setMovieSeat( int movieCode, int dateCode, int sessionTimeCode, int row, int col )
{
   movies[ movieCode ].setOccupiedSeat( dateCode, sessionTimeCode, row, col );
}

void MovieDatabase::displaySessionTimes( char movieNames[][ 60 ], char availableDates[][ 12 ] )
{
	for (int i = 0; i < movies.size(); i++) {
		cout << "\n" << i << ". Movie: " << movieNames[i] << "\n    Date:";

		for (int j = 0; j < 4; j++)
			if (movies[i].getDate(j)) printf("  %d. %s,", j, availableDates[j]);

		printf("\n    Session Time:");

		for (int j = 0; j < 17; j++)
			if (movies[i].getSessionTime(j)) printf("  %d. %s,", j, hours[j]);
	}
}

void MovieDatabase::loadMovies()
{
	ifstream file;
	file.open("Movies.dat", ios::in | ios::binary);
	Movie tmp;
	while (file && !file.eof()) {
		file.read(reinterpret_cast< char * >(&tmp), sizeof(Movie));
		movies.push_back(tmp);
	}
	movies.pop_back();
	file.close();
}

void MovieDatabase::saveMovies()
{
	ofstream file;
	file.open("Movies.dat", ios::out | ios::binary);
	for (int i = 0; i < movies.size(); i++)
		file.write(reinterpret_cast< const char * >(&movies[i]), sizeof(Movie));
	file.close();
}