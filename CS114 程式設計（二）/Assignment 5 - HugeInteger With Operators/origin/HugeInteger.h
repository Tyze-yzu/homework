// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > &hugeInteger );
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( const HugeInteger &op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( const  HugeInteger &op2 ) const;

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( const HugeInteger &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( const HugeInteger &op2 ) const;
     
   HugeInteger& operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger& operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   void convert( vector< T > v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
private:
   vector< T > integer;

   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
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
const HugeInteger< T >& HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( const HugeInteger< T > &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector< T >::iterator it1 = integer.begin();
   vector< T >::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector< T >::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( const HugeInteger< T > &op2 ) const
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger remainder = ( *this ) - ( quotient * op2 );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( vector< T > v )
{
   integer.resize( v.size() );
   vector< T >::iterator it1 = integer.end() - 1;
   vector< T >::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   vector< T >::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   vector< T >::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   vector< T >::iterator it = integer.begin();
   ( *it )++;
   vector< T >::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > &hugeInteger )
{
	vector< T >::iterator it = hugeInteger.integer.end() - 1;
	for (; it != hugeInteger.integer.begin() - 1; --it)
		if (*it < 10)
			output << *it;

	return output; // enables cout << x << y;
}





template<typename T>
bool HugeInteger< T >::operator<(const HugeInteger &right) const {
	if (integer.size() < right.integer.size())
		return true;
	if (integer.size() > right.integer.size())
		return false;
	vector<T>::iterator it1 = integer.end() - 1;
	vector<T>::iterator it2 = right.integer.end() - 1;
	for (; it1 != integer.begin() - 1; --it1, --it2) {
		if (*it1 < *it2)
			return true;
		if (*it1 > *it2)
			return false;
	}
	return false;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator-(const HugeInteger &op2) const {
	HugeInteger<T> difference(*this);
	// unsigned int 會出問題 所以先借位
	vector< T >::iterator tmp = difference.integer.end() - 1;
	for (; tmp != difference.integer.begin(); tmp--) {
		(*tmp)--;
		(*(tmp - 1)) += 10;
	}

	for (unsigned int i = 0; i < op2.integer.size(); i++)
	{
		difference.integer.begin()[i] -= op2.integer.begin()[i];
	}

	for (unsigned int i = 0; i < difference.integer.size() - 1; i++) {
		if (difference.integer.begin()[i] >= 10) {
			difference.integer.begin()[i] -= 10;
			difference.integer.begin()[i + 1] += 1;
		}
	}

	vector< T >::iterator it = difference.integer.end() - 1;
	while (*it == 0 && it != difference.integer.begin())
	{
		difference.integer.pop_back();
		it--;
	}

	return difference;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator*(const  HugeInteger &op2) const {
	int size = (integer.size() + op2.integer.size());
	HugeInteger product(size);

	for (unsigned int i = 0; i < integer.size(); i++) {
		for (unsigned int j = 0; j < op2.integer.size(); j++) {
			product.integer.begin()[i + j] += integer.begin()[i] * op2.integer.begin()[j];
		}
	}
	for (unsigned int k = 1; k < product.integer.size(); k++) {
		if (product.integer.begin()[k - 1] >= 10) {
			product.integer.begin()[k] += product.integer.begin()[k - 1] / 10;
			product.integer.begin()[k - 1] = product.integer.begin()[k - 1] % 10;
		}
	}

	vector<T>::iterator it = product.integer.end() - 1;
	while (*it == 0 && it != product.integer.begin())
	{
		product.integer.pop_back();
		it--;
	}
	return product;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator/(const HugeInteger<T> &op2) const {
	int n = integer.size() - op2.integer.size() + 1;

	if (*this < op2) {
		HugeInteger quotient(1);
		quotient.integer.begin()[0] = 0;
		return quotient;
	}
	// 開個buffer存除數
	HugeInteger quotient(n);
	HugeInteger buffer(*this);
	HugeInteger remainder(*this);

	// 將buffer位數升至與被除數相同
	unsigned int val = buffer.integer.size() - op2.integer.size();
	for (unsigned int i = 0; i < buffer.integer.size(); i++) {
		if (i < val)
			buffer.integer.begin()[i] = 0;
		else
			buffer.integer.begin()[i] = op2.integer.begin()[i - val];
	}
	for (int i = 0; i < n; i++) {
		while (buffer <= remainder) {
			//cout << "除數比較小，做除法" << endl;
			remainder = remainder - buffer;
			quotient.integer.begin()[n - i - 1]++;
		}
		//cout << "\n不夠了。縮除數" << endl;
		buffer.divideByTen();
	}
	// 算出正確的商size

	vector<T>::iterator it = quotient.integer.end() - 1;
	while (*it == 0 && it != quotient.integer.begin())
	{
		quotient.integer.pop_back();
		it--;
	}
	return quotient;
}

template<typename T>
HugeInteger<T>& HugeInteger< T >::operator++() {
	helpIncrement();
	return *this;
} // prefix increment operator

template<typename T>
HugeInteger<T> HugeInteger< T >::operator++(int) {
	HugeInteger A(*this);
	helpIncrement();
	return A;
} // postfix increment operator

template<typename T>
HugeInteger<T>& HugeInteger< T >::operator--() {
	helpDecrement();
	return *this;
}// prefix decrement operator

template<typename T>
HugeInteger<T> HugeInteger< T >::operator--(int) {
	HugeInteger A(*this);
	helpDecrement();
	return A;
} // postfix decrement operator

template<typename T>
void HugeInteger< T >::helpDecrement() {

	vector< T >::iterator it = integer.begin();
	(*it)--;
	vector< T >::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		if (*it < 0)
		{
			*it += 10;
			(*it2)--;
		}
};
#endif