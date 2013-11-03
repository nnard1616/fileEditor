#include "editTracker.h"

editTracker::editTracker(string inFileName){
    replaceCTR = 0;
    insertCTR = 0;
    appendCTR = 0;
    fileName = inFileName;
}

ostream& operator <<(ostream& osObject, editTracker etObject){
    osObject << "File Name: " << etObject.fileName << endl
             << "Number of replacements: " << etObject.replaceCTR << endl
             << "Number of insertions: " << etObject.insertCTR << endl
             << "Number of appends: " << etObject.appendCTR << endl
             << "Total Edits: " << etObject.totalEdits() << endl;
    return osObject;
}
