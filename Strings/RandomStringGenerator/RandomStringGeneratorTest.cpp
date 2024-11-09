#include "RandomStringGenerator.h"
/**
 * To test, run the following:
 * "g++ -std=c++11 RandomStringGeneratorTest.cpp RandomStringGenerator.cpp -o RandomStringGenerator"
 */
int main() {
    unsigned int num;
    string str;
    bool keepGoing = false;
    while(keepGoing != true) {
        cout << "Please enter a positive integer that represents len of str: ";
        getline(cin, str);
        // Check for illegal characters potentially given by user.
        if(containsIllegalChars(str) == false) {
            // Check overflow.
            if(overFlow(str) == false) {
                num = stoul(str);
                // Check range.
                if(num > 0) {
                    break;
                }
            }
        }
    }
    string randomWord = randomWordGen(num);
    cout << "The randomized word: " << randomWord << endl;
}