#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include "graph.h"
using namespace std;

//return distance from node to node
int Node::weight_to_node(Node n)
{
	return (pow((this->X)-(n.X), 2)+pow((this->Y)-(n.Y), 2));
}

Edge::Edge()
{
	nodes = new Node[2];
}

Edge::~Edge()
{
	delete nodes;
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

//set the whole weight table
void Graph::set_weight_table()
{
	for(int i = 0; i < nodes.size(); ++i)
	{
    	for(int j = i+1; j < nodes.size(); ++j)
		{
			weight[i][j] = nodes[i].weight_to_node(nodes[j]);
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
		for(int j = 0; j < nodes.size(); ++j)
		{
			cout << weight[i][j] << " ";
		}
		cout <<endl;
	}
}