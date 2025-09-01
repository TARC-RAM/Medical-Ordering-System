#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;


const int MAX_ITEMS = 10;       
const int MAX_ORDER_ITEMS = 20; 
const double SERVICE_CHARGE = 0.05; 
const double TAX_RATE = 0.06;      
const double DISCOUNT_RATE = 0.10; // 10% discount for orders above RM100


const string itemCodes[MAX_ITEMS] = {"A101", "A102", "A103", "A104", "A105", 
                                    "A106", "A107", "A108", "A109", "A110"};
const string itemNames[MAX_ITEMS] = {"Bandages", "Syringes", "Gloves", "Masks", "Disinfectant", 
                                    "Thermometer", "First Aid Kit", "Stethoscope", 
                                    "Blood Pressure Monitor", "Wheelchair"};
const double itemPrices[MAX_ITEMS] = {5.00, 2.50, 3.00, 1.50, 4.00, 
                                    10.00, 15.00, 25.00, 30.00, 200.00};


struct OrderItem {
    string code;
    string name;
    double price;
    int quantity;
};


void displayWelcomeScreen();
void displayCatalog();
int placeOrder(OrderItem order[], int &orderCount);
void calculateTotal(OrderItem order[], int orderCount, double &subtotal, double &service, 
                   double &tax, double &discount, double &total);
void displayInvoice(OrderItem order[], int orderCount, double subtotal, double service, 
                   double tax, double discount, double total);
void processPayment(double total);
void displayReceipt(OrderItem order[], int orderCount, double subtotal, double service, 
                   double tax, double discount, double total, string paymentMethod, 
                   double amountPaid, double change);

int main() {
    OrderItem currentOrder[MAX_ORDER_ITEMS];
    int orderCount = 0;
    char continueOrder = 'Y';
    
    displayWelcomeScreen();
    
    while ((continueOrder == 'Y' || continueOrder == 'y') && orderCount < MAX_ORDER_ITEMS) {
        displayCatalog();
        orderCount = placeOrder(currentOrder, orderCount);
        
        if (orderCount < MAX_ORDER_ITEMS) {
            cout << "Would you like to add more items? (Y/N): ";
            cin >> continueOrder;
        } else {
            cout << "Maximum order items reached (" << MAX_ORDER_ITEMS << " items).\n";
        }
    }
    
    if (orderCount > 0) {
        double subtotal, service, tax, discount, total;
        calculateTotal(currentOrder, orderCount, subtotal, service, tax, discount, total);
        displayInvoice(currentOrder, orderCount, subtotal, service, tax, discount, total);
        processPayment(total);
    } else {
        cout << "No items were ordered. Thank you for visiting!\n";
    }
    
    return 0;
}

void displayWelcomeScreen() {
    cout << "========================================\n";
    cout << "   MEDICAL SUPPLIES ORDERING SYSTEM    \n";
    cout << "========================================\n\n";
}

void displayCatalog() {
    cout << "\nMEDICAL SUPPLIES CATALOG\n";
    cout << "-----------------------------------------------------------------\n";
    cout << left << setw(10) << "Code" << setw(25) << "Item" << setw(10) << "Price (RM)" << endl;
    cout << "-----------------------------------------------------------------\n";
    
    for (int i = 0; i < MAX_ITEMS; i++) {
        cout << left << setw(10) << itemCodes[i] 
             << setw(25) << itemNames[i] 
             << fixed << setprecision(2) << itemPrices[i] << endl;
    }
    cout << "-----------------------------------------------------------------\n\n";
}

int placeOrder(OrderItem order[], int &orderCount) {
    string code;
    int quantity;
    bool found = false;
    
    cout << "Enter Item Code: ";
    cin >> code;
    
    // Input validation for quantity
    do {
        cout << "Enter Quantity: ";
        cin >> quantity;
        if (quantity <= 0) {
            cout << "Quantity must be positive. Please try again.\n";
        }
    } while (quantity <= 0);
    
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemCodes[i] == code) {
            order[orderCount].code = code;
            order[orderCount].name = itemNames[i];
            order[orderCount].price = itemPrices[i];
            order[orderCount].quantity = quantity;
            orderCount++;
            
            cout << quantity << " x " << itemNames[i] << " added to order.\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Item code not found. Please check the catalog and try again.\n";
    }
    
    return orderCount;
}

