#include "BloomFilter.h"
#include "HashFunctions.h"

/**
 * Implement insert() correctly
 */
void BloomFilter::insert(const string & s) {
    unsigned int hashFuncIndex = 0;
    while(hashFuncIndex != K) {
        unsigned int index = hash_functions[hashFuncIndex](s);
        index = index % M;
        bits[index] = true;
        hashFuncIndex += 1;
    }
}

/**
 * Implement find() correctly
 */
bool BloomFilter::find(const string & s) {
    unsigned int hashFuncIndex = 0;
    while(hashFuncIndex != K) {
        unsigned int index= hash_functions[hashFuncIndex](s);
        index = index % M;
        if(bits[index] == false) {
            return false;
        }
        hashFuncIndex += 1;
    }
    return true;
}