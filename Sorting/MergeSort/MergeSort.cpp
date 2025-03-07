#include "MergeSort.h"
using namespace std;

/**
 * Prints vectors neatly.
 */
void printList(vector<int> list) {
    cout << "{";
    int count = 0;
    while(count != list.size()) {
        for(const auto& element : list) {
            cout << element;
            if(count != list.size() - 1) {
                cout << ", ";
            }
            count += 1;
        }
    }
    cout << "}" << endl;
}

vector<int> mergeVectors(vector<int> list1, vector<int> list2) {
    vector<int> merged;
    auto itr1 = list1.begin();
    auto itr2 = list2.begin();
    auto end1 = list1.end();
    auto end2 = list2.end();
    while(itr1 != end1 && itr2 != end2) {
        if(*itr1 < *itr2) {
            merged.push_back(*itr1);
            ++itr1;
        }
        if(*itr2 < *itr1) {
            merged.push_back(*itr2);
            ++itr2;
        }
        // No duplicates allowed
        if(*itr1 == *itr2) {
            merged.push_back(*itr1);
            ++itr1;
            ++itr2;
        }
    }
    /**
     * If previous while loop ends, we will/might need to 
     * fill vector with remainder of elements in either list1/2
     */
    while(itr1 != end1) {
        merged.push_back(*itr1);
        ++itr1;
    }
    while(itr2 != end2) {
        merged.push_back(*itr2);
        ++itr2;
    }
    return merged;
}

vector<int> mergeSort(vector<int> list) {
    if(list.size() <= 1) {
        return list;
    }
    int middle = list.size()/2;
    vector<int> splitLow(list.begin(), list.begin()+middle);
    vector<int> splitHigh(list.begin()+middle,list.end());

    splitLow = mergeSort(splitLow);
    splitHigh = mergeSort(splitHigh);

    return mergeVectors(splitLow, splitHigh);
}

int main() {
    vector<int> test_1 = {7,4,5,2,8,1,3};
    vector<int> sorted_1 = mergeSort(test_1);
    printList(sorted_1);
    return 0;
}