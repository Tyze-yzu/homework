// string class member-function definitions.

#include <iostream>
using std::cerr;

#include "String.h" // string class definition

string::string()
{
   bx.buf[ 0 ] = '\0';
}

string::string( const string &str )
   : mySize( str.mySize ),
     myRes( str.myRes )
{
   if( myRes == 15 )
      for( size_t i = 0; i <= mySize; i++ )
         bx.buf[ i ] = str.bx.buf[ i ];
   else
   {
      bx.ptr = new char[ myRes + 1 ];
      for( size_t i = 0; i <= mySize; i++ )
         bx.ptr[ i ] = str.bx.ptr[ i ];
   }
}

// destructor
string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
} // end destructor

char* string::begin()
{
   if( myRes == 15 )
      return bx.buf;
   else
      return bx.ptr;
}

char* string::end()
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

std::ostream &operator<<( std::ostream &output, string &str )
{
   if( str.myRes == 15 )
      for( size_t i = 0; i < str.mySize; i++ )
         output << str.bx.buf[ i ];
   else
      for( size_t i = 0; i < str.mySize; i++ )
         output << str.bx.ptr[ i ];

   return output; // enables cout << x << y;
}

bool operator==( const string &lhs, const string &rhs )
{
   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=(const string &lhs, const string &rhs)
{
	return (lhs.compare(rhs) != 0);
}


string::string(const char *s, size_t n)
{
	resize(n);
	for (size_t i = 0; i < n; i++)
		if (myRes == 15)
			bx.buf[i] = s[i];
		else
			bx.ptr[i] = s[i];
}

string& string::operator=(const string &str)
{
	//if (str.myRes == 15)
		assign( (str.myRes == 15) ? str.bx.buf : str.bx.ptr , str.mySize);
	//else
	//	assign(str.bx.ptr, str.mySize);
	return *this;
}


void string::resize(size_t n)
{
	size_t newRes1 = myRes + myRes / 2;
	size_t newRes2 = (n / 16 + 1) * 16 - 1;
	size_t newRes = (n <= 15) ? 15 : (newRes1 > newRes2) ? newRes1 : newRes2;

	char* origin_ptr = (myRes == 15) ? bx.buf : bx.ptr;

	if (n > myRes) { // when (n > myRes)  means bx.ptr needs to be expand
		char* newArray = new char[newRes + 1]();
		for (size_t i = 0; i < mySize; i++)
			newArray[i] = origin_ptr[i];
		if (myRes != 15)
			delete[] origin_ptr; // beacause bx.buf can't be deleted
		bx.ptr = newArray;
		myRes = newRes;
	}
	// clear the elements which are not in range of size
	for (size_t i = mySize; i < myRes; i++)
		((myRes == 15) ? bx.buf : bx.ptr)[i] = '\0';

	mySize = n;
}

// Returns a reference to the character at position pos in the string.
char& string::operator[](size_t pos)
{
	return (myRes == 15) ? bx.buf[pos] : bx.ptr[pos];
	/*
	if (myRes == 15)
		return bx.buf[pos];
	else
		return bx.ptr[pos];*/
}

// Returns a reference to the character at position pos in the string.
const char& string::operator[](size_t pos) const
{
	return (myRes == 15) ? bx.buf[pos] : bx.ptr[pos];
}

string& string::assign(const char *s, size_t n)
{
	if (n > myRes)
		resize(n);
	for (size_t i = 0; i < n; i++)
		((myRes == 15) ? bx.buf : bx.ptr)[i] = s[i];
	mySize = n;
	return *this;
}

// Erases the portion of the string value that
// begins at the character position pos and spans len characters
// (or until the end of the string, if either the content is too short or if len is string::npos).
// Returns *this
string& string::erase(size_t pos, size_t len)
{
	char* arr = (myRes == 15) ? bx.buf : bx.ptr;
	unsigned int amount = (mySize - pos > len) ? len : mySize - pos; // caculate how many words need to be deleted
	for (unsigned int i = pos; (i < mySize) && (i + len <= myRes); i++)
		arr[i] = arr[i + len];
	resize(mySize - amount);
	return *this;
}

// Searches the string for the first occurrence of the character specified by its arguments.
// When pos is specified, the search only includes characters at or after position pos.
// Returns the position of the first match. If no matches were found, the function returns string::npos.
size_t string::find(char c, size_t pos) const
{
	if (pos < mySize)
		if (myRes == 15)
		{
			for (unsigned int i = pos; i < mySize; i++)
				if (c == bx.buf[i])
					return i;
		}
		else
		{
			for (unsigned int i = pos; i < mySize; i++)
				if (c == bx.ptr[i])
					return i;
		}

	return npos;
}

// Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
// The substring is the portion of the object that starts at character position pos and spans len characters
// (or until the end of the string, whichever comes first).
string string::substr(size_t pos, size_t len) const
{
	string subString;
	// homework
	unsigned int newSize = (mySize - pos > len) ? len : mySize - pos;
	subString.resize(newSize);
	for (unsigned int i = 0; i < newSize; i++)
		if (newSize <= 15)
			subString.bx.buf[i] = (myRes == 15) ? bx.buf[pos + i] : bx.ptr[pos + i];
		else
			subString.bx.ptr[i] = (myRes == 15) ? bx.buf[pos + i] : bx.ptr[pos + i];
	// homework end
	return subString;
}

int string::compare(const string& str) const
{
	// return 0 if these two string are the same
	if (mySize != str.mySize)
		return -1;

	for (size_t i = 0; i < mySize; i++) {
		if (myRes == 15) {
			if (bx.buf[i] != str.bx.buf[i])
				return -1;
		}
		else {
			if (bx.ptr[i] != str.bx.ptr[i])
				return -1;
		}
	}
	return 0;
}
