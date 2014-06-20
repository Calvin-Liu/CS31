//
//  main.cpp
//  Royalty
//
//  Created by Calvin Liu on 10/11/12.
//  Copyright (c) 2012 Calvin Liu. All rights reserved.
//
//I ordered it so I have the displays and the inputs come up first and then based on the person's input, I put what error messages should come up next. I put return 0 at the end of each error so that the program would stop at that point and it would terminate. The next lines are about calculations and how the arithmetic is calculated and it would determine the math based on if it is  premium item or not. The arithmetic is also matched to how many units were sold. At the end of the pogram I put another return 0 to signify that the program should terminate. 

#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Units sold: ";
    double unitsSold;
    cin >> unitsSold;
    cin.ignore(10000, '\n');
    
    cout << "Title: ";
    string title;
    getline (cin, title);
    
    cout << "Sales price: ";
    double salesPrice;
    cin >> salesPrice;
  
    cout << "Expense: ";
    double expense;
    cin >> expense;
    cin.ignore(10000, '\n');
    
    cout << "Premium item? (y/n) ";
    string premiumitem;
    getline (cin, premiumitem);
    
    cout << "---" << endl;
    
    cout.setf(ios::fixed);
    cout.precision(2);
    if (title == "")
        {
        cout << "You must enter a title.";
            return 0;
        }
    if (unitsSold < 0)
        {
        cout << "The units sold must be nonnegative.";
            return 0;
        }
    else if (expense < 0)
        {
        cout << "The expense must be nonnegative.";
            return 0;
        }
    else if (salesPrice < expense)
        {
        cout << "The sales price must not be less than the expense.";
            return 0;
        }
    
    
    if (premiumitem != "y" && premiumitem != "n")
        {
        cout << "You must enter y or n.";
            return 0;
        }
    else if (unitsSold > 0 && unitsSold <= 300)
        cout << title << " earned $" << (salesPrice - expense) * .08 * unitsSold << " in royalties." << endl;
    else if (unitsSold > 300 && unitsSold <= 1000)
        {if (premiumitem == "y")
            cout << title << " earned $" << (salesPrice - expense) * .14 * (unitsSold - 300) + ((salesPrice - expense) * .08 * 300) << " in royalties." << endl;
        else if (premiumitem == "n")
            cout << title << " earned $" << (salesPrice - expense) * .11 * (unitsSold - 300) + ((salesPrice - expense) * .08 * 300) << " in royalties." << endl;
        }
    if (unitsSold > 1000)
        {if (premiumitem == "n")
            cout << title << " earned $" << (salesPrice - expense) * .14 * (unitsSold - 1000) + (.11 * (salesPrice - expense) * 700) + (.08 * (salesPrice - expense) * 300) << " in royalties." << endl;
        else if (premiumitem == "y")
            cout << title << " earned $" << (salesPrice - expense) * .14 * (unitsSold - 1000) + (.14 * (salesPrice - expense) * 700) + (.08 * (salesPrice - expense) * 300) << " in royalties." << endl;
        }
    
    return 0;
}
