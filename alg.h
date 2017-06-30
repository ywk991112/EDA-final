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
    void setNodeType(int, int, int, int, int, nodeType, int);
    void setSource(int, int, int);
    void setTarget(int, int, int);
    void push2OpenList(NT t);
    //for all neighbor, update G value
    bool updateG(NT, int, NT);
    bool checkValid(NT, int, NT);
    bool forAllNeighbor(NT);
    //sort open list
    void runAlgorithm(int, int);
    //write file
    void writeH(ofstream&, NT, NT);
    void writeV(ofstream&, NT, NT);
    void writeVia(ofstream&, NT, NT);
    void writeFile(ofstream&, lineType, NT, NT);
    NT meetShape(NT, int, ofstream&, NT, lineType); 
    NT lineRule(NT, int);

    //test
    void testRouting();

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
    void setType(nodeType, int);
    void setParent(NT);
    void setOpen(bool);
    void setShapeEdge(int);

    int getF();
    int getG();
    nodeType getType();
    NT getParent();
    bool getOpen();
    int getShapeEdge();
    int getShapeIdx();
  private:
    bool open;
    int shapeEdge;
    int H;
    int G;
    int shapeIdx;
    nodeType type;
    NT parent;
};

#endif
