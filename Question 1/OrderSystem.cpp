// (My Documentation Placeholder)

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>

using namespace std;

// Other constant variables:
const double DISCOUNT_RATE = 0.10;        // 10% discount
const double DISCOUNT_THRESHOLD = 100.00; // Discount applies if bill is over R100
const int MAX_ITEMS = 25;

// Menu Variables:
const double COFFEE_PRICE = 15.00;
const double SANDWICH_PRICE = 30.00;
const double SALAD_PRICE = 25.00;
const double JUICE_PRICE = 10.00;
const double MUFFIN_PRICE = 20.00;
const double PIZZA_PRICE = 35.00;
const double SOUP_PRICE = 18.00;
const double BURGER_PRICE = 40.00;

// Global Arrays:
string orderedItemNames[MAX_ITEMS];
double orderedItemPrices[MAX_ITEMS];

// Other Global Variables:
string firstName, lastName;
int choice, orderCount = 0;
double grossTotal = 0;
bool continueRunning = true, hasOrdered = false;

// Function to take a price and returns a string with the price formatted to two decimal places:
string formatPrice(double price)
{
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.2f", price);
    return string(buffer);
}

// Function to end the program:
bool endProgram()
{
    cout << endl;
    cout << "Thank you for using the Cafeteria Order System, " << firstName << " " << lastName << "! Have a great day!" << endl;
    return false;
}

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

// Function to get the user's full name:
void getUserName(string &firstName, string &lastName)
{
    firstName = getValidInput("Please enter your first name: ");
    cout << endl;
    lastName = getValidInput("Please enter your last name:  ");
}

// Function for displaying the current order summary:
void displayOrderSummary()
{
    cout << "Your order summary:" << endl;
    cout << endl;
    for (int i = 0; i < orderCount; i++)
    {
        cout << i + 1 << ". " << orderedItemNames[i] << " - R " << formatPrice(orderedItemPrices[i]) << endl;
        cout << endl;
    }
    cout << endl;
}

// Function to display the item menu:
void viewMenu()
{
    cout << "======================= Cafeteria Item Menu ========================" << endl;
    cout << endl;
    cout << "1. Coffee       - R " << formatPrice(COFFEE_PRICE) << endl;
    cout << "2. Sandwich     - R " << formatPrice(SANDWICH_PRICE) << endl;
    cout << "3. Salad        - R " << formatPrice(SALAD_PRICE) << endl;
    cout << "4. Juice        - R " << formatPrice(JUICE_PRICE) << endl;
    cout << "5. Muffin       - R " << formatPrice(MUFFIN_PRICE) << endl;
    cout << "6. Pizza Slice  - R " << formatPrice(PIZZA_PRICE) << endl;
    cout << "7. Soup         - R " << formatPrice(SOUP_PRICE) << endl;
    cout << "8. Burger       - R " << formatPrice(BURGER_PRICE) << endl;
    cout << endl;
    cout << "====================================================================" << endl;
    cout << endl;
}

