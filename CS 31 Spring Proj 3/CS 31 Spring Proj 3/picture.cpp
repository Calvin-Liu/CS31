//
//  main.cpp
//  CS 31 Spring Proj 3
//
//  Created by Calvin on 4/25/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "graphlib.h"
#include <iostream>
#include <cmath>
using namespace std;

int eightWordIsWrong(string wordToCheck, int beginning) //check to see if every 8 char command is correct
{
    for(int k = beginning+1; k < beginning+7; k++) //loop to check the numbers
    {
        if(!isdigit(wordToCheck[k]))
            return (k+1);   //if there is an error then return the position
    }
    if(wordToCheck.size() == 7) //if the character is one short, don't plot ?
    {
        return 8; //return the eigth position
    }
    return 0; //it is correct
}

int tenWordIsWrong(string wordToCheck, int beginning) //check to see if every 10 char command is correct
{
    for(int k = beginning+1; k < beginning+9; k++) //check to see if every 10 char command is correct
    {
        if(!isdigit(wordToCheck[k]))
            return (k+1);       //return the position if it is wrong
    }
    if(wordToCheck.size() == 9) //if the size is just 9, don't plot ?
    {
        return 10;  //it's missing just 1 char
    }
    return 0; //it is correct
}

int textCommIsWrong(string wordToCheck, int beginning)
{
    for(int k = beginning+1; k < beginning+5; k++) //check the first 4 digits
    {
        if(!isdigit(wordToCheck[k]))
            return (k+1); //return position if it is wrong
    }
    
    int delimSpot = beginning + 5;
    for(int x = delimSpot+1; wordToCheck[x] != wordToCheck[wordToCheck.size()]; x++) //the delimiter spot
    {
        if(wordToCheck[delimSpot] == wordToCheck[x]) //if there is a second delim then the text is enclosed
        {
            return 0;
        }
    }
    return wordToCheck.size()+1; //if it doesnt find the second delim then return the position
}

int flipIsWrong(string wordToCheck, int beginning)
{
    for(int k = beginning+1; k < beginning+9; k++)
    {
        if(!isdigit(wordToCheck[k])) //check the numbers
            return (k+1);
    }
    return 0; //it is correct
}

void plotHorizontalLine(int r, int c, int length, char ch)
{
    if(length <= 0)
    {
        return;
    }
    for(int k = c; k < (c+length); k++)
    {
        if(k < 31 && k > 0) ////check to see if it is in the grid
        {
           setChar(r, k, ch); 
        }
    }
}

void plotVerticalLine(int r, int c, int length, char ch)
{
    if(length <= 0)
    {
        return;
    }
    for(int k = r; k < (r+length); k++) //check to see if it is in the grid
    {
        if(k < 21 && k > 0)
        {
            setChar(k, c, ch);
        }
    }
}

void plotRectangle(int r, int c, int height, int width, char ch)
{
    if(height < 0 || width < 0)
        return;
    for(int k = r; k < r+height; k++)
    {
        if(k < 21 && k > 0 && c > 0 && c < 31)
           setChar(k, c, ch); //one of the sides call it A
    }
    for(int i = r; i < r+height; i++)
    {
        if(i < 21 && i > 0 && c+width > 0 && c+width < 21)
            setChar(i, c+width-1, ch); //the opposite of A
    }
        
    for(int j = c; j < c+width; j++)
    {
        if(j < 31 && j > 0 && r > 0 && r < 31)
            setChar(r, j, ch); //one of the sides call it B
    }
    for(int m = c; m < c+width; m++)
    {
        if(m < 31 && m > 0 && r+height > 0 && r+height < 21)
            setChar(r+height-1, m, ch); //the opposite side of B
    }
}

void plotText(int r, int c, string text)
{
    //see if you need to check for the empty string
    int stringlength = 0;
    for(int k = c; k != (c+text.size()); k++) //skipping this for loop for some reason, works if != but not <
    {
        if(k < 31 && k > 0)
        {
            setChar(r, k, text[stringlength]);
        }
        stringlength++;
    }
}

