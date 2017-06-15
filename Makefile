all: route

route: main.o graph.o
	g++ --std=c++11 -o route main.o graph.o
main.o: main.cpp
	g++ --std=c++11 -c main.cpp -o main.o
graph.o: graph.h graph.cpp
	g++ --std=c++11 -c graph.cpp -o graph.o
