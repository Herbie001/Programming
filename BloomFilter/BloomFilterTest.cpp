#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>
#include "BloomFilter.h"
#include "HashFunctions.h"
using namespace std;
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const unsigned int MIN_K = 2;
const unsigned int MAX_K = 5;
const unsigned int MIN_M = 10000;
const unsigned int MAX_M = 100000;
const unsigned int MIN_N = 4000;
const unsigned int MAX_N = 4500;
const unsigned int MIN_STR_LEN = 10;
const unsigned int MAX_STR_LEN = 20;
const unsigned int NUM_FP_TEST = 10000;

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
 * Test the BloomFilter class
 */
int main() {
    // create BloomFilter object
    srand(time(NULL));
    const unsigned int k = sample_in_range(MIN_K, MAX_K);
    const unsigned int m = sample_in_range(MIN_M, MAX_M);
    const unsigned int n = sample_in_range(MIN_N, MAX_N);
    BloomFilter bf(k, m);

    // build set of words to add to BloomFilter object
    unordered_set<string> words;
    while(words.size() < n) {
        words.insert(random_string(sample_in_range(MIN_STR_LEN, MAX_STR_LEN)));
    }

    // add words to BloomFilter object and make sure they're found
    for(const string & s : words) {
        bf.insert(s);
    }
    for(const string & s : words) {
        if(!bf.find(s)) {
            cout << "Unable to find word that should exist" << endl;
            break;
        }
    }

    // compute theoretical FP probability
    const long double true_fp_prob = pow(1 - exp(-1 * (long double)k * (long double)n / (long double)m), k);

    // estimate empirical FP probability
    unsigned int fp_num = 0;
    for(unsigned int i = 0; i < NUM_FP_TEST; ++i) {
        string curr;
        do {
            curr = random_string(sample_in_range(MIN_STR_LEN, MAX_STR_LEN));
        } while(words.find(curr) != words.end());
        if(bf.find(curr)) {
            ++fp_num;
        }
    }
    const long double est_fp_prob = ((long double)fp_num) / ((long double)NUM_FP_TEST);
    cout << endl << (est_fp_prob / true_fp_prob) << endl;
}