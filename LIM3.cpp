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

// Constants for invoice calculations
const double SERVICE_CHARGE_PERCENT = 0.05;
const double TAX_PERCENT = 0.06;
const double DISCOUNT_AMOUNT = 10.00;

int option;
int order_option;

//Using arrays to search for item name and price
string item_name[10] = {"Bandages", "Syringes", "Gloves", "Masks", "Disinfectant", "Thermometer", "First Aid Kit", "Stethoscope", "Blood Pressure Monitor", "Wheelchair"};
string item_code[10] = {"A101", "A102", "A103", "A104", "A105", "A106", "A107", "A108", "A109", "A110"};
double item_price[10] = {5.00, 2.50, 3.00, 1.50, 4.00, 10.00, 15.00, 25.00, 30.00, 200.00};

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
    cout << setfill(' ') << setw(40) << "" << CYAN << BOLD << "=================================" << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << YELLOW << BOLD << "   MEDICAL SUPPLY ORDER SYSTEM   " << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << CYAN << BOLD << "=================================" << RESET << endl;
    cout << endl;
    
    cout << setfill(' ') << setw(40) << "" << BLUE << "+---------------------------+" << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << WHITE << BOLD << "|      MAIN MENU OPTIONS    |" << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << BLUE << "+---------------------------+" << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << GREEN << BOLD << "| [1] Order    [2] History  |" << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << GREEN << BOLD << "|        [3] Exit           |" << RESET << endl;
    cout << setfill(' ') << setw(40) << "" << BLUE << "+---------------------------+" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(40) << "" << BOLD << WHITE << "Please select an option (1-3): " << RESET;
    cin >> option;
    cin.ignore(); 
}

