// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector - Student ID - hw7.h" // include definition of class template vector
#include "List - Student ID - hw7.h" // include definition of class template list

/*
#include <vector> // include definition of class template vector
#include <list> // include definition of class template list
using std::vector;
using std::list;
*/

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > const &hugeInteger );
public:
   // constructor; construct a zero HugeInteger with mySize n
   HugeInteger( unsigned int n = 0 );

   // copy constructor; constructs a HugeInteger with a copy
   // of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator

   bool operator==( HugeInteger &right ); // less than or equal to
   bool operator<( HugeInteger &right );  // less than
   bool operator<=( HugeInteger &right ); // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( HugeInteger &op2 );

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( HugeInteger &op2 );

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%(HugeInteger &op2);

   HugeInteger &operator++();     // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger &operator--();     // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   // convert a vector of decimal digits into a HugeInteger
   void convert( T &buffer );
   bool isZero(); // return true if and only if all digits are zero

private:
   T integer;

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy
// of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger< T > &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger< T > &right )
{
   if (integer.size() != right.integer.size())
      return integer.size() < right.integer.size();
   for (T::reverse_iterator it1 = integer.rbegin(), it2 = right.integer.rbegin(); it1 != integer.rend(); ++it1, ++it2)
      if (*it1 != *it2)
         return *it1 < *it2;
   return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger< T > &right )
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );
   T::iterator it1 = integer.begin();
   T::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   T::iterator it2 = op2.integer.begin();
   it3 = sum.integer.begin();
   for( ; it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.integer.begin();
   T::iterator it4 = it3;
   for( ++it4; it4 != sum.integer.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 ) 
{
   HugeInteger< T > difference(*this);
   for (T::reverse_iterator tmp = difference.integer.rbegin(), tmp2 = (++difference.integer.rbegin()); tmp2 != difference.integer.rend(); ++tmp, ++tmp2) {
	   (*tmp)--;
	   (*tmp2) += 10;
   }
   // 這借位有問題 有緣再找bug
   
   // for (T::reverse_iterator tmp = difference.integer.rbegin(); tmp != (++difference.integer.rend()); ++tmp) {
   //    (*tmp)--;
   //    (*(--tmp)) += 10;
   //    ++tmp;
   // }

   for (T::iterator it1 = difference.integer.begin(), it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it1, ++it2){
      *it1 -= *it2;
   }

   for (T::iterator it = difference.integer.begin(), it1 = (++difference.integer.begin()); it1 != difference.integer.end(); ++it, ++it1){
      if (*it >= 10){
         *it -= 10;
         *(it1) += 1;
      }
   }

   while (*difference.integer.rbegin() == 0 && difference.integer.size() > 1)
      difference.integer.pop_back();

   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > &op2 )
{
	if (isZero() || op2.isZero())
		return HugeInteger< T >(0);

   unsigned int size = (integer.size() + op2.integer.size());
   HugeInteger product(size);

   unsigned int count = 0;
   for (T::iterator it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it2, count++) {
	   // 算 product 要從哪裡開始寫
	   T::iterator it = product.integer.begin();
	   for (unsigned int i = 0; i < count; i++)
		   ++it;
	
	   // 去乘 *it1
	   for (T::iterator it1 = integer.begin(); it1 != integer.end(); ++it1, ++it)
		   *it += (*it1 * *it2);
   }

   for( T::iterator it1 = product.integer.begin(), it2 = (++product.integer.begin()); it2 != product.integer.end(); ++it1, ++it2 ){
      if( *it1 >= 10) {
         *it2 += (*it1) / 10;
         *it1 %= 10;
      }
   }

   while (*product.integer.rbegin() == 0 && product.integer.size() > 1)
      product.integer.pop_back();
   return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that
// the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > &op2 )
{
   unsigned int n = integer.size() - op2.integer.size() + 1;

   if (*this < op2) {
      HugeInteger< T > quotient(1);
      *quotient.integer.begin() = 0;
      return quotient;
	  
   }

   HugeInteger< T > quotient(n);
   HugeInteger< T > buffer(*this);
   HugeInteger< T > remainder(*this);

   unsigned int val = buffer.integer.size() - op2.integer.size();
   unsigned int i = 0;
   for (typename T::iterator it = buffer.integer.begin(), it2 = op2.integer.begin(); it != buffer.integer.end(); ++it, i++) {
      if (i < val)
         *it = 0;
      else {
         *it = *it2;
         ++it2;
      }
   }

   for (T::reverse_iterator it = quotient.integer.rbegin(); it != quotient.integer.rend(); ++it) {
      while (buffer <= remainder) {
         remainder = remainder - buffer;
         (*it)++;
      }
      buffer.divideByTen();
   }

   while (*quotient.integer.rbegin() == 0 && quotient.integer.size() > 1)
      quotient.integer.pop_back();

   return quotient;
} // end function operator/

  // modulus operator; HugeInteger % HugeInteger
  // provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger &op2)
{
	HugeInteger quotient = (*this) / op2;
	HugeInteger tmp = quotient * op2;       // fixed
	HugeInteger remainder = (*this) - tmp;  // fixed
	return remainder;
};
// overloaded prefix increment operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
   helpIncrement();
   return *this;
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger A(*this);
   helpIncrement();
   return A;
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator--()
{
   helpDecrement();
   return *this;
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger A(*this);
   helpDecrement();
   return A;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( T &buffer )
{
   integer.resize( buffer.size() );
   T::reverse_iterator it1 = integer.rbegin();
   T::iterator it2 = buffer.begin();
   for( ; it2 != buffer.end(); ++it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   for( T::iterator it = integer.begin(); it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10;
// shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   T::iterator it1 = integer.begin();
   T::iterator it2 = it1;
   for( ++it2; it2 != integer.end(); ++it1, ++it2 )
      *it1 = *it2;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   T::iterator it = integer.begin();
   ( *it )++;
   T::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *it = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	for (T::reverse_iterator tmp = integer.rbegin(), tmp2 = (++integer.rbegin()); tmp2 != integer.rend(); ++tmp, ++tmp2) {
		(*tmp)--;
		(*tmp2) += 10;
	}

	(*integer.begin())--;

	for (T::iterator it = integer.begin(), it1 = (++integer.begin()); it1 != integer.end(); ++it, ++it1) {
		if (*it >= 10) {
			*it -= 10;
			*(it1) += 1;
		}
	}

	while (*integer.rbegin() == 0 && integer.size() > 1)
		integer.pop_back();
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > const &hugeInteger )
{
   typename T::reverse_iterator it = hugeInteger.integer.rbegin();
   for( ; it != hugeInteger.integer.rend(); ++it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}