// (My Documentation Placeholder)

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Function to get a valid string input from the user:
string getValidInput(const string &prompt)
{
    string input;
    do
    {
        // Input:
        cout << prompt;
        getline(cin, input);

        // Input Validation:
        if (input.empty())
        {
            cout << "You have entered an empty input. Please try again." << endl;
        }
    } while (input.empty());

    return input;
}

// Function to get the user's full name:
void getUserName(string &firstName, string &lastName)
{
    firstName = getValidInput("Please enter your first name: ");
    lastName = getValidInput("Please enter your last name: ");
}

// Function to display the item menu:
void viewMenu()
{
    // Item menu table:
    cout << endl;
    cout << "======================= Cafeteria Item Menu ========================" << endl;
    cout << "| No. | Item         | Price (R) || No. | Item         | Price (R) |" << endl;
    cout << "|-----|--------------|-----------||-----|--------------|-----------|" << endl;
    cout << "|  1. | Coffee       |    15.00  ||  5. | Muffin       |    20.00  |" << endl;
    cout << "|  2. | Sandwich     |    30.00  ||  6. | Pizza Slice  |    35.00  |" << endl;
    cout << "|  3. | Salad        |    25.00  ||  7. | Soup         |    18.00  |" << endl;
    cout << "|  4. | Juice        |    10.00  ||  8. | Burger       |    40.00  |" << endl;
    cout << "====================================================================" << endl;
    cout << endl;

    int done;
    do
    {
        cout << "Continue? (Enter 1 to continue)" << endl;
        cin >> done;
        cin.ignore();
    } while (done != 1);
}

void placeOrder()
{
    int itemAmount, itemNo; // (Should be a array here)

    cout << "Choose the amount of items you want to purchase: " << endl;
    cin >> itemAmount;

    cout << endl;

    for (int i; i < itemAmount; i++)
    {
        cout << "Choose the " << i << "st item number you want to purchase:" << endl;
        cout << "(Enter '0' to display the item menu again)" << endl;
        cout << endl;
        cin >> itemNo;
    }
}

void viewOrder()
{
}

void cancelOrder()
{
}

void checkoutOrder()
{
}

// Function to display the CLI menu:
void displayCLIMenu(int &choice)
{
    cout << endl;

    // CLI menu:
    cout << "===== Cafeteria CLI Menu =====" << endl;
    cout << endl;
    cout << "1. View Menu" << endl;
    cout << "2. Place Order" << endl;
    cout << "3. View Order" << endl;
    cout << "4. Cancel Order" << endl;
    cout << "5. Checkout" << endl;
    cout << "0. Logout" << endl;
    cout << endl;
    cout << "=============================" << endl;

    // Choosing the user option
    cout << endl;
    cout << "Enter your choice (0-5): ";
    cin >> choice;
    cin.ignore();
}

// Function to handle CLI menu choices:
bool handleCLIMenuChoice(int choice, const string &firstName, const string &lastName)
{
    switch (choice)
    {
    case 1:
        viewMenu();
        break;
    case 2:
        placeOrder();
        break;
    case 3:
        viewOrder();
        break;
    case 4:
        cancelOrder();
        break;
    case 5:
        checkoutOrder();
        break;
    case 0:
        cout << endl;
        cout << "Thank you for using the Cafeteria Order System, "
             << firstName << " " << lastName << "! Have a great day!" << endl;
        return false; // Program shouldn't be running
    default:
        // Input Validation:
        cout << "Invalid choice. Please enter a valid number from 0 to 5." << endl;
    }
    return true; // Program should be running
}

// Main Procedure:
int main()
{
    string firstName, lastName;
    int choice;
    bool continueRunning = true; // Variable used to check if the program is still running

    // Welcome Message:
    cout << "Welcome to the Cafeteria Order System!" << endl;
    cout << "Lets get you logged in." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the welcome message

    cout << endl;

    // User Login:
    getUserName(firstName, lastName);

    cout << endl;

    // Login Confirmation:
    cout << "Hello, " << firstName << " " << lastName << "!" << endl;
    cout << "You can now proceed with your order." << endl;
    cout << "Please wait..." << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Wait timer to simulate waiting for the program

    // Main Loop of the program (CLI Menu):
    do
    {
        displayCLIMenu(choice);
        continueRunning = handleCLIMenuChoice(choice, firstName, lastName);
    } while (continueRunning); // Check if the program is meant to be running or not.

    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the farewell message

    return 0;
}
