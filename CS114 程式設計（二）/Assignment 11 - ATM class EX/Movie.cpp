// Movie.cpp
// Member-function definitions for class Movie
#include "Movie.h" // Movie class definition

Movie::Movie()
{
}

void Movie::setMovieCode( int theMovieCode )
{
   movieCode = ( theMovieCode > 0 ? theMovieCode : 0 );
}

int Movie::getMovieCode()
{
   return movieCode;
}

void Movie::setPrices( int thePrices[] )
{
   for( int i = 0; i < 4; i++ )
      prices[ i ] = ( thePrices[ i ] > 0 ? thePrices[ i ] : 0 );
}

int Movie::getPrice( int ticketType )
{
   return prices[ ticketType ];
}

void Movie::setDates( bool theDates[] )
{
   for( int i = 0; i < 4; i++ )
      dates[ i ] = theDates[ i ];
}

bool Movie::getDate( int dateCode )
{
   return dates[ dateCode ];
}

void Movie::setSessionTimes( bool theSessionTimes[] )
{
   for( int i = 0; i < 17; i++ )
      sessionTimes[ i ] = theSessionTimes[ i ];
}

bool Movie::getSessionTime( int sessionTimeCode )
{
   return sessionTimes[ sessionTimeCode ];
}

void Movie::setOccupiedSeat( int dateCode, int sessionTimeCode, int row, int col )
{
   occupiedSeats[ dateCode ][ sessionTimeCode ][ row ][ col ] = true;
}

bool Movie::getOccupiedSeat( int dateCode, int sessionTimeCode, int row, int col )
{
   return occupiedSeats[ dateCode ][ sessionTimeCode ][ row ][ col ];
}