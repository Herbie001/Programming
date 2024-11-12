#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include "CountMinSketch.h"
#include "HashFunctions.h"
using namespace std;
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const unsigned int MIN_K = 2;
const unsigned int MAX_K = 5;
const unsigned int MIN_M = 100;
const unsigned int MAX_M = 1000;
const unsigned int MIN_NUM_WORDS = 1000;
const unsigned int MAX_NUM_WORDS = 2000;
const unsigned int MIN_COUNT = 50;
const unsigned int MAX_COUNT = 100;
const unsigned int MIN_STR_LEN = 10;
const unsigned int MAX_STR_LEN = 20;

/**
 * Generate a random string of length len
 */
string random_string(const unsigned int & len) {
    string curr;
    for(unsigned int i = 0; i < len; ++i) {
        curr += ALPHABET[rand() % ALPHABET.size()];
    }
    return curr;
}

/**
 * Test the CountMinSketch class
 */
int main() {
    // create CountMinSketch object
    srand(time(NULL));
    const unsigned int k = sample_in_range(MIN_K, MAX_K);
    const unsigned int m = sample_in_range(MIN_M, MAX_M);
    const unsigned int num_words = sample_in_range(MIN_NUM_WORDS, MAX_NUM_WORDS);
    unsigned int n = 0;
    CountMinSketch cms(k, m);

    // build set of words to add to CountMinSketch object
    unordered_map<string,unsigned int> count;
    while(count.size() < num_words) {
        string s = random_string(sample_in_range(MIN_STR_LEN, MAX_STR_LEN));
        unsigned int c = sample_in_range(MIN_COUNT, MAX_COUNT);
        count[s] = c;
        n += c;
    }

    // add words to CountMinSketch object and make sure they're found
    for(auto pair : count) {
        for(unsigned int i = 0; i < pair.second; ++i) {
            cms.increment(pair.first);
        }
    }

    // compute theoretical values
    const long double upper = (long double)n * (long double)exp(1) / (long double)m;
    const long double true_prob = (long double)1 - exp(-1 * (long double)k);

    // estimate empirical probability of being in range
    unsigned int in_range = 0;
    for(auto pair : count) {
        unsigned int cms_c = cms.find(pair.first);
        if(cms_c >= pair.second && cms_c <= pair.second + upper) {
            ++in_range;
        }
    }
    long double est_prob = ((long double)in_range / (long double)num_words);
    cout << endl << (true_prob / est_prob) << endl;
}