void calculateTotal(OrderItem order[], int orderCount, double &subtotal, double &service, 
                  double &tax, double &discount, double &total) {
    subtotal = 0.0;
    

    for (int i = 0; i < orderCount; i++) {
        subtotal += order[i].price * order[i].quantity;
    }
    

    service = subtotal * SERVICE_CHARGE;
    

    tax = subtotal * TAX_RATE;
 
   
    discount = (subtotal > 100.00) ? subtotal * DISCOUNT_RATE : 0.0;
    
    total = subtotal + service + tax - discount;
}

void displayInvoice(OrderItem order[], int orderCount, double subtotal, double service, 
                   double tax, double discount, double total) {
    cout << "\n\nINVOICE\n";
    cout << "========================================\n";
    cout << left << setw(5) << "Qty" << setw(25) << "Item" 
         << setw(10) << "Price" << setw(10) << "Total" << endl;
    cout << "----------------------------------------\n";
    
    for (int i = 0; i < orderCount; i++) {
        cout << left << setw(5) << order[i].quantity 
             << setw(25) << order[i].name 
             << fixed << setprecision(2) << setw(10) << order[i].price 
             << "RM" << order[i].price * order[i].quantity << endl;
    }
    
    cout << "----------------------------------------\n";
    cout << right << setw(40) << "Subtotal: RM" << subtotal << endl;
    if (discount > 0) {
        cout << right << setw(40) << "Discount (10%): -RM" << discount << endl;
    }
    cout << right << setw(40) << "Service Charge (5%): RM" << service << endl;
    cout << right << setw(40) << "Tax (6%): RM" << tax << endl;
    cout << right << setw(40) << "TOTAL: RM" << total << endl;
    cout << "========================================\n\n";
}

void processPayment(double total) {
    char paymentMethod;
    double amountPaid;
    
    cout << "\nPAYMENT PROCESSING\n";
    cout << "Total Amount Due: RM" << fixed << setprecision(2) << total << endl;
    
 
    do {
        cout << "Payment Methods:\n";
        cout << "C - Cash\nD - Debit Card\nV - Credit Card\nE - E-Wallet\n";
        cout << "Select payment method: ";
        cin >> paymentMethod;
        paymentMethod = toupper(paymentMethod);
        
        if (paymentMethod != 'C' && paymentMethod != 'D' && 
            paymentMethod != 'V' && paymentMethod != 'E') {
            cout << "Invalid payment method. Please try again.\n";
        }
    } while (paymentMethod != 'C' && paymentMethod != 'D' && 
             paymentMethod != 'V' && paymentMethod != 'E');
    

    do {
        cout << "Enter amount paid: RM";
        cin >> amountPaid;
        
        if (amountPaid < total) {
            cout << "Amount paid is less than total. Please try again.\n";
        }
    } while (amountPaid < total);
    
    double change = amountPaid - total;

string method;
    switch (paymentMethod) {
        case 'C': method = "Cash"; break;
        case 'D': method = "Debit Card"; break;
        case 'V': method = "Credit Card"; break;
        case 'E': method = "E-Wallet"; break;
    }

cout << "\n\nPAYMENT RECEIPT\n";
    cout << "========================================\n";
    cout << "Total Amount: RM" << total << endl;
    cout << "Payment Method: " << method << endl;
    cout << "Amount Paid: RM" << amountPaid << endl;
    cout << "Change: RM" << change << endl;
    cout << "========================================\n";
    cout << "       THANK YOU FOR YOUR ORDER!       \n";
    cout << "========================================\n\n";
}