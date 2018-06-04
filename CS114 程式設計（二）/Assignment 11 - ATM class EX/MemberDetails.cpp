// MemberDetails.cpp
// Member-function definitions for class MemberDetails
#include <iostream>
using namespace std;
#include "MemberDetails.h" // MemberDetails class definition

int inputAnInteger( int begin, int end );

MemberDetails::MemberDetails( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

void MemberDetails::execute( vector< Member >::iterator it )
{
	cout << "1. Name: " << it->getName() << endl;
	cout << "2. Email Address: " << it->getEmail() << endl;
	cout << "3. Phone Number: " << it->getPhone() << endl;
	cout << "4. ID Number: " << it->getIdNumber() << endl;
	cout << "5. Password: " << it->getPassword() << endl;
	cout << "\nWhich one do you want to modify (0 ¡V not modify)? ";
	int choice;
	while (true)
	{
		choice = inputAnInteger(0, 5);
		cout << endl;

		string tmp;
		switch (choice)
		{
		case 1:
			cout << "Enter correct data: ";
			cin >> tmp;
			it->setName(tmp);
			cout << "Successful!\n\n";
			return;
		case 2:

			cout << "Enter correct data: ";
			cin >> tmp;
			while (memberDatabase.existingEmail(tmp)) {
				cout << "This email is existing. Please input another one: ";
				cin >> tmp;
			}
			it->setEmail(tmp);
			cout << "Successful!\n\n";
			return;
		case 3:
			cout << "Enter correct data: ";
			cin >> tmp;
			it->setPhone(tmp);
			cout << "Successful!\n\n";
			return;
		case 4:
			cout << "Enter correct data: ";
			cin >> tmp;
			while (memberDatabase.existingId(tmp)) {
				cout << "This ID is existing. Please input another one: ";
				cin >> tmp;
			}
			it->setIdNumber(tmp);
			cout << "Successful!\n\n";
			return;
		case 5:
			cout << "Enter correct data: ";
			cin >> tmp;
			it->setPassword(tmp);
			cout << "Successful!\n\n";
			return;
		case 0:
			return;
		default:
			cout << "Input Error! Please try again: ";
			break;
		}
	}
}