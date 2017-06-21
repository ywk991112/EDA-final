all: net_open_finder

net_open_finder: main.o netParser.o graph.o
	g++ --std=c++11 -o net_open_finder main.o netParser.o graph.o
main.o: main.cpp
	g++ --std=c++11 -c main.cpp -o main.o
netParser.o: netParser.h netParser.cpp
	g++ --std=c++11 -c netParser.cpp -o netParser.o
graph.o: graph.h graph.cpp
	g++ --std=c++11 -c graph.cpp -o graph.o
clean:
	rm -f net_open_finder *.o
