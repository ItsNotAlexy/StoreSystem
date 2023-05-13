#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>

using namespace std;

int GetUserBalance();
string ExtractFromReciept(const string &ReceiptVar);
string SetUserBalance(int NewBalance);
string Withdraw(int WithdrawAmount);
string Deposit(int DepositAmount);
string CheckCoupon(string code, const string *coupon);
string MakeReceipt(const string *products, const int *prices, const int *quantity, int n, bool discount);

int main()
{
    string products[5] = {"Milk", "Bread", "Eggs", "Cheese", "Butter"};
    string coupon[2] = {"SMARICCI2HEBAT", "SMARICCI2"};
    int prices[5] = {5, 5, 3, 6, 3};
    int quantity[5] = {0, 0, 0, 0, 0};
    int total = 0;
    int choice = 0;

    cout << "=============================" << endl;
    cout << "Store System v2.0" << endl;
    cout << "=============================" << endl;
    cout << "Press 0 for exit" << endl;
    cout << "Press 9 for ATM" << endl;
    cout << "Press 8 for product list" << endl;
    cout << "=============================" << endl;

    while (true)
    {
        cout << "Enter Option: ";
        cin >> choice;

        if (choice == 8)
        {
            system("cls");

            cout << "=============================" << endl;
            cout << "Here is the product list: " << endl;
            cout << "=============================" << endl;
            for (int i = 0; i < 5; i++)
            {
                cout << i + 1 << ". " << products[i] << " - $" << prices[i] << endl;
            }
            cout << "=============================" << endl;
            int ProductChoice = -1;

            while (ProductChoice != 0)
            {
                cout << "Please select a product: ";
                cin >> ProductChoice;

                if (ProductChoice == 0)
                {
                    cout << "=============================" << endl;
                    cout << "Here is your receipt: " << endl;
                    cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
                    cout << "=============================" << endl;
                    cout << "Please enter your coupon code: ";
                    string code;
                    cin >> code;
                    cout << "=============================" << endl;
                    string IsValid = CheckCoupon(code, coupon);
                    if (IsValid == "Valid")
                    {
                        cout << "Here is your receipt with discount: " << endl;
                        cout << MakeReceipt(products, prices, quantity, 5, true) << endl;
                    }
                    else
                    {
                        cout << "Your coupon is " << IsValid << endl;
                        cout << "Here is your receipt without discount: " << endl;
                        cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
                    }

                    string ReceiptVar = MakeReceipt(products, prices, quantity, 5, false);
                    string Total = ExtractFromReciept(ReceiptVar);
                    int StringToInt = stoi(Total);

                    if (GetUserBalance() < StringToInt)
                    {
                        cout << "You have insufficient funds!" << endl;
                        cout << "All items have been removed from your cart" << endl;
                        return 0;
                    }
                    else
                    {
                        SetUserBalance(GetUserBalance() - StringToInt);
                        cout << "Processing payment..." << endl;
                        Sleep(2000);
                        cout << "Payment successful! Your new balance is $" << GetUserBalance() << endl;
                        cout << "=============================" << endl;
                        return 0;
                    }

                    return 0;
                }
                else if (ProductChoice > 5)
                {
                    cout << "Invalid product, please try again" << endl;
                    cout << "=============================" << endl;
                }
                else
                {
                    cout << "How many " << products[ProductChoice - 1] << " would you like to buy: ";
                    cin >> quantity[ProductChoice - 1];
                    cout << "=============================" << endl;
                    cout << "You have added " << quantity[ProductChoice - 1] << " " << products[ProductChoice - 1] << " to your cart" << endl;
                    cout << "=============================" << endl;
                }
            }
        }
        if (choice == 9)
        {
            system("cls");

            cout << "=============================" << endl;
            cout << "Welcome to the ATM" << endl;
            cout << "=============================" << endl;
            cout << "Please enter your pin: ";
            int pin;
            cin >> pin;
            cout << "=============================" << endl;
            while (pin != 1234)
            {
                cout << "Invalid pin, please try again: ";
                cin >> pin;
                cout << "=============================" << endl;
            }
            while (pin == 1234)
            {
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
                if (AtmOption == "withdraw")
                {
                    system("cls");

                    int WithdrawAmount;
                    cout << "How much would you like to withdraw: ";
                    cin >> WithdrawAmount;

                    string WithdrawStatus = Withdraw(WithdrawAmount);
                    if (WithdrawStatus == "Success")
                    {
                        balance -= WithdrawAmount;
                        cout << "Your new balance is $" << balance << endl;
                        cout << "=============================" << endl;
                    }
                    else
                    {
                        cout << "Your withdrawal was " << WithdrawStatus << endl;
                        cout << "=============================" << endl;
                    }
                }
                else if (AtmOption == "deposit")
                {
                    system("cls");

                    int DepositAmount;
                    cout << "How much would you like to deposit: ";
                    cin >> DepositAmount;

                    string DepositStatus = Deposit(DepositAmount);
                    if (DepositStatus == "Success")
                    {
                        balance += DepositAmount;
                        cout << "Your new balance is $" << balance << endl;
                        cout << "=============================" << endl;
                    }
                    else
                    {
                        cout << "Your deposit was " << DepositStatus << endl;
                        cout << "=============================" << endl;
                    }
                }
                else if (AtmOption == "check-balance")
                {
                    system("cls");

                    cout << "Your balance is $" << balance << endl;
                    cout << "=============================" << endl;
                }
                else if (AtmOption == "pay")
                {
                    system("cls");

                    int PayAmount;
                    cout << "How much would you like to pay: ";
                    cin >> PayAmount;

                    string IntToString = to_string(PayAmount);

                    if (PayAmount > GetUserBalance())
                    {
                        cout << "You do not have enough money to pay!" << endl;
                        cout << "=============================" << endl;
                    }
                    else if (!all_of(IntToString.begin(), IntToString.end(), ::isdigit))
                    {
                        cout << "Invalid amount" << endl;
                        cout << "=============================" << endl;
                    }
                    else
                    {
                        SetUserBalance(GetUserBalance() - GetUserBalance());
                        cout << "Processing payment..." << endl;
                        Sleep(2000);
                        cout << "Payment successful! Your new balance is $" << GetUserBalance() << endl;
                        cout << "=============================" << endl;
                    }
                }
                else if (AtmOption == "exit")
                {
                    system("cls");

                    cout << "Thank you for using the ATM" << endl;
                    cout << "=============================" << endl;
                    break;
                }
            }
        }
        else
        {
            if (choice == 0)
            {
                cout << "Exiting..." << endl;
                Sleep(2000);
                break;
            }
            else
            {
                cout << "Invalid option, please try again" << endl;
            }
        }
    }
    return 0;
}

