#include "BloomFilter.h"
#include "BloomFilter.cpp"
#include <math.h>
#include <time.h>
#include <unordered_set>

const string ALPHABET = "QWERTYUIOPLKJHGFDSAMNBVCXZqwertyuioplkjhgfdsamnbvcxz";
// The number of hash functions [2,5]
const unsigned int MIN_K = 2;
const unsigned int MAX_K = 5;
// The length of the bitset
const unsigned int MIN_M = 10000;
const unsigned int MAX_M = 100000;