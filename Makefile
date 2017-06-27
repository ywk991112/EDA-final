all: net_open_finder

net_open_finder: main.o netParser.o graph.o alg.o
	g++ --std=c++11 -o net_open_finder main.o netParser.o graph.o alg.o
main.o: main.cpp
	g++ --std=c++11 -c main.cpp -o main.o
graph.o: graph.h graph.cpp
	g++ --std=c++11 -c graph.cpp -o graph.o
netParser.o: netParser.h netParser.cpp
	g++ --std=c++11 -c netParser.cpp -o netParser.o
alg.o: alg.h alg.cpp
	g++ --std=c++11 -c alg.cpp -o alg.o
clean:
	rm -f net_open_finder *.o
