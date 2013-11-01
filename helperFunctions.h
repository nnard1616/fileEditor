#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stdio.h>  /* defines FILENAME_MAX */


using namespace std;
vector<string> split(string query);
bool greedy_phrase_comparison(const string &searchField, const string& query);//semi greedy, actually :P
string upper(const string query);
#endif // HELPERFUNCTIONS_H
