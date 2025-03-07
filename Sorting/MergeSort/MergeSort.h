#include <vector>
#include <string>
#include <iostream>
using namespace std;

/**
 * Function is the initial call to run mergeSort on a vector of numbers
 * @param vector or type int
 * @return a vector of type int
 */
vector<int> mergeSort(vector<int> list);

/**
 * Seeks to merge two vectors together.
 * @param vector of type int
 * @return sorted vector
 */
vector<int> mergeVectors(vector<int> list1, vector<int> list2);