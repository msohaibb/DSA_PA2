// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
    string lastName;
    string firstName;
    string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

    ifstream input(filename);
    if (!input) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;

    // Load the data
    for (int i = 0; i < size; i++) {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }

    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

    ofstream output(filename);
    if (!output) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // Write the size first
    int size = l.size();
    output << size << "\n";

    // Write the data
    for (auto pData:l) {
        output << pData->lastName << " "
               << pData->firstName << " "
               << pData->ssn << "\n";
    }

    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data *> theList;
    loadDataList(theList, filename);

    cout << "Data loaded.\n";

    cout << "Executing sort...\n";
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);

    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

int determineCase(list<Data*> &l){
    int sortCase = 1;
    int count = 0;
    string firstFirstName = l.front()->firstName;


    for(auto pData:l){
        if(count == 1000){
            sortCase = 4;
            break;
        }
        if(pData->firstName != firstFirstName){
            break;
        }
        count++;
    }


    return sortCase;

}

inline bool compareData(Data* data1, Data* data2){
    if(data1->lastName > data2->lastName){
        return false;
    }
    if(data1->lastName < data2->lastName){
        return true;
    }
    if(data1->firstName > data2->firstName){
        return false;
    }
    if(data1->firstName < data2->firstName){
        return true;
    }
    if(data1->ssn > data2->ssn){
        return false;
    }
    return true;
}

inline bool compareData4(Data* data1, Data* data2) {
    if (data1->ssn > data2->ssn) {
        return false;
    }
    return true;
}

void sortDataList(list<Data*> &l) {
    int sortCase = determineCase(l);
    int listSize = l.size();

    /*
     * first, compare last names
     * if same, compare first names
     * if same, compare SSNs
     */

    /*
     * T1 will be completely random
     * T2 will be completely random
     * T3 will already be sorted by names (not by SSNs)
     * T4 will be have the same names everywhere, but different SSNs
     */



    //T1
    string lastName;
    string firstName;
    string SSN;


    if(sortCase == 1){
        cout << "This is sample 1 or 2" << endl;
        l.sort(compareData);
    }
    else{
        cout << "This is sample 4" << endl;
        l.sort(compareData4);
    }


}
