//
//  main.cpp
//  CS 31 Spring Proj 4
//
//  Created by Calvin on 5/2/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool itIsIncreasingOrder(const string a[], int n) //checks to see fi it is in increasing order
{
    for(int k = 0; k < n-1; k++)
    {
        if(a[k] > a[k+1])
            return false;
    }
    return true;
}

int tally(const string a[], int n, string target)
{
    if(n < 0)
    {
        return -1;
    }
    int numberOfMatches = 0;
    for(int k = 0; k < n; k++)
    {
        if(a[k] == target) //if it found the target
        {
            numberOfMatches++; //increase the tally
        }
    }
    return numberOfMatches;
}

int findFirst(const string a[], int n, string target)
{
    if(n <= 0)
    {
        return -1;
    }
    for(int k = 0; k < n; k++)
    {
        if(a[k] == target) //if it found the target
        {
            return k; //return the position
        }
    }
    return -1;
}

bool findFirstSequence(const string a[], int n, string target, int& begin, int& end)
{
    if(n <= 0)
    {
        return -1;
    }
    for(int k = 0; k < n; k++)
    {
        if(a[k] == target) //if it found the target
        {
            begin = k; //the beginning will be set to that position
            //cout << "begin " << begin << endl;
            for(int j = begin+1; j < n; j++) //start checking the things after it
            {
                if(a[j] != a[k]) //if they start becoming different
                {
                    j--;
                    end = j; //set the end to j
                    //cout << "end " << end << endl;
                    return true;
                }
            }
            end = k; //to cover if only 1 consecutive words are present
            //cout << "second end " << end << endl;
            return true;
        }
    }
    return false;
}

int positionOfMin(const string a[], int n)
{
    if(n <= 0)
        return -1;
    string closestToA = a[0];
    for(int k = 0; k < n; k++)
    {
        if(a[k] <= closestToA)
        {
            closestToA = a[k]; //sets the minimum value
        }
    }
    //cout << "function value " << findFirst(a, n, closestToA) << endl;
    return findFirst(a, n, closestToA); //returns the minimum position of that string
}

int moveToEnd(string a[], int n, int pos)
{
    if (n <= 0)
        return -1;
    if (pos > (n-1) || pos < 0)
        return -1;
    
    string movingvariableforleft = a[pos]; //copy
    
    for (int i = 0; i < n; i++)
    {
        if (pos < i)
            a[i-1] = a[i];  //move everything over
    }
    

    a[n-1] = movingvariableforleft;  //make the right end the copy
//    for(int w = 0; w < n; w++)
//    {
//        cout << a[w] << endl;
//    }
    return pos;
}

int moveToBeginning(string a[], int n, int pos) //string g[4] = { "peter", "lois", "chris", "stewie" };
{
    if (n <= 0)
    return -1;
    if (pos > (n-1) || pos < 0)
        return -1;

    //cout << pos << endl;
    string movingvariableforright = a[pos];
    cout << movingvariableforright << endl;

    for(int i = pos; i > 0 ; i--)
    {
        a[i] = a[i-1];
    }
//    for(int k = 0; k < n; k++)
//    {
//        cout << a[k] << endl;
//    }
    a[0] = movingvariableforright; //make left end the copy
    //cout << pos << endl;
    return pos;
}

int disagree(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 <= 0)
        return -1;
    
    int x;
    if (n1 >= n2)
        for (x = 0; x < n2; x++)
        {
            if (a1[x] != a2[x])
                return x;
            if (x == (n2 - 1))
                return (n2-1);
        }
    else if (n2 > n1)
        for (x = 0; x < n1; x++)
        {
            if (a1[x] != a2[x])
                return x;
            if (x == (n1 - 1))
                return (n1-1);
        }
    return -1;
}

