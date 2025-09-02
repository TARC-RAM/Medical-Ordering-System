#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>
using namespace std;

// ANSI Color Codes for better UI
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

// Background Colors
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

// Transaction history arrays
string transaction_dates[10];
double transaction_totals[10];
int transaction_item_counts[10];
int transaction_index = 0;
int total_transactions = 0;

// Constants for invoice calculations
const double SERVICE_CHARGE_PERCENT = 0.05;
const double TAX_PERCENT = 0.06;
const double DISCOUNT_AMOUNT = 10.00;

int option;
int order_option;

//Using arrays to search for item name and price
string item_name[10] = { "Bandages", "Syringes", "Gloves", "Masks", "Disinfectant", "Thermometer", "First Aid Kit", "Stethoscope", "Blood Pressure Monitor", "Wheelchair" };
string item_code[10] = { "A101", "A102", "A103", "A104", "A105", "A106", "A107", "A108", "A109", "A110" };
double item_price[10] = { 5.00, 2.50, 3.00, 1.50, 4.00, 10.00, 15.00, 25.00, 30.00, 200.00 };

//Using arrays to create a cart function to hold the type and amount of items
string cart[100];
int cart_qty[100];
int cart_count = 0;

// Payment structure
struct PaymentInfo {
    char method;
    double paidAmount;
    double change;
};

void mainmenu()
{
    cout << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << "       MEDICAL SUPPLY ORDER SYSTEM" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(86) << "" << BLUE << "+---------------------------+" << RESET << endl;
    cout << setfill(' ') << setw(86) << "" << WHITE << BOLD << "|      MAIN MENU OPTIONS    |" << RESET << endl;
    cout << setfill(' ') << setw(86) << "" << BLUE << "+---------------------------+" << RESET << endl;
    cout << setfill(' ') << setw(86) << "" << GREEN << BOLD << "| [1] Order  [2] Reports    |" << RESET << endl;
    cout << setfill(' ') << setw(86) << "" << GREEN << BOLD << "|        [3] Exit           |" << RESET << endl;
    cout << setfill(' ') << setw(86) << "" << BLUE << "+---------------------------+" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(85) << "" << BOLD << WHITE << "Please select an option (1-3): " << RESET;
    cin >> option;
    cin.ignore();
}

void catalogue()
{
    cout << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << "         MEDICAL SUPPLY CATALOGUE         " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(78) << "" << CYAN << "+--------+----------------------+-----------+" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << WHITE << BOLD << "| Item ID|      Item Name       |Price (RM) |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << CYAN << "+--------+----------------------+-----------+" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A101  | Bandages             |   5.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A102  | Syringes             |   2.50    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A103  | Gloves               |   3.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A104  | Masks                |   1.50    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A105  | Disinfectant         |   4.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A106  | Thermometer          |  10.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A107  | First Aid Kit        |  15.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A108  | Stethoscope          |  25.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A109  | Blood Pressure Mon.  |  30.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << GREEN << "|  A110  | Wheelchair           | 200.00    |" << RESET << endl;
    cout << setfill(' ') << setw(78) << "" << CYAN << "+--------+----------------------+-----------+" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(87) << "" << BLUE << "+-------------------------+" << RESET << endl;
    cout << setfill(' ') << setw(87) << "" << YELLOW << BOLD << "| [1] Order [2] Main Menu |" << RESET << endl;
    cout << setfill(' ') << setw(87) << "" << BLUE << "+-------------------------+" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(87) << "" << BOLD << WHITE << "Please select an option (1-2): " << RESET;
    cin >> order_option;
    cout << endl;
    cin.ignore();
}

