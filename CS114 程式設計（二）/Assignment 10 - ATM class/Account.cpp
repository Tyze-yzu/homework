#include "Account.h"

Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance,
	double theTotalBalance)
	:accountNumber(theAccountNumber), pin(thePIN), availableBalance(theAvailableBalance), totalBalance(theTotalBalance)
{
}; // constructor sets attributes

bool Account::validatePIN(int userPIN) const
{
	return userPIN == pin;
}; // is user-specified PIN correct?

double Account::getAvailableBalance() const
{
	return availableBalance;
};// returns available balance

double Account::getTotalBalance() const
{
	return totalBalance;
}; // returns total balance

void Account::credit(double amount)
{
	totalBalance += amount;
}; // adds an amount to the Account balance

void Account::debit(double amount)
{
	availableBalance -= amount;
	totalBalance -= amount;
}; // subtracts an amount from the Account balance

int Account::getAccountNumber() const
{
	return accountNumber;
}; // returns account number