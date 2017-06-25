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

enum nodeType { none, shape, obstacle }

class A_star {
  public:
    A_star(int, int, int, int, const char*);
    ~A_star();
    void setNodeType(int, int, int, int, int, nodeType);
    void setSource(int, int, int);
    void setTarget(int, int, int);
    void push2OpenList(NT t);
    //for all neighbor, update G value
    bool updateG(NT, int, A_star_node*);
    bool checkValid(NT, int, A_star_node*);
    bool forAllNeighbor(NT);
    //sort open list
    void compareNode(NT, NT);
    void runAlgorithm();
    void writeFile();
  private:
    int width;
    int length;
    int n_layer;
    int viaCost;
    ofstream os;
    NT target;
    A_star_node*** graph;
    vector< NT > openList;
}

class A_star_node {
  public:
    A_star_node();
    ~A_star_node();
    void setH();
    void setG();
    void setType(nodeType);
    void setParent(NT);
    void setOpen(bool);

    int getF();
    nodeType getType();
    NT getParent();
    bool getOpen();
  private:
    bool open;
    int H;
    int G;
    nodeType type;
    NT parent;
}

#endif
