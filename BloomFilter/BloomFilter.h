#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H
#include <string>
#include <vector>
using namespace std;

/**
 * Class to implement a Bloom Filter that stores strings
 */
class BloomFilter {
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
         * Bitset (boolean vector) of length m
         */
        vector<bool> bits;

    public:
        /**
         * BloomFilter constructor
         */
        BloomFilter(const unsigned int & k, const unsigned int & m) : K(k), M(m), bits(m,false) {}

        /**
         * Insert string s into this BloomFilter
         */
        void insert(const string & s);

        /**
         * Return false if s definitely doesn't exist in this BloomFilter,
         * or true if s MIGHT exist in this BloomFilter
         * @param string
         * @return True/False
         */
        bool find(const string & s);
};
#endif