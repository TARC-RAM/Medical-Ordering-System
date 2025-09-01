#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

// 兼容清屏
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Global variables
int option = 0;   // ✅ 必须初始化
int order_option;
int item_id;

string itemCodes[] = { "A101", "A102", "A103", "A104", "A105", "A106", "A107", "A108", "A109", "A110" };
string itemNames[] = { "Bandages", "Syringes", "Gloves", "Masks", "Disinfectant", "Thermometer", "First Aid Kit", "Stethoscope", "Blood Pressure Monitor", "Wheelchair" };
double itemPrices[] = { 5.00, 2.50, 3.00, 1.50, 4.00, 10.00, 15.00, 25.00, 30.00, 200.00 };
int totalItems = 10;

// Order related variables
const double SERVICE_CHARGE = 0.05; // 5% service charge
const double TAX_RATE = 0.06;       // 6% tax

// Structure to hold order items
struct OrderItem
{
    string code;
    string name;
    double price;
    int quantity;
    double total;
};

OrderItem currentOrder[10];
int orderItemCount = 0;
double orderSubtotal = 0.0;
double orderTotal = 0.0;

// Function prototypes
void order_menu();
void place_order();
void catalogue();
void mainmenu();
void display_invoice();
void display_receipt(double paymentAmount, double change, string paymentMethod);
void process_payment();
void clear_order();

void order_menu()
{
    cout << "Displaying Medical Supply Catalogue..\n";
    cout << "Item ID| Item Name             |Price(RM)" << endl;
    cout << "A101   |Bandages               |5.00     " << endl;
    cout << "A102   |Syringes               |2.50     " << endl;
    cout << "A103   |Gloves                 |3.00     " << endl;
    cout << "A104   |Masks                  |1.50     " << endl;
    cout << "A105   |Disinfectant           |4.00     " << endl;
    cout << "A106   |Thermometer            |10.00    " << endl;
    cout << "A107   |First Aid Kit          |15.00    " << endl;
    cout << "A108   |Stethoscope            |25.00    " << endl;
    cout << "A109   |Blood Pressure Monitor |30.00    " << endl;
    cout << "A110   |Wheelchair             |200.00   " << endl << endl;

    cout << "[1] Order  [2] Main Menu: ";
    cin >> order_option;
}

void place_order()
{
    string code;
    char continueOrder;
    orderItemCount = 0;
    orderSubtotal = 0.0;

    do {
        cout << "Enter Item ID: ";
        cin >> code;

        bool found = false;
        int itemIndex = -1;

        for (int i = 0; i < totalItems; i++) {
            if (itemCodes[i] == code) {
                found = true;
                itemIndex = i;
                break;
            }
        }

        if (found) {
            int quantity;
            cout << "Item: " << itemNames[itemIndex] << " | Price: RM" << itemPrices[itemIndex] << endl;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity > 0) {
                currentOrder[orderItemCount].code = itemCodes[itemIndex];
                currentOrder[orderItemCount].name = itemNames[itemIndex];
                currentOrder[orderItemCount].price = itemPrices[itemIndex];
                currentOrder[orderItemCount].quantity = quantity;
                currentOrder[orderItemCount].total = itemPrices[itemIndex] * quantity;

                orderSubtotal += currentOrder[orderItemCount].total;
                orderItemCount++;

                cout << "Item added to order!\n";
            }
            else {
                cout << "Invalid quantity!\n";
            }
        }
        else {
            cout << "Item code not found.\n";
        }

        cout << "\nDo you want to add another item? (y/n): ";
        cin >> continueOrder;
        cout << endl;

    } while ((continueOrder == 'y' || continueOrder == 'Y') && orderItemCount < 10);

    if (orderItemCount > 0) {
        display_invoice();
        process_payment();
    }
}

void display_invoice()
{
    system(CLEAR);
    cout << "==============================================\n";
    cout << "                  INVOICE                    \n";
    cout << "==============================================\n";
    cout << "MEDICAL SUPPLY ORDERING SYSTEM\n";
    cout << "Tel: 03-1234-5678\n";
    cout << "----------------------------------------------\n";
    cout << left << setw(5) << "No" << setw(20) << "Item"
        << setw(8) << "Qty" << setw(10) << "Price" << setw(12) << "Total(RM)" << endl;
    cout << "----------------------------------------------\n";

    for (int i = 0; i < orderItemCount; i++) {
        cout << left << setw(5) << i + 1
            << setw(20) << currentOrder[i].name
            << setw(8) << currentOrder[i].quantity
            << fixed << setprecision(2) << setw(10) << currentOrder[i].price
            << setw(12) << currentOrder[i].total << endl;
    }

    double serviceCharge = orderSubtotal * SERVICE_CHARGE;
    double tax = orderSubtotal * TAX_RATE;
    orderTotal = orderSubtotal + serviceCharge + tax;

    cout << "----------------------------------------------\n";
    cout << right << setw(43) << "Subtotal: RM" << setw(8) << orderSubtotal << endl;
    cout << right << setw(43) << "Service Charge (5%): RM" << setw(8) << serviceCharge << endl;
    cout << right << setw(43) << "Tax (6%): RM" << setw(8) << tax << endl;
    cout << right << setw(43) << "Total Amount: RM" << setw(8) << orderTotal << endl;
    cout << "==============================================\n";
}

