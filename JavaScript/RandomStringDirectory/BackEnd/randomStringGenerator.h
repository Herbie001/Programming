#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <limits>
#include <stdexcept>
#include <algorithm>
using namespace std;

// Create a class which initializes unordered_set<char> full of the illegal chars

/**
 * Function helps catch a potential overflow from the user input.
 * @param string the value passed by the user.
 * @return bool if there exists overflow.
 */
bool overFlow(const string & str);

/**
 * The random word generator function.
 * @param unsigned int provided by the user.
 * @return string concatenated from ALPHABET variable.
 */
string randomWordGen(unsigned int & desiredWordLen);