#define DEBUG

#include <iostream>
#include <climits>
#include <cmath>
#include <iomanip>
#include <vector>
#include "graph.h"
using namespace std;

//return distance from node to node
int Node::weight_to_node(Node* n)
{
	int weight = 0;
	if(this->URx <= n->LLx )
	{
		weight += n->LLx - this->URx;
	}
	else if(n->URx <= this->LLx)
	{
		weight += this->LLx - n->URx;
	}
	if(this->URy <= n->LLy)
	{
		weight += n->LLy - this->URy;
	}
	else if(n->URy <= this->LLy)
	{
		weight += this->LLy - n->URy;
	}
	//weight += (this->viaCost * abs(this->Layer - n->Layer));
	weight += abs(this->Layer - n->Layer);
	return weight;
}

Edge::Edge(int n1, int n2)
{
	node[0] = n1;
	node[1] = n2;
}

int* Edge::get_node()
{
	return node;
}

Graph::Graph(int n)
{
	this->nShape = n;
	weight = new int*[nShape];
	for(int i = 0; i < nShape; ++i)
	{
		weight[i] = new int[nShape];
		for(int j = 0; j < nShape; ++j)
		{
			weight[i][j] = INT_MAX;
		}
	}
}

Graph::~Graph()
{
	for(int i = 0; i < nShape; ++i)
	{
    	delete [] weight[i];
	}
	delete [] weight;
}

//add new node into graph
void Graph::add_node(Node n)
{
	nodes.push_back(n);
}

//add new edge into graph
void Graph::add_edge(Edge e)
{
	edges.push_back(e);
}

//set the whole weight table
void Graph::set_weight_table()
{
	for(int i = 0; i < nodes.size(); ++i)
	{
    	for(int j = 0; j < nodes.size(); ++j)
		{
			weight[i][j] = nodes[i].weight_to_node(&nodes[j]);
		}
	}
}

//set the weight of i and j to weight
void Graph::set_weight(int i, int j, int w)
{
	weight[i][j] = w;
}

//print the weight table, for debug
void Graph::print_weight()
{
	for(int i = 0; i < nodes.size(); ++i)
	{
		cout << i <<"   ";
		for(int j = 0; j < nodes.size(); ++j)
		{
			cout << std::setw(12) << right << weight[i][j] << " ";
		}
		cout <<endl;
	}
}

//add edges to solve MST
void Graph::PRIM_build_edges()
{
	int* predecessor = new int[nodes.size()];
	int* key = new int[nodes.size()];
	bool* visited = new bool[nodes.size()];
	
#ifdef DEBUG
	cout << "PRIM start, initialize all factor\n";
#endif
	//initialize
	for(int i = 0; i < nodes.size(); ++i)
	{
		predecessor[i] = -1;
		key[i] = INT_MAX;
		visited[i] = false;
	}
	
#ifdef DEBUG
	cout << "set node[0] as root, if no node, failed\n";
#endif
	//choose root as node[0]
	if(nodes.size() == 0)
	{
		cerr << "Error: no nodes in the graph";
		return;
	}
	key[0] = 0;
	visited[0] = true;
	int current_node_number = 0;

#ifdef DEBUG
	cout << "start growing MST\n";
#endif
	//set vector of not visited
	vector<Node> not_visited;
	for(int i = 1; i < nodes.size(); ++i)
	{
		not_visited.push_back(nodes[i]);
	}
	
	//something should be fixed
	while(!(not_visited.size() == 0))
	{
		int minimum_number = 0, minimum_key = INT_MAX;
		for(int i = 0; i < nodes.size(); ++i)
		{
			if(!visited[i])
			{
				if(key[i] > weight[current_node_number][i])
				{
					predecessor[i] = current_node_number;
					key[i] = weight[current_node_number][i];
				}
				if(key[i] < minimum_key)
				{
					minimum_number = i;
					minimum_key = key[i];
				}
			}		
		}
		current_node_number = minimum_number;
		visited[minimum_number] = true;
		not_visited.erase(not_visited.begin() + minimum_number);
#ifdef DEBUG
	cout << "predecessor\n"; 
	for(int i = 0; i < nodes.size(); ++i)
	{
		cout << std::setw(12) << right << predecessor[i] << " ";
	}
	cout << "\nkey\n"; 
	for(int i = 0; i < nodes.size(); ++i)
	{
		cout << std::setw(12) << right << key[i] << " ";
	}
	cout << "\nvisited\n"; 
	for(int i = 0; i < nodes.size(); ++i)
	{
		cout << std::setw(12) << right << visited[i] << " ";
	}
	cout << endl;
#endif

	}
#ifdef DEBUG
	cout << "PRIM result\nnode 0 as root\n"; 
	for(int i = 1; i < nodes.size(); ++i)
	{
		cout << "node " << i << " connect to node " << predecessor[i] << " with weight " << key[i] << endl;
	}
#endif

	//construct edges
	for(int i = 1; i < nodes.size(); ++i)
	{
		if(key[i] != 0)
		{
			Edge new_edge(i, predecessor[i]);
			this->edges.push_back(new_edge);
		}
	}
}

vector<int*> Graph::get_edge_table()
{
	vector<int*> table;
	for(int i = 0; i < edges.size(); ++i)
	{
		table.push_back(edges[i].get_node());
	}
	return table;
}
