/**
*  Assignment 1 - Vector in Visual Studio 2017
*  powered by tyzescgm@gmail.com
**/
#include "Vector.h" // include definition of class vector 

// Constructs a zero vector with size n.
vector::vector(unsigned int n)
{
   if (n == 0)
      myFirst = myLast = myEnd = nullptr;
   else
   {
      myFirst = new int[n]();
      myLast = myEnd = myFirst + n;
   }
} // end default constructor

  // Destroys the vector.
vector::~vector()
{
   if (myFirst != nullptr)
      delete[] myFirst;
} // end destructor

unsigned int vector::size()
{
   return (myLast - myFirst);
}

unsigned int vector::capacity()
{
   return (myEnd - myFirst);
}

void vector::push_back(const int val)
{
   int* tmpptr = myFirst;
   unsigned int s = size();
   unsigned int c = capacity();
   //calculate real capacity
   if( s+1 > c )
      c = (unsigned int)(s*1.5);
   if( c <= 1)
      c++;

   myFirst = new int[c]();
   myEnd = myFirst + c;

   for (unsigned int i = 0; i < s; i++)
      myFirst[i] = tmpptr[i];
   myFirst[s] = val;
   delete[] tmpptr;
   myLast = myFirst + s + 1;
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if (size() > 0)
   {
      --myLast;
      *myLast = int();
   }
}

void vector::resize(unsigned int n)
{
   int* tmpptr = myFirst;
   unsigned int s = size();
   unsigned int c = capacity();
   //calculate real capacity
   if(n > c)
      if(n>(unsigned int)(c*1.5))
         c = n;
      else
         c = (unsigned int)(c*1.5);

   myFirst = new int[c]();
   myLast = myFirst + n;
   myEnd = myFirst + c;

   for(unsigned int i = 0; i < n; i++){
      if(i < s) 
         myFirst[i] = tmpptr[i];
      else
         myFirst[i] = 0;
   }
}

// Determines if two vectors are equal.
bool vector::equal(std::vector< int > &v)
{
   if (capacity() != v.capacity())
      return false;

   if (size() != v.size())
      return false;

   for (unsigned int i = 0; i < size(); i++)
      if (myFirst[i] != v[i])
         return false;

   return true;
}