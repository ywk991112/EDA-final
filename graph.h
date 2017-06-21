#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Node
{
	public:
		Node(int* central = 0) : X(central[0]), Y(central[1]) {};
		~Node() {};
		int weight_to_node(Node);
	private:
		int X, Y;
};

class Edge
{
	public:
		Edge();
		~Edge();
	private:
		Node* nodes;
};

class Graph
{
	public:
		Graph(int);
		~Graph();
	
		void add_node(Node);
		void set_weight_table();
		void set_weight(int, int, int);
		void print_weight();
	private:
		int nShape;
		vector<Node> nodes;
		vector<Edge> edges;
		int** weight;
};

#endif