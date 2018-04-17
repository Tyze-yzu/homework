#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

// vector class template definition
template< typename T >
class vector
{
   template< typename T >
   friend bool operator==( vector< T > &lhs, std::vector< T > &rhs );
public:
   using iterator = T*;

   vector();

   ~vector();

   iterator begin();

   iterator end();

   size_t size() const;

   size_t capacity() const;

   // The vector is extended by inserting a new element before the element
   // at the specified position, effectively increasing the container size by one.
   // This causes an automatic reallocation of the allocated storage space
   // if -and only if- the new vector size surpasses the current vector capacity.
   // Relocates all the elements that were after position to their new positions.
   void insert( iterator position, const T val );

   // Removes from the vector a single element.   
   // This effectively reduces the container size by one.   
   // Relocates all the elements after the element erased to their new positions.
   void erase( iterator position );

private:
   T *myFirst = nullptr;
   T *myLast = nullptr;
   T *myEnd = nullptr;
}; // end class template vector


template< typename T >
vector< T >::vector()
{
}

template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

template< typename T >
typename vector< T >::iterator vector< T >::begin()
{
   return myFirst;
}

template< typename T >
typename vector< T >::iterator vector< T >::end()
{
   return myLast;
}

template< typename T >
size_t vector< T >::size() const
{
   return ( myLast - myFirst );
}

template< typename T >
size_t vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

template< typename T >
void vector< T >::insert( iterator position, const T val )
{
	unsigned int s = size();
	unsigned int c = capacity();
	unsigned int n = s + 1;

	if (n > c)
		c = (n > (unsigned int)c*1.5) ? n : (unsigned int)c*1.5;

	iterator tmpptr = myFirst;
	myFirst = new T[c]();
	iterator it3 = myLast;
	myLast = myFirst + n;
	myEnd =  myFirst + c;

	iterator it1 = myFirst;
	iterator it2 = tmpptr;
	for (; it2 != position; it1++, it2++)
		*it1 = *it2;
	*(it1++) = val;
	for(; it2 != it3; it1++, it2++)
		*it1 = *it2;
	delete[] tmpptr;
}

template< typename T >
void vector< T >::erase( iterator position )
{
   for( iterator p = position + 1; p != myLast; p++ )
      *( p - 1 ) = *p;

   myLast--;
}

template< typename T >
bool operator==( vector< T > &lhs, std::vector< T > &rhs )
{
   if( lhs.capacity() != rhs.capacity() )
      return false;

   if( lhs.size() != rhs.size() )
      return false;

   for( unsigned int i = 0; i < lhs.size(); i++ )
      if( lhs.myFirst[ i ] != rhs[ i ] )
         return false;

   return true;
}

#endif