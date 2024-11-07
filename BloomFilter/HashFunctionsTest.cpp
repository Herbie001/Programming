#include "HashFunctions.h"
#include "HashFunctions.cpp"
/**
 * Calculating the following strings to test:
 * a -> 
 * Flower -> 
 * abcABCdefDEF - >
 * 
 */
// Cannot have main() in HashFunctions.cpp or bug.
int main() {
    string hash_str_test_0 = "abcABCdefDEF";
    unsigned int hash_str_test_result_0 = hashTwo(hash_str_test_0);
    cout << "Given: " << hash_str_test_0 << ", the output is: " << hash_str_test_result_0 << endl;
    unsigned int expectedValue_test0 = 0;
    
    return 0;
}