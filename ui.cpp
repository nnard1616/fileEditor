#include "ui.h"

UI::UI()
{
    currFileEditITR = fileEdits.end();
}

void UI::openFile(){//no args given and/or continuation of opening files loop
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

            bool previouslyOpened = false;
            for (auto it = fileEdits.begin(); it != fileEdits.end(); it++){
                if (it->fileName == fileName){
                    currFileEditITR = it;
                    previouslyOpened = true;
                    searchOrEnd();
                }
            }

            if (!previouslyOpened){
                editTracker fileInfo(fileName);
                inFile.open(fileName);

                string sLine;
                while(getline(inFile, sLine))
                    fileInfo.lines.push_back(sLine);
                inFile.close();

                if (fileInfo.lines.size() == 0)
                    cout << "File does not exist or it is empty, please try again." << endl;//not really sure what you want me to do here, I am assuming you want me to do nothing. xD
                else if (!::validFile(fileInfo))
                    cout << "File has either too many lines (more than 10) or line(s) that are too long (256 chars max).  Please try again." << endl;
                else{
                    fileEdits.push_back(fileInfo);
                    currFileEditITR = fileEdits.end()-1;
                    searchOrEnd();
                }
            }
        }
        else
            finished = true;

    }while(finished == false);
    cout << "Editing has finished.  Here are the number of changes per file edited: " << endl;
    int totalInserts = 0, totalAppends = 0, totalReplaces = 0;
    for (auto eitr = fileEdits.begin(); eitr != fileEdits.end(); eitr++){
        cout << *eitr << endl;
        totalInserts += eitr->insertCTR;
        totalAppends += eitr->appendCTR;
        totalReplaces += eitr->replaceCTR;
    }
    cout << "============================================================\n";
    cout << "Total files edited with total number of edits: " << endl << "============================================================\n"
         << "Total Files Edited: " << fileEdits.size() << endl
         << "Total Number of Edits (breakdown below) : " << (totalInserts+totalAppends+totalReplaces) << endl
         << "Total Replaces: " << totalReplaces << endl
         << "Total Inserts: " << totalInserts << endl
         << "Total Appends: " << totalAppends << endl;

}//not completely finished here

void UI::searchOrEnd(){
    string inchoice;
    char choice;
    bool finished = false;
    do{
        cout << "What would you like to do?\n";
        bool notanoption = true;
        do{
               cout << "\tA) Start a new search" << endl
                    << "\tB) Close file without saving changes" << endl
                    << "\tC) Close file after saving changes" << endl;
               cin >>  inchoice;
               choice = toupper(inchoice[0]);
               string choicecheck(1,choice);
               if (choicecheck.find_first_of("ABC") == string::npos)
                   cout << inchoice << " not in the list of options; redo" << endl;
               else
                   notanoption = false;
            } while (notanoption == true);
        switch(choice){
            case 'A':
                search();
                break;
            case 'B':
                closeFileWOchanges();
                finished = true;
                break;
            case 'C':
                closeFileWchanges();
                finished = true;
                break;
            default:
                cout << "User entered " << choice << " for their choice" << endl;
        }
    }while(finished == false);
}//may not be finished