void order()
{
    //Clear cart after previous order
    cart_count = 0;

    //This part handles the ordering of items
    string code;

    //This part decides to end the order or to continue it
    char continueOrder = 'Y';
    char addToCart = 'N';

    //This part holds the quantity of the item
    int quantity;

    cout << endl;
    cout << setfill(' ') << setw(87) << "" << GREEN << BOLD << "=============================" << RESET << endl;
    cout << setfill(' ') << setw(87) << "" << YELLOW << BOLD << "       ORDERING SYSTEM       " << RESET << endl;
    cout << setfill(' ') << setw(87) << "" << GREEN << BOLD << "=============================" << RESET << endl;
    cout << endl;

    while ((continueOrder == 'Y' || continueOrder == 'y') && cart_count < 100) {
        bool found = false;

        // Keep asking for item code until a valid one is entered or user wants to quit
        while (!found) {
            cout << setfill(' ') << setw(87) << "" << CYAN << BOLD << "Enter Item Code: " << RESET;
            cin >> code;

            // Search for the code
            do {
                for (int i = 0; i < 10; i++) {
                    if (item_code[i] == code) {
                        //Display item info first
                        cout << setfill(' ') << setw(87) << "" << GREEN << BOLD << "Item: " << RESET << item_name[i] << GREEN << " | Price: " << fixed << setprecision(2) << RESET << "RM " << item_price[i] << RESET << endl;

                        // Ask if user wants to add to cart
                        cout << setfill(' ') << setw(87) << "" << YELLOW << BOLD << "Do you want to add this item to cart? (Y/N): " << RESET;
                        cin >> addToCart;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (addToCart == 'Y' || addToCart == 'y') {
                            // Enhanced input validation for quantity with proper error handling
                            do {
                                cout << setfill(' ') << setw(87) << "" << CYAN << BOLD << "Enter Quantity: " << RESET;
                                cin >> quantity;
                                
                                // Check if cin failed (non-numeric input)
                                if (cin.fail()) {
                                    cin.clear(); // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                                    cout << setfill(' ') << setw(86) << "" << RED << BOLD << " Invalid input. Please enter a valid number." << RESET << endl;
                                    quantity = -1; // Set to invalid value to continue loop
                                } else if (quantity <= 0) {
                                    cout << setfill(' ') << setw(87) << "" << RED << BOLD << "Quantity must be positive. Please try again." << RESET << endl;
                                }
                            } while (quantity <= 0);

                            //Cart control
                            cart[cart_count] = code;
                            cart_qty[cart_count] = quantity;
                            cart_count++;

                            cout << setfill(' ') << setw(87) << "" << BLUE << BOLD << quantity << " " << item_name[i] << " added to cart." << RESET << endl;
                        }

                        found = true;
                        break;
                    }
                }
            } while (addToCart != 'Y' && addToCart != 'y' && addToCart != 'N' && addToCart != 'n');

            if (!found) {
                cout << setfill(' ') << setw(87) << "" << RED << BOLD << "Item code not found. Please check the catalog and try again." << RESET << endl;
                cout << endl;
            }
        }

        if (cart_count < 100) {
            // Input validation for continue order prompt
            do {
                cout << setfill(' ') << setw(87) << "" << YELLOW << BOLD << "Would you like to add a different items? (Y/N): " << RESET;
                cin >> continueOrder;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Convert to uppercase for easier comparison
                continueOrder = toupper(continueOrder);

                if (continueOrder != 'Y' && continueOrder != 'N') {
                    cout << setfill(' ') << setw(91) << "" << RED << BOLD << "Invalid input. Please enter Y or N only." << RESET << endl;
                }
            } while (continueOrder != 'Y' && continueOrder != 'N');
        }
        else {
            cout << setfill(' ') << setw(91) << "" << YELLOW << BOLD << "Maximum order items reached (100 items)." << RESET << endl;
        }
        cout << endl;
    }
}