int removeDups(string a[], int n) //string t[6] = { "qwer", "asdf", "asdf", "qwer", "exe", "qwer"};
                                    //q,a,e,doesnt matter, return 3 unique strings
{
    if(n == 0)
        return 0;
    if(n < 0)
        return -1;
    int numberDifferent = n;
    for(int i = 0; i < numberDifferent; i++)
    {
        for(int k = i+1; k < numberDifferent; k++)
        {
            if(a[i] == a[k])
            {
                moveToEnd(a, n, k);
                numberDifferent--;
                k--;
            }
        }
    }
    return numberDifferent;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 < 0)
        return false;
    if (n2 > n1)
        return false;
    if(n2 == 0)
        return true;

    int k = 0;
    int i;
    int numberOfMatches = 0;
    for (i = 0; i < n1; i++)
    {
        if (a1[i] == a2[k]) //found the first subset in a2
        {
            while(k < n2)
            {
                if (a2[k] == a1[i])
                {
                    numberOfMatches++;
                    k++;
                    break;
                }
                else
                    break;
            }
        }
    }
    if(numberOfMatches == n2)
    {
        return true;
    }
    else
        return false;
}

int mingle(const string a1[], int n1, const string a2[], int n2,
           string result[], int max)
{
    if(!itIsIncreasingOrder(a1, n1) || !itIsIncreasingOrder(a2, n2))
    {
        return -1;
    }
    if(n2 < 0 || n1 < 0)
    {
        return -1;
    }
    if(max < n1+n2)
    {
        return -1;
    }
    int spotInResult = 0;
    int i = 0;
    for(int k = 0; k < n1; k++)
    {
        while (i < n2)
        {
            if(a1[k] <= a2[i])
            {
                result[spotInResult] = a1[k];
                spotInResult++;
                break;
            }
            else
            {
                result[spotInResult] = a2[i];
                spotInResult++;
                i++;
            }
        }
    }
//    for(int k = 0; k < n1+n2; k++)
//    {
//        cout << result[k] << endl; 
//    }
    //cout << n1+n2 << endl;
    return n1+n2;
}

int divide(string a[], int n, string divider)
{
    int endpoint = n-1;
    int i = 0;
    
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    while (i < endpoint)
    {
        if (a[i] >= divider)
        {
            string temp = a[endpoint];   //swap something to the left of divider with something to the right of the divider
            a[endpoint] = a[i];
            a[i] = temp;
            endpoint--;
        }
        else
            i++; //you're good keep going
    }
    for (int u = 0; u < i; u++)
    {
        if (a[u] == divider)
        {
            if (a[i] > divider)
                i--;
            string temp = a[i];
            a[i] = a[u];
            a[u] = temp;
            break;
        }
    }

    
//    for(int m = 0; m < n; m++)
//    {
//        cout << a[m] << endl;
//    }
//    cout << i << endl;
//    cout << a[i] << endl; 
    if (a[i] >= divider)
        return i;
    else
        return i+1;
}

