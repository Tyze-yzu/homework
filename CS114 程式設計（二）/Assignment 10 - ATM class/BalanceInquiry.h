// BalanceInquiry.h
// BalanceInquiry class definition. Represents a balance inquiry.
#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class BalanceInquiry
{
public:
   BalanceInquiry( int userAccountNumber, vector< Account > &atmAccounts ); // constructor
   void execute(); // perform the balance inquiry transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
}; // end class BalanceInquiry

#endif // BALANCE_INQUIRY_H

BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account > &atmAccounts) 
	:accountNumber(userAccountNumber), accounts(atmAccounts)
{	
};

Account * BalanceInquiry::getAccount(int accountNumber, vector< Account > &accounts)
{
	// loop through accounts searching for matching account number
	for (size_t i = 0; i < accounts.size(); i++)
	{
		// return current account if match found
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	} // end for

	return NULL; // if no matching account was found, return NULL
};

void BalanceInquiry::execute() 
{
	Account* tmp = getAccount(accountNumber, accounts);
	cout << "Balance Information:" << endl;
	cout << " - Available balance: $" << tmp->getAvailableBalance() << endl;
	cout << " - Total balance:     $" << tmp->getTotalBalance() << endl;
};