#include <iostream>
#include <string>
#include <map>
using namespace std;

// Structure to hold account details
struct Account {
    string password;
    double balance;
};

// Bank account database (in-memory for simplicity)
map<string, Account> accounts;

void createAccount() {
    string userId, password;
    cout << "Please enter your user name: ";
    cin >> userId;
    if (accounts.find(userId) != accounts.end()) {
        cout << "Account already exists! Try logging in." << endl;
        return;
    }

    cout << "Please enter your password: ";
    cin >> password;
    accounts[userId] = {password, 0};
    cout << "Thank You! Your account has been created!" << endl;
}

string login() {
    string userId, password;
    cout << "Please enter your user id: ";
    cin >> userId;

    if (accounts.find(userId) == accounts.end()) {
        cout << "*** LOGIN FAILED! ***" << endl;
        return "";
    }

    cout << "Please enter your password: ";
    cin >> password;

    if (accounts[userId].password == password) {
        cout << "Access Granted!" << endl;
        return userId;
    } else {
        cout << "*** LOGIN FAILED! ***" << endl;
        return "";
    }
}

void withdrawMoney(string userId) {
    double amount;
    cout << "Amount of withdrawal: $";
    cin >> amount;
    if (accounts[userId].balance >= amount) {
        accounts[userId].balance -= amount;
        cout << "$" << amount << " has been withdrawn." << endl;
    } else {
        cout << "Insufficient funds!" << endl;
    }
}

void depositMoney(string userId) {
    double amount;
    cout << "Amount of deposit: $";
    cin >> amount;
    accounts[userId].balance += amount;
    cout << "$" << amount << " has been deposited." << endl;
}

void requestBalance(string userId) {
    cout << "Your balance is $" << accounts[userId].balance << "." << endl;
}

void atmMenu() {
    char option;

    do {
        cout << "\nPlease select an option from the menu below:" << endl;
        cout << "l -> Login" << endl;
        cout << "c -> Create New Account" << endl;
        cout << "q -> Quit" << endl;
        cout << "> ";
        cin >> option;

        switch (option) {
            case 'c':
                createAccount();
                break;
            case 'l': {
                string userId = login();
                if (!userId.empty()) {
                    char action;
                    do {
                        cout << "\nd -> Deposit Money" << endl;
                        cout << "w -> Withdraw Money" << endl;
                        cout << "r -> Request Balance" << endl;
                        cout << "q -> Quit" << endl;
                        cout << "> ";
                        cin >> action;

                        switch (action) {
                            case 'd':
                                depositMoney(userId);
                                break;
                            case 'w':
                                withdrawMoney(userId);
                                break;
                            case 'r':
                                requestBalance(userId);
                                break;
                            case 'q':
                                cout << "Logging out..." << endl;
                                break;
                            default:
                                cout << "Invalid option, please try again." << endl;
                        }
                    } while (action != 'q');
                }
                break;
            }
            case 'q':
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option, please try again." << endl;
        }
    } while (option != 'q');
}

int main() {
    cout << "Hi! Welcome to the ATM Machine!" << endl;
    atmMenu();
    return 0;
}