void process_payment()
{
    char paymentChoice;
    double paymentAmount;

    cout << "\nSelect payment method:\n";
    cout << "C - Cash\n";
    cout << "D - Debit Card\n";
    cout << "Credit Card (not available)\n";
    cout << "Enter payment method (C/D): ";
    cin >> paymentChoice;

    if (toupper(paymentChoice) == 'C') {
        cout << "Enter payment amount: RM";
        cin >> paymentAmount;

        while (paymentAmount < orderTotal) {
            cout << "Insufficient amount! Please enter at least RM" << orderTotal << ": ";
            cin >> paymentAmount;
        }

        double change = paymentAmount - orderTotal;
        cout << "Change: RM" << fixed << setprecision(2) << change << endl;

        cout << "\nPress Enter to generate receipt...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        display_receipt(paymentAmount, change, "Cash");
    }
    else if (toupper(paymentChoice) == 'D') {
        cout << "Debit card payment processed successfully.\n";
        cout << "\nPress Enter to generate receipt...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        display_receipt(orderTotal, 0.0, "Debit Card");
    }
    else {
        cout << "Invalid payment method! Using cash.\n";
        cout << "Enter payment amount: RM";
        cin >> paymentAmount;

        while (paymentAmount < orderTotal) {
            cout << "Insufficient amount! Please enter at least RM" << orderTotal << ": ";
            cin >> paymentAmount;
        }

        double change = paymentAmount - orderTotal;
        cout << "Change: RM" << fixed << setprecision(2) << change << endl;

        cout << "\nPress Enter to generate receipt...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        display_receipt(paymentAmount, change, "Cash");
    }
}

void display_receipt(double paymentAmount, double change, string paymentMethod)
{
    system(CLEAR);
    cout << "==============================================\n";
    cout << "                  RECEIPT                    \n";
    cout << "==============================================\n";
    cout << "MEDICAL SUPPLY ORDERING SYSTEM\n";
    cout << "Tel: 03-1234-5678\n";
    cout << "----------------------------------------------\n";
    cout << left << setw(5) << "No" << setw(20) << "Item"
        << setw(8) << "Qty" << setw(10) << "Price" << setw(12) << "Total(RM)" << endl;
    cout << "----------------------------------------------\n";

    for (int i = 0; i < orderItemCount; i++) {
        cout << left << setw(5) << i + 1
            << setw(20) << currentOrder[i].name
            << setw(8) << currentOrder[i].quantity
            << fixed << setprecision(2) << setw(10) << currentOrder[i].price
            << setw(12) << currentOrder[i].total << endl;
    }

    double serviceCharge = orderSubtotal * SERVICE_CHARGE;
    double tax = orderSubtotal * TAX_RATE;

    cout << "----------------------------------------------\n";
    cout << right << setw(43) << "Subtotal: RM" << setw(8) << orderSubtotal << endl;
    cout << right << setw(43) << "Service Charge: RM" << setw(8) << serviceCharge << endl;
    cout << right << setw(43) << "Tax: RM" << setw(8) << tax << endl;
    cout << right << setw(43) << "Total: RM" << setw(8) << orderTotal << endl;
    cout << right << setw(43) << "Payment Method: " << paymentMethod << endl;
    cout << right << setw(43) << "Payment Amount: RM" << setw(8) << paymentAmount << endl;
    if (change > 0) {
        cout << right << setw(43) << "Change: RM" << setw(8) << change << endl;
    }
    cout << "==============================================\n";
    cout << "        Thank you for your purchase!         \n";
    cout << "==============================================\n";

    cout << "\nPress Enter to return to main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    clear_order();
}

void clear_order()
{
    orderItemCount = 0;
    orderSubtotal = 0.0;
    orderTotal = 0.0;
}
void catalogue()
{
    cout << "Displaying Medical Supply Catalogue..\n";
    cout << "Item ID| Item Name             |Price(RM)" << endl;
    cout << "A101   |Bandages               |5.00     " << endl;
    cout << "A102   |Syringes               |2.50     " << endl;
    cout << "A103   |Gloves                 |3.00     " << endl;
    cout << "A104   |Masks                  |1.50     " << endl;
    cout << "A105   |Disinfectant           |4.00     " << endl;
    cout << "A106   |Thermometer            |10.00    " << endl;
    cout << "A107   |First Aid Kit          |15.00    " << endl;
    cout << "A108   |Stethoscope            |25.00    " << endl;
    cout << "A109   |Blood Pressure Monitor |30.00    " << endl;
    cout << "A110   |Wheelchair             |200.00   " << endl << endl;

    cout << "Press Enter to return to the main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mainmenu()
{
    cout << "==========================" << endl << endl;
    cout << "   MEDICAL SUPPLY ORDER   " << endl << endl;
    cout << "==========================" << endl << endl;

    cout << "[1] Catalogue    [2] Order    [3] History    [4] Exit\n\n";
    cout << "Please select an option (1-4): ";
    cin >> option;
}

int main()
{
    while (option != 4)
    {
        system(CLEAR);
        mainmenu();

        if (option == 1)
        {
            system(CLEAR);
            catalogue();
        }
        else if (option == 2)
        {
            system(CLEAR);
            order_menu();

            if (order_option == 1)
            {
                system(CLEAR);
                place_order();
            }
        }
        else if (option == 3)
        {
            system(CLEAR);
            cout << "Order History feature coming soon...\n";
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    cout << "Thank you for using Medical Supply Order System!\n";
    return 0;
}