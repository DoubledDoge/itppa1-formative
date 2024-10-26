// (My Documentation Placeholder)

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Function to get a valid string input from the user:
string getValidInput(const string &PROMPT)
{
    string input;
    do
    {
        // Input:
        cout << PROMPT;
        getline(cin, input);

        // Input Validation:
        if (input.empty())
        {
            cout << "You have entered an empty input. Please try again." << endl;
        }
    } while (input.empty());

    return input;
}

void createAccount(string &name, int &accountNumber, double &balance)
{
}

void depositMoney(double &balance)
{
}

void withdrawMoney(double &balance)
{
}

void checkBalance(const double &balance)
{
}

// Function to display the CLI menu:
void displayCLIMenu()
{
    // CLI menu:
    cout << "===== Cafeteria CLI Menu =====" << endl;
    cout << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Display Account Details" << endl;
    cout << "0. Logout" << endl;
    cout << endl;
    cout << "=============================" << endl;
    cout << endl;

    // Choosing the user option
    cout << "Enter your choice (0-5): ";
    cin >> choice;
    cin.clear();
    cout << endl;
}

// Function to handle CLI menu choices:
void handleCLIMenu(const string &name)
{
    switch (choice)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 0:
        break;
    default:
        break;
    }
}

void displayAccountDetails(const string &name, const int &accountNumber, const double &balance)

    // Main Procedure:
    int main()
{
}