void UI::search(){
    string inchoice;
    char choice;
    bool finished = false;
    bool success = false;
    int numOfEdits = 0;
    string query;
    cout << "Please enter the word or phrase you wish to search for: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, query);
    size_t found = 0;

    for (auto lineITR = currFileEditITR->lines.begin(); lineITR != currFileEditITR->lines.end(); lineITR++){
        found = lineITR->find(query);
        while(found != string::npos){

            int sizeAdjustment;
            success = true;
            cout << "Found an occurrence:\n\n"
                 << "\t" << returnSubStr(found, query, *lineITR) << endl << endl
                 << "What would you like to do?\n";
            bool notanoption = true;
            do{
                   cout << "\tA) Replace instance of query" << endl
                        << "\tB) Keep instance of query" << endl
                        << "\tC) Insert new string at instance of query" << endl
                        << "\tD) Append new string after instance of query" << endl
                        << "\tE) End searching process with query" << endl;
                   cin >>  inchoice;
                   choice = toupper(inchoice[0]);
                   string choicecheck(1,choice);
                   if (choicecheck.find_first_of("ABCDE") == string::npos)
                       cout << inchoice << " not in the list of options; redo" << endl;
                   else
                       notanoption = false;
                } while (notanoption == true);
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            switch(choice){
                case 'A':
                    replaceString(found, query, *lineITR);
                    found = lineITR->find(query, found+1);
                    numOfEdits++;
                    if (numOfEdits%3 == 0)
                        saveTemp();
                    break;
                case 'B':
                    found = lineITR->find(query, found+1);
                    break;
                case 'C':
                    sizeAdjustment = insertString(found, *lineITR);
                    found = lineITR->find(query, found+sizeAdjustment+1);
                    numOfEdits++;
                    if (numOfEdits%3 == 0)
                        saveTemp();
                    break;
                case 'D':
                    appendString(found+query.size(), *lineITR);
                    found = lineITR->find(query, found+query.size()+1);
                    numOfEdits++;
                    if (numOfEdits%3 == 0)
                        saveTemp();
                    break;
                case 'E':
                    found = string::npos;
                    finished = true;
                    break;
                default:
                    cout << "User entered " << choice << " for their choice" << endl;
            }
        }
        found = 0;
        if(finished == true)
            break;//end the for loop early, search is over
    }
    if (!success)
        cout << "No item matching your query was found in the document." << endl;

}
void UI::closeFileWOchanges(){
    remove(("temp-"+currFileEditITR->fileName).c_str());
    cout << "Closing file without any changes." << endl;
    fileEdits.erase(currFileEditITR);
}

void UI::closeFileWchanges(){
    remove(("temp-"+currFileEditITR->fileName).c_str());
    cout << "Saving changes to the file:" << endl;
    cout << *currFileEditITR;

    ofstream outfile;
    outfile.open(currFileEditITR->fileName);

    ostream_iterator<string> osit (outfile, "\n");
    copy(currFileEditITR->lines.begin(), currFileEditITR->lines.end(), osit);

    outfile.close();
    cout << "Successfully saved temp file." << endl;

}

void UI::saveTemp(){
    string tempName = "temp-" + currFileEditITR->fileName;
    ofstream outfile;
    outfile.open(tempName);

    ostream_iterator<string> osit (outfile, "\n");
    copy(currFileEditITR->lines.begin(), currFileEditITR->lines.end(), osit);

    outfile.close();

}


void  UI::replaceString(size_t pos, string &query, string &line){
    string newString;
    int newLineLength;
    string inchoice;
    char choice;
    bool finished = false;
    do{
        cout << "What would you like to replace the found string with? : " << endl;
        getline(cin, newString);
        newLineLength = (line.size()-query.size()+newString.size());
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
            line.replace(pos, query.size(), newString);
            finished = true;
            currFileEditITR->replaceCTR++;
        }
    }while(finished == false);
}

int UI::insertString(size_t pos, string &line){
    string newString;
    int newLineLength;
    string inchoice;
    char choice;
    bool finished = false;
    do{
        cout << "What would you like to insert? : " << endl;
        getline(cin, newString);
        newLineLength = (line.size()+newString.size());
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
            line.insert(pos, newString);
            finished = true;
            currFileEditITR->insertCTR++;
        }
    }while(finished == false);
    return newString.size();
}

void UI::appendString(size_t pos, string &line){
    string newString;
    int newLineLength;
    string inchoice;
    char choice;
    bool finished = false;
    do{
        cout << "What would you like to append? : " << endl;
        getline(cin, newString);
        newLineLength = (line.size()+newString.size());
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
            line.insert(pos, newString);
            finished = true;
            currFileEditITR->appendCTR++;
        }
    }while(finished == false);
}

string UI::returnSubStr(size_t pos, string query, string line){// Hurray, it works! :P
    try{
        return (line.substr(pos-15, query.size()+30));
    }
    catch(...){
        try{
            return (line.substr(0, query.size()+30));
        }
        catch(...){
            try{
                return (line.substr(pos-15));
            }
            catch(...){
                return (line.substr(0));
            }
        }
    }
}

bool validFile(editTracker& query){
    if (query.lines.size() <= 10){
        for (auto itr = query.lines.begin(); itr != query.lines.end(); itr++)
            if (itr->size() > 256)
                return false;
        return true;
    }
    return false;
}
