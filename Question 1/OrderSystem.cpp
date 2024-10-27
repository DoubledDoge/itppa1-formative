/*
Cafeteria Order System

This program implements a command-line interface (CLI) for a university cafeteria ordering system.
It allows users to:
- View the menu
- Place orders
- View current orders
- Cancel orders
- Checkout and apply discounts
- Save order details to a file

Key features:
- User "authentication" with first and last name
- Menu with various food items and prices
- Order management (add, view, cancel)
- Automatic discount application for orders over R100
- Order summary and bill generation
- File output for completed orders
- User-friendly interface with brief pauses for readability
*/

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <limits>
#include <iomanip>

using namespace std;

// Global Arrays:
string orderedItemNames[25];
double orderedItemPrices[25];

// Global Variables:
int orderCount = 0;
double grossTotal = 0;
bool continueRunning = true, hasOrdered = false;

// Menu Variables:
const double COFFEE_PRICE = 15.00;
const double SANDWICH_PRICE = 30.00;
const double SALAD_PRICE = 25.00;
const double JUICE_PRICE = 10.00;
const double MUFFIN_PRICE = 20.00;
const double PIZZA_PRICE = 35.00;
const double SOUP_PRICE = 18.00;
const double BURGER_PRICE = 40.00;

// Function to end the program:
bool endProgram(const string &firstName, const string &lastName)
{
    cout << endl;
    cout << "Thank you for using the Cafeteria Order System, " << firstName << " " << lastName << "! Have a great day!" << endl;
    return false;
}

// Function to get a valid string input from the user:
string getValidStrInput(const string &PROMPT)
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
            cin.clear();                                         // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears input buffer (Kalinichenko, 2021)
        }
    } while (!validInput);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears input buffer (Kalinichenko, 2021)
    return input;
}

// Function to get the user's full name:
void getUserName(string &firstName, string &lastName)
{
    firstName = getValidStrInput("Please enter your first name: ");
    cout << endl;
    lastName = getValidStrInput("Please enter your last name:  ");
    return;
}

// Function for displaying the current order summary:
void displayOrderSummary()
{
    cout << "Your order summary:" << endl;
    cout << endl;
    for (int i = 0; i < orderCount; i++)
    {
        cout << i + 1 << ". " << orderedItemNames[i] << " - R " << fixed << setprecision(2) << orderedItemPrices[i] << endl; // (GeeksforGeeks, 2024a)
    }
    cout << endl;
    return;
}

// Function to display the item menu:
void viewMenu()
{
    cout << "======================= Cafeteria Item Menu ========================" << endl;
    cout << endl;
    cout << fixed << setprecision(2); // (GeeksforGeeks, 2024a)
    cout << "1. Coffee       - R " << COFFEE_PRICE << endl;
    cout << "2. Sandwich     - R " << SANDWICH_PRICE << endl;
    cout << "3. Salad        - R " << SALAD_PRICE << endl;
    cout << "4. Juice        - R " << JUICE_PRICE << endl;
    cout << "5. Muffin       - R " << MUFFIN_PRICE << endl;
    cout << "6. Pizza Slice  - R " << PIZZA_PRICE << endl;
    cout << "7. Soup         - R " << SOUP_PRICE << endl;
    cout << "8. Burger       - R " << BURGER_PRICE << endl;
    cout << endl;
    cout << "====================================================================" << endl;
    cout << endl;
    return;
}

