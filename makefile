CPPFLAGS=-g -std=c++0x -Wall

%.out:	%.cpp
	g++ $(CPPFLAGS) $*.cpp -o $*.out
