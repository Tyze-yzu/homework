// NewMember.cpp
// Member-function definitions for class NewMember
#include <iostream>
#include <fstream>
#include "NewMember.h" // NewMember class definition

NewMember::NewMember( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

void NewMember::execute()
{
	string str_id, str_name, str_email, str_password, str_phone;
	cout << "Enter your ID number: ";
	cin >> str_id;
	while(memberDatabase.existingId(str_id)){
		cout << "This ID is existing. Please input another one: ";
		cin >> str_id;
	}
	cout << "Enter your name: ";
	cin >> str_name;
	cout << "Enter an email address: ";
	cin >> str_email;
	while(memberDatabase.existingEmail(str_email)){
		cout << "This email is existing. Please input another one: ";
		cin >> str_email;
	}
	cout << "Enter a password: ";
	cin >> str_password;
	cout << "Enter your phone number: ";
	cin >> str_phone;
	cout << "\nSuccessful!\n" << endl;
	Member tmp(str_email, str_password, str_id, str_name, str_phone);
	memberDatabase.addMember(tmp);
}