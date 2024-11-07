CXX=g++
CXXFLAGS?=-Wall -g -std=c++11
OUTFILES=SuffixArrayTest

all: $(OUTFILES)

SuffixArrayTest: SuffixArrayTest.cpp SuffixArray.cpp SuffixArray.h
	$(CXX) $(CXXFLAGS) -o SuffixArrayTest SuffixArrayTest.cpp SuffixArray.cpp

clean: 
	$(RM) $(OUTFILES) *.o