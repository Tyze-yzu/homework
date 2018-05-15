#include <iostream>
#include <string>
using namespace std;

class User {
public:
    User()
        : account_number(""),
          pin(""),
          avalible(0.0),
          total(0.0)
    {
    }
    User(User const &u){
        account_number = u.account_number;
        pin = u.pin;
        total = u.total;
        avalible = u.avalible;
    };
    User(string an, string p, double a, double t)
        : account_number(an),
          pin(p),
          avalible(a),
          total(t)
    {            
    };

    void viewBalance(){
        cout << "Balance Information:" << endl;
        cout << " - Available balance: $" << avalible << endl;
        cout << " - Total balance:     $" << total << endl;
    };

    void withdraw(){
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
        cin >> choise;
        double value;
        if(choise == 1)
            value = 20.0;
        if(choise == 2)
            value = 40.0;
        if(choise == 3)
            value = 60.0;
        if(choise == 4)
            value = 100.0;
        if(choise == 5)
            value = 200.0;
        if(choise == 6)
            return;
        if(choise <= 0 || choise >= 7){
            cout << "Input error" << endl;
            return;
        }

        if(avalible >= value){
            avalible -= value;
            total -= value;
            cout << "Please take your cash from the cash dispenser." << endl;
            return;
        }else{
            cout << "You have no enough money" << endl;
            return;
        }
    };

    void deposit(){
        double value;
        cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
        cin >> value;
        cout << endl;
        if(value == 0){
            cout << "Cancel." << endl;
            return;
        }
        cout << "Please insert a deposit envelope containing $" << value/100.0 << " in the deposit slot." << endl;
        cout << endl;
        cout << "Your envelope has been received." << endl;
        cout << "NOTE: The money deposited will not be available until we verify the amount of any enclosed cash, and any enclosed checks clear." << endl;
        total += value;
    };

    string account_number;
    string pin;
    double total;
    double avalible;
};

User empty_user = User("", "", 0, 0);

User& getUser(User users[], string an, string pin){
    for(int i = 0; i < 2; i++){
        if(users[i].account_number == an && users[i].pin == pin)
            return users[i];
    }
    return empty_user;
}

int main(){
    User users[2];
    users[0] = User("12345", "54321", 1000.0, 1200.0);
    users[1] = User("98765", "56789", 200.0, 200.0);
    while(true){
        string account_number;
        string PIN;

        cout << "Welcome!" << endl;
        cout << "\nPlease enter your account number: ";
        cin >> account_number;
        cout << "\nEnter your PIN: ";
        cin >> PIN;

        User& user = getUser(users, account_number, PIN);
        if(user.account_number == ""){
            cout << "\nLogin Error!\n" << endl;
            continue;
        }

        // stage 2
        int choise = 0;

        while(choise != 4){
            cout << "\nMain menu:" << endl;
            cout << "1 - View my balance" << endl;
            cout << "2 - Withdraw cash" << endl;
            cout << "3 - Deposit funds" << endl;
            cout << "4 - Exit" << endl;
            cout << "Enter a choice: ";
            cin >> choise;
            cout << endl;
            if(choise == 1)
                user.viewBalance();
            if(choise == 2)
                user.withdraw();
            if(choise == 3)
                user.deposit();
        }
        cout << "Exiting the system...\n\nThank you! Goodbye!\n\n";
    }

    system("PAUSE");
    return 0;    
}