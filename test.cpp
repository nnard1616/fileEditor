#include <iostream>
#include "helperFunctions.h"

using namespace std;

void testDriver(){
    cout << "testing" << endl;
}



int main() {
    cout << "Run test driver (T) or user interface (U): ";
    char choice, inchoice;
    cin >> inchoice;
    choice = toupper(inchoice);
    if (choice == 'T')
        testDriver();
    else if (choice == 'U') {
//        UIDetectiveOffice ui;
//        ui.process();
        cout << "WIP" << endl;
    }
    return 0;
}