// Modified checkout function with invoice display
double checkout()
{
    system("cls");
    double subtotal = 0.0;
    int totalItems = 0;

    cout << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================================" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << "                     INVOICE SUMMARY                      " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================================" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(80) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << WHITE << BOLD << "| No |      Product         | Qty |Unit Price|Total(RM) |" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;

    int itemNumber = 1;
    for (int i = 0; i < cart_count; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (item_code[j] == cart[i])
            {
                double itemTotal = item_price[j] * cart_qty[i];
                subtotal += itemTotal;
                totalItems += cart_qty[i];

                cout << setfill(' ') << setw(80) << "" << GREEN << "| " << setw(2) << itemNumber++
                    << " | " << left << setw(20) << item_name[j]
                    << " | " << right << setw(3) << cart_qty[i]
                    << " | " << setw(8) << fixed << setprecision(2) << item_price[j]
                    << " | " << setw(8) << itemTotal << " |" << RESET << endl;
                break;
            }
        }
    }

    double serviceCharge = subtotal * SERVICE_CHARGE_PERCENT;
    double tax = subtotal * TAX_PERCENT;
    double total = subtotal + serviceCharge + tax - DISCOUNT_AMOUNT;

    cout << setfill(' ') << setw(80) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << WHITE << right << setw(45) << "Subtotal:" << setw(10) << subtotal << " " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << WHITE << right << setw(45) << "Service Charge (5%):" << setw(10) << serviceCharge << " " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << WHITE << right << setw(45) << "Tax (6%):" << setw(10) << tax << " " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << GREEN << right << setw(45) << "Discount:" << setw(10) << -DISCOUNT_AMOUNT << " " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << right << setw(45) << "TOTAL PAYABLE:" << setw(10) << total << " " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================================" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << BLUE << BOLD << "Total Items: " << totalItems << RESET << endl;
    cout << endl;

    // Save transaction to history
    transaction_dates[transaction_index] = "Transaction " + to_string(total_transactions + 1);
    transaction_totals[transaction_index] = total;
    transaction_item_counts[transaction_index] = totalItems;

    transaction_index = (transaction_index + 1) % 10;
    total_transactions++;

    return total;
}

void displayReports()
{
    cout << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl; //41
    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << "          TRANSACTION HISTORY           " << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << endl;

    if (total_transactions == 0) {
        cout << setfill(' ') << setw(90) << "" << RED << BOLD << "No transactions found" << RESET << endl;
        cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
        cout << setfill(' ') << setw(80) << "" << WHITE << BOLD << "Press Enter to return to main menu..." << RESET;
        cin.get();
        return;
    }

    int displayCount = (total_transactions < 10) ? total_transactions : 10;
    int startIndex;

    if (total_transactions < 10) {
        startIndex = 0;
    }
    else {
        startIndex = transaction_index;
    }

    cout << setfill(' ') << setw(73) << "" << CYAN << "+----------------------+-------------+----------------+" << RESET << endl; //55
    cout << setfill(' ') << setw(73) << "" << WHITE << BOLD << "|     Transaction      | Total Items | Total (RM)    |" << RESET << endl;
    cout << setfill(' ') << setw(73) << "" << CYAN << "+----------------------+-------------+----------------+" << RESET << endl;

    for (int i = 0; i < displayCount; i++) {
        int currentIndex = (startIndex + i) % 10;
        cout << setfill(' ') << setw(73) << "" << GREEN << "| " << left << setw(20) << transaction_dates[currentIndex]
            << " | " << right << setw(11) << transaction_item_counts[currentIndex]
            << " | " << setw(13) << fixed << setprecision(2) << transaction_totals[currentIndex] << " |" << RESET << endl;
    }

    cout << setfill(' ') << setw(73) << "" << CYAN << "+----------------------+-------------+---------------+" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << WHITE << BOLD << "Press Enter to return to main menu..." << RESET;
    cin.get();
}

