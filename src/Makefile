CXXFLAGS += -g -Wall -Wextra -D_GLIBCXX_DEBUG -pthread -std=c++0x

all: ncTest

clean :
	rm -rf *.o

unionFind.o : unionFind.cpp unionFind.hpp
	$(CXX) $(CXXFLAGS) -c unionFind.cpp

geometry.o : geometry.cpp geometry.hpp
	$(CXX) $(CXXFLAGS) -c geometry.cpp

mapGenerator.o : mapGenerator.cpp mapGenerator.hpp
	$(CXX) $(CXXFLAGS) -c mapGenerator.cpp

pathfinder.o : pathfinder.cpp pathfinder.hpp
	$(CXX) $(CXXFLAGS) -c pathfinder.cpp

ncTest : mapGenerator.o unionFind.o ncTest.cpp geometry.o pathfinder.o
	$(CXX) $(CXXFLAGS) -o ncTest $^


