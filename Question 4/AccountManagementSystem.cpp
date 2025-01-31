/*
Bank Account Management System (Documentation)

This program implements a command-line interface (CLI) for a basic bank account management system.
It allows users to:
- Create a new account
- Deposit money
- Withdraw money
- Check account balance
- Display account details

Key features:
- Single user account management
- Input validation for all user inputs
- Persistent account state during program execution
- User-friendly interface with brief pauses for readability
*/

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;

// Global variable to check if the user has an account:
bool accountExists = false;

// Function to get a valid string input from the user:
string getValidStrInput(const string &PROMPT)
{
    string input;
    do
    {
        // Input:
        cout << PROMPT;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer (Kalinichenko, 2021)
        getline(cin, input);

        // Input Validation:
        if (input.empty())
        {
            cout << "You have entered an empty input. Please try again." << endl;
        }
    } while (input.empty());
    return input;
}

// Function to get a valid integer input from the user:
int getValidIntInput(const string &PROMPT, int minValue, int maxValue)
{
    int input;
    bool validInput = false;

    do
    {
        cout << PROMPT;

        // Check if the input is an integer
        if (cin >> input)
        {
            // Check if the input is within the specified range
            if (input >= minValue && input <= maxValue)
            {
                validInput = true;
            }
            else
            {
                cout << "Please enter a number between " << minValue << " and " << maxValue << "." << endl;
            }
        }
        else
        {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear(); // Clear the error flag
        }
    } while (!validInput);
    return input;
}

// Function to create a new account:
void createAccount(string &name, int &accountNumber, double &balance)
{
    if (accountExists)
    {
        int choice = getValidIntInput("You already have a bank account with us. Do you want to overwrite your current account details? (Enter '1' for yes): ", 0, 1);
        if (choice != 1)
        {
            cout << endl
                 << "Returning to the main menu." << endl;
            return;
        }
        cout << endl;
    }

    accountExists = true; // Account is created

    // Getting the user's name:
    name = getValidStrInput("Please enter your name: ");

    // Getting the user's account number:
    accountNumber = getValidIntInput("Please enter your account number (6 digits max): ", 0, 999999);

    // Getting the user's initial deposit amount:
    do
    {
        cout << "Please enter your initial deposit amount (greater than 0): R";
        cin >> balance;

        // Input Validation message:
        if (balance < 0)
        {
            cout << "Please enter a valid amount greater than R 0." << endl;
        }
    } while (balance < 0);

    cout << "You have successfully created an account with R" << balance << " as your initial deposit." << endl
         << endl;
}

// Function to deposit money into the user's account:
void depositMoney(double &balance)
{
    double depositAmount;

    // Checking if the user has an bank account:
    if (accountExists)
    {
        do
        {
            // Getting the amount of money the user wants to deposit:
            cout << "Please enter the amount of money you want to deposit: R";
            cin >> depositAmount;

            // Input Validation message:
            if (depositAmount < 0)
            {
                cout << "Please enter a valid amount greater than R 0." << endl;
            }
        } while (depositAmount < 0);

        // Adding the deposit amount to the balance:
        balance += depositAmount;

        cout << endl
             << "You have successfully deposited R" << depositAmount << " into your account." << endl;
        cout << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the success message
    }
    else
    {
        cout << "You do not have a bank account with us. You need to create an account first." << endl;
        cout << endl;
    }
    return;
}

// Function to withdraw money from the user's account:
void withdrawMoney(double &balance)
{
    double withdrawAmount;

    if (accountExists)
    {
        // Getting the amount of money the user wants to withdraw (must be bigger than zero):
        do
        {
            // The withdraw amount must be less than the balance:
            do
            {
                // Getting the amount of money the user wants to withdraw:
                cout << "Please enter the amount of money you want to withdraw: R";
                cin >> withdrawAmount;

                // Input Validation message:
                if (withdrawAmount > balance)
                {
                    cout << "You do not have enough money to withdraw R" << withdrawAmount << "." << endl;
                    cout << "Your current balance is: R" << balance << endl;
                    cout << endl;
                }
            } while (withdrawAmount > balance);

            // Input Validation message:
            if (withdrawAmount < 0)
            {
                cout << "Please enter a valid amount greater than R 0." << endl;
            }
        } while (withdrawAmount < 0);

        // Subtracting the withdraw amount from the balance:
        balance -= withdrawAmount;

        cout << endl
             << "You have successfully withdrawn R" << withdrawAmount << " from your account." << endl;
        cout << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the success message
    }
    else
    {
        cout << "You do not have a bank account with us. You need to create an account first." << endl;
        cout << endl;
    }
    return;
}

// Function to check the user's current balance:
void checkBalance(const double &balance)
{
    if (accountExists)
    {
        // Displaying the current balance to the user:
        cout << "Your current balance is: R" << balance << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the current balance (Sruthy, 2020)
        cout << endl;
    }
    else
    {
        cout << "You do not have a bank account with us. You need to create an account first." << endl;
        cout << endl;
    }
    return;
}

// Function to display the user's account details:
void displayAccountDetails(const string &name, const int &accountNumber, const double &balance)
{
    if (accountExists)
    {
        // Displaying the account details to the user:
        cout << "========= Account Details =========" << endl;
        cout << endl;
        cout << "Your name: " << name << endl;
        cout << "Your account number: " << accountNumber << endl;
        cout << "Your current balance: R" << balance << endl;
        cout << endl;
        cout << "===================================" << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the account details (Sruthy, 2020)
        cout << endl;
    }
    else
    {
        cout << "You do not have a bank account with us. You need to create an account first." << endl;
        cout << endl;
    }
    return;
}

// Function to display the CLI menu:
void displayCLIMenu(int &choice)
{
    cout << "===== Bank Account CLI Menu =====" << endl
         << endl
         << "1. Create New Account" << endl
         << "2. Deposit Money" << endl
         << "3. Withdraw Money" << endl
         << "4. Check Balance" << endl
         << "5. Display Account Details" << endl
         << "0. Exit Program" << endl
         << endl
         << "=================================" << endl
         << endl;

    choice = getValidIntInput("Enter your choice (0-5): ", 0, 5);
    cout << endl;
}

// Function to handle CLI menu choices:
void handleCLIMenu(int &choice, string &name, int &accountNumber, double &balance, bool &continueRunning)
{
    switch (choice)
    {
    case 1:
        createAccount(name, accountNumber, balance);
        break;
    case 2:
        depositMoney(balance);
        break;
    case 3:
        withdrawMoney(balance);
        break;
    case 4:
        checkBalance(balance);
        break;
    case 5:
        displayAccountDetails(name, accountNumber, balance);
        break;
    case 0:
        continueRunning = false; // Program shouldn't be running
        break;
    }
    return;
}

// Main Procedure:
int main()
{
    string name;
    int accountNumber, choice;
    double balance;
    bool continueRunning = true;

    // Welcome Message:
    cout << "------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Welcome to the Bank Account Management System!" << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the welcome message (Sruthy, 2020)
    cout << endl;

    // Main Loop of the program (CLI Menu):
    do
    {
        displayCLIMenu(choice);
        handleCLIMenu(choice, name, accountNumber, balance, continueRunning);
    } while (continueRunning); // Continue running the program until the user chooses to exit

    cout << endl;
    cout << "Thank you for using the Bank Account Management System, " << name << "! Have a great day!" << endl;
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the farewell message (Sruthy, 2020)
    return 0;
}
