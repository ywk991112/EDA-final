//TODO: makefile
#ifndef _ALG_H_
#define _ALG_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

#define NT tuple<int, int, int>   //node tuple
#define NTP tuple<int, int, int>* //node tuple pointer
#define IT make_tuple(-1, -1, -1) //invalid tuple

enum nodeType { none, shape, obstacle };
enum lineType { hLine, vLine, via, init };

class A_star_node;

class A_star {
  public:
    A_star(int, int, int, int, const char*);
    ~A_star();
    void setNodeType(int, int, int, int, int, nodeType);
    void setSource(int, int, int);
    void setTarget(int, int, int);
    void push2OpenList(NT t);
    //for all neighbor, update G value
    bool updateG(NT, int, NT);
    bool checkValid(NT, int, NT);
    bool forAllNeighbor(NT);
    //sort open list
    void runAlgorithm();
    //write file
    void writeH(ofstream&, NT, NT);
    void writeV(ofstream&, NT, NT);
    void writeVia(ofstream&, NT, NT);
    NT lineRule(NT);

  private:
    int width;
    int length;
    int n_layer;
    int viaCost;
    const char* filename;
    NT target;
    A_star_node*** graph;
    vector< NT > openList;
};

class A_star_node {
  public:
    A_star_node();
    ~A_star_node();
    void setH(int, int, int, int);
    void setG(int, NT);
    void setType(nodeType);
    void setParent(NT);
    void setOpen(bool);
    void setShapeEdge(bool);

    int getF();
    int getG();
    nodeType getType();
    NT getParent();
    bool getOpen();
    bool getShapeEdge();
  private:
    bool shapeEdge;
    bool open;
    int H;
    int G;
    nodeType type;
    NT parent;
};

#endif
