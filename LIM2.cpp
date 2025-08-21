#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>
using namespace std;

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
    cout << setfill('=') << setw(26) << "" << endl << endl;
    cout << "   MEDICAL SUPPLY ORDER   " << endl << endl;
	cout << setfill('=') << setw(26) << "" << endl << endl;
    cout << "[1] Order    [2] History    [3] Exit\n\n";

	cout << "Please select an option (1-3): ";
	cin >> option;
    cin.ignore(); 
}

void catalogue()
{
    cout << "Displaying Medical Supply Catalogue..\n";
	cout << "Item ID| Item Name             |Price(RM)" << endl; 
	cout << "A101   |Bandage                |5.00     " << endl;
	cout << "A102   |Syringe                |2.50     " << endl;
	cout << "A103   |Glove                  |3.00     " << endl;
	cout << "A104   |Mask                   |1.50     " << endl;
	cout << "A105   |Disinfectant           |4.00     " << endl;
	cout << "A106   |Thermometer            |10.00    " << endl;	
	cout << "A107   |First Aid Kit          |15.00    " << endl;
	cout << "A108   |Stethoscope            |25.00    " << endl;
	cout << "A109   |Blood Pressure Monitor |30.00    " << endl; 	
	cout << "A110   |Wheelchair             |200.00   " << endl << endl;

	cout << "[1] Order  [2] Main Menu: ";
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
    
    while ((continueOrder == 'Y' || continueOrder == 'y') && cart_count < 100) {
        cout << "Enter Item Code: ";
        cin >> code;
        
        // Input validation for quantity (from LIM's code) - ensures positive quantity
        do {
            cout << "Enter Quantity: ";
            cin >> quantity;
            if (quantity <= 0) {
                cout << "Quantity must be positive. Please try again.\n";
            }
        } while (quantity <= 0);
        
        bool found = false; //Search for the code. if not found keep looping until go through the whole list. If still not found then return "Item does not exist."
        
        for (int i = 0; i < 10; i++) {
            if (item_code[i] == code) {
                //Pull the item info based on its code
                cout << "Item: " << item_name[i] << " | Price: RM" << fixed << setprecision(2) << item_price[i] << endl;
                
                //Cart control
                cart[cart_count] = code;
                cart_qty[cart_count] = quantity;
                cart_count++;
                
                cout << quantity << " " << item_name[i] << " added to cart." << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Item code not found. Please check the catalog and try again.\n";
        }
        
        if (cart_count < 100) {
            cout << "Would you like to add more items? (Y/N): ";
            cin >> continueOrder;
        } else {
            cout << "Maximum order items reached (100 items).\n";
        }
    }
}

// Modified checkout function with invoice display
double checkout()
{
    double subtotal = 0.0;
    int totalItems = 0;
    
    cout << "\n===============================================================\n";
    cout << "                      INVOICE SUMMARY                         \n";
    cout << "===============================================================\n\n";
    cout << left << setfill(' ') << setw(4) << "No"
        << setw(22) << "Product"
        << right << setw(8) << "Qty"
        << setw(14) << "Unit Price"
        << setw(14) << "Total (RM)" << endl;
    cout << "---------------------------------------------------------------\n";
    
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
                
                cout << left << setw(4) << itemNumber++
                    << setw(22) << item_name[j]
                    << right << setw(8) << cart_qty[i]
                    << setw(14) << fixed << setprecision(2) << item_price[j]
                    << setw(14) << itemTotal << endl;
                break;
            }
        }
    }
    
    double serviceCharge = subtotal * SERVICE_CHARGE_PERCENT;
    double tax = subtotal * TAX_PERCENT;
    double total = subtotal + serviceCharge + tax - DISCOUNT_AMOUNT;
    
    cout << "---------------------------------------------------------------\n";
    cout << right << setw(48) << "Subtotal:" << setw(14) << subtotal << endl;
    cout << right << setw(48) << "Service Charge (5%):" << setw(14) << serviceCharge << endl;
    cout << right << setw(48) << "Tax (6%):" << setw(14) << tax << endl;
    cout << right << setw(48) << "Discount:" << setw(14) << -DISCOUNT_AMOUNT << endl;
    cout << "---------------------------------------------------------------\n";
    cout << right << setw(48) << "TOTAL PAYABLE:" << setw(14) << total << endl;
    cout << "===============================================================\n";
    cout << "Total Items: " << totalItems << endl;
    
    return total;
}

// Payment processing function
PaymentInfo processPayment(double total) {
    char method;
    double paidAmount;
    
    do {
        cout << "\n===========================================================\n";
        cout << "             MEDICAL SUPPLIES PAYMENT METHOD               \n";
        cout << "===========================================================\n";
        cout << "|               Available payment method                  |\n";
        cout << "+---------------------------------------------------------+\n";
        cout << "| W - eWallet                                             |\n";
        cout << "| C - Credit Card                                         |\n";
        cout << "| D - Debit Card                                          |\n";
        cout << "| H - Cash                                                |\n";
        cout << "+---------------------------------------------------------+\n";
        cout << "\nSelect payment method (W/C/D/H): ";
        cin >> method;
        method = toupper(method);
        if (method != 'W' && method != 'C' && method != 'D' && method != 'H') {
            cout << "\nInvalid input. Please try again.\n";
        }
    } while (method != 'W' && method != 'C' && method != 'D' && method != 'H');
    
    do {
        cout << fixed << setprecision(2);
        cout << "Payment amount: RM ";
        cin >> paidAmount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }
        if (paidAmount < total) {
            cout << "Insufficient amount. Please try again.\n";
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
                    
                    cout << "\nPayment successful!" << endl;
                    cout << "Change: RM" << fixed << setprecision(2) << payment.change << endl;
                    cout << "Thank you for your purchase!" << endl;
                    cout << "\nPress Enter to return to main menu..." << endl;
                    cin.ignore();
                    cin.get();
                    system("clear");
                } 
                else 
                {
                    cout << "No items in cart. Press Enter to return to main menu." << endl;
                }
            }
        }

    } while (option != 3);

    return 0;
}