void plotCircle(int r, int c, int diameter, char ch) //does not work so great
{
    int radius = static_cast<int>(diameter/2);
    if(diameter <= 0)
    {
        return;
    }
    if(diameter % 2 == 0) //if it is an even number, make it 1 bigger
    {
        diameter++;
    }
    if(diameter == 1)
    {
        setChar(r, c, ch); //if it is a diameter of 1 just plot a character
    }
    
    for(double theta = 0; theta < 2*atan(1.0); theta += .1)
    {
        int rowPosition = static_cast<int>(((radius * cos(theta)) + .5)); //cst to not get an int
        int colPosition = static_cast<int>(((radius * sin(theta)) + .5));
        int yPosOffset = r+rowPosition;
        int yNegOffset = r-rowPosition; //set and x and y offsets that will be used for the coordinates
        int xPosOffset = c+colPosition;
        int xNegOffset = c-colPosition;
        
        if((yPosOffset > 0) && (yNegOffset < 21) && (xNegOffset > 0) && (xPosOffset < 31))
        {
            setChar(yPosOffset, xPosOffset, ch);
            setChar(yPosOffset, xNegOffset, ch);
            setChar(yNegOffset, xPosOffset, ch); //set the characters based on the offset
            setChar(yNegOffset, xNegOffset, ch);
        }
    }
}

void clearPicture()
{
    for(int k = 1; k < (NCOLS+1); k++)
    {
        for(int j = 1; j < (NROWS+1); j++) //loop thorugh twice and make everything a space
        {
            setChar(j, k, ' ');
        }
    }
}

void invertRectangle(int r, int c, int height, int width, char ch)
{
    if(height <= 0 || width <= 0)
    {
        return;
    }
    for(int k = r; k < (r+height) ; k++)
    {
        for(int j = c; j < (c+width); j++)
        {
            if(j > 0 && j < 31 && k > 0 && k < 21) //plot only if it is on the grid
            {
                if(getChar(k, j) == ch)
                {
                    setChar(k, j, ' ');
                }
                else if(getChar(k, j) == ' ')
                {
                    setChar(k, j, ch);
                }
            }
        }
    }
}

void flipHorizontal(int r, int c, int height, int width)
{
    char tempswap;
    char endswap;
    for(int k = r; k < (r+height); k++)
    {
        int numberOfSwaps = 0;
        for(int j = 0; j < (width/2); j++) //flip only half so it doesnt flip back
        {
            tempswap = getChar(k, c+numberOfSwaps); //save first char
            endswap = getChar(k, (c+width-1)-numberOfSwaps); //save last letter
            setChar(k, c+numberOfSwaps, endswap); //switch the first letter with the last
            setChar(k, ((c+width-1)-numberOfSwaps), tempswap); //switch the last letter with the first
            numberOfSwaps++; //increment this to go inward
        }
    }
}

bool inGrid(int r, int c)
{
    if(r < 0 || r > NROWS || c < 0 || c > NCOLS) //if it is out of the grid, return false
    {
        return false;
    }
    else
    {
        return true; 
    }
}

