#include "Burrows-Wheeler.h"

/**
 * This function will acquire the last character from each rotated string
 * and will concatenate each character into the desired string to return.
 * @param vectorOfSubStr the vector of rotated strings.
 * @return the string of each last char from rotated string.
 */
string getLastColumn(vector<string> vectorOfStr) {
    string lastColStr = "";
    for(string str : vectorOfStr) {
        lastColStr = lastColStr + str.back();
    }
    return lastColStr;
}

/**
 * Function that will rotate characters yielding a new string  
 * which will be inserted into a vector.
 * @param str the string provided by the user.
 * @return a vector containing rotations of the string.
 */
vector<string> rotations(const string str) {
    vector<string> stringRotations;
    int count = 0;
    string rotatedString = str;
    while(count < str.length()) {
        char lastChar = rotatedString.back();
        rotatedString.pop_back();
        rotatedString.insert(0,1,lastChar);
        stringRotations.push_back(rotatedString);
        count++;
    }
    return stringRotations;
}

/**
 * Function 
 * @param str provided by the user.
 * @return the transformed string.
 */
string bwt(const string & str) {
    vector<string> rotatedStrings = rotations(str);
    sort(rotatedStrings.begin(), rotatedStrings.end());
    string bwtString = getLastColumn(rotatedStrings);
    return bwtString;
}