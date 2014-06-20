//
//  main.cpp
//  CS 31 Spring Proj 5
//
//  Created by Calvin on 5/16/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

bool saveADoc()
{
    ofstream outfile("/Users/icecool5280/Library/Developer/Xcode/DerivedData/CS_31_Spring_Proj_5-dduyxkzbivnlcxfdkniqrpyrorge/Build/Products/Debug/Proj5.txt");   // outfile is a name of our choosing.
	if ( ! outfile )		   // Did the creation fail?
	{
	    cerr << "Error: Cannot create results.txt!" << endl;
	    return false;
	}
	outfile << "DhaiiA, zyxZYXzyx--A aBc    dE## $$fGhi6437 wvuWVUwvu" << endl;
	outfile << "2 + 2 = " << 2+2 << endl;
    outfile << "DhaiiA, zyxZYXzyx--A aBc    dE## $$fGhi6437 wvuWVUwvu" << endl;
    outfile << "Tftdn lxwdqkoft lhgzztr of Ltezgk zvtfzn-ltctf." << endl;
	outfile << "O ziofa zit Zktqlxkt gy Doeiossofrq ol wxkotr lgdtvitkt of dn wqeanqkr." << endl;
	outfile << "Ror ngx itqk ziqz Sgktzzq ol ugofu gxz vozi Dqkexl?" << endl;
    return true;
}

int findFirst(const char a[], int n, char target)
{
    if (n < 0)
        return -1;
    for (int k = 0; k < n; k++)
        if (a[k] == target)
            return k;
    return -1;
}

void rotateLeft(int positionToRemove, char array[])
{
    for(int k = positionToRemove; array[k] != '\0'; k++)
    {
        array[k] = array[k+1];
    }
}

void removeMultipleSpaces(char noMoreSpaces[])
{
    for(int k = 0; k < strlen(noMoreSpaces)-1; k++)
    {
        if(noMoreSpaces[k] == ' ' && noMoreSpaces[k+1] == ' ')
        {
            rotateLeft(k, noMoreSpaces);
            k--;
        }
    }
}

void cleanArray(char array[])
{
    for(int k = 0; array[k] != '\0'; k++)
    {
        array[k] = '\0';
    }
}

void normalizeCrib(char copiedCribToNormalize[])
{
    for(int k = 0; k < copiedCribToNormalize[k]; k++)
    {
        tolower(copiedCribToNormalize[k]);
        if(!isalpha(copiedCribToNormalize[k]) && copiedCribToNormalize[k] != ' ') //cleaned but can have multiple spaces
        {
            copiedCribToNormalize[k] = ' ';
        }
    }
    removeMultipleSpaces(copiedCribToNormalize);
    if(copiedCribToNormalize[0] == ' ')
    {
        rotateLeft(0, copiedCribToNormalize);
    }
}

int moveToNextWord(int start, int row, char array[][81])
{
    int count = 0;
    for(int k = start; array[row][k] != ' '; k++)
    {
        count++;
    }
    return count;
}
    
