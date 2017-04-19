CXXFLAGS += -g -Wall -Wextra -D_GLIBCXX_DEBUG -pthread -std=c++0x

all: mapGenerator.o

clean :
	rm -rf *.o

unionFind.o : unionFind.cpp unionFind.hpp
	$(CXX) $(CXXFLAGS) -c unionFind.cpp

mapGenerator.o : mapGenerator.cpp mapGenerator.hpp unionFind.o
	$(CXX) $(CXXFLAGS) -c mapGenerator.cpp unionFind.o
