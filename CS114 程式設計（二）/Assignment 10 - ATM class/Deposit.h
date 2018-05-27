// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Deposit
{
public:
   Deposit( int userAccountNumber, vector< Account > &atmAccounts );
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit

#endif // DEPOSIT_H

Deposit::Deposit(int userAccountNumber, vector< Account > &atmAccounts)
	:accountNumber(userAccountNumber), accounts(atmAccounts)
{
};

void Deposit::execute()
{
	double value = promptForDepositAmount();
	if (value == 0) {
		cout << "Cancel." << endl;
		return;
	}
	cout << "Please insert a deposit envelope containing $" << value / 100.0 << " in the deposit slot." << endl;
	cout << endl;
	cout << "Your envelope has been received." << endl;
	cout << "NOTE: The money deposited will not be available until we verify the amount of any enclosed cash, and any enclosed checks clear." << endl;
	Account* tmp = getAccount(accountNumber, accounts);
	tmp->credit(value/100.0);
	return;
} // perform the deposit transaction

Account * Deposit::getAccount(int accountNumber, vector< Account > &accounts)
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
double Deposit::promptForDepositAmount() const
{
	double value;
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> value;
	cout << endl;
	return value;
};// prompt user to enter a deposit amount in cents 
