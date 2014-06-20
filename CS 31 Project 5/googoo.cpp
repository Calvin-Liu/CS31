//
//  main.cpp
//  googoo
//
//  Created by Calvin Liu on 11/11/12.
//  Copyright (c) 2012 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <string.h>
using namespace std;

const int MAX_WORD_LENGTH = 20;

void shiftingelements();
void shiftingnumbers();

void shiftingelements(int start, char aWord[][MAX_WORD_LENGTH+1], int nCriteria)
{
    for(int m = start; m < nCriteria; m++)
        strcpy(aWord[m], aWord[m+1]);
}
void shiftingnumbers(int start, int aNumber[], int nCriteria)
{
    for(int m = start; m < nCriteria; m++)
        aNumber[m] = aNumber[m+1];
}


int normalizeCriteria(int distance[],
                      char word1[][MAX_WORD_LENGTH+1],
                      char word2[][MAX_WORD_LENGTH+1],
                      int nCriteria)
{
    int j;
    int numElementsInArr = nCriteria;
    for (j = 0; j != numElementsInArr; j++)
    {
        for (int k = 0; k != strlen(word1[j]); k++)
        {
            if (isupper(word1[j][k]))           //if it is uppercase, make it lowercase
                word1[j][k] = tolower(word1[j][k]);
        }
        for (int k = 0; k != strlen(word2[j]); k++)
        {
            if (isupper(word2[j][k]))
                word2[j][k] = tolower(word2[j][k]);
        }
        
        bool b = false;
        
        for (int k = 0; k < strlen(word1[j]); k++)
        {
            if(!islower(word1[j][k])) //if the word has something that is not a letter
            {
                b = true;
            }
        }
        
        for (int k = 0; k < strlen(word2[j]); k++)
        {
            if(!islower(word2[j][k])) //if the word has something that is not a letter
            {
                b = true;
            }
        }
        
       if (distance[j] <= 0 || word1[j][0] == '\0' || word2[j][0] == '\0' || b)
       {
           shiftingelements(j, word1, numElementsInArr);
           shiftingelements(j, word2, numElementsInArr);
           shiftingnumbers(j, distance, numElementsInArr);
           numElementsInArr--;
           j--;
       }
        
        for (int m = j+1; m < numElementsInArr; m++)
        {
            if (strcmp(word1[j],word1[m]) == 0)
            {
                if(distance[j] < distance[m])
                {
                    shiftingelements(j, word1, numElementsInArr);
                    shiftingelements(j, word2, numElementsInArr);
                    shiftingnumbers(j, distance, numElementsInArr);
                    numElementsInArr--;
                    j--;
                }
                else
                {
                    shiftingelements(m, word1, numElementsInArr);
                    shiftingelements(m, word2, numElementsInArr);
                    shiftingnumbers(m, distance, numElementsInArr);
                    numElementsInArr--;
                    j--;
                }
            }
        }
    }
    return numElementsInArr;
}

/*
int main()
{
    const int TEST1_NCRITERIA = 4;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "123",    "plot",      "mad"
    };
 
    int n = normalizeCriteria(test1dist, test1w1, test1w2, TEST1_NCRITERIA);
    cout << n << endl;
    for (int k = 0; k < n; k++)
    {
        cout << test1dist[k] << "   " << test1w1[k] << "   " << test1w2[k] << endl;
    }
        
}
*/    

//now everything is correct and can't be wrong


void rotateleft();

void rotateleft(int startRotation, char localarr[], const char document[])
{
    for (int n = startRotation; n < strlen(document); n++)
    {
        localarr[n] = localarr[n+1];
    }
    
}