void catalogue()
{
    cout << endl;
    cout << setfill(' ') << setw(35) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << setfill(' ') << setw(35) << "" << YELLOW << BOLD << "       MEDICAL SUPPLY CATALOGUE         " << RESET << endl;
    cout << setfill(' ') << setw(35) << "" << MAGENTA << BOLD << "=========================================" << RESET << endl;
    cout << endl;
    
    cout << setfill(' ') << setw(30) << "" << CYAN  << "+--------+----------------------+-----------+" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << WHITE << BOLD << "| Item ID|      Item Name       |Price (RM) |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << CYAN  << "+--------+----------------------+-----------+" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A101  | Bandages             |   5.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A102  | Syringes             |   2.50    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A103  | Gloves               |   3.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A104  | Masks                |   1.50    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A105  | Disinfectant         |   4.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A106  | Thermometer          |  10.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A107  | First Aid Kit        |  15.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A108  | Stethoscope          |  25.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A109  | Blood Pressure Mon.  |  30.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << GREEN << "|  A110  | Wheelchair           | 200.00    |" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << CYAN  << "+--------+----------------------+-----------+" << RESET << endl;
    cout << endl;

    cout << setfill(' ') << setw(38) << "" << BLUE << "+-------------------------+" << RESET << endl;
    cout << setfill(' ') << setw(38) << "" << YELLOW << BOLD << "| [1] Order [2] Main Menu |" << RESET << endl;
    cout << setfill(' ') << setw(38) << "" << BLUE << "+-------------------------+" << RESET << endl;
    cout << endl;
    
    cout << setfill(' ') << setw(40) << "" << BOLD << WHITE << "Select option: " << RESET;
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

    //This part holds the quantity of the item
    int quantity;
    
    cout << endl;
    cout << setfill(' ') << setw(38) << "" << GREEN << BOLD << "=============================" << RESET << endl;
    cout << setfill(' ') << setw(38) << "" << YELLOW << BOLD << "       ORDERING SYSTEM       " << RESET << endl;
    cout << setfill(' ') << setw(38) << "" << GREEN << BOLD << "=============================" << RESET << endl;
    cout << endl;
    
    while ((continueOrder == 'Y' || continueOrder == 'y') && cart_count < 100) {
        cout << setfill(' ') << setw(40) << "" << CYAN << BOLD << "Enter Item Code: " << RESET;
        cin >> code;
        
        // Input validation for quantity (from LIM's code) - ensures positive quantity
        do {
            cout << setfill(' ') << setw(40) << "" << CYAN << BOLD << "Enter Quantity: " << RESET;
            cin >> quantity;
            if (quantity <= 0) {
                cout << setfill(' ') << setw(35) << "" << RED << BOLD << "Quantity must be positive. Please try again." << RESET << endl;
            }
        } while (quantity <= 0);
        
        bool found = false; //Search for the code. if not found keep looping until go through the whole list. If still not found then return "Item does not exist."
        
        for (int i = 0; i < 10; i++) {
            if (item_code[i] == code) {
                //Pull the item info based on its code
                cout << setfill(' ') << setw(30) << "" << GREEN << BOLD << "Item: " << item_name[i] << " | Price: RM" << fixed << setprecision(2) << item_price[i] << RESET << endl;
                
                //Cart control
                cart[cart_count] = code;
                cart_qty[cart_count] = quantity;
                cart_count++;
                
                cout << setfill(' ') << setw(35) << "" << BLUE << BOLD << quantity << " " << item_name[i] << " added to cart." << RESET << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << setfill(' ') << setw(30) << "" << RED << BOLD << "Item code not found. Please check the catalog and try again." << RESET << endl;
        }
        
        if (cart_count < 100) {
            cout << setfill(' ') << setw(35) << "" << YELLOW << BOLD << "Would you like to add more items? (Y/N): " << RESET;
            cin >> continueOrder;
        } else {
            cout << setfill(' ') << setw(35) << "" << YELLOW << BOLD << "Maximum order items reached (100 items)." << RESET << endl;
        }
        cout << endl;
    }
}

// Modified checkout function with invoice display
double checkout()
{
    system("clear");
    double subtotal = 0.0;
    int totalItems = 0;
    
    cout << endl;
    cout << setfill(' ') << setw(30) << "" << MAGENTA << BOLD << "===============================================" << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << YELLOW << BOLD << "               INVOICE SUMMARY                 " << RESET << endl;
    cout << setfill(' ') << setw(30) << "" << MAGENTA << BOLD << "===============================================" << RESET << endl;
    cout << endl;
    
    cout << setfill(' ') << setw(25) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << WHITE << BOLD << "| No |      Product         | Qty |Unit Price|Total(RM) |" << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    
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
                
                cout << setfill(' ') << setw(25) << "" << GREEN << "| " << setw(2) << itemNumber++
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
    
    cout << setfill(' ') << setw(25) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << WHITE << right << setw(45) << "Subtotal:" << setw(10) << subtotal << " " << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << WHITE << right << setw(45) << "Service Charge (5%):" << setw(10) << serviceCharge << " " << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << WHITE << right << setw(45) << "Tax (6%):" << setw(10) << tax << " " << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << GREEN << right << setw(45) << "Discount:" << setw(10) << -DISCOUNT_AMOUNT << " " << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << CYAN << "+----+----------------------+-----+----------+----------+" << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << YELLOW << BOLD << right << setw(45) << "TOTAL PAYABLE:" << setw(10) << total << " " << RESET << endl;
    cout << setfill(' ') << setw(25) << "" << MAGENTA << BOLD << "===============================================" << RESET << endl;
    cout << setfill(' ') << setw(35) << "" << BLUE << BOLD << "Total Items: " << totalItems << RESET << endl;
    cout << endl;
    
    return total;
}

// Payment processing function
PaymentInfo processPayment(double total) {
    char method;
    double paidAmount;
    
    do {
        cout << endl;
        cout << setfill(' ') << setw(32) << "" << BLUE << BOLD << "=======================================" << RESET << endl;
        cout << setfill(' ') << setw(32) << "" << YELLOW << BOLD << "        PAYMENT METHOD SELECTION        " << RESET << endl;
        cout << setfill(' ') << setw(32) << "" << BLUE << BOLD << "=======================================" << RESET << endl;
        cout << endl;
        
        cout << setfill(' ') << setw(30) << "" << CYAN << "+---------------------------------+" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << WHITE << BOLD << "|    Available Payment Methods    |" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << CYAN << "+---------------------------------+" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << GREEN << "| W - eWallet                     |" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << GREEN << "| C - Credit Card                 |" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << GREEN << "| D - Debit Card                  |" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << GREEN << "| H - Cash                        |" << RESET << endl;
        cout << setfill(' ') << setw(30) << "" << CYAN << "+---------------------------------+" << RESET << endl;
        cout << endl;
        
        cout << setfill(' ') << setw(35) << "" << BOLD << YELLOW << "Select payment method (W/C/D/H): " << RESET;
        cin >> method;
        method = toupper(method);
        if (method != 'W' && method != 'C' && method != 'D' && method != 'H') {
            cout << setfill(' ') << setw(35) << "" << RED << BOLD << "Invalid input. Please try again." << RESET << endl;
        }
    } while (method != 'W' && method != 'C' && method != 'D' && method != 'H');
    
    do {
        cout << fixed << setprecision(2);
        cout << setfill(' ') << setw(40) << "" << BOLD << GREEN << "Payment amount: RM " << RESET;
        cin >> paidAmount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(30) << "" << RED << BOLD << "Invalid input. Please enter a valid number." << RESET << endl;
            continue;
        }
        if (paidAmount < total) {
            cout << setfill(' ') << setw(35) << "" << YELLOW << BOLD << "Insufficient amount. Please try again." << RESET << endl;
        }
    } while (cin.fail() || paidAmount < total);
    
    double change = paidAmount - total;
    return PaymentInfo{ method, paidAmount, change };
}

