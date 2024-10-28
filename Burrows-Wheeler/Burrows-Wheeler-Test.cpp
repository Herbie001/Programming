#include "Burrows-Wheeler.h"

/**
 * This is the test which asks the user to input a string that ends with $ symbol
 * and after computes then returns a string containing the last character of 
 * each rotated string.
 */
int main() {
    string str;
    cout << "Please enter a string: ";
    getline(cin, str);
    if(str[str.size()-1] != '$') {
        cerr << "String must end with end-of-string symbol ($)" << endl;
        exit(1);
    }
    cout << endl << bwt(str) << endl;
    return 0;
}