# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=CountMinSketchTest

all: $(OUTFILES)

CountMinSketchTest: CountMinSketchTest.cpp CountMinSketch.cpp CountMinSketch.h HashFunctions.cpp HashFunctions.h
	$(CXX) $(CXXFLAGS) -o CountMinSketchTest CountMinSketchTest.cpp CountMinSketch.cpp HashFunctions.cpp

clean:
	$(RM) $(OUTFILES) *.o