// Function to place an order:
void placeOrder()
{
    int amountOrdered, itemNo;

    if (hasOrdered)
    {
        int returnChoice;
        cout << "It seems that you have already added an order before. Do you want to add more items? (Enter '1' for yes): ";
        cin >> returnChoice;
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
    do
    {
        cout << "Choose the amount of items you want to purchase (" << MAX_ITEMS << " items max): ";
        cin >> amountOrdered;
        cout << endl;
    } while (amountOrdered > MAX_ITEMS);

    viewMenu();

    // Loop to buy the items according to the specified amount:
    for (int i = 1; i <= amountOrdered; i++)
    {
        cout << endl;
        cout << "Choose the item no. " << i << " that you want to purchase (Enter '0' to display the item menu again): ";
        cin >> itemNo;
        cin.clear();
        cout << endl;

        // Variables used for the switch statement:
        string itemName;
        double itemPrice;

        // Switch statement to get the item name and price according to the item number:
        switch (itemNo)
        {
        case 0:
            // Display the menu again at the user's request:
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
        default:
            // Input Validation:
            cout << "Invalid item number. Please try again." << endl;
            i--; // Reset i to previous value to prevent the item being discarded
            break;
        }

        // Check if its a valid item number:
        if (itemNo > 0 && itemNo < 9)
        {
            // Calculations:
            grossTotal += itemPrice;                   // Add the item price to the gross total
            orderedItemNames[orderCount] = itemName;   // Add the item name to the ordered item names array
            orderedItemPrices[orderCount] = itemPrice; // Add the item price to the ordered item prices array
            orderCount++;                              // Increment the order count

            // Confirmation Message:
            cout << "Added " << itemName << " to your order." << endl;
            cout << endl;
        }
    }

    // Final Message (Gross total and ordered items):
    displayOrderSummary();
    cout << "Total Bill: R " << formatPrice(grossTotal) << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the gross total
    cout << endl;
}

void viewOrder()
{
    // Display the order summary if the user has ordered:
    if (hasOrdered)
    {
        displayOrderSummary();
        cout << "Total Bill: R " << formatPrice(grossTotal) << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the gross total
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the error message
    }
    cout << endl;
}

void cancelOrder()
{
    // Cancel the order if the user has ordered:
    if (hasOrdered)
    {
        // Simple confirmation of the user:
        int confirm = 0;

        cout << "Are you sure you want to cancel your order? (Enter '1' for Yes): ";
        cin >> confirm;

        // Resetting the order:
        if (confirm == 1)
        {
            grossTotal = 0;                     // Reset the gross total
            orderCount = 0;                     // Reset the order count
            for (int i = 0; i < MAX_ITEMS; i++) // Clear the ordered items arrays one by one
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

        cout << "Total Bill: R " << formatPrice(grossTotal) << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the gross total
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the error message
    }
    cout << endl;
}

void checkoutOrder()
{
    double netTotal = 0, discountAmount = 0;
    int confirmed1 = 0, confirmed2 = 0;

    // Check if the user has ordered:
    if (hasOrdered)
    {
        // Check if the user is applicable for the discount (Gross total over R 100):
        if (grossTotal >= DISCOUNT_THRESHOLD)
        {
            cout << "Hooray! You are applicable for our daily discount special!" << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Brief wait timer for the user to read the message

            // Calculations:
            discountAmount = grossTotal * DISCOUNT_RATE;
            netTotal = grossTotal - discountAmount;
            cout << "Discounted Amount: R " << formatPrice(discountAmount) << endl;
        }
        else
        {
            cout << "No discount is applied to your order. Too bad." << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Brief wait timer for the user to read the message
            netTotal = grossTotal;
        }

        displayOrderSummary();
        cout << "Final Bill: R " << formatPrice(netTotal) << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the final bill
        cout << endl;

        // Ask the user to write their details to CafeteriaBill.txt:
        cout << "Confirm transaction? Your bill and details will be written to a file called CafeteriaBill.txt (Enter '1' for Yes): ";
        cin >> confirmed1;
        cout << endl;

        if (confirmed1 == 1)
        {
            // Writing the details to the file:
            filesystem::path filePath = "CafeteriaBill.txt";
            ofstream outFile(filePath, ios::app); // Open in append mode

            if (outFile.is_open())
            {
                outFile << firstName << " " << lastName << ": R" << formatPrice(netTotal) << endl;
                outFile.close();
                cout << "Bill details have been written to CafeteriaBill.txt" << endl;
                cout << endl;
            }
            else
            {
                cout << "Unable to open file for writing." << endl;
            }

            // Ask the user to finish the program once the file has been written:
            cout << "Are you finished using this program? (Enter '1' for Yes): ";
            cin >> confirmed2;
            cout << endl;
            if (confirmed2 == 1)
            {
                cout << "Thank you for shopping at our university cafeteria!";
                continueRunning = endProgram();
            }
        }
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the message
    }
}

// Function to display the CLI menu:
void displayCLIMenu()
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
    cout << "Enter your choice (0-5): ";
    cin >> choice;
    cin.clear();
    cout << endl;
}

// Function to handle CLI menu choices:
void handleCLIMenu()
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
        checkoutOrder();
        break;
    case 0:
        continueRunning = endProgram(); // Program shouldn't be running
        break;
    default:
        // Input Validation:
        cout << "Invalid choice. Please enter a valid number from 0 to 5." << endl;
        cout << endl;
        break;
    }
}

// Main Procedure:
int main()
{
    // Welcome Message:
    cout << "--------------------------------------" << endl;
    cout << endl;
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
    cout << endl;

    // Main Loop of the program (CLI Menu):
    while (continueRunning) // Check if the program is meant to be running or not.
    {
        displayCLIMenu();
        handleCLIMenu();
    }

    cout << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the farewell message

    return 0;
}