bool mappingIsRight(char crib[], char cipherLine[], int decoding[27]) //cipher and crib are the same length
{
    char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
    for(int p = 0; p < 27; p++)
    {
        decoding[p] = -1;
    }
    
    for(int k = 0; crib[k] != '\0'; k++)
    {
        char c = tolower(crib[k]);
        char t = tolower(cipherLine[k]);
        if(isalpha(crib[k]))
        {
            if(decoding[findFirst(alphabet, 27, c)] == -1 || decoding[findFirst(alphabet, 27, t)] == findFirst(alphabet, 27, c) || decoding[findFirst(alphabet, 27, t)] == -1)
            {
                decoding[findFirst(alphabet, 27, t)] = findFirst(alphabet, 27, c);
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool cribNotFound(istream& cipherstream, const char crib[], int decoding[27], char unchanged[50][81])
{
    const int MAXC = 81;
    const int MAXR = 50;
    char copiedCrib[MAXC];
    for(int k = 0; k < strlen(crib)+1; k++) //copy the crib
    {
        copiedCrib[k] = crib[k];
    }
    normalizeCrib(copiedCrib); //normalize the crib
    if(strlen(copiedCrib) > 80)       //crib cannot be this length
    {
        return false;
    }
    
    int rowPosition = 0;
    int colPosition = 0;
    char wordToCheck[MAXR][MAXC];
    char c;
	while ( cipherstream.get(c) ) //don't fix the array, just save it and then fix it using a function
	{
        wordToCheck[rowPosition][colPosition] = c; //put the character in the array
        if(c == '\0' || c == '\n')
        {
            wordToCheck[rowPosition][colPosition+1] = '\0'; //what if it is 80 letters and null?
            rowPosition++;  //put the next character in the new line
            colPosition = -1;
        }
        colPosition++;
    }
    
    for(int m = 0; m < rowPosition; m++)  //copy the wordToCheck, unnormalized into the uchanged array
    {
        strcpy(unchanged[m], wordToCheck[m]);
    }
    
    for(int k = 0; k < rowPosition; k++)
    {
        normalizeCrib(wordToCheck[k]);
    }
    
    char tempArray[81];
    int tempPos = 0;
    int letterCount = 0;
    int row = 0;
    int cribPos = 0;
    for(int k = 0; wordToCheck[row][k] != '\0'; k++)
    {
        if((isalpha(copiedCrib[cribPos]) == isalpha(wordToCheck[row][k]))) //checking to see if they are both letters
        {
            tempArray[tempPos] = wordToCheck[row][k]; //store the temporary cipher
            tempPos++;
            letterCount++;
            if(letterCount+1 == strlen(copiedCrib))
            {
                tempArray[tempPos] = wordToCheck[row][k+1];
                tempArray[tempPos+1] = '\0';
                return mappingIsRight(copiedCrib, tempArray, decoding);
            }
            cribPos++;
        }
        else
        {
            cleanArray(tempArray);
            letterCount = 0;
            cribPos = 0;
            k += moveToNextWord(k, row, wordToCheck);
            tempPos = 0;
        }
        if(wordToCheck[row][k+1] == '\n' || wordToCheck[row][k+1] == '\0')
        {
            row++;
            k = -1;
        }
    }
    
    return false;
}

bool decrypt(istream& cipherstream, const char crib[])
{
    char unchanged[50][81];
    int decoderIndex[27];
    if(crib[0] == '\0' || !cribNotFound(cipherstream, crib, decoderIndex, unchanged)) //decoding index is now saved
    {
        return false; //why is it not executing this if it is false
    }
    char upperAlphabet[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char lowerAlphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
    int temp;
    bool changeBack = false;
    int rowPos = 0;
    for(int k = 0; unchanged[rowPos][k] != '\0'; k++)
    {
        char c = unchanged[rowPos][k];
        if(isalpha(c)) //if it is a character
        {
            if(isupper(c))
            {
                c = tolower(c);
                changeBack = true;
            }
            temp = findFirst(lowerAlphabet, 27, c); //find where the character is. Ex) a = 0
            if(decoderIndex[temp] == -1)
            {
                if(changeBack)
                {
                    c = toupper(c);
                    cout << c;     //cout the original
                }
                else
                {
                    cout << c;
                }
            }
            else
            {
                cout << upperAlphabet[decoderIndex[temp]]; //otherwise cout the decoded
            }
        }
        else
        {
            cout << c; //just cout the symbol or w/e
            if(c == '\n')
            {
                rowPos++;
                k = -1;
            }
        }
        changeBack = false;
    }
    return true;
}

int main()
{
    string filename;
    saveADoc();
    ifstream cipher("/Users/icecool5280/Library/Developer/Xcode/DerivedData/CS_31_Spring_Proj_5-dduyxkzbivnlcxfdkniqrpyrorge/Build/Products/Debug/Proj5.txt");    // infile is a name of our choosing
	if ( ! cipher )		        // Did opening the file fail?
	{
	    cerr << "Error: Cannot open data.txt!" << endl;
	    return false;
	}
    char fakecrib[100] = {' ', ' ', 't', 'r', 'e', 'a', 's', 'u', 'r', 'e', ' ', 'o', 'f', ' ', 'm', 'i', 'c', 'h', 'i', 'l', 'l', 'i','n','d','a', ' ', ' ', '\0'};
    if(decrypt(cipher, fakecrib))
    {
    }
}

/*
 
 "DhaiiA, zyxZYXzyx--A aBc    dE## $$fGhi6437 wvuWVUwvu"
 causing the partially decrypted plaintext of that string to be written as
 
 "INDEED, zyxzyxzyx--D DAY    IS## $$JUNE6437 wvuwvuwvu"
 
 INDEED, zyx908988zyx--D DAY    IS## $$JUNE6437 wvu878685wvu
 2 + 2 = 4
 INDEED, zyx908988zyx--D DAY    IS## $$JUNE6437 wvu878685wvu
 
*/
