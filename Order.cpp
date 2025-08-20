#include <iostream>
#include <string>
using namespace std;

string itemCodes[] = {"A101", "A102", "A103", "A104", "A105", "A106", "A107", "A108", "A109", "A110"};
string itemNames[] = {"Bandages", "Syringes", "Gloves", "Masks", "Disinfectant", "Thermometer", "First Aid Kit", "Stethoscope", "Blood Pressure Monitor", "Wheelchair"};
double itemPrices[] = {5.00, 2.50, 3.00, 1.50, 4.00, 10.00, 15.00, 25.00, 30.00, 200.00};
int totalItems = 10; // number of products

void place_order()
{
    string code;
    cout << "Enter Item ID: ";
    cin >> code;

    bool found = false;

    for (int i = 0; i < totalItems; i++) {
        if (itemCodes[i] == code) {
            cout << "Item: " << itemNames[i] 
                 << " | Price: RM" << itemPrices[i] << endl;
            found = true;
            break; // stop searching once found
        }
    }

    if (!found) {
        cout << "Item code not found.\n";
    }
}

int main()
{
    place_order();
}