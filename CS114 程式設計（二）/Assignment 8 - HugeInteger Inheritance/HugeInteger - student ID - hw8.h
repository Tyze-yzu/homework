// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "list - student ID - hw8.h" // include definition of class template list

//#include <list> // include definition of class template list
//using std::list;

template< typename T >
class HugeInteger : public list< T >
{
   template< typename T >
   friend ostream &operator<<( ostream &output, HugeInteger< T > &hugeInteger );
public:
   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with mySize n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator
   const HugeInteger &operator=( const list &right ); // assignment operator

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
   HugeInteger operator%( HugeInteger &op2 );

   HugeInteger &operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger &operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   bool isZero(); // return true if and only if all digits are zero

private:
   void divideByTen();   // divides a HugeInteger by 10
   void helpIncrement(); // increments a HugeInteger by 1
   void helpDecrement(); // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif

// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : list( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : list( integerToCopy )
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
      list< T >::operator=( right );

   return *this; // enables x = y = z, for example
} // end function operator=

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const list< T > &right )
{
   if( &right != this ) // avoid self-assignment
      list< T >::operator=( right );

   return *this; // enables x = y = z, for example
} // end function operator=

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger< T > &right )
{
   if (size() != right.size())
      return size() < right.size();
   for (reverse_iterator it1 = rbegin(), it2 = right.rbegin(); it1 != rend(); ++it1, ++it2)
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
   unsigned int op1Size = size();
   unsigned int op2Size = op2.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );
   iterator it1 = begin();
   iterator it3 = sum.begin();
   for( ; it1 != end(); ++it1, ++it3 )
      *it3 = *it1;

   iterator it2 = op2.begin();
   it3 = sum.begin();
   for( ; it2 != op2.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.begin();
   iterator it4 = it3;
   for( ++it4; it4 != sum.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.pop_back();

   return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 )
{
   HugeInteger< T > difference(*this);
   for (reverse_iterator tmp = difference.rbegin(), tmp2 = (++difference.rbegin()); tmp2 != difference.rend(); ++tmp, ++tmp2) {
      (*tmp)--;
      (*tmp2) += 10;
   }

   for (iterator it1 = difference.begin(), it2 = op2.begin(); it2 != op2.end(); ++it1, ++it2){
      *it1 -= *it2;
   }

   for (iterator it = difference.begin(), it1 = (++difference.begin()); it1 != difference.end(); ++it, ++it1){
      if (*it >= 10){
         *it -= 10;
         *(it1) += 1;
      }
   }

   while (*difference.rbegin() == 0 && difference.size() > 1)
      difference.pop_back();

   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > &op2 )
{
   if (isZero() || op2.isZero())
      return HugeInteger< T >(0);

   unsigned int s = (size() + op2.size());
   HugeInteger product(s);

   unsigned int count = 0;
   for (iterator it2 = op2.begin(); it2 != op2.end(); ++it2, count++) {
      // 算 product 要從哪裡開始寫
      iterator it = product.begin();
      for (unsigned int i = 0; i < count; i++)
         ++it;
   
      // 去乘 *it1
      for (iterator it1 = begin(); it1 != end(); ++it1, ++it)
         *it += (*it1 * *it2);
   }

   for( iterator it1 = product.begin(), it2 = (++product.begin()); it2 != product.end(); ++it1, ++it2 ){
      if( *it1 >= 10) {
         *it2 += (*it1) / 10;
         *it1 %= 10;
      }
   }

   while (*product.rbegin() == 0 && product.size() > 1)
      product.pop_back();
   return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > &op2 )
{
   unsigned int n = size() - op2.size() + 1;

   if (*this < op2) {
      HugeInteger< T > quotient(1);
      *quotient.begin() = 0;
      return quotient;     
   }

   HugeInteger< T > quotient(n);
   HugeInteger< T > buffer(*this);
   HugeInteger< T > remainder(*this);

   unsigned int val = buffer.size() - op2.size();
   unsigned int i = 0;
   for (iterator it = buffer.begin(), it2 = op2.begin(); it != buffer.end(); ++it, i++) {
      if (i < val)
         *it = 0;
      else {
         *it = *it2;
         ++it2;
      }
   }

   for (reverse_iterator it = quotient.rbegin(); it != quotient.rend(); ++it) {
      while (buffer <= remainder) {
         remainder = remainder - buffer;
         (*it)++;
      }
      buffer.divideByTen();
   }

   while (*quotient.rbegin() == 0 && quotient.size() > 1)
      quotient.pop_back();

   return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger remainder = ( *this ) - ( quotient * op2 );
   return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger< T > temp = *this; // hold current state of object
   helpIncrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator--()
{
   helpDecrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpDecrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   for( iterator it = begin(); it != end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   iterator it1 = begin();
   iterator it2 = it1;
   for( ++it2; it2 != end(); ++it1, ++it2 )
      *it1 = *it2;
   pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   iterator it = begin();
   ( *it )++;
   iterator it2 = it;
   for( ++it2; it2 != end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *it = 0;
      resize( size() + 1 );
      it = end();
      --it;
      *it = 1;
   }
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   for (reverse_iterator tmp = rbegin(), tmp2 = (++rbegin()); tmp2 != rend(); ++tmp, ++tmp2) {
      (*tmp)--;
      (*tmp2) += 10;
   }

   (*begin())--;

   for (iterator it = begin(), it1 = (++begin()); it1 != end(); ++it, ++it1) {
      if (*it >= 10) {
         *it -= 10;
         *(it1) += 1;
      }
   }

   while (*rbegin() == 0 && size() > 1)
      pop_back();
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > &hugeInteger )
{
   list< T >::reverse_iterator it = hugeInteger.rbegin();
   for( ; it != hugeInteger.rend(); ++it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}