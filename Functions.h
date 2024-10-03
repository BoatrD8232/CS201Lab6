#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//NOTE: these structs may be changed!!
struct showInfo {
    string country;
    string type;
    string title;
    int releaseYear;
    string rating;
    string duration;
    vector<string> genres;
    string description;
};

struct countryInfo {
    string country;
    string genre;
    int count;
};

struct genreCount {
    string genre;
    int count;
    vector<countryInfo> countries;
};


//PRE: Accept input stream, output file stream (for errors) and empty vectors for showInfo & countryInfo
//POST:Read input stream which will load the fields in shows & countrys
void loadVector(ifstream& in, ofstream& err, vector<showInfo>& shows, 
                vector<countryInfo>& country, vector<genreCount> &gCount);


//PRE: Accepts loaded vector
//POST:Prints vector to report
void printReport(ofstream& report, vector<genreCount> gCount, vector<countryInfo> country);

//PRE: Accepts an unsorted vector of genres
//POST: outputs a sorted vertor of genres
void sortByCount(vector <genreCount>& gCount);

//PRE: Accepts an unsorted vector of country
//POST: outputs a sorted vector of countries
void sortByCountry(vector<countryInfo>& countries);