#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



int main() {
    string str;
    char symbol = '$';
    bool validStr = false;
    while(validStr == false) {
        cout << "Enter the BWT string: ";
        getline(cin, str);
        if(find(str.begin(), str.end(), symbol) == str.end()) {
            cout << "The character " << symbol << " wasn't found! Try again.";
            cout << endl;
        } else {
             cout << "The string you entered was: " << str << endl;
             validStr = true;
        }
    }
    // Use the string and pass to functions to recover original message.
    
    return 0;
}