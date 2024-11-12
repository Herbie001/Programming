#include <limits>
#include "CountMinSketch.h"
#include "HashFunctions.h"

/**
 * Implement increment() correctly
 */
void CountMinSketch::increment(const string & s) {
    // Iterate through the hash functions
    unsigned int hashFuncIndex = 0;
    while(hashFuncIndex != K) {
        unsigned int index = hash_functions[hashFuncIndex](s);
        index = index % M;
        count[hashFuncIndex][index] += 1;
        hashFuncIndex += 1;
    }
}

/**
 * Implement find() correctly
 */
unsigned int CountMinSketch::find(const string & s) {
    unsigned int estimation = std::numeric_limits<unsigned int>::max();
    unsigned int hashFuncIndex = 0;
    while(hashFuncIndex != K) {
        unsigned int index = hash_functions[hashFuncIndex](s);
        index = index % M;
        unsigned int currentValue = count[hashFuncIndex][index];
        if(currentValue < estimation) {
            estimation = currentValue;
        }
        hashFuncIndex += 1;
    }
    return estimation;
}