int executeCommands(string commandString)
{
    string loweredString = "";
    for(int k = 0; k < commandString.size(); k++)
    {
        loweredString += tolower(commandString[k]); //lower the whole string
    }
    for(int strBegin = 0; strBegin < loweredString.size(); strBegin++)
    {
        switch(loweredString[strBegin]) //check the first letter
        {
            case 'h':
            {
                if(eightWordIsWrong(loweredString, strBegin)) //is this syntacically valid?
                {
                    cout << "Syntax error at position " << eightWordIsWrong(loweredString, strBegin) << endl;
                    return eightWordIsWrong(loweredString, strBegin);
                }
                else
                {
                    int row = (loweredString[strBegin+1] - '0') * 10; //convert the numbers and use in func
                    row += (loweredString[strBegin+2] - '0');
                    int col = (loweredString[strBegin+3] - '0') * 10;
                    col += (loweredString[strBegin+4] - '0');
                    int num = (loweredString[strBegin+5] - '0') * 10;
                    num += (loweredString[strBegin+6] - '0');
                    plotHorizontalLine(row, col, num, commandString[strBegin+7]);
                    strBegin += 7; //onto the next command, the first 8 are checked
                }
            }
                break;
            case 'v':
            {
                if(eightWordIsWrong(loweredString, strBegin)) //is this syntacically valid?
                {
                    cout << "Syntax error at position " << eightWordIsWrong(loweredString, strBegin) << endl;
                    return eightWordIsWrong(loweredString, strBegin);
                }
                else
                {
                    int row = (loweredString[strBegin+1] - '0') * 10; //convert the numbers and use in func
                    row += (loweredString[strBegin+2] - '0');
                    int col = (loweredString[strBegin+3] - '0') * 10;
                    col += (loweredString[strBegin+4] - '0');
                    int num = (loweredString[strBegin+5] - '0') * 10;
                    num += (loweredString[strBegin+6] - '0');
                    plotVerticalLine(row, col, num, commandString[strBegin+7]);
                    strBegin += 7; //onto the next command, the first 8 are checked
                }
            }
                break;
            case 'r':
            {
                if(tenWordIsWrong(loweredString, strBegin)) //is it syntacically valid?
                {
                    cout << "Syntax error at position " << tenWordIsWrong(loweredString, strBegin) << endl;
                    return tenWordIsWrong(loweredString, strBegin);
                }
                else
                {
                    int row = ((loweredString[strBegin+1]) - '0') * 10;//convert the numbers and use in func
                    row += (loweredString[strBegin+2] - '0');
                    int col = ((loweredString[strBegin+3]) - '0') * 10;
                    col += (loweredString[strBegin+4] - '0');
                    int height = ((loweredString[strBegin+5] - '0')) * 10;
                    height += ((loweredString[strBegin+6] - '0'));
                    int width = ((loweredString[strBegin+7] - '0') * 10);
                    width += ((loweredString[strBegin+8] - '0'));
                    plotRectangle(row, col, height, width, commandString[strBegin+9]);
                    strBegin += 9; //onto the next command, the first 10 are checked
                }
            }
                break;
            case 't':
            {
                if(textCommIsWrong(loweredString, strBegin)) //is it syntacically valid?
                {
                    cout << "Syntax error at position " << textCommIsWrong(loweredString, strBegin) << endl;
                    return textCommIsWrong(loweredString, strBegin);
                }
                string textString = "";
                for(int k = strBegin+6; commandString[k] != commandString[strBegin+5]; k++)
                {
                    textString += commandString[k];
                }
                int row = (loweredString[strBegin+1] - '0') * 10; //convert the numbers and use in func
                row += (loweredString[strBegin+2] - '0');
                int col = (loweredString[strBegin+3] - '0') * 10;
                col += (loweredString[strBegin+4] - '0');
                plotText(row, col, textString);
                strBegin += (6+textString.size()); //move on to the next command
            }
                break;
            case 'c':
            {
                if(eightWordIsWrong(loweredString, strBegin)) //is it syntacically valid?
                {
                    cout << "Syntax error at position " << eightWordIsWrong(loweredString, strBegin) << endl;
                    return eightWordIsWrong(loweredString, strBegin);
                }
                else
                {
                    int row = (loweredString[strBegin+1] - '0') * 10; //convert the numbers and use in func
                    row += (loweredString[strBegin+2] - '0');
                    int col = (loweredString[strBegin+3] - '0') * 10;
                    col += (loweredString[strBegin+4] - '0');
                    int num = (loweredString[strBegin+5] - '0') * 10;
                    num += (loweredString[strBegin+6] - '0');
                    plotCircle(row, col, num, commandString[strBegin+7]);
                    strBegin += 7; //increment where youre at by 7
                }
            }
                break;
            case 'x':
            {
                clearPicture(); //clear, one word command
            }
                break;
            case 'i':
            {
                if(tenWordIsWrong(loweredString, strBegin)) //is it syntacically valid?
                {
                    cout << "Syntax error at position " << tenWordIsWrong(loweredString, strBegin) << endl;
                    return tenWordIsWrong(loweredString, strBegin);
                }
                else
                {
                    int row = ((loweredString[strBegin+1]) - '0') * 10; //convert the numbers for func
                    row += (loweredString[strBegin+2] - '0');
                    int col = ((loweredString[strBegin+3]) - '0') * 10;
                    col += (loweredString[strBegin+4] - '0');
                    int height = ((loweredString[strBegin+5] - '0')) * 10;
                    height += ((loweredString[strBegin+6] - '0'));
                    int width = ((loweredString[strBegin+7] - '0') * 10);
                    width += ((loweredString[strBegin+8] - '0'));
                    invertRectangle(row, col, height, width, commandString[strBegin+9]);
                    strBegin += 9; //increment by 9 to check new position
                }
            }
                break;
            case 'f':
            {
                if(flipIsWrong(loweredString, strBegin)) //check to see if the flip command is wrong
                {
                    cout << "Syntax error at position " << flipIsWrong(loweredString, strBegin) << endl;
                    return flipIsWrong(loweredString, strBegin);
                }
                else
                {
                    int row = ((loweredString[strBegin+1]) - '0') * 10; //convert numbers
                    row += loweredString[strBegin+2] - '0';
                    int col = ((loweredString[strBegin+3]) - '0') * 10;
                    col += loweredString[strBegin+4] - '0';
                    int height = ((loweredString[strBegin+5] - '0') * 10);
                    height += loweredString[strBegin+6] - '0';
                    int width = ((loweredString[strBegin+7] - '0') * 10);
                    width += loweredString[strBegin+8] - '0';
                    flipHorizontal(row, col, height, width);
                    strBegin += 8; //move onto next string
                }
            }
                break;
            default:
            {
                cout << "Syntax error at position " << strBegin+1 << endl;
                return strBegin;
            }
        }
    }
    return -1; //everything is correct and it did not return early meaning everything is syntactically valid!
}