int computeScore(const int distance[],
                 const char word1[][MAX_WORD_LENGTH+1],
                 const char word2[][MAX_WORD_LENGTH+1],
                 int nCriteria,
                 const char document[])
{
   
    int score = 0;
    char localarr[201];
    char localarr2[101][201];
    strcpy(localarr,document); //make a copy of the document because you can't modify the document

    for (int k = 0; k < strlen(localarr); k++)
    {
        if (isupper(localarr[k]))          //fix the document
            localarr[k] = tolower(localarr[k]);
        if (!islower(localarr[k]) && localarr[k] != ' ')
        {
            rotateleft(k, localarr, document);
            k--;
        }
    }
    
    
    int j = 0;
    int i;
    for (int k = 0; k < strlen(localarr); k++)  //converting the document to a 2D array
    {
       if (localarr[k] != ' ')
       {
           localarr2[j][i] = localarr[k];
           i++;
       }
       else
       {
            localarr2[j][i] = '\0';
            j++;
            i = 0;
       }
    }
    
    
    localarr2[j][i] = '\0';
    bool found[nCriteria];
    for(int i=0; i < nCriteria; i++)
    {
        found[i] = false;
    }
    
    for (int x = 0; x < nCriteria; x++)
    {
        for (int k = 0; k < j; k++)       
        {
            
            if (strcmp(word1[x], localarr2[k]) == 0)
            {
                int place = distance[x];
                int m = 0;
                for (m = k; m <= (k+place); m++)
                {
                    if (strcmp(word2[x], localarr2[m]) == 0 && !found[x])
                    {
                        score++;
                        found[x] = true;
                    }
                }
            }
        }
    }
    return score;
}







#include <iostream>
#include <cassert>
using namespace std;
int main()
{
    const int TEST1_NCRITERIA = 4;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    
   
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "**** 2012 ****") == 0);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "  What a NEFARIOUS plot!") == 1);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "deranged deranged robot deranged robot robot") == 1);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "Two mad scientists have deranged-robot fever.") == 0);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "                                        ") == 0);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "mad mad mad goal is the best scientist") == 0);
    assert(computeScore(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                        "blah blah blah, deranged robot") == 1);

    cout << "All tests succeeded" << endl;
}


