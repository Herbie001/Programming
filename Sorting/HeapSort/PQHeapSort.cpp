#include "PQHeapSort.h"
#include <fstream>
#include <sstream>


string trimWhiteSpace(string data) {
    auto itr = data.begin();
    auto end = data.end()-1;
    // iterate through and eliminate white space in values
    int whiteSpace = 32;
    // If the beginning char is whitespace, shift pointer
    if(*itr == char(whiteSpace)) {
        ++itr;
    }
    if(*end == char(whiteSpace)) {
        --end;
    }
    return string(itr, end+1);
}

void printVector(vector<int> list) {
    cout << "{";
    int count = 0;
    for(const auto&elem : list) {
        cout << elem;
        if(count != list.size() - 1) {
            cout << ", ";
        }
        count += 1;
    }
    cout << "}" << endl;
}

vector<int> heapSort(vector<int> list) {
    priority_queue<int, vector<int>, greater<int>>pq;
    for(const auto&elem : list) {
        pq.push(elem);
    }
    int count = 0;
    while(!pq.empty()) {
        int value = pq.top();
        pq.pop();
        list[count] = value;
        count += 1;
    }
    return list;
}

int main() {
    vector<int> test_1 = {7,4,5,2,8,1,3};
    vector<int> test_1_results = heapSort(test_1);
    printVector(test_1_results);

    //Read from csv file one line at a time and process data to organize.
    ifstream file("example_input_1.csv");
    string line;
    vector<int> dataValues;

    /**
     * Check to make sure csv file has no spaces at the end of each row, '\n' 
     * will cause a bug during the line processing portion of the program
     * It is assumed the data in the csv is orderly, but could potentially have
     * spaces before, after or both 
     */
    while(getline(file, line)) {
        istringstream ss(line);
        string value;
        while(getline(ss, value, ',')) {
            value = trimWhiteSpace(value);
            dataValues.push_back(stoi(value));
        }
    }
    file.close();
    cout << "The dataValues are: ";
    printVector(dataValues);
    cout << "The sorted dataValues are: ";
    vector<int> sortedDataValues = heapSort(dataValues);
    printVector(sortedDataValues);

    ofstream outfile("example_output_1.csv");
    int count = 0;
    int lastElement = dataValues.size()-1;
    // Write ~10 elements per line then '\n'
    for(const auto& elem : sortedDataValues) {
        if(count % 10 == 0 && count != 0) {
            outfile << endl;
        }
        if(count != lastElement) {
            outfile << elem << ", ";
        } else {
            outfile << elem;
        }
        count += 1;
    }
    outfile.close();
    return 0;
}