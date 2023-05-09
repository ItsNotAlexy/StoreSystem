#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// Function Prototypes
int GetUserBalance();
void SetUserBalance(int balance);
string Withdraw(int amount);
string Deposit(int amount);
string Pay(int total);
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
    cout << "Store System v3.0" << endl;
    cout << "=============================" << endl;
    cout << "Press 9 for ATM" << endl;
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
            // Checkout
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
            // Automatic payment
            string PaymentStatus = Pay(total);
            
            if(PaymentStatus == "Success"){
                cout << "Your payment was successful" << endl;
            } else {
                cout << "Your payment was " << PaymentStatus << endl;
                break;
            }

            cout << "Thank you for shopping with us!" << endl;
            cout << "=============================" << endl;
            break;
        }
        if(choice == 9){
            // ATM
            system("cls");

            cout << "=============================" << endl;
            cout << "Welcome to the ATM" << endl;
            cout << "=============================" << endl;
            cout << "Please enter your pin: ";
            int pin;
            cin >> pin;
            cout << "=============================" << endl;
            while(pin != 1234){
                cout << "Invalid pin, please try again: ";
                cin >> pin;
                cout << "=============================" << endl;
            }
            while(pin == 1234){
                system("cls");

                int balance = GetUserBalance();
                cout << "Your balance is $" << balance << endl;
                cout << "=============================" << endl;
                string AtmOption;

                cout << "Please select an option: " << endl;
                cout << "- Withdraw" << endl;
                cout << "- Deposit" << endl;
                cout << "- Check Balance" << endl;
                cout << "- Pay" << endl;
                cout << "- Exit" << endl;
                cout << "=============================" << endl;
                cout << "Enter Option: ";
                cin >> AtmOption;

                cout << "=============================" << endl;
                if(AtmOption == "withdraw"){
                    system("cls");

                    int WithdrawAmount;
                    cout << "How much would you like to withdraw: ";
                    cin >> WithdrawAmount;

                    string WithdrawStatus = Withdraw(WithdrawAmount);
                    if(WithdrawStatus == "Success"){
                        balance -= WithdrawAmount;
                        cout << "Your new balance is $" << balance << endl;
                        cout << "=============================" << endl;
                    } else {
                        cout << "Your withdrawal was " << WithdrawStatus << endl;
                        cout << "=============================" << endl;
                    }
                }
                else if(AtmOption == "deposit"){
                    system("cls");

                    int DepositAmount;
                    cout << "How much would you like to deposit: ";
                    cin >> DepositAmount;

                    string DepositStatus = Deposit(DepositAmount);
                    if(DepositStatus == "Success"){
                        balance += DepositAmount;
                        cout << "Your new balance is $" << balance << endl;
                        cout << "=============================" << endl;
                    } else {
                        cout << "Your deposit was " << DepositStatus << endl;
                        cout << "=============================" << endl;
                    }
                }
                else if(AtmOption == "check-balance"){
                    system("cls");

                    cout << "Your balance is $" << balance << endl;
                    cout << "=============================" << endl;
                }
                else if(AtmOption == "pay"){
                    system("cls");

                    int PayAmount;
                    cout << "How much would you like to pay: ";
                    cin >> PayAmount;

                    string PayStatus = Pay(PayAmount);
                    if(PayStatus == "Success"){
                        balance -= PayAmount;
                        cout << "Your new balance is $" << balance << endl;
                        cout << "=============================" << endl;
                    } else {
                        cout << "Your payment was " << PayStatus << endl;
                        cout << "=============================" << endl;
                    }
                }
                else if(AtmOption == "exit"){
                    system("cls");

                    cout << "Thank you for using the ATM" << endl;
                    cout << "=============================" << endl;
                    break;
                }
            }
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

// Balance Variable
int Bankbalance = 1000;

int GetUserBalance(){
    return Bankbalance;
}

void SetUserBalance(int balance){
    Bankbalance = balance;
}

// ATM Functions

string Withdraw(int amount){
    if(amount > GetUserBalance()){
        return "Insufficient Funds";
    } else {
        SetUserBalance(GetUserBalance() - amount);
        return "Success";
    }
}

string Deposit(int amount){
    SetUserBalance(GetUserBalance() + amount);
    return "Success";
}

string Pay(int total){
    if(total > GetUserBalance()){
        return "Insufficient Funds";
    } else {
        SetUserBalance(GetUserBalance() - total);
        return "Success";
    }
}
