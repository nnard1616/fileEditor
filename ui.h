#ifndef UI_H
#define UI_H
#include "editTracker.h"
#include "helperFunctions.h"

bool validFile(editTracker& query);
typedef vector<editTracker>::iterator vetITR;
class UI{
public:
    UI();
    void openFile();
    void searchOrEnd();//asks if user wants to do more searching/edits, or if they want to save (or not save) and close the file
    void search();
    vector<editTracker> fileEdits;
    vetITR currFileEditITR;
    bool validFile();
    void replaceString(size_t pos, string& query, string& line);
    int insertString(size_t pos, string& line);
    void appendString(size_t pos, string& line);
    void closeFileWchanges();
    void closeFileWOchanges();
    void saveTemp();
    string returnSubStr(size_t pos, string query, string line);
//    vector<string> lines;
//    main(int argc, char** argv);

};

#endif // UI_H
