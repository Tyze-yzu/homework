// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Withdrawal
{
public:
   Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, double &atmRemainingBills );
   void execute(); // perform the withdrawal transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   int amount; // amount to withdraw
   double &remainingBills;

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts );

   // display a menu of withdrawal amounts and the option to cancel;
   // return the chosen amount or 0 if the user chooses to cancel
   int displayMenuOfAmounts() const;
}; // end class Withdrawal

#endif // WITHDRAWAL_H

Withdrawal::Withdrawal(int userAccountNumber, vector< Account > &atmAccounts, double &atmRemainingBills)
	:accountNumber(userAccountNumber), accounts(atmAccounts), remainingBills(atmRemainingBills)
{
};

void Withdrawal::execute()
{
	int choise = displayMenuOfAmounts();

	double value;
	if (choise == 1)
		value = 20.0;
	if (choise == 2)
		value = 40.0;
	if (choise == 3)
		value = 60.0;
	if (choise == 4)
		value = 100.0;
	if (choise == 5)
		value = 200.0;
	if (choise == 6)
		return;

	if (choise <= 0 || choise >= 7) {
		cout << "Input error" << endl;
		return;
	}

	Account * tmp = getAccount(accountNumber, accounts);

	if (remainingBills < value) {
		cout << "ATM have no enough money" << endl;
		return;
	}

	if (tmp->getAvailableBalance() >= value) {
		tmp->debit(value);
		remainingBills -= value;
		cout << "Please take your cash from the cash dispenser." << endl;
		return;
	}
	else {
		cout << "You have no enough money" << endl;
		return;
	}
};

Account * Withdrawal::getAccount(int accountNumber, vector< Account > &accounts)
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

int Withdrawal::displayMenuOfAmounts() const
{
	cout << "Withdrawal options:" << endl;
	cout << "1 - $20" << endl;
	cout << "2 - $40" << endl;
	cout << "3 - $60" << endl;
	cout << "4 - $100" << endl;
	cout << "5 - $200" << endl;
	cout << "6 - Cancel transaction" << endl;
	cout << endl;
	cout << "Choose a withdrawal option (1-6): ";

	int choise = 0;
	while (choise <= 0 || choise >= 7)
		cin >> choise;

	return choise;
};