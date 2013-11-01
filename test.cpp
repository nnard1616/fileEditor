
#include "ui.h"


void testDriver(){
    cout << "testing" << endl;
    ifstream inFile;
//    ofstream outFile;

    inFile.open("testFile.txt");

    cout << "a" <<endl;
    vector<string> sLines;
    string sLine;
    while(getline(inFile, sLine))
        sLines.push_back(sLine);
    for (auto itr = sLines.begin(); itr != sLines.end(); itr++)
        cout << *itr << endl;

    inFile.close();

    editTracker history("testFile.txt");
    cout << history << endl;
}



int main() {
    cout << "Run test driver (T) or user interface (U): ";
    char choice, inchoice;
    cin >> inchoice;
    choice = toupper(inchoice);
    if (choice == 'T')
        testDriver();
    else if (choice == 'U') {
//        UI ui;
//        ui.process();
        cout << "WIP" << endl;
    }
    return 0;
}