int main()
{
    string h[7] = { "peter", "lois", "meg", "chris", "", "stewie", "meg" };
    string a[4] = { "a", "b", "c", "d"};
    string b[4] = { "", "b", "z", "z"};
    string c[4] = { "a", "", "b", "c"};
    string d[5] = { "asdf", "asdf", "asdf", "asdf", "asdf"};
    /*
    assert(itIsIncreasingOrder(a, 4));
    assert(itIsIncreasingOrder(b, 3));
    assert(!itIsIncreasingOrder(c, 3));
    assert(tally(h, 7, "meg") == 2);
    assert(tally(h, 7, "") == 1);
    assert(tally(h, 7, "quagmire") == 0);
    assert(tally(h, 0, "meg") == 0);
    assert(tally(d, 5, "asdf") == 5);
    assert(findFirst(h, 7, "meg") == 2);
    assert(findFirst(h, 2, "meg") == -1);
    assert(findFirst(c, 3, "") == 1);
    assert(findFirst(a, 4, "d") == 3);
    assert(findFirst(a, 0, "d") == -1);
     */
    int bg;
    int en;
    string i[7] = {"monica", "chandler", "ross", "rachel", "joey", "joey", ""};
    /*
    assert(findFirstSequence(h, 7, "chris", bg, en) && bg == 3 && en == 3);
    assert(findFirstSequence(i, 7, "joey", bg, en) && bg == 4 && en == 5);
    assert(!findFirstSequence(i, 0, "pheobe", bg, en));
     */
    
    string g[4] = { "peter", "lois", "chris", "stewie" };
    string l[5] = { "qwer", "asdf", "asdf", "qwer", "qwer"};
    string t[6] = { "qwer", "asdf", "asdf", "qwer", "exe", "qwer"};
    string k[4] = { "", "king", "kid", "prize"};
    string u[4] = { "", "kid", "king", "prize"};
    string m[5] = { "", "king", "kid", "prize", "many"};
    string n[5] = { "", "king", "kid", "balloon", "many"};
    string p[0];
    string q[1] = {"onething"};
    /*
    assert(positionOfMin(g, 4) == 2);
    assert(positionOfMin(g, 0) == -1);
    assert(positionOfMin(l, 5) == 1);
    assert(positionOfMin(l, 3) == 1);
    assert(positionOfMin(l, 1) == 0);
    assert(positionOfMin(k, 4) == 0);
    assert(disagree(h, 4, g, 4) == 2);
    assert(disagree(k, 4, m, 5) == 3);
    assert(disagree(n, 5, m, 5) == 3);
    assert(disagree(n, 1, m, 5) == 0);
    assert(disagree(n, 2, m, 5) == 1);
    assert(subsequence(h, 7, g, 4));
    assert(subsequence(n, 5, p, 0));
    assert(subsequence(m, 5, n, 3));
    assert(!subsequence(m, 5, n, 4));
    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "lois");
    assert(moveToEnd(n, 5, 3) == 3 && n[4] == "balloon" && n[0] == "" && n[3] == "many");
    assert(moveToEnd(p, 0, 0) == -1);
    assert(moveToEnd(q, 1, 0) == 0 && q[0] == "onething");
    assert(moveToEnd(t, 6, 4) == 4 && t[5] == "exe" && t[4] == "qwer" && t[3] == "qwer" && t[2] == "asdf" && t[1] == "asdf" && t[0] == "qwer");
     */
	
    string f[4] = { "chris", "stewie", "meg", "lois" };
    /*
    assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "meg" && f[2] == "stewie");
    assert(moveToBeginning(g, 4, 1) == 1 && g[0] == "lois" && g[1] == "peter");
    assert(moveToBeginning(m, 5, 2) == 2 && m[0] == "kid" && m[2] == "king");
    assert(moveToBeginning(m, 1, 0) == 0);
    assert(moveToBeginning(i, 7, 3) == 3 && i[3] == "ross" && i[2] == "chandler");
     */
	
    string e[5] = { "chris", "chris", "chris", "meg", "meg" };
    
//    assert(removeDups(e, 5) == 2 && e[1] == "meg");
//    assert(removeDups(d, 5) == 1 && d[0] == "asdf");
//    assert(removeDups(l, 5) == 2 && l[0] == "qwer" && l[1] == "asdf");
//    assert(removeDups(t,6) == 3 && t[0] == "qwer" && t[1] == "asdf" && t[2] == "exe");
//    assert(removeDups(l, 0) == 0);
    
    string x[4] = { "brian", "lois", "lois", "quagmire" };
    string y[4] = { "chris", "lois", "meg", "stewie" };
    string z[10];
    /*
    assert(mingle(x, 4, y, 4, z, 10) == 8 && z[5] == "meg");
    assert(mingle(e, 5, k, 4, z, 6) == -1);
    assert(mingle(e, 5, k, 4, z, 10) == -1);
    assert(mingle(e, 5, u, 4, z, 10) == 9 && z[4] == "kid" && z[1] == "chris");
    
    assert(divide(h, 7, "meg") == 3);
	assert(divide(m, 5, "z") == 5);
    assert(divide(n, 5, "a") == 1);
    assert(divide(y, 4, "o") == 3);
    assert(divide(y, 0, "o") == 0);
    assert(divide(y, -1, "o") == -1);
    */
    
    cout << "All tests succeeded" << endl;
}
