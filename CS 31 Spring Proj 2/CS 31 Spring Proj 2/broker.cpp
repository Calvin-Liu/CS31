//
//  main.cpp
//  CS 31 Spring Proj 2
//
//  Created by Calvin on 4/13/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    string buyOrSell;                       //buying or selling?
    cout << "Buy or sell (b/s): ";
    getline(cin, buyOrSell);
    if(buyOrSell != "b" && buyOrSell != "s") //check to see if the input is correct
    {
        cout << "---" << endl;
        cout << "You must enter b or s";
        return 0;
    }
    
    double shares; 
    cout << "Number of shares: ";
    cin >> shares;                  //take in the number of shares
    if(shares <= 0)
    {
        cout << "---" << endl;
        cout << "The number of shares must be positive"; //check the number of shares
        return 0;
    }
    
    //cin.ignore(10000, '\n');
    double sharePrice;
    cout << "Share price: ";    //take in the price of each share
    cin >> sharePrice;
    cin.ignore(10000, '\n');  //cin a number now getline a string, so need ignore
    if(sharePrice <= 0)         //check if the price is positive
    {
        cout << "---" << endl;
        cout << "The share price must be positive";
        return 0;
    }
    
    double principal = (shares * sharePrice); //get the principal
    
    string clientName;
    cout << "Client name: ";
    getline(cin, clientName);           //get the name of the client
    if(clientName == "")
    {
        cout << "---" << endl;
        cout << "You must enter a name";   //make sure a name is put into
        return 0;
    }
    
    int priorTrans;
    cout << "Number of prior transactions: ";
    cin >> priorTrans;              //get the prior transactions
    if(priorTrans <= 0)             //check it
    {
        cout << "---" << endl;
        cout << "The number of prior transactions must not be negative";
        return 0;
    }
    
    cout << "---" << endl;      //do the computation after this line
    cout.setf(ios::fixed);      //everything should be just to 2 decimal places rounded
    cout.precision(2);
    

    double commission; 
    if(sharePrice >= 1.00)
    {
        commission = .025 * shares;         //calculation based off the spec
        if(commission <= 25.00)
        {
            commission = 25.00;
        }
        if(priorTrans >= 30 & priorTrans <= 60)
        {
            commission -= (.1 * commission);
        }
        else if(priorTrans > 60)
        {
            commission -= (.25 * commission);
        }
    }
    else
    {
        commission = 20 + (.02 * principal);
    }
    
    if(commission > principal)          //based off the spec
    {
        commission = principal;
    }
    
    if(buyOrSell == "b")
        cout << "Net amount for " << clientName << " is $" << (principal + commission);
    if(buyOrSell == "s")
        cout << "Net amount for " << clientName << " is $" << (principal - commission);
    //two outcomes, one for selling and one for buying
    
    return 0;  //end the program
}
