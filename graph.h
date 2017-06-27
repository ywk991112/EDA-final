#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Node
{
	public:
		Node(int* shape = 0, int viaCost = 0)
		{
			LLx = shape[0];
			LLy = shape[1];
			URx = shape[2];
			URy = shape[3];
			Layer = shape[4] * viaCost;
      viaCost = viaCost;
		};
		~Node() {};
		int weight_to_node(Node*);
	private:
		int Layer;
		int LLx, LLy, URx, URy;
    int viaCost;
};

class Edge
{
	public:
		Edge(int, int);
		~Edge() {};
		int* get_node();
	private:
		int node[2];
};

class Graph
{
	public:
		Graph(int);
		~Graph();
	
		void add_node(Node);
		void add_edge(Edge);
		void set_weight_table();
		void set_weight(int, int, int);
		void print_weight();
		void PRIM_build_edges();
		vector<int*> get_edge_table();
	private:
		int nShape;
		vector<Node> nodes;
		vector<Edge> edges;
		int** weight;
};

#endif
