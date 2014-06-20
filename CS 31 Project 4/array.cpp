//
//  main.cpp
//  array.cpp
//
//  Created by Calvin Liu on 11/3/12.
//  Copyright (c) 2012 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;


int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++)
    {
        a[i] += value; //Attach value to everything
    }
    return n;
}


int lookup(const string a[], int n, string target)
{
    if (n <= 0)
        return -1;
    for (int i = 0; i < n; i++)
    {
        if(target == a[i])
            return i;
    }
    return -1;
}


int positionOfMax(const string a[], int n)
{
    if (n <= 0)
        return -1;
    string max = a[0]; //make the first element the max until....
    int i = 0;
    int position = 0;
    for (i = 1; i < n; i++)
    {
        if (max < a[i]) //it finds a new bigger one and makes that the max
        {   max = a[i];
            position = i; //keeps track of the position the max is in
        }
    }
    return position;
}


int rotateLeft(string a[], int n, int pos)
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
    return pos;
}


int rotateRight(string a[], int n, int pos)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    string movingvariableforright = a[pos];
    
    for (int i = 0; i < n; i++)
    {
        if (pos > i)
            a[i+1] = a[i];
    }
    
    a[0] = movingvariableforright;
    return pos;
    
}


int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    for (int i = 0; i < (n/2); i++) //you only want to loop it half or else it will become the same
    {
        string newStorage = a[i];
        a[i] = a[(n-1) - i];
        a[(n-1) - i] = newStorage; //goes inward
    }
    return n;
}


int differ(const string a1[], int n1, const string a2[], int n2)
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
    
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 <= 0)
        return -1;
    if (n2 > n1)
        return -1;
    
    int i;
    int k;
    
    for (i = 0; i < n1; i++)
    {
        if (a1[i] == a2[0])
        {
            for (k = 0; k < n2; k++)
            {
                if (a2[k] != a1[i+k])
                    break;
            }
            return i;
        }
    }
    return -1;
}
    
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 <= 0)
        return -1;
    
    for (int i = 0; i < n1; i++)
    {
        for (int k = 0; k < n2; k++)
        {
            if (a1[i] == a2[k])
                return i;
        }
    }
    return -1;
}

int partition(string a[], int n, string separator)
{
    int endpoint = (n-1);
    int i = 0;
    
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    while (i < endpoint)
    {    if (a[i] > separator)
        {
            string temp = a[endpoint];
            a[endpoint] = a[i];
            a[i] = temp;
            endpoint--;
        }
        else
            i++;
    }
    for (int u = 0; u < i; u++)
        if (a[u] == separator)
        {
            if (a[i] > separator)
                i--;
            string temp = a[i];
            a[i] = a[u];
            a[u] = temp;
        }

    if (a[i] >= separator)
        return i;
    else
        return i+1;
}

/*
	int main()
	{
	   string h[7] = { "obiwan", "minnie", "han", "simba", "", "jabba", "ariel" };
        assert(lookup(h, 7, "jabba") == 5);
	    assert(lookup(h, 7, "han") == 2);
	    assert(lookup(h, 2, "han") == -1);
	    assert(positionOfMax(h, 7) == 3);
        
	    string g[4] = { "obiwan", "minnie", "simba", "jabba" };
	    assert(differ(h, 4, g, 4) == 2);
	    
        assert(appendToAll(g, 4, "?") == 4 && g[0] == "obiwan?" && g[3] == "jabba?");
	    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "simba?" && g[3] == "minnie?");
        
	    string e[4] = { "han", "simba", "", "jabba" };
	    assert(subsequence(h, 7, e, 4) == 2);
	    assert(rotateRight(e, 4, 1) == 1 && e[0] == "simba" && e[2] == "");
        
	    string f[3] = { "simba", "han", "ursula" };
	    assert(lookupAny(h, 7, f, 3) == 2);
	    
        assert(flip(f, 3) == 3 && f[0] == "ursula" && f[2] == "simba");
        //assert(flip(f, 2) == 2 && f[0] == "han" && f[1] == "simba");
        //assert(flip(h, 7) == 7 && h[0] == "ariel" && h[6] == "obiwan" && h[1] == "jabba" && h[5] == "minnie" && h[2] == "" && h[4] == "han");

        assert(partition(h, 7, "jabba") == 3);
         
	    cout << "All tests succeeded" << endl;
	}

*/