#ifndef COUNTMINSKETCH_H
#define COUNTMINSKETCH_H
#include <string>
#include <vector>
using namespace std;

/**
 * Class to implement a CountMinSketch that stores strings
 */
class CountMinSketch {
    private:
        /**
         * Number of hash functions to use (must be in range 1,5])
         */
        const unsigned int K;

        /**
         * Length of the bitset (m)
         */
        const unsigned int M;

        /**
         * Count matrix with k rows and m columns
         */
        vector<vector<unsigned int>> count;

    public:
        /**
         * CountMinSketch constructor
         */
        CountMinSketch(const unsigned int & k, const unsigned int & m) : K(k), M(m), count(K,vector<unsigned int>(M,0)) {}

        /**
         * Increment the count of s
         */
        void increment(const string & s);

        /**
         * Return an over-estimate of the count of string s
         */
        unsigned int find(const string & s);
};
#endif