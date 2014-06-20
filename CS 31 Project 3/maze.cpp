//
//  main.cpp
//  maze.cpp
//
//  Created by Calvin Liu on 10/27/12.
//  Copyright (c) 2012 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include "grid.h"
#include <cassert>
#include <cctype>
using namespace std;

bool isPathWellFormed(string path) //need to see if the input is correct or not..
{
	for (int i = 0; i < path.size(); i++)
    {
        if (isdigit(path[i]))
        {
            if(i+1 >= path.size())
                return false;
            
            if(path[i+1] == 'N' ||
			   path[i+1] == 'S' ||
			   path[i+1] == 'W' ||
			   path[i+1] == 'E' ||
			   path[i+1] == 'n' ||
			   path[i+1] == 's' ||
			   path[i+1] == 'w' ||
			   path[i+1] == 'e')
				i =i+1;
			else if(isdigit(path[i+1]))
			{
                if(i+2 >= path.size())
                    return false;
				if(path[i+2] == 'N' ||
                   path[i+2] == 'S' ||
                   path[i+2] == 'W' ||
                   path[i+2] == 'E' ||
                   path[i+2] == 'n' ||
                   path[i+2] == 's' ||
                   path[i+2] == 'w' ||
                   path[i+2] == 'e')
                    i = i + 2;
                else
                    return false;
			}
            else
                return false;
        }
        else
			return false;
    }
    return true;
    
}


int traverseSegment(int r, int c, char dir, int maxSteps)
{
    
    if (maxSteps < 0) //If your maxSteps is negative....
        return (-1);
    if (r < 1 || r > getRows()) //If youre off the grid..
        return (-1);
    if (c < 1 || c > getCols()) //If youre off the grid..
        return (-1);
    if (isWall(r,c)) //If youre starting at a wall...
        return (-1);
    int x = 0; // You took 0 steps
    while (x <= maxSteps)
    {
        if (dir == 'N' || dir == 'n')
            r -= 1;
        else if (dir == 'S' || dir == 's')
            r += 1;
        else if (dir == 'W' || dir == 'w')
            c -= 1;
        else if (dir == 'E' || dir == 'e')
            c += 1;
        else
            return -1;
        x++;
        
        if (r < 1 || r > getRows())
            return x-1;
        if (c < 1 || c > getCols())
            return x-1;
        if (isWall(r,c))
            return x-1; //You hit the wall, so step back to show how many steps you actually took
    }
    return maxSteps;
}


int traversePath(int sr, int sc, int er, int ec, string path, int& nsteps)
{
    if (isWall(sr, sc)) //If you're starting at a wall...
        return 3;
    if (isWall(er, ec)) //If you're ending at a wall...
        return 3;
    if (sr < 1 || sr > getRows()) //If you're starting off the grid
        return 3;
    if (sc < 1 || sc > getCols()) //If you're starting off the grid
        return 3;
    if (er < 1 || er > getRows()) //If you're ending off the grid
        return 3;
    if (ec < 1 || ec > getCols()) //If you're ending off the grid
        return 3;
    if (!isPathWellFormed(path)) //If it's not syntactically valid
        return 3;
    
    int currentRow = sr;
    int currentColumn = sc;
    //You want to represented sr and sc as a different variable because you want to change the copies
    
    //Go through the path string, extract steps and dir, call traverse segment
    int stepsFinished = 0;
    int stepsAttempting = 0;
    char dir;
    
    for (int i = 0; i < path.size(); i++)
    {
        //if number is 2 digits
        if(isdigit(path[i+1])) //checking every 2 places to see if one number or two
		{
			stepsAttempting = ((path[i] - '0') * 10) + (path[i+1] - '0');
			dir = path[i+2];
			i=i+2;
		}
        //if number is 1 digit
        else
		{
			stepsAttempting = (path[i]) - '0';
			dir = path[i+1];
			i++;
		}
        
        int stepsPossible = traverseSegment(currentRow, currentColumn, dir, stepsAttempting);
        
        if (stepsAttempting == stepsPossible)
        {
            stepsFinished += stepsAttempting;
            
            switch (dir)
            {
                case 'N':
                case 'n':
                    currentRow -= stepsAttempting;
                    break;
                case 'S':
                case 's':
                    currentRow += stepsAttempting;
                    break;
                case 'E':
                case 'e':
                    currentColumn += stepsAttempting;
                    break;
                case 'W':
                case 'w':
                    currentColumn -= stepsAttempting;
                    break;
            }
            nsteps = stepsFinished;
        }
        else
        {
            nsteps = stepsFinished + stepsPossible;
            return 2;
        }
    }
    
    if (currentRow != er || currentColumn != ec)
        return 1;
    
    return 0;
}

