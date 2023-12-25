CXX=g++
CXXFLAGS=-Wall -g -I.
LDFLAGS= -g

.PHONY: clean

main: main.o graph.o actions.o
	$(CXX) $(LDFLAGS) $^ -o $@

test: test.o actions.o
	$(CXX) $(LDFLAGS) $^ -o $@

graph.o: graph.cpp graph.hpp

actions.o: actions.cpp actions.hpp graph.hpp

main.o: main.cpp graph.hpp actions.hpp

test.o: test.cpp graph.hpp actions.hpp


clean:
	rm -f *.o main