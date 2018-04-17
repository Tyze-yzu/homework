// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include "Vector.h"

void testVector();

int main()
{
   for( unsigned int seed = 0; seed < 30; seed++ )
   {
      srand( seed );
      testVector();
   }

   system( "pause" );
}

void testVector()
{
   vector< int > v1;
   std::vector< int > v2;

   unsigned int numErrors = 1001;
   if( v1 == v2 )
      numErrors--;

   unsigned int position;
   unsigned int value;
   unsigned int choice;

   for( unsigned int i = 0; i < 1000; i++ )
   {
      choice = rand() % 2;
      switch( choice )
      {
      case 0:         
         value = 1 + rand() % 99;
         position = rand() % ( v1.size() + 1 );
         v1.insert( v1.begin() + position, value );
         v2.insert( v2.begin() + position, value );
         break;
      case 1:
         if( v1.size() > 0 )
         {
            position = rand() % v1.size();
            v1.erase( v1.begin() + position );
            v2.erase( v2.begin() + position );
         }
         break;
      default:
         break;
      }

//      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
//      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;

      if( v1 == v2 )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}