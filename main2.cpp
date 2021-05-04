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
// class definitions here if you wish.


int determineCase(list<Data*> &l){
    int sortCase = 1;
    int count = 0;
    int count2 = 0;
    string firstFirstName = l.front()->firstName;
    string firstLastName = l.front()->lastName;


    for(auto pData:l){
        if(count == 100){
            sortCase = 4;
            return sortCase;
        }
        if(pData->firstName != firstFirstName){
            break;
        }
        count++;
    }

    for(auto pData:l){
        if(count2 == 2){
            sortCase = 3;
            return sortCase;
            break;
        }
        if(pData->firstName != firstFirstName && pData->lastName != firstLastName){
            break;
        }
        count2++;
    }

    if(l.size() > 500000){
        sortCase = 2;
    }

    return sortCase;

}

int convertSSN(Data* data){
    return std::stoi(data->ssn.substr(0,3) + data->ssn.substr(4,2) + data->ssn.substr(7,4));
}

string convertDigits(int ssn){
    string stringSSN = std::to_string(ssn);
    while(stringSSN.length() != 9){
        stringSSN = "0" + stringSSN;
    }
    stringSSN.insert(3, "-");
    stringSSN.insert(6, "-");
    return stringSSN;
}


int theArray[1010001];

void binSort(int unsortedArray[], int size, int place)
{
    int buckets[10] = {0};

    for(int i = 0; i < size; i++){
        buckets[(unsortedArray[i]/place) % 10]++;
    }

    for(int bucketIndex = 1; bucketIndex < 10; bucketIndex++){
        buckets[bucketIndex] += buckets[bucketIndex - 1];
    }

    for(int j = size - 1; j >= 0; j--){
        theArray[buckets[(unsortedArray[j]/place) % 10] - 1] = unsortedArray[j];
        buckets[(unsortedArray[j]/place) % 10]--;
    }

    for (int k = 0; k < size; k++){
        unsortedArray[k] = theArray[k];
    }
}

void radixSort(int unsortedArray[], int size){
    for (int place = 1; 999999999/place > 0; place *= 10){
        binSort(unsortedArray, size, place);
    }
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

/*inline bool compareData4(Data* data1, Data* data2) {
    if (data1->ssn > data2->ssn) {
        return false;
    }
    return true;
}*/

int indirectArray[1010001];
list<list<Data*>> miniLists(100000);
list<Data*> tempList(20);
int SSNsRadix[100000];

void siftT3(list<Data*> &l){
    string currentFirstName = l.front()->firstName;
    string currentLastName = l.front()->lastName;
    int tempSize = 0;
    int i = 0;
    Data* tempData = nullptr;

    for(auto it = l.begin(); it != l.end(); ++it)
    {
        if((*it)->firstName == currentFirstName && ((*it)->lastName) == currentLastName){
            tempList.push_front(*it);
            tempSize++;
        }
        //cout << "done finding same names" << endl;
        else{
            i = 0;
            tempData = *it;
            cout << "tempData : ";
            cout << tempData->lastName << " " << tempData->firstName << " " << tempData->ssn << endl;
            for(auto test:tempList){
                if(tempSize == i){
                    break;
                }
                cout << "tempList: ";
                cout << test->lastName << " " << test->firstName << " " << test->ssn << endl;
                i++;
            }
            cout << endl;
            miniLists.push_front(tempList);
            cout << "list pushed!" << endl;
            i = 0;
            for(auto currentData:tempList){
                if(i == tempSize){
                    break;
                }

                SSNsRadix[i] = convertSSN(currentData);
                i++;
                cout << "populating array" << endl;

            }
            cout << "sorting" << endl;
            radixSort(SSNsRadix, i);
            cout << "sort done" << endl;

            //ofstream output("test.txt");

            i = 0;
            for(auto currentData1:tempList){
                if(i == tempSize){
                    break;
                }
                currentData1->ssn = convertDigits(SSNsRadix[i]);
                cout << "populating templist" << endl;
                cout << currentData1 -> lastName << " " << currentData1 -> firstName << " " << currentData1->ssn << endl;
                i++;
            }
            cout << endl;
            tempList.clear();
            tempList.push_front(tempData);
            tempSize = 1;
            currentFirstName = (*it)->firstName;
            currentLastName = (*it)->lastName;
        }
        auto it1 = l.begin();
        auto it2 = miniLists.end();
        l.clear();
        for(; it1 != l.end() && it2 != miniLists.end(); ++it1, ++it2)
        {

            auto it3 = (*it2).begin();
            for(; it3 != (*it2).end(); ++it3) {
                 l.push_front(*it3);
            }
        }



        //miniLists.push_back()
    }
};


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
     * T2 will be completely random (bigger than T2)
     * T3 will already be sorted by names (not by SSNs)
     * T4 will be have the same names everywhere, but different SSNs
     */

    //setPartialData(l);

    ofstream output("test.txt");

    //radixSort(indirectArray, listSize);


    if(sortCase == 1){
        cout << "This is sample 1" << endl;
        l.sort(compareData);
    }

    else if(sortCase == 2){
        cout << "This is sample 2" << endl;
        l.sort(compareData);
        /*theList.sort(comparePartialData);
        output << listSize << endl;
        for(const auto& currentData:theList){
            output
                << currentData.dataAddress->lastName  << " "
                << currentData.dataAddress->firstName<< " "
                << currentData.dataAddress->ssn << endl;
        }*/


    }

    else if(sortCase == 3){
        cout << "This is sample 3" << endl;
        siftT3(l);
        //l.sort(compareData);
    }

    else{
        cout << "This is sample 4" << endl;

        int i = 0;
        for(auto currentData:l){
            if(i == listSize){
                break;
            }
            indirectArray[i] = convertSSN(currentData);
            i++;
        }
        radixSort(indirectArray, listSize);

        i = 0;
        for(auto currentData:l){
            if(i == listSize){
                break;
            }
            currentData->ssn = convertDigits(indirectArray[i]);
            i++;
        }
        //radixSort(l);
    }
}

