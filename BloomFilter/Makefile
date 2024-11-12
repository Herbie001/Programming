# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=BloomFilterTest 

all: $(OUTFILES)

BloomFilterTest: BloomFilterTest.cpp BloomFilter.cpp BloomFilter.h HashFunctions.cpp HashFunctions.h
	$(CXX) $(CXXFLAGS) -o BloomFilterTest BloomFilterTest.cpp BloomFilter.cpp HashFunctions.cpp

clean:
	$(RM) $(OUTFILES) *.o