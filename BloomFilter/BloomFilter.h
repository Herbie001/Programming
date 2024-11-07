#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H
#include <string>
#include <vector>
using namespace std;

/**
 * Class to implement the bloom filter that stores strings.
 */
class BloomFilter {
    private:
        /**
         * K, the number of hash functions to use.
         */
        const unsigned int K;

        /**
         * M, the length of the bitset
         */
        const unsigned int M;

        /**
         * Boolean vector of size M
         */
        vector<bool> bits;

    public:
        /**
         * Constructor for the Bloom Filter
         */
        BloomFilter(const unsigned int & k, const unsigned int & m) : K(k), M(m), bits(m,false) {}

        /**
         * Insert function for the bloom filter
         */
        void insert(const string & str);

        /**
         * Find function for the bloom filter
         */
        bool find(const string & str);
};
#endif