/*int getMax(list<Data*> &l)
{
    int max = convertSSN(l.front());
    for(auto pData:l){
        if (max < convertSSN(pData)){
            max = convertSSN(pData);
        }
    }
    return max;
}


void countingSort(list<Data*> &l, int div)
{
    int buckets[10] = {0};
    int size = l.size();
    for(auto pData:l) {
        buckets[(convertSSN(pData) / div) % 10]++;
    }
    for (int i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];
    for (auto it = l.rBegin(); it != l.rend(); ++it){
        theArray[buckets[(convertSSN(*it)/div)%10] - 1] = convertSSN(*it);
        buckets[ (convertSSN(*it)/div)%10 ]--;
    }
    int i = 0;
    for(auto pData:l){
        if(i == size){
            break;
        }
        pData->ssn = convertDigits(theArray[i]);
        i++;
    }
}
void radixSort(list<Data*> &l){
    int max = getMax(l);
    for (int div = 1; max/div > 0; div *= 10) {
        countingSort(l, div);
    }
}*/


/*class partialData{
public:
    string partialLastName;
    string partialFirstName;
    Data* dataAddress{};

    partialData(){}

    partialData(string PLN, string PFN, Data* DA){
        partialLastName = PLN;
        partialFirstName = PFN;
        dataAddress = DA;
    }
};

list<partialData> theList;


void setPartialData(list<Data*> &l){
    int i = 0;
    partialData temp;
    for(auto currentData:l){
        if(i == l.size()){
            break;
        }

        theList.emplace_back(partialData(currentData->firstName.substr(0, 4), currentData->lastName.substr(0, 4), currentData));
        i++;
    }
}


bool comparePartialData(const partialData& data1, const partialData& data2){
    if(data1.partialLastName == data2.partialLastName){
        if(data1.dataAddress->lastName > data2.dataAddress->lastName){
            return false;
        }
        if(data1.dataAddress->lastName < data2.dataAddress->lastName){
            return true;
        }
    }
    if(data1.partialLastName > data2.partialLastName){
        return false;
    }
    if(data1.partialLastName < data2.partialLastName){
        return true;
    }

    if(data1.partialFirstName == data2.partialFirstName){
        if(data1.dataAddress->firstName > data2.dataAddress->firstName){
            return false;
        }
        if(data1.dataAddress->firstName < data2.dataAddress->firstName){
            return true;
        }
    }
    if(data1.partialFirstName > data2.partialFirstName){
        return false;
    }
    if(data1.partialFirstName < data2.partialFirstName){
        return true;
    }
    if(data1.dataAddress->ssn > data2.dataAddress->ssn ){
        return false;
    }
    return true;
}*/