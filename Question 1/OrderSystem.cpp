// (My Documentation Placeholder)

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Item object:
struct Item
{
    int no;
    string name;
    double price;
};

// My global variables
Item orderedItems[25];
string firstName, lastName;
int choice, orderCount = 0, grossTotal = 0;
bool continueRunning = true, hasOrdered = false; // Variable used to check if the program is still running

// Global menu array:
const int menuSize = 8;
const Item menu[menuSize] = {
    {1, "Coffee", 15.00},
    {2, "Sandwich", 30.00},
    {3, "Salad", 25.00},
    {4, "Juice", 10.00},
    {5, "Muffin", 20.00},
    {6, "Pizza Slice", 35.00},
    {7, "Soup", 18.00},
    {8, "Burger", 40.00}};

// Function to end the program:
bool endProgram()
{
    cout << endl;
    cout << "Thank you for using the Cafeteria Order System, " << firstName << " " << lastName << "! Have a great day!" << endl;
    return false;
}

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
        cout << i + 1 << ". Item " << orderedItems[i].no << ": " << orderedItems[i].name << " - R " << orderedItems[i].price << ".00" << endl;
        cout << endl;
    }
    cout << endl;
}

// Function to display the item menu:
void viewMenu()
{
    // Item menu table:
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
        cout << "Continue? (Enter '1' to continue): ";
        cin >> done;
        cin.clear();
    } while (done != 1);
}

// Function to place an order:
void placeOrder(const Item menu[], int menuSize)
{
    int amountOrdered, itemNo;

    if (hasOrdered)
    {
        int returnChoice;
        cout << "It seems that you have already added an order before. Do you want to add more items? (Enter '1' for yes): ";
        cin >> returnChoice;
        if (returnChoice != 1)
        {
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
        cout << "Choose the amount of items you want to purchase (25 items max): ";
        cin >> amountOrdered;
        cout << endl;
    } while (amountOrdered > 25);

    // Loop to buy the items according to the specified amount:
    for (int i = 1; i <= amountOrdered; i++)
    {
        cout << endl;
        cout << "Choose the item no. " << i << " that you want to purchase (Enter '0' to display the item menu again): ";
        cin >> itemNo;
        cin.clear();
        cout << endl;

        // Display the menu again at the user's request:
        if (itemNo == 0)
        {
            viewMenu();
            i--; // Reset i to previous value to prevent the item being discarded
            continue;
        }

        // Input Validation:
        if (itemNo < 0 || itemNo > menuSize)
        {
            cout << "Invalid item number. Please try again." << endl;
            i--; // Reset i to previous value to prevent the item being discarded
            continue;
        }

        cout << endl;
        // Calculation of gross total and adding the item to the current order array:
        grossTotal += menu[itemNo - 1].price;
        orderedItems[orderCount++] = menu[itemNo - 1]; // Add the ordered item to the array
        cout << "Added " << menu[itemNo - 1].name << " to your order." << endl;
        cout << endl;
    }

    // Final Message (Gross total and ordered items):
    displayOrderSummary();
    cout << "Total Bill: R " << grossTotal << ".00" << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the gross total
    cout << endl;
}

void viewOrder()
{
    if (hasOrdered)
    {
        displayOrderSummary();
        cout << "Total Bill: R " << grossTotal << ".00" << endl;
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
    if (hasOrdered)
    {
        // Simple confirmation of the user:
        int confirm = 0;

        cout << "Are you sure you want to cancel your order? (Enter '1' for Yes): ";
        cin >> confirm;
        cin.clear();

        // Reset:
        if (confirm == 1)
        {
            grossTotal = 0;              // Reset the gross total
            orderCount = 0;              // Reset the order count
            for (int i = 0; i < 25; i++) // Clear the orderedItems array
            {
                orderedItems[i] = Item{0, "", 0.0};
            }
            cout << endl;
            cout << "Order cancelled. Your order summary has been cleared." << endl;
            cout << endl;
            hasOrdered = false;
        }
        else // No reset:
        {
            cout << endl;
            cout << "Order cancellation aborted." << endl;
            cout << endl;
        }

        cout << "Total Bill: R " << grossTotal << ".00" << endl;
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
    int netTotal = 0, confirmed = 0, discountAmount;
    const double discountThreshold = 100.00, discountRate = 0.10;

    // Check if there is an order before
    if (hasOrdered)
    {
        if (grossTotal > discountThreshold)
        {
            cout << "Hooray! You are appllicable for our daily discount special!" << endl;
            cout << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Brief wait timer for the user to read the discount message
            discountAmount = grossTotal * discountRate;
            netTotal = grossTotal - discountAmount;
            cout << endl;
            cout << "Discounted Amount: R " << discountAmount << ".00" << endl;
        }
        else
        {
            cout << "No discount is applied to your order. Too bad." << endl;
            cout << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Brief wait timer for the user to read the discount message
            netTotal = grossTotal;
        }

        cout << endl;
        displayOrderSummary();
        cout << "Final Bill: R " << netTotal << ".00" << endl;
        cout << endl;
        this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the net total

        // Ask the user to write their details to CafeteriaBill.txt:
        cout << "Confirm transaction? Your bill and details will be written to a file called CafeteriaBill.txt (Enter '1' for Yes):" << endl;
        cin >> confirmed;
        cout << endl;
        if (confirmed == 1)
        {
            // Writing the details to the file:
            //  (Writing to a file goes here)

            confirmed = 0; // Reuse the same variable for the second question

            // Ask the user to finish the program once the file has been written:
            cout << "Are you finished using this program? (Enter '1' for Yes):" << endl;
            cin >> confirmed;
            cout << endl;
            if (confirmed == 1)
            {
                cout << "Thank you for shopping at our university cafeteria!";
                continueRunning = endProgram();
            }
        }
    }
    else
    {
        cout << "You need to place an order first, silly!" << endl;
        cout << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Brief wait timer for the user to read the error message
    }
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
    cout << "Enter your choice (0-5): ";
    cin >> choice;
    cin.clear();
    cout << endl;
}

// Function to handle CLI menu choices:
void handleCLIMenuChoice(int choice, const Item menu[], int menuSize)
{
    switch (choice)
    {
    case 1:
        viewMenu();
        break;
    case 2:
        placeOrder(menu, menuSize);
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
    cout << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Wait timer to simulate waiting for the program

    // Main Loop of the program (CLI Menu):
    while (continueRunning) // Check if the program is meant to be running or not.
    {
        displayCLIMenu(choice);
        handleCLIMenuChoice(choice, menu, menuSize);
    }

    cout << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the farewell message

    return 0;
}
