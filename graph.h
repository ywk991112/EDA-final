#ifndef _GRAPH_H_
#define _GRAPH_H_
 
#include <vector>
#include <string>
#include <fstream>
 
using namespace std;

enum NodeType{none, shape, obstacle};
enum Pos{no, up, down};
 
class Node{
 public:
  Node();

  void setType(NodeType);
  NodeType getType();
  void setViaPos(Pos);
  Pos getViaPos();

 private:
  NodeType type;
  bool viaUp;
  bool viaDown;
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

  // node
  NodeType getNodeType(int, int, int);
  Pos getViaPos(int, int, int);
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
  vector<int*> shapeCenter;
};

#endif
