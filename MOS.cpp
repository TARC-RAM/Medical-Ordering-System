#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;
int option;
int order_option;
int item_id;

string itemCodes[] = {"A101", "A102", "A103", "A104", "A105", "A106", "A107", "A108", "A109", "A110"};
string itemNames[] = {"Bandages", "Syringes", "Gloves", "Masks", "Disinfectant", "Thermometer", "First Aid Kit", "Stethoscope", "Blood Pressure Monitor", "Wheelchair"};
double itemPrices[] = {5.00, 2.50, 3.00, 1.50, 4.00, 10.00, 15.00, 25.00, 30.00, 200.00};
int totalItems = 10; // number of products

// Cart functionality
string cartItemCodes[100];  // Store item codes in cart
string cartItemNames[100];  // Store item names in cart
double cartItemPrices[100]; // Store item prices in cart
int cartQuantities[100];    // Store quantities in cart
int cartItemCount = 0;      // Number of different items in cart

// Function to add item to cart
void addToCart(string code, string name, double price, int quantity) {
    // Check if item already exists in cart
    for (int i = 0; i < cartItemCount; i++) {
        if (cartItemCodes[i] == code) {
            cartQuantities[i] += quantity;  // Add to existing quantity
            cout << "Updated quantity in cart. Total quantity for " << name << ": " << cartQuantities[i] << endl;
            return;
        }
    }
    
    // Add new item to cart
    if (cartItemCount < 100) {  // Check cart capacity
        cartItemCodes[cartItemCount] = code;
        cartItemNames[cartItemCount] = name;
        cartItemPrices[cartItemCount] = price;
        cartQuantities[cartItemCount] = quantity;
        cartItemCount++;
        cout << "Item added to cart successfully!" << endl;
    } else {
        cout << "Cart is full! Cannot add more items." << endl;
    }
}

// Function to display cart contents
void displayCart() {
    if (cartItemCount == 0) {
        cout << "Your cart is empty." << endl;
        return;
    }
    
    cout << "\n========== YOUR CART ==========" << endl;
    cout << "Code  | Item Name             | Qty | Unit Price | Total" << endl;
    cout << "------|----------------------|-----|------------|-------" << endl;
    
    double grandTotal = 0;
    for (int i = 0; i < cartItemCount; i++) {
        double itemTotal = cartItemPrices[i] * cartQuantities[i];
        cout << cartItemCodes[i] << "  | " 
             << left << setw(20) << cartItemNames[i] << " | "
             << setw(3) << cartQuantities[i] << " | RM"
             << fixed << setprecision(2) << setw(8) << cartItemPrices[i] << " | RM"
             << setw(6) << itemTotal << endl;
        grandTotal += itemTotal;
    }
    
    cout << "==============================" << endl;
    cout << "GRAND TOTAL: RM" << fixed << setprecision(2) << grandTotal << endl;
    cout << "==============================" << endl << endl;
}

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
    
    do {
        cout << "Enter Item ID: ";
        cin >> code;

        bool found = false;
        int foundIndex = -1;

        // Search for the item
        for (int i = 0; i < totalItems; i++) {
            if (itemCodes[i] == code) {
                cout << "Item: " << itemNames[i] 
                     << " | Price: RM" << fixed << setprecision(2) << itemPrices[i] << endl;
                found = true;
                foundIndex = i;
                break;
            }
        }

        if (!found) {
            cout << "Item code not found.\n";
        } else {
            // Ask for quantity
            int quantity;
            cout << "Enter quantity: ";
            cin >> quantity;
            
            if (quantity <= 0) {
                cout << "Invalid quantity. Please enter a positive number.\n";
            } else {
                // Show item details with total price
                double totalPrice = itemPrices[foundIndex] * quantity;
                cout << "\nItem Details:" << endl;
                cout << "Item: " << itemNames[foundIndex] << endl;
                cout << "Unit Price: RM" << fixed << setprecision(2) << itemPrices[foundIndex] << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Total Price: RM" << fixed << setprecision(2) << totalPrice << endl;
                
                // Ask for confirmation
                char confirm;
                cout << "\nConfirm to add this item to cart? (Y/N): ";
                cin >> confirm;
                
                if (confirm == 'Y' || confirm == 'y') {
                    addToCart(itemCodes[foundIndex], itemNames[foundIndex], itemPrices[foundIndex], quantity);
                    
                    // Display current cart
                    displayCart();
                } else {
                    cout << "Item not added to cart." << endl;
                }
            }
        }
        
        cout << "\nAdd another item? (Y/N): ";
        cin >> continueOrder;
        cout << endl;
        
    } while (continueOrder == 'y' || continueOrder == 'Y');
    
    // Show final cart summary
    if (cartItemCount > 0) {
        cout << "\n========== FINAL ORDER SUMMARY ==========" << endl;
        displayCart();
        cout << "Thank you for your order!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } else {
        cout << "No items were added to cart." << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void mainmenu()	
{
	cout << "==========================" << endl << endl; 
	cout << "   MEDICAL SUPPLY ORDER   " << endl << endl;
	cout << "==========================" << endl << endl;
	

cout << "[1] Order    [2] History    [3] Exit\n\n";



	cout << "Please select an option (1-4): ";
	cin >> option;
}

int main()
{
	
	while(option != 4)
	{
		system("clear");
		mainmenu();

		if (option == 1)
		{
			system("clear");
			order_menu();

	    		if (order_option == 1)
			{
				place_order();

		    }
		}

	}

}