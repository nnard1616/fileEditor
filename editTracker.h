#ifndef EDITTRACKER_H
#define EDITTRACKER_H
#include "helperFunctions.h"
struct editTracker{
    editTracker(string inFileName);
    int replaceCTR;
    int insertCTR;
    int appendCTR;
    int totalEdits(){return (replaceCTR+insertCTR+appendCTR);}
    string fileName;
    vector<string> lines;

    friend ostream& operator<< (ostream& osObject, editTracker etObject);
//    editTracker& operator+= (const editTracker& right);
};

#endif // EDITTRACKER_H
