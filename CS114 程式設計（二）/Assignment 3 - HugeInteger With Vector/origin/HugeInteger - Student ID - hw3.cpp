// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( const HugeInteger &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( const HugeInteger &op2 ) const
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output









bool HugeInteger::equal( const HugeInteger &right ) const
{
	if (integer.size() != right.integer.size())
		return false;
	vector::iterator it1 = integer.begin();
	vector::iterator it2 = right.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it2)
		if (*it1 != *it2)
			return false;
	return true;
}          // equal to
//   bool notEqual( const HugeInteger &right ) const;       // not equal to
bool HugeInteger::less( const HugeInteger &right ) const
{
	if (integer.size() < right.integer.size())
		return true;
	if (integer.size() > right.integer.size())
		return false;
	vector::iterator it1 = integer.end()-1;
	vector::iterator it2 = right.integer.end()-1;
	for (; it1 != integer.begin()-1; --it1, --it2){
		if (*it1 < *it2)
			return true;
		if(*it1 > *it2)
			return false;
	}
	return false;
}


HugeInteger HugeInteger::subtract( const HugeInteger &op2 ) const
{
	HugeInteger difference(*this);

	for (unsigned int i = 0; i < op2.integer.size(); i++)
	{
		difference.integer.begin()[i] -= op2.integer.begin()[i];
	}
	
	for (unsigned int i = 1; i < difference.integer.size(); i++) {
		if (difference.integer.begin()[i - 1] < 0) {
			difference.integer.begin()[i - 1] += 10;
			difference.integer.begin()[i] -= 1;
		}
	}
	
	vector::iterator it = difference.integer.end()-1;
	while (*it == 0 && it != difference.integer.begin())
	{
		difference.integer.pop_back();
		it--;
	}
	
	return difference;
}

   // multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply( const  HugeInteger &op2 ) const
{
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

	vector::iterator it = product.integer.end() - 1;
	while (*it == 0 && it != product.integer.begin())
	{
		product.integer.pop_back();
		it--;
	}
	return product;
}

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
HugeInteger HugeInteger::divide( const HugeInteger &op2 ) const
{
	int n = integer.size() - op2.integer.size() + 1;

	if (less(op2)) {
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
			while (buffer.less(remainder) || buffer.equal(remainder)) {
			//cout << "除數比較小，做除法" << endl;
			remainder.assign(remainder.subtract(buffer));
			quotient.integer.begin()[n - i - 1]++;
		}
		//cout << "\n不夠了。縮除數" << endl;
		buffer.divideByTen();
	}
	// 算出正確的商size

	vector::iterator it = quotient.integer.end() - 1;
	while (*it == 0 && it != quotient.integer.begin())
	{
		quotient.integer.pop_back();
		it--;
	}
	return quotient;
}