
#include "ui.h"
//void closeFileWchanges(editTracker& current){
//    cout << "Saving changes to the file:" << endl;
//    cout << current;

//    ofstream outfile;
//    outfile.open(current.fileName);

//    ostream_iterator<string> osit (outfile, "\n");
//    copy(current.lines.begin(), current.lines.end(), osit);

//    outfile.close();
//    cout << "Successfully saved the file." << endl;
//}

void appendString(size_t pos, string& line){
    string newString;
    int newLineLength;
    string inchoice;
    char choice;
    bool finished = false;
    do{
        cout << "What would you like to append? : " << endl;
        getline(cin, newString);
        newLineLength = (line.size()+newString.size());
//        cout << "1" << endl;
        if ( newLineLength > 256){
            do{
                cout << "The result of the indicated operation would exceed the max length of a line by " << newLineLength-256 << "." << endl
                     << "Would you like to try again? (y/n): ";
                cin >> inchoice;
                choice = toupper(inchoice[0]);
            } while (choice != 'Y' && choice != 'N');
            if (choice == 'N')
                finished = true;
            choice = 'a';
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else{
//            cout << "2" << endl;
            line.insert(pos, newString);
            finished = true;
        }
//        cout << "3 " << finished  << " " << line.substr(pos, 15) << endl;
    }while(finished == false);
}

void testDriver(){
    cout << "testing" << endl;
    string thing;
    cin >> thing;
    ifstream inFile;
//    ofstream outFile;
    typedef vector<editTracker>::iterator vetITR;
    inFile.open("testFile.txt");

    cout << "a" <<endl;

    string sLine;
//    vector< vector<string> > lines;
//    while(getline(inFile, sLine))
//        lines.push_back(split(sLine));
//    int countChars = 0;
//    for (auto itr = lines.begin(); itr != lines.end(); itr++){
//        countChars = 0;
//        for (auto itr2 = itr->begin(); itr2 != itr->end(); itr2++)
//            countChars += itr2->size();
//        countChars += (itr->size()-1);
//        cout << countChars << endl;
//    }






    editTracker history("testFile.txt");
    while(getline(inFile, sLine))
        history.lines.push_back(sLine);
    for (auto itr = history.lines.begin(); itr != history.lines.end(); itr++)
        cout << itr->size() << endl;
    if (validFile(history))
        cout << "Valid!" << endl;
    else
        cout << "Not valid!" << endl;




    inFile.close();

    vector<editTracker> tracks;
    editTracker test("test");

    cout << history << endl;
    if (history.lines.size() == 0)
        cout << "File is empty" << endl;

    tracks.push_back(test);

    tracks.push_back(history);
    vetITR itr = tracks.end()-1;


    cout << "testing the iter" << endl << *itr << endl;
    cout << itr->lines.size() << endl;
    size_t found;
    string query = "unicorn";
    int count = 0;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    for(auto litr = itr->lines.begin(); litr != itr->lines.end(); litr++){
//        cout << *litr << endl;
        found = litr->find(query);

        while (found != string::npos){
//            cout << count << "|" << found << endl;
            try{
                cout << litr->substr(found-15, query.size()+30);
            }
            catch(...){
                try{
                    cout << litr->substr(0, query.size()+30);
                }
                catch(...){
                    try{
                        cout << litr->substr(found-15);
                    }
                    catch(...){
                        cout << litr->substr(0);
                    }
                }

            }
            appendString(found+query.size(), *litr);
            found = litr->find(query, found+query.size()+1);
        }
//        cout << *litr << endl;
        count++;
    }
//    closeFileWchanges(*itr);

    cout << "==========================================="<<endl;

}



int main(int argc, char* argv[]) {
    if (argc > 2){
        cerr << "Please give a file name as an argument, or none at all." << endl;
        return 1;
    }
    else{
        UI ui;
        if (argc == 2){
            ui.openFile(string(argv[1]));
        }
        else{
            ui.openFile();
        }
    }
    return 0;
}

