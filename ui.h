#ifndef UI_H
#define UI_H
#include "editTracker.h"
#include "helperFunctions.h"

class UI{
public:
    UI();
    void openFile();
    void search(string fileName);
    vector<editTracker> fileEdits;
//    vector<string> lines;
//    main(int argc, char** argv);

};

#endif // UI_H
