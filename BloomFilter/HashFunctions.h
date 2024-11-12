#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H
#include <functional>
#include <vector>
using namespace std;
extern const vector<function<unsigned int(const string &)>> hash_functions;
unsigned int sample_in_range(unsigned int min_val, unsigned int max_val);
#endif