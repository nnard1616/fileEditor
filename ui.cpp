#include "ui.h"

UI::UI()
{
}

void UI::openFile(){
    string inchoice;
    char choice;
    bool finished = false;
    do{
        do{
            cout << "Do you have a file you wish to open for editing? (y/n): ";
            cin >> inchoice;
            choice = toupper(inchoice[0]);
        } while (choice != 'Y' && choice != 'N');

        if (choice == 'Y'){
            ifstream inFile;
            string fileName;
            cout << "Please enter the file name you wish to open: ";
            cin >> fileName;
            inFile.open("testFile.txt");



        }
        else
            finished = true;

    }while(finished == false);

}
