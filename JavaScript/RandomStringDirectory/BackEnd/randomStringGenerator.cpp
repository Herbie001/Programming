#include "randomStringGenerator.h"
#include <fstream>
#include <random>

// Chars of string that are accepted for random string.
const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string NUMERICAL = "0123456789";
const string ALPHANUMERICAL = ALPHABET + NUMERICAL;
// Chars of string that shouldn't be provided by user.
const string ILLEGALCHARS = ALPHABET + "~`!@#$%^&*()_+-=[],./{}|:<>?";

/**
 * Function to determine if the users input will cause an overflow
 * @param string passed by the user
 * @return boolean value determining if there was an overflow
 */
bool overFlow(const string& str) {
    try {
        unsigned long strToUL = stoul(str);
        if (strToUL > numeric_limits<unsigned int>::max()) {
            cerr << "Debug: Input exceeds unsigned int max value." << endl;
            return true;
        }
    } catch (const out_of_range&) {
        cerr << "Debug: Input is out of range for stoul." << endl;
        return true; 
    } catch (const invalid_argument&) {
        cerr << "Debug: Invalid argument for stoul." << endl;
        return true;
    }
    return false;
}
/**
 * Function to generate a unique string at random
 * The idea is to generate a string consisting of the maximum number of 
 * characters, shuffling them around, then taking the substring if
 * the desired word length is <= 94 which is the maximum size
 * @param unsignedint which is provided by the user
 * @return string 
 */
string uniqueStrGen(unsigned int & desiredWordLen) { 
    string charSet;
    string curr;
    for (int i = 33; i <= 126; ++i) {
        charSet += static_cast<char>(i); 
    }
    if(desiredWordLen > charSet.size()) {
        throw::invalid_argument("Request is too large, enter in the range of [0, 94]");
    }
    // Non-deterministic random device
    random_device rd; 
    // Mersenne Twister RNG 
    mt19937 rng(rd()); 
    shuffle(charSet.begin(), charSet.end(), rng);
    curr = charSet.substr(0,desiredWordLen);
    return curr;
}
/**
 * Function to generate a string consisting of ASCII characters
 * The idea is analogous to the unique ASCII string generator; however,
 * character uniqueness isn't a factor here
 * @param unsignedint passed by the user which represents string length
 * @return string which is randomly generated
 */
string asciiStringGen(unsigned int & desiredWordLen) {
    string curr;
    // seed random number generator
    random_device random;
    // Mersenne Twister RNG
    mt19937 gen(random());
    int randomInt;
    uniform_int_distribution<int> distribuion(33,126);
    for(unsigned int i = 0; i < desiredWordLen; ++i) {
        curr += distribuion(random);
    }
    return curr;
}
/**
 * Function to generate a string consisting only of alphanumerical characters
 * @param unsignedint passed by the user which represents string length
 * @return randomly generated string 
 */
string alphanumerical(unsigned int & desiredWordLen) {
    string curr;
    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<int> distribution(0,ALPHANUMERICAL.size());
    for(unsigned int i = 0; i < desiredWordLen; ++i) {
        curr += ALPHANUMERICAL[distribution(random)];
    }
    return curr;
}

/**
 * Function to generate a string consisting of alphabetical characters
 * @param unsignedint passed by the user which represents string length
 * @return string randomly generated
 */
string randomWordGen(unsigned int & desiredWordLen) {
    string curr;
    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<int> distribution(0,ALPHABET.size());
    for(unsigned int i = 0; i < desiredWordLen; ++i) {
        curr += ALPHABET[distribution(random)];
    }
    return curr;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Error: Incorrect number of arguments provided." << endl;
        cerr << "Usage: ./randomStringGenerator (stringGeneratorCommand) (lengthOfTheString)" << endl;
        cerr << "stringGeneratorCommand: " << "randomAlphaString, randomAlphaNumericalString, randomASCIIString, uniqueASCIIString" << endl;
        exit(1);
    }
    if (overFlow(argv[2])) {
        cerr << "Error: Input length is too large to process." << endl;
        return 1;
    }
    unsigned int length;
    try {
        length = stoi(argv[2]);
    } catch (const invalid_argument &) {
        cerr << "Error: Invalid input. Please provide a valid integer." << endl;
        return 1;
    } catch (const out_of_range &) {
        cerr << "Error: Input is out of range." << endl;
        return 1;
    }
    string randomWord;
    const unordered_set<string> desiredString = {"randomAlphaString", "randomAlphaNumericalString", "randomASCIIString", "uniqueASCIIString"};
    if(desiredString.find(argv[1]) == desiredString.end()) {
        cerr << "Error, couldn't find the correct string value." << endl;
        cerr << "arg1: <stringType> arg2: <length>" << endl;
        cerr << "<stringtype>: " << "randomAlphaString, randomAlphaNumericalString, randomASCIIString, uniqueASCIIString" << endl;
        return 1;
    } else {
        if(strcmp(argv[1],"randomAlphaString") == 0) {
            randomWord = randomWordGen(length);
        }
        if(strcmp(argv[1],"randomAlphaNumericalString") == 0) {
            randomWord = alphanumerical(length);
        }
        if(strcmp(argv[1],"randomASCIIString") == 0) {
            randomWord = asciiStringGen(length);
        }
        if(strcmp(argv[1],"uniqueASCIIString") == 0) {
            randomWord = uniqueStrGen(length);
        }
    }
    cout << "The randomized word: " << randomWord << endl;
    ofstream outfile("./BackEnd/randomizedString.txt");
    if (!outfile) {
        cerr << "Error: Could not open file randomizedString.txt for writing."  << endl;
        return 1;
    }
    outfile << randomWord << endl;
    outfile.close();
    return 0;
}