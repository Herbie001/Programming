#include "BloomFilter.h"
#include "HashFunctions.h"

/**
 * Implement the insert function for the bloom filter.
 * @param string to insert in the bloom filter
 * @return void 
 * 
 */
void BloomFilter::insert(const string & str) {
    unsigned int hashFuncIndex = 0;
    while(hashFuncIndex != K) {
        unsigned int index = hash_functions[hashFuncIndex](str);
        index = index % M;
        bits[hashFuncIndex] = true;
        hashFuncIndex += 1;
    }
}

/**
 * Implement the find function for the bloom filter.
 * @param string to determine existence 
 * @return void
 */
bool BloomFilter::find(const string & str) {
    unsigned int hashFuncIndex = 0;
    while(hashFuncIndex != K) {
        unsigned int index = hash_functions[hashFuncIndex](str);
        index = index % M;
        if(bits[index] == false) {
            return false;
        }
        hashFuncIndex += 1;
    }
    return true;
}