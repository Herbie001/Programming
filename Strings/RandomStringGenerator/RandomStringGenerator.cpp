#include "RandomStringGenerator.h"
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string ILLEGALCHARS = ALPHABET + "~`!@#$%^&*()_+-=[],./{}|:<>?";

/**
 * Function helps catch a potential overflow from the user input.
 * @param string the value passed by the user.
 * @return bool if there exists overflow.
 */
bool overFlow(const string & str) {
    try {
        // Set as unsigned long initially to test.
        unsigned long strToUL = stoul(str);
        // Check if the value fits within the range of unsigned int
        if (strToUL > numeric_limits<unsigned int>::max()) {
            return true;
        }
    } catch (const out_of_range &) {
        // Exception caught if the value is too large to convert
        return true;
    } catch (const invalid_argument &) {
        // Exception caught if the string is not a valid number
        return true;
    }
    return false;
}
/**
 * Determines if the input string contains anything other than ints.
 * Unfortunately runs in O(strlen * illegalchars len), but must be checked.
 * @param string provided by the user.
 * @return bool value
 */
bool containsIllegalChars(const string & str) {
    for(char c : str) {
         if(find(ILLEGALCHARS.begin(), ILLEGALCHARS.end(), c) != ILLEGALCHARS.end()) {
            return true;
         }
    }
    return false;
}
/**
 * The random word generator function.
 * @param unsigned int provided by the user.
 * @return string concatenated from ALPHABET variable.
 */
string randomWordGen(unsigned int & desiredWordLen) {
    string curr;
    // Seed random number generator.
    srand(time(0)); 
    int randomInt;
    for(unsigned int i = 0; i < desiredWordLen; ++i) {
        randomInt = rand();
        curr += ALPHABET[randomInt % ALPHABET.size()];
    }
    return curr;
}