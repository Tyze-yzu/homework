#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include "String.h" // string class definition

string::string()
{
	bx.buf[ 0 ] = '\0';
}

string::string( const string &str )
{
	mySize = str.mySize;
	myRes = str.myRes;

	if( myRes == 15 )
		for( unsigned int i = 0; i <= mySize; i++ )
			bx.buf[ i ] = str.bx.buf[ i ];
	else
	{
		bx.ptr = new char[ myRes + 1 ];
		for( unsigned int i = 0; i <= mySize; i++ )
			bx.ptr[ i ] = str.bx.ptr[ i ];
	}
}

string::string( const char *s, unsigned int n )
{
	resize(n);
	for(unsigned int i = 0; i < n; i++)
		if( myRes == 15)
			bx.buf[i] = s[i];
		else
			bx.ptr[i] = s[i];
}

string::~string()
{
	if( myRes > 15 )
		delete[] bx.ptr;
}

unsigned int string::size() const
{
	return mySize;
}

unsigned int string::capacity() const
{
	return myRes;
}

void string::resize( unsigned int n )
{
	unsigned int newRes1 = myRes + myRes/2;
	unsigned int newRes2 = (n/16+1)*16 - 1;
	unsigned int newRes = (n<=15) ? 15 : (newRes1 > newRes2) ? newRes1 : newRes2;

	char* origin_ptr = (myRes==15) ? bx.buf : bx.ptr;
	char* newArray = new char[newRes+1]();

	if(n > myRes){
		for(unsigned int i = 0; i < mySize; i++)
			newArray[i] = origin_ptr[i];
		if(myRes!=15)
			delete[] origin_ptr;
		bx.ptr = newArray;
		myRes = newRes;
	}
	else{
		if( n >= mySize )
			for(unsigned int i = mySize; i < n; i++)
				origin_ptr[i] = '\0';
	}
	mySize = n;
}

void string::clear()
{
	mySize = 0;
	if( myRes == 15 )
		bx.buf[ 0 ] = '\0';
	else
		bx.ptr[ 0 ] = '\0';
}

void string::push_back( char c )
{
	resize(mySize+1);
	if(myRes == 15)
		bx.buf[ mySize - 1 ] = c;
	else
		bx.ptr[ mySize - 1 ] = c;
}

void string::pop_back()
{
	if( mySize > 0 )
		--mySize;
}

string& string::assign( const char *s, unsigned int n )
{
	if(n > myRes)
		resize(n);
	char* myArray = (myRes == 15) ? bx.buf : bx.ptr;
	for(unsigned int i = 0; i < n; i++)
		myArray[i] = s[i];
	mySize = n;
	return *this;
}

string& string::erase( unsigned int pos, unsigned int len )
{
	char* arr = (myRes == 15) ? bx.buf : bx.ptr;
	unsigned int amount = (mySize-pos > len) ? len : mySize-pos; // caculate how many words need to be deleted
	for (unsigned int i = pos; (i < mySize) && (i+len <= myRes); i++) 
		arr[i] = arr[i + len];
	resize(mySize - amount);
	return *this;
}

unsigned int string::find( char c, unsigned int pos ) const
{
	if( pos < mySize )
		if( myRes == 15 )
		{
			for( unsigned int i = pos; i < mySize; i++ )
				if( c == bx.buf[ i ] )
					return i;
		}
		else
		{
			for( unsigned int i = pos; i < mySize; i++ )
				if( c == bx.ptr[ i ] )
					return i;
		}

	return npos;
}

string string::substr( unsigned int pos, unsigned int len ) const
{
	string subString;
	// homework
	unsigned int newSize = (mySize-pos > len) ? len : mySize-pos;	
	for (unsigned int i = 0; i < newSize; i++) {
		subString.resize(newSize);
		if (newSize <= 15) {
			if (myRes == 15)
				subString.bx.buf[i] = bx.buf[pos + i];
			else
				subString.bx.buf[i] = bx.ptr[pos + i];
		}
		else {
			if (myRes == 15)
				subString.bx.ptr[i] = bx.buf[pos + i];
			else
				subString.bx.ptr[i] = bx.ptr[pos + i];
		}
	}
	// homework end
	return subString;
}

bool string::equal( std::string &str )
{
	if( myRes != str.capacity() )
		return false;

	if( mySize != str.size() )
		return false;

	if( myRes == 15 )
	{
		for( unsigned int i = 0; i < mySize; i++ )
			if( bx.buf[ i ] != str[ i ] )
				return false;
	}
	else
	{
		for( unsigned int i = 0; i < mySize; i++ )
			if( bx.ptr[ i ] != str[ i ] )
				return false;
	}

	return true;
}