// Payment processing function
PaymentInfo processPayment(double total) {
    char method;
    double paidAmount;

    do {
        cout << endl;
        cout << setfill(' ') << setw(89) << "" << BLUE << BOLD << "=======================================" << RESET << endl;
        cout << setfill(' ') << setw(89) << "" << YELLOW << BOLD << "        PAYMENT METHOD SELECTION        " << RESET << endl;
        cout << setfill(' ') << setw(89) << "" << BLUE << BOLD << "=======================================" << RESET << endl;
        cout << endl; //39

        cout << setfill(' ') << setw(91) << "" << CYAN << "+---------------------------------+" << RESET << endl; //35
        cout << setfill(' ') << setw(91) << "" << WHITE << BOLD << "|    Available Payment Methods    |" << RESET << endl;
        cout << setfill(' ') << setw(91) << "" << CYAN << "+---------------------------------+" << RESET << endl;
        cout << setfill(' ') << setw(91) << "" << GREEN << "| W - eWallet                     |" << RESET << endl;
        cout << setfill(' ') << setw(91) << "" << GREEN << "| C - Credit Card                 |" << RESET << endl;
        cout << setfill(' ') << setw(91) << "" << GREEN << "| D - Debit Card                  |" << RESET << endl;
        cout << setfill(' ') << setw(91) << "" << GREEN << "| H - Cash                        |" << RESET << endl;
        cout << setfill(' ') << setw(91) << "" << CYAN << "+---------------------------------+" << RESET << endl;
        cout << endl;

        cout << setfill(' ') << setw(91) << "" << BOLD << YELLOW << "Select payment method (W/C/D/H): " << RESET;
        cin >> method;
        method = toupper(method);
        if (method != 'W' && method != 'C' && method != 'D' && method != 'H') {
            cout << setfill(' ') << setw(91) << "" << RED << BOLD << "Invalid input. Please try again." << RESET << endl;
        }
    } while (method != 'W' && method != 'C' && method != 'D' && method != 'H');

    do {
        cout << fixed << setprecision(2);
        cout << setfill(' ') << setw(91) << "" << BOLD << GREEN << "Payment amount: RM " << RESET;
        cin >> paidAmount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(91) << "" << RED << BOLD << "Invalid input. Please enter a valid number." << RESET << endl;
            continue;
        }
        if (paidAmount < total) {
            cout << setfill(' ') << setw(91) << "" << YELLOW << BOLD << "Insufficient amount. Please try again." << RESET << endl;
        }
    } while (cin.fail() || paidAmount < total);

    double change = paidAmount - total;
    return PaymentInfo{ method, paidAmount, change };
}

int main()
{
    do
    {
        system("cls");
        mainmenu();

        if (option == 1)
        {
            system("cls");
            catalogue();

            if (order_option == 1)
            {
                order();
                if (cart_count > 0)
                {
                    double total = checkout();
                    PaymentInfo payment = processPayment(total);

                    cout << endl;
                    cout << setfill(' ') << setw(91) << "" << GREEN << BOLD << "=============================" << RESET << endl;
                    cout << setfill(' ') << setw(91) << "" << YELLOW << BOLD << "     PAYMENT SUCCESSFUL!     " << RESET << endl;
                    cout << setfill(' ') << setw(91) << "" << GREEN << BOLD << "=============================" << RESET << endl;
                    cout << endl;
                    cout << setfill(' ') << setw(91) << "" << BLUE << BOLD << "Change: RM" << fixed << setprecision(2) << payment.change << RESET << endl;
                    cout << setfill(' ') << setw(91) << "" << MAGENTA << BOLD << "Thank you for your purchase!" << RESET << endl;
                    cout << endl;
                    cout << setfill(' ') << setw(91) << "" << WHITE << BOLD << "Press Enter to return to main menu..." << RESET << endl;
                    cin.ignore();
                    cin.get();
                    system("cls");
                }
                else
                {
                    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << "No items in cart. Press Enter to return to main menu." << RESET;
                    cin.get();
                }
            }
        }
        else if (option == 2)
        {
            system("cls");
            displayReports();
            system("cls");
        }

    } while (option != 3);

    cout << endl;
    cout << setfill(' ') << setw(80) << "" << CYAN << BOLD << "=========================================" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << YELLOW << BOLD << "          THANK YOU & GOODBYE!!" << RESET << endl;
    cout << setfill(' ') << setw(80) << "" << CYAN << BOLD << "=========================================" << RESET << endl;
    cout << endl;

    return 0;
}