string CheckCoupon(string code, const string *coupon)
{
    int length = 5;
    for (int i = 0; i < length; i++)
    {
        if (code == coupon[i])
        {
            return "Valid";
        }
    }
    return "Invalid";
}

string MakeReceipt(const string *products, const int *prices, const int *quantity, int n, bool discount)
{
    string receipt = "";
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        if (quantity[i] > 0)
        {
            receipt += products[i] + " - " + to_string(quantity[i]) + " - $" + to_string(prices[i] * quantity[i]) + "\n";
            if (discount)
            {
                receipt += "Discount - 10%\n";
                total += prices[i] * quantity[i] * 0.9;
            }
            else
            {
                total += prices[i] * quantity[i];
            }
        }
    }
    receipt += "Total - $" + to_string(total) + "\n";
    return receipt;
}

string ExtractFromReciept(const string &ReceiptVar)
{
    string Total = "";
    int length = ReceiptVar.length();
    for (int i = 0; i < length; i++)
    {
        if (ReceiptVar[i] == 'T' && ReceiptVar[i + 1] == 'o' && ReceiptVar[i + 2] == 't' && ReceiptVar[i + 3] == 'a' && ReceiptVar[i + 4] == 'l')
        {
            for (int j = i + 8; j < length; j++)
            {
                if (ReceiptVar[j] == '\n')
                {
                    break;
                }
                else
                {
                    Total += ReceiptVar[j];
                }
            }
        }
    }
    Total.erase(0, 1);
    return Total;
}

int Bankbalance = 1000;

int GetUserBalance()
{
    return Bankbalance;
}

string SetUserBalance(int NewBalance)
{
    if (NewBalance < 0)
    {
        return "Unsuccess";
    }
    else
    {
        Bankbalance = NewBalance;
        return "Success";
    }
}

string Withdraw(int WithdrawAmount)
{
    if (WithdrawAmount > GetUserBalance())
    {
        return "Unsuccess";
    }
    else
    {
        SetUserBalance(GetUserBalance() - WithdrawAmount);
        return "Success";
    }
}

string Deposit(int DepositAmount)
{
    SetUserBalance(GetUserBalance() + DepositAmount);
    return "Success";
}
