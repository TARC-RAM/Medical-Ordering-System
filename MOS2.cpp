#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

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
    cin.ignore(); 
}

void order()
{
    //Clear cart after previous order
    cart_count = 0;

    //This part handles the ordering of items
    string code;

    //This part decides to end the order or to continue it
    char ContinueOrder;

    //This part holds the quantity of the item
    int quantity;

    do 
    {
        cout << "Enter Item Code: ";
        cin >> code;
        cin.ignore();
        bool found = false; //Search for the code. if not found keep looping until go through the whole list. If still not found then return "Item does not exist."
    for (int i = 0; i < 10; i++)
    {
        if (item_code[i] == code)
        {
            //Pull the item info based on its code
            cout << "Item: " << item_name[i] << " | Price: RM" << fixed << setprecision(2) << item_price[i] << endl;
            
            //Ask for Quantity
            cout << "Enter Quantity: ";
            cin >> quantity;
            cin.ignore(); //clear buffer for next input

            //Cart control
            cart[cart_count] = code;
            cart_qty[cart_count] = quantity;
            cart_count++;


            cout << quantity << " " << item_name[i] << " added to cart." << endl;
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "Item code not found. Try again.\nPress ENTER to return to main menu.";
        cin.get();
        cout << endl;
    }
        cout << "Would you like to add another item? (Y/N): ";
        cin >> ContinueOrder;
        cin.ignore();
    } while(ContinueOrder == 'Y' || ContinueOrder == 'y');
}

void checkout()
{
    cout << setfill('=') << setw(26) << "" << endl << endl;
    cout << "  YOUR CART  " << endl;
    cout << setfill('=') << setw(26) << "" << endl << endl;

    for (int i = 0; i < cart_count; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (item_code[j] == cart[i])
            {
                cout << cart[i]<< cart_qty[i]<< item_price[j] * cart_qty[i] << endl;
            }
        }
    }
}
int main()
{
    do
    {
        mainmenu();

        if (option == 1)
        {
            catalogue();

            if(order_option == 1)
            {
                order();
                if (cart_count > 0) 
                {
                    checkout();
                } 
                else 
                {
                    cout << "No items in cart. Press Enter to return to main menu." << endl;
                    cin.get();
                }
            }
        }

    } while (option != 3);

    return 0;
}