#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string CheckCoupon(string code, const string* coupon);
string MakeReceipt(const string* products, const int* prices, const int* quantity, int n, bool discount);

int main(){
    // Variables
    string products[5] = {"Milk", "Bread", "Eggs", "Cheese", "Butter"};
    string coupon[5] = {"F05GT", "G05GT", "H05GT", "I05GT", "J05GT"};
    int prices[5] = {5, 5, 3, 6, 3};
    int quantity[5] = {0, 0, 0, 0, 0};
    int total = 0;
    int choice = 0;

    // Welcome GUI
    cout << "=============================" << endl;
    cout << "Store System v2.0" << endl;
    cout << "=============================" << endl;
    cout << "Here is a list of our products: " << endl;
    for(int i = 0; i < 5; i++){
        cout << i + 1 << ". " << products[i] << " - $" << prices[i] << endl;
    }
    cout << endl;
    cout << "Please enter the number of the product you would like to buy" << endl;
    cout << "=============================" << endl;
    cout << "Enter 0 to checkout" << endl;
    cout << "=============================" << endl;

    while(true){
        cout << "Enter Option: ";
        cin >> choice;

        if(choice == 0){
        cout << "=============================" << endl;
        cout << "Here is your receipt: " << endl;
        cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
        cout << "=============================" << endl;
        cout << "Please enter your coupon code: ";
        string code;
        cin >> code;
        cout << "=============================" << endl;
        string IsValid = CheckCoupon(code, coupon);
        if(IsValid == "Valid"){
            cout << "Here is your receipt with discount: " << endl;
            cout << MakeReceipt(products, prices, quantity, 5, true) << endl;
        } else {
            cout << "Your coupon is " << IsValid << endl;
            cout << "Here is your receipt without discount: " << endl;
            cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
        }
        cout << "Thank you for shopping with us!" << endl;
        cout << "=============================" << endl;
        break;
    } else {
        cout << "How many " << products[choice - 1] << " would you like to buy: ";
        cin >> quantity[choice - 1];
        cout << "=============================" << endl;
        cout << "You have added " << quantity[choice - 1] << " " << products[choice - 1] << " to your cart" << endl;
        cout << "=============================" << endl;
    }
}
    return 0;
}

// Checking if a coupon is valid
string CheckCoupon(string code, const string* coupon){
    int length = 5;
    for(int i = 0; i < length; i++){
        if(code == coupon[i]){
            return "Valid";
        }
    }
    return "Invalid";
}

// Making a receipt
string MakeReceipt(const string* products, const int* prices, const int* quantity, int n, bool discount) {
    string receipt = "";
    int total = 0;
    for(int i = 0; i < n; i++) {
        if(quantity[i] > 0) {
            receipt += products[i] + " - " + to_string(quantity[i]) + " - $" + to_string(prices[i] * quantity[i]) + "\n";
            if(discount){
                receipt += "Discount - 10%\n";
                total += prices[i] * quantity[i] * 0.9;
            }else{
                total += prices[i] * quantity[i];
            }
        }
    }
    receipt += "Total - $" + to_string(total) + "\n";
    return receipt;
}
