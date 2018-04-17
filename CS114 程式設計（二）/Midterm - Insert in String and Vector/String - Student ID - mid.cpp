// string class member-function definitions.

#include "String.h" // string class definition

string::string()
{
   bx.buf[ 0 ] = '\0';
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::iterator string::begin()
{
   if( myRes == 15 )
      return bx.buf;
   else
      return bx.ptr;
}

string::iterator string::end()
{
   if( myRes == 15 )
      return bx.buf + mySize;
   else
      return bx.ptr + mySize;
}

size_t string::size() const
{
   return mySize;
}

unsigned int string::capacity() const
{
   return myRes;
}

void string::insert( iterator p, char c )
{
	// resize
	iterator tmpptr = (myRes == 15) ? bx.buf : bx.ptr;
	size_t cc = capacity();
	size_t s = size();
	size_t n = s + 1;
	size_t new1 = (unsigned int)cc*1.5;
	size_t new2 = (n / 16 + 1) * 16 - 1;
	if(n > cc)
		cc = (n <= 15) ? 15 : (new1 > new2) ? new1 : new2;

	iterator it1 = (cc == 15) ? bx.buf : new char[cc + 1]();
	iterator it2 = tmpptr;
	iterator it3 = begin() - 1;

	it1 += s;
	it2 += (s - 1);

	for (; it2 != p - 1; it1--, it2--)
		*it1 = *it2;

	*(it1--) = c;

	for (; it2 != it3; it1--, it2--)
		*it1 = *it2;

	if (myRes != 15)
		delete[] tmpptr;

	if (cc != 15)
		bx.ptr = it1 + 1;

	myRes = cc;
	mySize = n;
}

void string::erase( iterator p )
{
   iterator start = ( myRes == 15 ? bx.buf : bx.ptr );
   for( iterator it = p + 1; it != start + mySize; it++ )
      *( it - 1 ) = *it;

   mySize--;
}

bool operator==( string &lhs, std::string &rhs )
{
   if( lhs.myRes != rhs.capacity() )
      return false;

   if( lhs.mySize != rhs.size() )
      return false;

   string::iterator tempPtr = ( lhs.myRes == 15 ? lhs.bx.buf : lhs.bx.ptr );
   for( unsigned int i = 0; i < lhs.mySize; i++ )
      if( tempPtr[ i ] != rhs[ i ] )
         return false;

   return true;
}