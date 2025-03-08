#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

/**
 * Assuming data is ordered such as: 100, 101,931, 101 , 3014 
 * then we just need to check if there exists whitespace,
 * then remove it accordingly returning the data with zero whitespace
 * @param string 
 * @return string containing zero whitespace
 */
string trimWhiteSpace(string data);

/**
 * Simple HeapSort function that utilizes PQ's in C++ STL
 * @param vector of type int
 * @return a sorted list of type int 
 */
vector<int> heapSort(vector<int> list);