int main()
{
    do
    {
        mainmenu();

        if (option == 1)
        {   system("clear");
            catalogue();

            if(order_option == 1)
            {
                order();
                if (cart_count > 0) 
                {
                    double total = checkout();
                    PaymentInfo payment = processPayment(total);
                    
                    cout << endl;
                    cout << setfill(' ') << setw(35) << "" << GREEN << BOLD << "=============================" << RESET << endl;
                    cout << setfill(' ') << setw(35) << "" << YELLOW << BOLD << "     PAYMENT SUCCESSFUL!     " << RESET << endl;
                    cout << setfill(' ') << setw(35) << "" << GREEN << BOLD << "=============================" << RESET << endl;
                    cout << endl;
                    cout << setfill(' ') << setw(40) << "" << BLUE << BOLD << "Change: RM" << fixed << setprecision(2) << payment.change << RESET << endl;
                    cout << setfill(' ') << setw(35) << "" << MAGENTA << BOLD << "Thank you for your purchase!" << RESET << endl;
                    cout << endl;
                    cout << setfill(' ') << setw(30) << "" << WHITE << BOLD << "Press Enter to return to main menu..." << RESET << endl;
                    cin.ignore();
                    cin.get();
                    system("clear");
                } 
                else 
                {
                    cout << setfill(' ') << setw(30) << "" << YELLOW << BOLD << "No items in cart. Press Enter to return to main menu." << RESET << endl;
                }
            }
        }

    } while (option != 3);
    
    cout << endl;
    cout << setfill(' ') << setw(35) << "" << CYAN << BOLD << "=============================" << RESET << endl;
    cout << setfill(' ') << setw(35) << "" << YELLOW << BOLD << "   THANK YOU & GOODBYE!   " << RESET << endl;
    cout << setfill(' ') << setw(35) << "" << CYAN << BOLD << "=============================" << RESET << endl;
    cout << endl;

    return 0;
}
