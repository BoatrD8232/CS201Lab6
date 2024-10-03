// CS201L-Lab6-FileIO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Functions.h"

int main()
{
    ifstream inFile;
    ofstream errFile, outFile1;


    inFile.open("netflix_titles.csv");
    errFile.open("error.txt");
    outFile1.open("report.txt");
 
    if (!inFile.good() || !outFile1.good()) {
        cout << "error opening files\n";
        return 0;
    }

    vector<showInfo> shows;
    vector<countryInfo> country;
    vector<genreCount> gCount;

    loadVector(inFile, errFile, shows, country, gCount);
    sortByCount(gCount);
    for (int i = 0; i < 20; i++) {
        sortByCountry(gCount.at(i).countries);
    }
    /*for (int i = 0; i < 20; ++i) {
        cout << gCount.at(i).genre << ": " << gCount.at(i).count << endl;
        sortByCountry(gCount.at(i).countries);
        for (int j = 0; j < gCount.at(i).countries.size(); ++j) {
            cout << gCount.at(i).countries.at(j).country << " | " << gCount.at(i).countries.at(j).count << endl;
        }
        cout << endl;
    }*/
 

    printReport(outFile1, gCount, country);

    inFile.close();
    errFile.close();
    outFile1.close();
}