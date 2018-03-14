#include "Vector.h" // include definition of class vector 

// constructor; constructs a zero vector with size n
vector::vector( unsigned int n )
   : myFirst( n == 0 ? nullptr : new int[ n ]() ),
      myLast( n == 0 ? nullptr : myFirst + n ),
       myEnd( n == 0 ? nullptr : myLast )
{
} // end vector default constructor

// destructor; destroys the vector
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

int* vector::begin() const
{
   return myFirst;
}

int* vector::end() const
{
   return myLast;
}

unsigned int vector::size() const
{
   return ( myLast - myFirst );
}

unsigned int vector::capacity() const
{
   return ( myEnd - myFirst );
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
   {
      --myLast;
      *myLast = int();
   }
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



   // Copy constructor; Constructs a vector with a copy of each of the elements in x.
vector::vector( const vector &x )
{
   myFirst = new int[x.capacity()]();
   for(unsigned int i = 0; i < x.size(); i++)
      myFirst[i] = x.myFirst[i];
   myLast = myFirst + x.size();
   myEnd = myFirst + x.capacity();
}

const vector &vector::assign( const vector &x )
{
   delete[] myFirst;
   myFirst = new int[x.capacity()]();
   for(unsigned int i = 0; i < x.size(); i++)
      myFirst[i] = x.myFirst[i];
   myLast = myFirst + x.size();
   myEnd = myFirst + x.capacity();
   return *this;
} // assignment operator