// Code for Project 1
// Report student survey results

#include <iostream>
#include <iomanip>
using namespace std;       // see p. 36-37 in Savitch book

int main()
{
    int surveyed;
    int studiers;
	
    cout << "How many students were surveyed? ";
    cin >> surveyed;
    cout << "How many of them study more than 20 hours per week? ";
    cin >> studiers;
	
    double pctStudiers = 100.0 * studiers / surveyed;
    
    // The following line ensures that fractional numbers will be
    // printed with 1 digit to the right of the decimal point.
    cout << fixed << setprecision(1);
	
    cout << endl;
    cout << pctStudiers << "% study more than 20 hours per week." << endl;
    
    // See http://usatoday.com/news/education/story/2011-11-17/college-students-study-hours/51245162/1
    if (pctStudiers >= 40)
        cout << "The survey must include a lot of engineers!" << endl;
}