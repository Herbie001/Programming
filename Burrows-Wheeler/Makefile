CXX = g++
CXXFLAGS?=-Wall -g -std=c++11
OUTFILES = Burrows-Wheeler-Test

all: $(OUTFILES)

Burrows-Wheeler-Test: Burrows-Wheeler-Test.cpp Burrows-Wheeler.cpp Burrows-Wheeler.h
	$(CXX) $(CXXFLAGS) -o Burrows-Wheeler-Test Burrows-Wheeler-Test.cpp Burrows-Wheeler.cpp

clean:
	$(RM) $(OUTFILES) *.o