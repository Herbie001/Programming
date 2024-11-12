#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H
#include <string>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <iostream>
using namespace std;
extern const vector<function<unsigned int(const string &)>> hash_functions;
unsigned int sample_in_range(unsigned int min_val, unsigned int max_val);
#endif