/*
int main()
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    if (isPathWellFormed("2n1e"))
		cout << "Passed test 1: isPathWellFormed(\"2n1e\")" << endl;
    if (!isPathWellFormed("2x13n"))
		cout << "Passed test 2: !isPathWellFormed(\"2x13n\")" << endl;
    if (traverseSegment(3, 1, 'N', 5) == 2)
		cout << "Passed test 3: traverseSegment(3, 1, 'N', 2)" << endl;
    int len;
    len = -999;  // so we can detect whether traversePath sets len
    if (traversePath(1,3, 3,1, "2S2w", len) == 2  &&  len == 2)
		cout << "Passed test 4: traversePath(3,1, 3,4, \"2N1e01E0n2s1e\", len)" << endl;
    len = -999;  // so we can detect whether traversePath sets len
    if (traversePath(1,4, 3,4, "1ex", len) == 3  &&  len == -999)
		cout << "Passed test 5: traversePath(3,1, 3,4, \"1ex\", len)" << endl;
}
*/




/*
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    assert(isPathWellFormed("2n1e"));
    assert(!isPathWellFormed("1ex"));
    assert(!isPathWellFormed("n12"));
    assert(!isPathWellFormed("123N"));
    assert(!isPathWellFormed("e12"));           Excellent, it works!
    assert(!isPathWellFormed("12e4ss"));
    assert(!isPathWellFormed("45t30"));
    assert(!isPathWellFormed("45e2"));
    assert(!isPathWellFormed("x23n"));
    assert(!isPathWellFormed("2x13n"));
}
*/
/*
    assert(traverseSegment(21, 5, 'N', 2) == 2);
    assert(traverseSegment(3, 25, 'N', 2) == 2);
    assert(traverseSegment(3, 1, 'X', 2) == 2);
    assert(traverseSegment(-21, 1, 'N', 2) == 2);  It makes it fail, which is good
    assert(traverseSegment(3, -25, 'N', 2) == 2);
    assert(traverseSegment(3, 1, 'N', 5) == -2);
    assert(traverseSegment(3, 1, 'N', -2) == 2);
    assert(traverseSegment(3, 1, 'N', 5) == 2);
 

 
    int len;
    len = -999;  // so we can detect whether traversePath sets len
    assert(traversePath(3,1, 3,4, "2N1e01E0n2s1e", len) == 0  &&  len == 7);
    assert(traversePath(3,1, 3,4, "3N1e01E0n2s1e", len) == 1  &&  len == 8); if it goes through this and doesnt end up at the end
 
    assert(traversePath(3,1, 3,4, "2N1e01E0n2s1e", len) == 2  &&  len == 7);
    assert(traversePath(3,1, 3,4, "2N1e01E0n2s1e", len) == 3  &&  len == 7);
    assert(traversePath(3,1, 3,4, "2N1e01E0n2s1e", len) == 3  &&  len == 7);
 
    len = -999;  // so we can detect whether traversePath sets len
    
    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
    assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);
 assert(traversePath(3,1, 3,4, "1ex", len) == 3  &&  len == -999);

 
    cout << "All tests succeeded" << endl;
}
*/