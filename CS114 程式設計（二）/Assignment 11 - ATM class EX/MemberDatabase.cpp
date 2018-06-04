// MemberDatabase.cpp
// Member-function definitions for class MemberDatabase
#include <iostream>
#include <fstream>
#include "MemberDatabase.h" // MemberDatabase class definition

// MemberDatabase default constructor loads members from the file Members.dat
MemberDatabase::MemberDatabase()
{
   loadMembers();
}

// MemberDatabase destructor saves members into the file Members.dat
MemberDatabase::~MemberDatabase()
{
   saveMembers();
}

vector< Member >::iterator MemberDatabase::end()
{
   return members.end();
}

// retrieve Member object containing specified id
bool MemberDatabase::existingId( string id )
{
	for (unsigned int i = 0; i < members.size(); i++)
		if (id == members[i].getIdNumber())
			return true;
	return false;
} // end function existingId

// retrieve Member object containing specified email
bool MemberDatabase::existingEmail( string email )
{
	for (unsigned int i = 0; i < members.size(); i++)
		if (email == members[i].getEmail())
			return true;
	return false;
} // end function existingEmail

void MemberDatabase::addMember( Member newMember )
{
   members.push_back( newMember );
}

vector< Member >::iterator MemberDatabase::getMember( string email, string password )
{
	auto it = members.begin();
	for( ; it != members.end(); ++it)
		if (it->getEmail() == email && it->getPassword() == password)
			return it;
	return nullptr;
}

void MemberDatabase::loadMembers()
{
	ifstream inMemberFile;
	inMemberFile.open("Members.dat", ios::in | ios::binary);
	while (inMemberFile && !inMemberFile.eof()) {
		Member tmp;
		inMemberFile.read(reinterpret_cast< char * >(&tmp), sizeof(Member));
		members.push_back(tmp);
	}
	inMemberFile.close();
}

void MemberDatabase::saveMembers()
{
	ofstream file;
	file.open("Members.dat", ios::out | ios::binary);
	for (unsigned int i = 0; i < members.size(); i++)
		file.write(reinterpret_cast< const char * >(&members[i]), sizeof(Member));
	file.close();
}