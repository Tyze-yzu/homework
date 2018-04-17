#ifndef STRING_H
#define STRING_H

#include <string>

// string class definition
class string
{
   friend bool operator==( string &lhs, std::string &rhs );
public:
   using iterator = char*;

   string();

   ~string();

   iterator begin();

   iterator end();

   size_t size() const;

   size_t capacity() const;

   // Inserts character c into the string right before the character indicated by p.
   void insert( iterator p, char c );

   // Erases the character pointed by p.
   void erase( iterator p );

private:
   union Bxty
   {	// storage for small buffer or pointer to larger one
      char buf[ 16 ];
      char *ptr;
   } bx;

   size_t mySize = 0; // current length of string

   size_t myRes = 15; // current storage reserved for string
}; // end class string

#endif