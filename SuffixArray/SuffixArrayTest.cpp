#include "SuffixArray.h"
#include <iomanip>
/**
 * Ask the user to enter a string and compute the suffix array.
 */
int main() {
    string s;
    cout << "Please enter a string: ";
    getline(cin, s);
    cout << endl;
    cout << "The string provided was: " << s << endl;
    vector<string> mySubStrVector = subStringVector(s);
    for(unsigned int i : suffix_array(s)) {
        cout << i << ":\t" << mySubStrVector[i] << endl;
    }
    return 0;
}