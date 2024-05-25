#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

ifstream fin("input.in");
ofstream fout("places.json");

vector<string> splitCSV(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string item;
    bool insideQuotes = false;

    while (ss.good()) {
        char c = ss.get();
        if (c == '"') {
            insideQuotes = !insideQuotes;
        } else if (c == ',' && !insideQuotes) {
            result.push_back(item);
            item.clear();
        } else {
            item += c;
        }
    }
    result.push_back(item);
    return result;
}

float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}
int main() {
    string input;
    string line;

    // Read the input from file until end of file
    while (getline(fin, line)) {
        input += line + "\n";
    }

    stringstream inputSS(input);
    fout << "[" << endl; // Start of JSON array

    bool first = true;
    while (getline(inputSS, line)) {
        if (!first) {
            fout << "," << endl; // Add comma between JSON objects
        }
        first = false;

        vector<string> fields = splitCSV(line);

        fout << "{" << endl;
        fout << "    \"geometry\": {" << endl;
        fout << "        \"location\": {" << endl;
        fout << "            \"lat\": " << fields[8] << "," << endl;
        fout << "            \"lng\": " << fields[9] << endl;
        fout << "        }," << endl;
        fout << "        \"viewport\": {" << endl;
        fout << "            \"northeast\": {" << endl;
        fout << "                \"lat\": " << stof(fields[8]) + 0.001 << "," << endl;
        fout << "                \"lng\": " << stof(fields[9]) + 0.001 << endl;
        fout << "            }," << endl;
        fout << "            \"southwest\": {" << endl;
        fout << "                \"lat\": " << stof(fields[8]) - 0.001 << "," << endl;
        fout << "                \"lng\": " << stof(fields[9]) - 0.001 << endl;
        fout << "            }" << endl;
        fout << "        }" << endl;
        fout << "    }," << endl;
        fout << "    \"name\": \"" << fields[2] << "\"," << endl;
        fout << "    \"rating\": ";
        int random_number = 1 + ( std::rand() % ( 5 - 1 + 1 ) );
        fout<<random_number;
        fout<< "," << endl; // Assuming a fixed rating for this example
        fout << "    \"vicinity\": \"" << fields[4] << ", " << fields[5] << ", " << fields[6] << "\"" << endl;
        fout << "}";
    }

    fout<<endl << "]" << endl; // End of JSON array
    return 0;
}