// Function to place an order:
void placeOrder()
{
    int amountOrdered, itemNo, returnChoice;

    if (hasOrdered)
    {
        // Use the function to get a valid integer input:
        returnChoice = getValidIntInput("It seems that you have already added an order before. Do you want to add more items? (Enter '1' for yes): ", 0, 1);
        if (returnChoice != 1)
        {
            cout << endl;
            cout << "Returning to the main menu." << endl;
            return;
        }
    }
    else
    {
        orderCount = 0; // Reset order count only for new orders
        hasOrdered = true;
    }

    // Inputting only 25 items max:
    amountOrdered = getValidIntInput("Choose the amount of items you want to purchase (25 items max): ", 1, 25);
    cout << endl;

    viewMenu();

    // Loop to buy the items according to the specified amount:
    for (int i = 1; i <= amountOrdered; i++)
    {
        cout << endl;
        itemNo = getValidIntInput("Choose the item no. " + to_string(i) + " that you want to purchase (Enter '0' to display the item menu again): ", 0, 8); // to_string(i) converts the integer i to a string (GeeksforGeeks, 2024b)
        cout << endl;

        // Variables used for the switch statement:
        string itemName;
        double itemPrice;

        // Switch statement to get the item name and price according to the item number:
        switch (itemNo)
        {
        case 0:
            viewMenu();
            i--; // Reset i to previous value to prevent the item being discarded
            break;
        case 1:
            itemName = "Coffee";
            itemPrice = COFFEE_PRICE;
            break;
        case 2:
            itemName = "Sandwich";
            itemPrice = SANDWICH_PRICE;
            break;
        case 3:
            itemName = "Salad";
            itemPrice = SALAD_PRICE;
            break;
        case 4:
            itemName = "Juice";
            itemPrice = JUICE_PRICE;
            break;
        case 5:
            itemName = "Muffin";
            itemPrice = MUFFIN_PRICE;
            break;
        case 6:
            itemName = "Pizza Slice";
            itemPrice = PIZZA_PRICE;
            break;
        case 7:
            itemName = "Soup";
            itemPrice = SOUP_PRICE;
            break;
        case 8:
            itemName = "Burger";
            itemPrice = BURGER_PRICE;
            break;
        }

        // Calculations:
        grossTotal += itemPrice;                   // Add the item price to the gross total
        orderedItemNames[orderCount] = itemName;   // Add the item name to the ordered item names array
        orderedItemPrices[orderCount] = itemPrice; // Add the item price to the ordered item prices array
        orderCount++;

        // Confirmation Message:
        cout << "Added " << itemName << " to your order." << endl;
        cout << endl;
    }

    // Final Message (Gross total and ordered items):
    displayOrderSummary();
    cout << "Total Bill: R " << fixed << setprecision(2) << grossTotal << endl; // (GeeksforGeeks, 2024a)
    this_thread::sleep_for(chrono::seconds(3));                                 // Brief wait timer for the user to read the gross total (Sruthy, 2020)
    cout << endl;
    return;
}

void viewOrder()
{
    // Display the order summary if the user has ordered:
    if (hasOrdered)
    {
        displayOrderSummary();
        cout << "Total Bill: R " << fixed << setprecision(2) << grossTotal << endl; // (GeeksforGeeks, 2024a)
        this_thread::sleep_for(chrono::seconds(3));
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the error message (Sruthy, 2020)
    }
    cout << endl;
    return;
}

void cancelOrder()
{
    // Cancel the order if the user has ordered:
    if (hasOrdered)
    {
        int confirm;

        // Simple confirmation of the user:
        confirm = getValidIntInput("Are you sure you want to cancel your order? (Enter '1' for Yes, '0' for No): ", 0, 1);

        // Resetting the order:
        if (confirm == 1)
        {
            grossTotal = 0;              // Reset the gross total
            orderCount = 0;              // Reset the order count
            for (int i = 0; i < 25; i++) // Clear the ordered items arrays one by one
            {
                orderedItemNames[i] = ""; // "" = empty string
                orderedItemPrices[i] = 0.00;
            }
            cout << endl;
            cout << "Order cancelled. Your order summary has been cleared." << endl;
            cout << endl;
            hasOrdered = false; // Reset the hasOrdered variable
        }
        else // No reset:
        {
            cout << endl;
            cout << "Order cancellation aborted." << endl;
            cout << endl;
        }

        cout << "Total Bill: R " << fixed << setprecision(2) << grossTotal << endl; // (GeeksforGeeks, 2024a)
        this_thread::sleep_for(chrono::seconds(3));
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the error message (Sruthy, 2020)
    }
    cout << endl;
    return;
}

