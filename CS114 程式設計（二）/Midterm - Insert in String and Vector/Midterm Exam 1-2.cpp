// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include "String.h"

void testString();

int main()
{
   for( unsigned int seed = 0; seed < 30; seed++ )
   {
      srand( seed );
      testString();
   }

   system( "pause" );
}

void testString()
{
   string str1;
   std::string str2;

   unsigned int numErrors = 1001;
   if( str1 == str2 )
      numErrors--;

   unsigned int pos;
   char c;
   unsigned int choice;

   for( unsigned int i = 0; i < 1000; i++ )
   {
      choice = rand() % 2;
      switch( choice )
      {
      case 0:
         // Randomly generates a lower-case letter of English.
         c = static_cast< char >( 97 + rand() % 26 );
         pos = rand() % ( str1.size() + 1 );
         str1.insert( str1.begin() + pos, c );
         str2.insert( str2.begin() + pos, c );
         break;
      case 1:
         if( str1.size() > 0 )
         {
            pos = rand() % str1.size();
            str1.erase( str1.begin() + pos );
            str2.erase( str2.begin() + pos );
         }
         break;
      default:
         break;
      }

//      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
//      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;

      if( str1 == str2 )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}