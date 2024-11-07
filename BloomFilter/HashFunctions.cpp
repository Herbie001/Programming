#include "HashFunctions.h"

/**
 * First Hash function
 */
unsigned int hashOne(const string & str) {
    unsigned int x = 0;
    for(const char & ch : str) {
        x += ch;
    }
    return x;
}
/**
 * Second Hash Function
 */
unsigned int hashTwo(const string & str) {
    unsigned int x = 0;
    for(const auto & ch : str) {
        x = (x*13) + ch;
    }
    return x;
}
/**
 * Third Hash Function
 */
unsigned int hashThree(const string & str) {
    unsigned int x = 0;
    for(const auto & ch : str) {
        x = (x*23) + ch;
        if(x > 23) {
            x -= 17;
        }
    }
    return x;
}
/**
 * Fourth Hash Function
 */
unsigned int hashFour(const string & str) {
    unsigned int x = 0;
    for(const auto & ch : str) {
        x = (x*ch) + ch
        if(x > 1000) {
            x -= 500;
        }
    }
    return x;
}
/**
 * Fifth Hash Function
 */
unsigned int hashFive(const string & str) {
    return str.length();
}


const vector<function<unsigned int(const string &)>> hash_functions{hashOne, hashTwo, hashThree, hashFour, hashFive};

unsigned int sample_in_range(unsigned int min_val, unsigned int max_val) {
    return (rand() % (max_val - min_val)) + min_val;
}
