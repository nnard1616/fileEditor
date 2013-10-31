#include "helperFunctions.h"

vector<string> split(string query){
    vector<string> strings;
    istringstream iss(query);
    string s;
    while (getline(iss, s, ' ')){
        strings.push_back(s);
    }
    return strings;
}


bool greedy_phrase_comparison(const string &searchField, const string &query){
    vector<string> fieldTerms = split(searchField);
    vector<string> queryTerms = split(query);
    for (auto x = queryTerms.begin(); x != queryTerms.end(); x++)
        for (auto y = fieldTerms.begin(); y != fieldTerms.end(); y++)
            if (upper(*y) == upper(*x))
                return true;

    return false;
}

string upper(const string query){
    string big;
    string letter;
    for (auto itr = query.begin(); itr != query.end(); itr++){
        letter = toupper(*itr);
        big.append(letter);
    }
    return big;
}