void checkoutOrder(const string &firstName, const string &lastName)
{
    double netTotal = 0, discountAmount = 0;
    int confirmed1 = 0, confirmed2 = 0;

    // Constant variables:
    const double DISCOUNT_RATE = 0.10;        // 10% discount
    const double DISCOUNT_THRESHOLD = 100.00; // Discount applies if bill is over R100

    // Check if the user has ordered:
    if (hasOrdered)
    {
        // Check if the user is applicable for the discount (Gross total over R 100):
        if (grossTotal >= DISCOUNT_THRESHOLD)
        {
            cout << "Hooray! You are applicable for our daily discount special!" << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Brief wait timer for the user to read the message (Sruthy, 2020)

            // Calculations:
            discountAmount = grossTotal * DISCOUNT_RATE;
            netTotal = grossTotal - discountAmount;
            cout << "Discounted Amount: R " << fixed << setprecision(2) << discountAmount << endl; // (GeeksforGeeks, 2024a)
        }
        else
        {
            cout << "No discount is applied to your order. Too bad." << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Brief wait timer for the user to read the message (Sruthy, 2020)
            netTotal = grossTotal;
        }

        displayOrderSummary();
        cout << "Final Bill: R " << fixed << setprecision(2) << netTotal << endl; // (GeeksforGeeks, 2024a)
        this_thread::sleep_for(chrono::seconds(3));                               // Brief wait timer for the user to read the final bill (Sruthy, 2020)
        cout << endl;

        // Ask the user to write their details to CafeteriaBill.txt:
        confirmed1 = getValidIntInput("Are you sure you want to write your details to CafeteriaBill.txt? (Enter '1' for Yes): ", 0, 1);
        cout << endl;

        if (confirmed1 == 1)
        {
            // Writing the details to the file: (W3Schools, n.d.)
            filesystem::path filePath = "CafeteriaBill.txt";
            ofstream outFile(filePath, ios::app); // Open in append mode

            // Check if the file exists and is open:
            if (outFile.is_open())
            {
                outFile << firstName << " " << lastName << ": R" << fixed << setprecision(2) << netTotal << endl; // Writing to the next line of the file (GeeksforGeeks, 2024a)
                outFile.close();                                                                                  // Close the file
                cout << "Bill details have been written to CafeteriaBill.txt" << endl;                            // Success message
                cout << endl;
            }
            else
            {
                cout << "Unable to open file for writing." << endl; // Error message
            }

            // Ask the user to finish the program once the file has been written:
            confirmed2 = getValidIntInput("Are you finished using this program? (Enter '1' for Yes, '0' for No): ", 0, 1);
            cout << endl;
            if (confirmed2 == 1)
            {
                cout << "Thank you for shopping at our university cafeteria!";
                continueRunning = endProgram(firstName, lastName);
            }
        }
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the message (Sruthy, 2020)
    }
    return;
}

// Function to display the CLI menu:
void displayCLIMenu(int &choice)
{
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
    cout << endl;

    // Advertising of the discount:
    cout << "**************** SPECIAL OFFER ****************" << endl;
    cout << endl;
    cout << "Get a 10% discount on orders of R100.00 or more!" << endl;
    cout << endl;
    cout << "************************************************" << endl;
    cout << endl;

    // Choosing the user option
    choice = getValidIntInput("Enter your choice (0-5): ", 0, 5);
    cout << endl;
    return;
}

// Function to handle CLI menu choices:
void handleCLIMenu(int &choice, const string &firstName, const string &lastName)
{
    switch (choice)
    {
    case 1:
        viewMenu();
        int done;
        // Confirmation before returning to the CLI menu:
        do
        {
            cout << "Continue? (Enter '1' to continue): ";
            cin >> done;
            cin.clear();
        } while (done != 1);
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
        checkoutOrder(firstName, lastName);
        break;
    case 0:
        continueRunning = endProgram(firstName, lastName); // Program shouldn't be running
        break;
    }
    return;
}

// Main Procedure:
int main()
{
    string firstName, lastName;
    int choice;
    // Welcome Message:
    cout << "------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Welcome to the Cafeteria Order System!" << endl;
    cout << "Lets get you logged in." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the welcome message (Sruthy, 2020)
    cout << endl;

    // User Login:
    getUserName(firstName, lastName);
    cout << endl;

    // Login Confirmation:
    cout << "Hello, " << firstName << " " << lastName << "!" << endl;
    cout << "You can now proceed with your order." << endl;
    cout << "Please wait..." << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Wait timer to simulate waiting for the program (Sruthy, 2020)
    cout << endl;

    // Main Loop of the program (CLI Menu):

    do
    {
        displayCLIMenu(choice);
        handleCLIMenu(choice, firstName, lastName);
    } while (continueRunning); // Check if the program is meant to be running or not.

    cout << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the farewell message (Sruthy, 2020)
    return 0;
}