/*
 #include <cstring>
 #include <cctype>
 using namespace std;
 
 const int MAX_WORD_LENGTH = 20;
 const int MAX_DOCUMENT_LENGTH = 200;
 
 // Convert word to lower case, returning true if the word is non-empty
 // and contains only letters.
 bool normalizeWord(char s[])
 {
    if (s[0] == '\0')  // Is word empty?
        return false;
    for (int k = 0; s[k] != '\0'; k++)
    {
        if (isalpha(s[k]))
            s[k] = tolower(s[k]);
        else // Any non-alphabetic character means the word is bad.
            return false;
    }
    return true;  // Everything was OK
 }
 
 int normalizeCriteria(int distance[], char word1[][MAX_WORD_LENGTH+1],
 char word2[][MAX_WORD_LENGTH+1], int nCriteria)
 {
    if (nCriteria < 0)
        return 0;
    int c = 0;
    while (c < nCriteria)
    {
        bool eliminateThisCriterion = false;
        if (distance[c] <= 0  ||  ! normalizeWord(word1[c])  || ! normalizeWord(word2[c]))
            eliminateThisCriterion = true;
        else
        {
 // Does an earlier criterion have the same words?  (There will
 // be at most one, since we will have previously eliminated
 // others.)
            for (int c2 = 0; c2 < c; c2++)
            {
                if (strcmp(word1[c2], word1[c]) == 0  &&
                    strcmp(word2[c2], word2[c]) == 0)
                {
 // Words match, so retain in position c2 the criterion
 // with the greater distance.
                    if (distance[c2] < distance[c])
                        distance[c2] = distance[c];
                    eliminateThisCriterion = true;
            break;
            }
        }
    }
    if (eliminateThisCriterion)
    {
 // Copy the last criterion into this one.  Don't increment c,
 // so that we examine that criterion on the next iteration.
        nCriteria--;
        distance[c] = distance[nCriteria];
        strcpy(word1[c], word1[nCriteria]);
        strcpy(word2[c], word2[nCriteria]);
    }
    else // go on to the next criterion
        c++;
    }
    return nCriteria;
 }
 
 int computeScore(const int distance[], const char word1[][MAX_WORD_LENGTH+1],
 const char word2[][MAX_WORD_LENGTH+1], int nCriteria, const char document[])
 {
 // Get document words
 
 // There can't be more than this many words.  (Worst case is a
 // document like "a a a a a ..."
 const int MAX_DOC_WORDS = MAX_DOCUMENT_LENGTH / 2;
 
 // We'll store the document words here.  If a document word is more
 // than MAX_WORD_LENGTH letters long, we'll store only the first
 // MAX_WORD_LENGTH+1 letters; since the long word can't possibly
 // match a criterion word (which is limited to MAX_WORD_LENGTH
 // characters), we'll store only enough to ensure we don't match.
 char docWord[MAX_DOC_WORDS][MAX_WORD_LENGTH+1+1];
 
 // Visit each character of the document, transferring letters into
 // the docWord array.
 int nDocWords = 0;
 int docWordPos = 0;
 for (int pos = 0; document[pos] != '\0'; pos++)
 {
    if (isalpha(document[pos]))
    {
 // Append letter to the end of the current docWord
        if (docWordPos < MAX_WORD_LENGTH+1)
        {
            docWord[nDocWords][docWordPos] = tolower(document[pos]);
            docWordPos++;
        }
    }
    else if (document[pos] == ' ')
    {
 // If a word was started, mark the end and prepare for the next
        if (docWordPos > 0)
        {
            docWord[nDocWords][docWordPos] = '\0';
            nDocWords++;
            docWordPos = 0;
        }
    }
 // Non-letter, non-blank characters aren't transferred and don't
 // end a word, so do nothing with them.
 }
 // If the document didn't end with a blank, end the last word
 if (docWordPos > 0)
 {
    docWord[nDocWords][docWordPos] = '\0';
    nDocWords++;
 }
 
 // Count matching criteria
 
 int nMatches = 0;
 
 // For each criterion
 for (int c = 0; c < nCriteria; c++)
 {
 // For each occurrence of the second word
    for (int pos2 = 1; pos2 < nDocWords; pos2++)
    {
        if (strcmp(docWord[pos2], word2[c]) != 0)
            continue;
 // Find the first word within the distance
 int pos1 = pos2 - distance[c];
 if (pos1 < 0)  // Don't start before the first word of the doc.
 pos1 = 0;
 for ( ; pos1 < pos2 && strcmp(docWord[pos1], word1[c]) != 0; pos1++)
 ;
 if (pos1 < pos2)  // found
 {
 nMatches++;
 break;  // Don't find any more matches for this criterion.
 }
 }
 }
 return nMatches;
 }

 There were 52 test cases, each worth 13/9 points. Each test case is represented by an assertion that must be true for you to pass that test. To run the test cases:
 
 Remove the main routine from your googoo.cpp file.
 Append the following text to the end of your googoo.cpp file, and build the resulting program.
 For any test case you wish to try, run the program, providing as input the test number.
 #include <iostream>
 #include <cstring>
 #include <cctype>
 #include <cstdlib>
 #include <cassert>
 
 using namespace std;
 
 int d[3] =                      {    2,    1,    3 };
 char w1[3][MAX_WORD_LENGTH+1] = { "aa", "bb", "cc" };
 char w2[3][MAX_WORD_LENGTH+1] = { "dd", "ee", "ff" };
 
 int e[2] =                      {    4,    4 };
 char x1[2][MAX_WORD_LENGTH+1] = { "aa", "cc" };
 char x2[2][MAX_WORD_LENGTH+1] = { "bb", "dd" };
 
 const int THREE_LETTERS = 26*26*26;
 int dd[THREE_LETTERS];
 char ww1[THREE_LETTERS][MAX_WORD_LENGTH+1];
 char ww2[THREE_LETTERS][MAX_WORD_LENGTH+1];
 
 bool equals(int c, int dist, const char wd1[], const char wd2[])
 {
 return d[c] == dist  &&  strcmp(w1[c], wd1) == 0  &&
 strcmp(w2[c], wd2) == 0;
 }
 
 void testone(int n)
 {
 switch (n)
 {
 case  1: {
 assert(normalizeCriteria(d, w1, w2, 0) == 0);
 } break; case  2: {
 assert(normalizeCriteria(d, w1, w2, 1) == 1  &&
 equals(0, 2, "aa", "dd"));
 } break; case  3: {
 d[0] = 0;
 assert(normalizeCriteria(d, w1, w2, 1) == 0);
 } break; case  4: {
 d[0] = 0;
 assert(normalizeCriteria(d, w1, w2, 2) == 1  &&
 equals(0, 1, "bb", "ee"));
 } break; case  5: {
 d[1] = 0;
 assert(normalizeCriteria(d, w1, w2, 2) == 1  &&
 equals(0, 2, "aa", "dd"));
 } break; case  6: {
 d[1] = 0;
 d[2] = 0;
 assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
 equals(0, 2, "aa", "dd"));
 } break; case  7: {
 d[0] = 0;
 d[1] = 0;
 assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
 equals(0, 3, "cc", "ff"));
 } break; case  8: {
 d[0] = 0;
 d[1] = 0;
 d[2] = 0;
 assert(normalizeCriteria(d, w1, w2, 3) == 0);
 } break; case  9: {
 strcpy(w1[1], "");
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 10: {
 strcpy(w2[1], "");
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 11: {
 strcpy(w1[1], "bb@");
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 12: {
 strcpy(w1[1], "bb ");
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 13: {
 strcpy(w1[1], "bBBb");
 assert(normalizeCriteria(d, w1, w2, 2) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 1, "bbbb", "ee"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 1, "bbbb", "ee")));
 } break; case 14: {
 strcpy(w1[1], "bBBb");
 strcpy(w2[1], "EeEeE");
 assert(normalizeCriteria(d, w1, w2, 2) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 1, "bbbb", "eeeee"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 1, "bbbb", "eeeee")));
 } break; case 15: {
 strcpy(w2[1], "bb");
 assert(normalizeCriteria(d, w1, w2, 2) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 1, "bb", "bb"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 1, "bb", "bb")));
 } break; case 16: {
 strcpy(w1[1], "aa");
 strcpy(w2[1], "dd");
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 17: {
 strcpy(w1[1], "aa");
 strcpy(w2[1], "dd");
 d[1] = 1;
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 18: {
 strcpy(w1[1], "aa");
 strcpy(w2[1], "dd");
 d[1] = 5;
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 5, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 5, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 19: {
 strcpy(w1[1], "aa");
 strcpy(w2[1], "dd");
 strcpy(w1[2], "aa");
 strcpy(w2[2], "dd");
 assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
 equals(0, 3, "aa", "dd"));
 } break; case 20: {
 strcpy(w1[2], "aa");
 strcpy(w2[2], "dd");
 d[1] = 0;
 assert(normalizeCriteria(d, w1, w2, 3) == 1  &&
 equals(0, 3, "aa", "dd"));
 } break; case 21: {
 strcpy(w1[1], "abcdefghijklmnopqrst");
 strcpy(w2[1], "abcdefghijklmnopqrsu");
 d[0] = 0;
 assert(normalizeCriteria(d, w1, w2, 2) == 1  &&
 equals(0, 1, "abcdefghijklmnopqrst",
 "abcdefghijklmnopqrsu"));
 } break; case 22: {
 strcpy(w2[0], "DD");
 strcpy(w1[1], "AA");
 strcpy(w2[1], "dD");
 assert(normalizeCriteria(d, w1, w2, 3) == 2  &&
 (equals(0, 2, "aa", "dd")  &&
 equals(1, 3, "cc", "ff"))  ||
 (equals(1, 2, "aa", "dd")  &&
 equals(0, 3, "cc", "ff")));
 } break; case 23: {
 int dx[7] = { 2, 4, 1, 3, 2, 1, 13 };
 char w1x[7][MAX_WORD_LENGTH+1] = { "mad", "deranged",
 "NEFARIOUS", "half-witted", "deranged", "Nefarious",
 "plot" };
 char w2x[7][MAX_WORD_LENGTH+1] = { "scientist", "robot",
 "PLOT", "assistant", "robot", "plot", "mad" };
 assert(normalizeCriteria(dx, w1x, w2x, 7) == 4);
 } break; case 24: {
 assert(computeScore(e, x1, x2, 2, "") == 0);
 } break; case 25: {
 assert(computeScore(e, x1, x2, 2, " ") == 0);
 } break; case 26: {
 assert(computeScore(e, x1, x2, 2, "aa bb") == 1);
 } break; case 27: {
 e[0] = 1;
 assert(computeScore(e, x1, x2, 2, "aa bb") == 1);
 } break; case 28: {
 e[0] = 1;
 assert(computeScore(e, x1, x2, 2, "aa     bb") == 1);
 } break; case 29: {
 assert(computeScore(e, x1, x2, 2, " aa bb") == 1);
 } break; case 30: {
 assert(computeScore(e, x1, x2, 2, "aa bb ") == 1);
 } break; case 31: {
 assert(computeScore(e, x1, x2, 2, "aa bb cc dd xx") == 2);
 } break; case 32: {
 assert(computeScore(e, x1, x2, 1, "aa bb cc dd xx") == 1);
 } break; case 33: {
 assert(computeScore(e, x1, x2, 2, "aa xx xx bb cc dd xx") == 2);
 } break; case 34: {
 assert(computeScore(e, x1, x2, 2, "aa xx xx xx bb cc dd xx") == 2);
 } break; case 35: {
 assert(computeScore(e, x1, x2, 2, "aa xx xx xx xx bb cc dd xx") == 1);
 } break; case 36: {
 e[0] = 1;
 e[1] = 1;
 assert(computeScore(e, x1, x2, 2, "aa xx bb cc dd xx") == 1);
 } break; case 37: {
 e[0] = 2;
 e[1] = 2;
 assert(computeScore(e, x1, x2, 2, "aa cc bb dd xx") == 2);
 } break; case 38: {
 assert(computeScore(e, x1, x2, 2, "aa bb aa bb cc dd xx") == 2);
 } break; case 39: {
 assert(computeScore(e, x1, x2, 2, "aa aa bb bb cc dd xx") == 2);
 } break; case 40: {
 assert(computeScore(e, x1, x2, 2, "aA bb cc dd xx") == 2);
 } break; case 41: {
 assert(computeScore(e, x1, x2, 2, "aa @@ ## $$ %% ^^ bb cc dd xx") == 2);
 } break; case 42: {
 assert(computeScore(e, x1, x2, 2, "aa b@@b cc dd xx") == 2);
 } break; case 43: {
 assert(computeScore(e, x1, x2, 2, "aa b123456789012345678901234567890b cc dd xx") == 2);
 } break; case 44: {
 e[0] = 1;
 assert(computeScore(e, x1, x2, 2, "aa abcdefghijklmnopqrstuvwxyz bb cc dd xx") == 1);
 } break; case 45: {
 e[0] = 2;
 assert(computeScore(e, x1, x2, 2, "aa abcdefghijklmnopqrstuvwxyz bb cc dd xx") == 2);
 } break; case 46: {
 strcpy(x1[0], "abcdefghijklmnopqrst");
 assert(computeScore(e, x1, x2, 2, "abcdefghijklmnopqrst bb cc dd xx") == 2);
 } break; case 47: {
 strcpy(x1[0], "abcdefghijklmnopqrst");
 assert(computeScore(e, x1, x2, 2, "abcdefghijklmnopqrstu bb cc dd xx") == 1);
 } break; case 48: {
 assert(computeScore(e, x1, x2, 2, "aaa bb cc dd xx") == 1);
 } break; case 49: {
 assert(computeScore(e, x1, x2, 2, "aa@bb cc dd xx") == 1);
 } break; case 50: {
 assert(computeScore(e, x1, x2, 2, "aa bb@cc dd xx") == 0);
 } break; case 51: {
 for (int k = 0; k < THREE_LETTERS; k++)
 {
 dd[k] = k % 2;
 strcpy(ww1[k], "a");
 strcpy(ww2[k], "aaa");
 int kk = k;
 ww2[k][2] += kk % 26;
 kk /= 26;
 ww2[k][1] += kk % 26;
 kk /= 26;
 ww2[k][0] += kk;
 }
 assert(normalizeCriteria(dd, ww1, ww2, THREE_LETTERS) == THREE_LETTERS / 2);
 for (int k = 0; k < THREE_LETTERS / 2; k++)
 assert(dd[k] == 1 && strcmp(ww1[k], "a") == 0 &&
 islower(ww2[k][2]) &&
 (ww2[k][2] - 'a') % 2 == 1);
 } break; case 52: {
 for (int k = 0; k < THREE_LETTERS; k++)
 {
 dd[k] = 1;
 strcpy(ww1[k], "a");
 strcpy(ww2[k], "aaa");
 int kk = k;
 ww2[k][2] += kk % 26;
 kk /= 26;
 ww2[k][1] += kk % 26;
 kk /= 26;
 ww2[k][0] += kk;
 }
 assert(computeScore(dd, ww1, ww2, THREE_LETTERS,
 "a aaa a iaa a pzz a zzz") == 4);
 assert(computeScore(dd, ww1, ww2, THREE_LETTERS,
 "a aaaa a iaaa a pzzz a zzzz") == 0);
 } break;
 }
 }
 
 int main()
 {
 cout << "Enter a test number (1 to 52): ";
 int n;
 cin >> n;
 if (n < 1  ||  n > 52)
 {
 cout << "Bad test number" << endl;
 return 1;
 }
 testone(n);
 cout << "Passed test " << n << endl;
 }

*/