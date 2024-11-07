#include "SuffixArray.h"

/**
 * Given a string of length k,
 * return a vector of type string with k substrings.
 * Each substring will have -1 length until the final
 * substring is of length 1.
 * @param str given by user
 * @return vector<string> which consists of substrings
 */
vector<string> subStringVector(const string & str) {
    vector<string> subStringVector;
    int count = 0;
    while(count != str.length()) {
        subStringVector.push_back(str.substr(count));
        count += 1;
    }
    return subStringVector;
}

/**
 * @param string str given by the user 
 * @return vector<unsigned int> represents the lexigraphically sorted substrings
 */
vector<unsigned int> suffix_array(const string & str) {
    vector<string> subStr = subStringVector(str);
    map<string, int> suffixMap;
    for(int i = 0; i < subStr.size(); i++) {
        suffixMap[subStr[i]] = i;
    }
    vector<unsigned int> suffixMapValues;
    for(const auto & pair : suffixMap) {
        suffixMapValues.push_back((unsigned int)pair.second);
    }
    return suffixMapValues;
}