/*
void testPlotting(int testnum)
{
    clearGrid();
    switch (testnum)
    {
        default:
	        cout << "There is no test number " << testnum << endl;
	        break;
        case 1:
	        cout << "Horiz line of % from (10,15) of length 7" << endl;
 	        plotHorizontalLine(10, 25, 7, '%');
	        break;
        case 2:
	        cout << "Horiz line of # from (10,28) of length 7, "
            << "should see only 3" << endl;
            plotHorizontalLine(10, 28, 7, '#');
	        break;
        case 3:
	        cout << "Underlined message in upper left" << endl;
            plotText(1, 1, "Hello there!");
            plotHorizontalLine(1, -1, 12, '-');
	        break;
        case 4:
            cout << "Horiz line of # from (18,10) of length 7, "
            << "should see only 3" << endl;
            plotVerticalLine(18, 10, 7, '#');
            break;
        case 5:
            cout << "Text that is going to be truncated" << endl;
            plotText(4, 17, "CalvinWFGHJKFGHJFGHERTYUI");
            break;
        case 6:
            cout << "Nothing" << endl;
            plotText(1, 28, "Calvin");
            clearPicture();
            break;
        case 7:
            cout << "Presenting a circle" << endl;
            plotCircle(10, 15, 1, 'O');
            break;
        case 8:
            cout << "Only some of the circle" << endl; //failing this test
            plotCircle(10, 4, 11, 'O');
            break;
        case 9:
            cout << "Radius of 1" << endl;
            plotCircle(5, 6, 1, 'O');
        case 10:
            if(inGrid(5, 6))
            {
                cout << "inGrid works" << endl;
            }
            break;
        case 11:
            cout << "Rectangle Drawing" << endl;
            plotRectangle(-4, -5, 15, 15, '#');
        case 12:
            cout << "Rectangle Drawing" << endl;
            plotRectangle(-4, -5, 4, 4, '#');
            break;
        case 13:
            cout << "Test for inverting" << endl;
            plotRectangle(-4, -5, 15, 15, 'r');
            plotHorizontalLine(7, 1, 3, '%');
            invertRectangle(-4, -5, 17, 17, '#');
            break;
        case 14:
            plotText(4, 1, "ABCDEF");
            plotText(5, 1, "GHIJKL");
            plotText(6, 1, "CS 31");
            flipHorizontal(4, 1, 4, 6);
        case 15:
            executeCommands("R051003049");
    }
    draw();
}

int main()
{
    for (;;)
    {
        cout << "Enter test number (0 to quit): ";
        int n;
        cin >> n;
        if (n <= 0)
            break;
        testPlotting(n);
    }
}
*/
 
int main()
{
    clearGrid();
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int result = executeCommands(cmd);
        if (result == -1)
            draw();
    }
}