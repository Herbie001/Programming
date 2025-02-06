#!/bin/bash

# Check for the correct number of arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 <stringType> <length>"
    echo "Available string types: randomAlphaString, randomAlphaNumericalString, randomASCIIString, uniqueASCIIString"
    exit 1
fi


# Assign arguments to variables
stringType=$1
length=$2

# Compile the C++ program
echo "Compiling the C++ program..."
g++ -std=c++11 -o ./BackEnd/randomStringGenerator ./BackEnd/randomStringGenerator.cpp

# Check for compilation errors
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed."
    exit 1
fi

# Run the compiled C++ program with the provided arguments
echo "Running the program with arguments: stringType=$stringType, length=$length ..."
./BackEnd/randomStringGenerator "$stringType" "$length"

# Check if the program ran successfully
if [ $? -ne 0 ]; then
    echo "Error: Program execution failed."
    exit 1
fi

echo "Random string generated and written to randomizedString.txt"