#include "Functions.h"

bool isDigits(string str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

// TO HELP WITH READING A CSV FILE THAT CONTAINS COMMAS IN FIELDS
// THE FOLLOWING TWO FUNCTIONS HAVE BEEN PROVIDED FOR YOU
 

vector<string> parseCSVLine(const string& line) {
    vector<string> result; // the input line with strings representing each field
    string value;
    bool inQuotes = false;

    for (char ch : line) {
        // if the current character is a quote - toggle the inQuotes field
        if (ch == '\"') 
            inQuotes = !inQuotes;

        // if we hit a comma and it is not in quotes
        // add current field to result
        else if (ch == ',' && !inQuotes) { 
            result.push_back(value);
            value.clear();
        }

        // Inside quotes or a regular character
        else {
            
            value += ch;
        }
    }

    // Add the last field
    result.push_back(value);

    return result;
}

// THIS FUNCTION WILL PARSE  Function to parse a CSV field
vector<string> parseCSVField(const string& line) {
    vector<string> result;
    string field;
    istringstream iss(line);
    while (getline(iss, field, ',')) {
        if (field[0] == ' ')
            field = field.substr(1);
        result.push_back(field);
    }
    return result;
}

 
void loadVector(ifstream& in, ofstream& err, vector<showInfo>& shows, 
                vector<countryInfo>& country,vector<genreCount> &gCount) {
    string line;
    genreCount tempG;
    countryInfo genreCountry;
    bool isFound, countryFound;

    while (getline(in, line)) {
        // Parse the line into fields
        vector<string> tokenList = parseCSVLine(line);

        showInfo show;
        try {
            if (tokenList.size() != 11) {
                throw runtime_error("Invalid number of tokens");
            }
            show.type = tokenList[1];
            show.title = tokenList[2];

            // parse field of 'countries' into individual parts
            vector<string> countries = parseCSVField(tokenList[4]);
            if (countries.size() == 0) {
                throw runtime_error("No Countries Listed");
            }
            if (tokenList[6].find_first_not_of("0123456789") != string::npos) {
                throw runtime_error("Release Year Invalid");
            }


            // add lots of logic here :-)
            vector<string> genres = parseCSVField(tokenList[9]);
            for (int i = 0; i < genres.size(); ++i) {
                isFound = false;
                for (int j = 0; j < gCount.size(); ++j) {
                    if (genres.at(i) == gCount.at(j).genre) {
                        gCount.at(j).count++;
                        isFound = true;
                        for (int k = 0; k < countries.size(); ++k) {
                            countryFound = false;
                            for (int l = 0; l < gCount.at(j).countries.size(); ++l) {
                                if (countries.at(k) == gCount.at(j).countries.at(l).country) {
                                    gCount.at(j).countries.at(l).count++;
                                    countryFound = true;
                                    break;
                                }
                            }
                            if (!countryFound) {
                                genreCountry.country = countries.at(k);
                                genreCountry.count = 1;
                                gCount.at(j).countries.push_back(genreCountry);
                            }
                        }
                        break;
                    }
                }
                if (!isFound) {
                    tempG.genre = genres.at(i);
                    tempG.count = 1;
                    for (int k = 0; k < countries.size(); ++k) {
                        genreCountry.country = countries.at(k);
                        genreCountry.count = 1;
                        tempG.countries.push_back(genreCountry);
                    }
                    gCount.push_back(tempG);
                }
            }
        }
        catch (const runtime_error& e) {
            err << left << "Error: " << setw(28) << e.what() << " - " << line << endl;
            continue;
        }
        catch (...) {
            err << left << "Error: " << " - " << line << endl;
            continue;
        }
    }
            
}
void sortByCount(vector <genreCount>& gCount) {
    int max, start;
    for (int i = 0; i < 20; i++) {
        max = i;
        for (int j = i + 1; j < gCount.size(); ++j) {
            if (gCount.at(j).count > gCount.at(max).count) {
                max = j;
            }
        }
        swap(gCount.at(i), gCount.at(max));
    }
}
void sortByCountry(vector<countryInfo>& countries) {
    int max;
    for (int i = 0; i < 8; ++i) {
        max = i;
        for (int j = i + 1; j < countries.size(); ++j) {
            if (countries.at(j).count > countries.at(max).count) {
                max = j;
            }
        }
        swap(countries.at(i), countries.at(max));
    }
}

 
void printReport(ofstream& report, vector<genreCount> gCount, vector<countryInfo> country) {
    for (int i = 0; i < 20; ++i) {
        report << left <<  "Genre: " << setw(30) << gCount.at(i).genre << "Count: " << gCount.at(i).count << endl;
        for (int j = 0; j < 8; ++j) {
            report << setw(20) << gCount.at(i).countries.at(j).country << gCount.at(i).countries.at(j).count << endl;
        }
    }
}
