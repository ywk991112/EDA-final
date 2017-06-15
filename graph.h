#ifndef GRAPH_H
#define GRAPH_H
 
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
 
using namespace std;
 
class Node{
 public:
  Node* rightNode;
  Node* leftNode;
  Node* upNode;
  Node* downNode;
};
 
class Graph{
 public:
  Graph(const char*);
  ~Graph();

  // parse
  void parseCase(const char*);
  void parseLine(string, int);
  void parseShape(string);
  void parseVia(string);
  void parseObstacle(string);
  int* parseTuple(string);

  // test
  void testParse();

 private:
  int width;
  int length;
  int height;
  int llx;
  int lly;
  int urx;
  int ury;
  int viaCost;
  int spacing;
  int nShapes;
  int nVias;
  int nObstacles;
  Node*** graph;
};

#endif
