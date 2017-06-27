#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <climits>
#include <fstream>
#include "alg.h"
using namespace std;
/************************************
 *           A* algorithm           *
 ************************************/
A_star::A_star(int width, int length, int n_layer, int viaCost, const char* filename) 
  :filename(filename)
{
  this->width = width; this->length = length; this->n_layer = n_layer;
  this->graph = new A_star_node**[width];
  for(int i = 0; i < width; i++) {
    this->graph[i] = new A_star_node*[length];
    for(int j = 0; j < width; j++) {
      this->graph[i][j] = new A_star_node[n_layer];
    }
  }
  this->viaCost = viaCost;
}

A_star::~A_star() {
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      delete [] this->graph[i][j];
    }
    delete [] this->graph[i];
  }
  delete [] this->graph;
}

void
A_star::setNodeType(int llx, int lly, int urx, int ury, int layer, nodeType t) {
  for(int i = llx; i <= urx; i++) {
    for(int j = lly; j <= ury; i++)
      //TODO: layer
      this->graph[i][j][layer-1].setType(t);
  }
  if(t == shape) {
    int fixedX = llx;
    for(int i = lly; i <= ury; i++) 
      this->graph[fixedX][i][layer-1].setShapeEdge(true);
    fixedX = urx;
    for(int i = lly; i <= ury; i++) 
      this->graph[fixedX][i][layer-1].setShapeEdge(true);
    int fixedY = lly;
    for(int i = llx; i <= urx; i++)
      this->graph[i][fixedY][layer-1].setShapeEdge(true);
    fixedY = ury;
    for(int i = llx; i <= urx; i++)
      this->graph[i][fixedY][layer-1].setShapeEdge(true);
  }
}

void
A_star::push2OpenList(NT t) {
  A_star_node* n = &graph[get<0>(t)][get<1>(t)][get<2>(t)];
  if(n->getOpen()) return; //node is already in open list
  n->setOpen(true);
  openList.push_back(t);
}

void
A_star::setTarget(int target_x, int target_y, int target_z) {
  target = make_tuple(target_x, target_y, target_z);
  for(int i = 0; i < this->width; i++) {
    for(int j = 0; j < this->length; j++) {
      for(int k = 0; k < this->n_layer; k++) {
        int x_dif = abs(target_x - i);
        int y_dif = abs(target_y - j);
        int z_dif = abs(target_z - k);
        this->graph[i][j][k].setH(x_dif, y_dif, z_dif, this->viaCost);
      }
    }
  }
}

void
A_star::setSource(int x, int y, int z) {
  this->push2OpenList(make_tuple(x, y, z));
}

/***************************************
 *  For all neighbor, update G value   *
 **************************************/
// return true if update a target node
bool
A_star::updateG(NT t, int G, NT parent) {
  push2OpenList(t);
  A_star_node* n = &graph[get<0>(t)][get<1>(t)][get<2>(t)];
  n->setG(G, parent);
  if(t == target) {
    return true;
  }
  return false;
}

bool
A_star::checkValid(NT t, int G, NT parent) {
  //check out of range
  int x = get<0>(t), y = get<1>(t), z = get<2>(t);
  if(x < 0 || y < 0 || z < 0 || x >= width || y >= length || z >= n_layer) //TODO:check width, length, height in code >= not >
    return false;
  //check obstacle
  if(graph[x][y][z].getType() == obstacle)
    return false;
  return updateG(t, G, parent);
}

bool
A_star::forAllNeighbor(NT t) {
  A_star_node* n = &graph[get<0>(t)][get<1>(t)][get<2>(t)];
  vector< NT > same_layer;
  vector< NT > dif_layer;
  same_layer.push_back(make_tuple(get<0>(t)+1, get<1>(t), get<2>(t)));
  same_layer.push_back(make_tuple(get<0>(t)-1, get<1>(t), get<2>(t)));
  same_layer.push_back(make_tuple(get<0>(t), get<1>(t)+1, get<2>(t)));
  same_layer.push_back(make_tuple(get<0>(t), get<1>(t)-1, get<2>(t)));
  dif_layer.push_back(make_tuple(get<0>(t), get<1>(t), get<2>(t)+1));
  dif_layer.push_back(make_tuple(get<0>(t), get<1>(t), get<2>(t)-1));
  //Only if target, checkValid = true
  for(auto& node : same_layer) {
    int newG = n->getG() + 1;
    return checkValid(node, newG, t); 
  }
  for(auto& node : dif_layer) {
    int newG = n->getG() + this->viaCost;
    return checkValid(node, newG, t); 
  }
}

void
A_star::writeH(ofstream& ofs, NT a, NT b) {
  NT small = (a < b)? a : b;
  NT large = (a < b)? b : a;
  ofs << "H-line M" << (get<2>(small) + 1) <<" (" << get<0>(small) << ","
    << get<1>(small) << ") (" << get<0>(large) << "," << get<1>(large) << ")" << endl;
}

void
A_star::writeV(ofstream& ofs, NT a, NT b) {
  NT small = (a < b)? a : b;
  NT large = (a < b)? b : a;
  ofs << "V-line M" << (get<2>(small) + 1) <<" (" << get<0>(small) << ","
    << get<1>(small) << ") (" << get<0>(large) << "," << get<1>(large) << ")" << endl;
}

void
A_star::writeVia(ofstream& ofs, NT a, NT b) {
  NT small = (a < b)? a : b;
  ofs << "Via V" << (get<2>(small) + 1) <<" (" << get<0>(small) << ","
    << get<1>(small) << ")" << endl;
}

// return next start node, return invalid tuple if terminate 
NT
A_star::lineRule(NT start) {
  lineType lt(init);
  NT tem = start; 
  A_star_node* s = &graph[get<0>(start)][get<1>(start)][get<2>(start)];
  NT end = s->getParent();
  int change = 0;
  ofstream ofs;
  ofs.open(this->filename, ios::out | ios::app);
  while(1) {
    A_star_node* n = &graph[get<0>(end)][get<1>(end)][get<2>(end)];
    if(n->getParent() == IT) 
      cerr << "line parent should not be invalid node" << endl;
    if(abs(get<0>(tem) - get<0>(end)) == 1) {
      if(lt != hLine)
        change = ((change + 1) % 2);
      if(!change) {
        writeH(ofs, start, tem);
        return tem;
      }
      if(n->getShapeEdge()) {
        writeH(ofs, start, end);
        return IT;
      }
    } else if(abs(get<1>(tem) - get<1>(end)) == 1) {
      if(lt != vLine)
        change = ((change + 1) % 2);
      if(!change) {
        writeV(ofs, start, tem);
        return tem;
      }
      if(n->getShapeEdge()) {
        writeV(ofs, start, end);
        return IT;
      }
    } else if(abs(get<2>(tem) - get<2>(end)) == 1) {
      if(lt != via)
        change = ((change + 1) % 2);
      if(!change) {
        writeVia(ofs, start, tem);
        return tem;
      }
      if(n->getShapeEdge()) {
        writeVia(ofs, start, end);
        return IT;
      }
      return end;
    } else {
      cerr << "no such case in line rule" << endl;
    }
  }
  ofs.close();
}

void
A_star::runAlgorithm() {
  while(!openList.empty()) {
    sort(openList.begin(), openList.end(), 
      [this](NT a, NT b) {
        return(this->graph[get<0>(a)][get<1>(a)][get<2>(a)].getF() >
               this->graph[get<0>(b)][get<1>(b)][get<2>(b)].getF()); 
      }
    );
    NT start = openList.back();
    openList.pop_back();
    if(forAllNeighbor(start)) break;
  }
  //backtrace
  //find port
  NT port;
  A_star_node* n = &graph[get<0>(target)][get<1>(target)][get<2>(target)];
  while(!n->getShapeEdge()) {
    port = n->getParent();
    n = &graph[get<0>(port)][get<1>(port)][get<2>(port)];
  }
  //output the file
  while(port != IT) {
    port = lineRule(port);
  }
}

/************************************
 *             A* node              *
 ************************************/
A_star_node::A_star_node() {
  this->open = false;
  this->type = none;
  this->parent = IT;
  this->H = INT_MAX; this->G = INT_MAX;
  this->shapeEdge = false;
}

A_star_node::~A_star_node() {
}

void
A_star_node::setType(nodeType t) {
  this->type = t;
}

nodeType
A_star_node::getType() {
  return this->type;
}

int
A_star_node::getF() {
  return (this->H + this->G);
}

void
A_star_node::setH(int x_dif, int y_dif, int z_dif, int via_cost) {
  this->H = (x_dif + y_dif + (z_dif * via_cost));
}

void
A_star_node::setOpen(bool b) {
  this->open = b;
}

bool
A_star_node::getOpen() {
  return this->open;
}

void
A_star_node::setG(int G, NT from) {
  if(this->G > G) {
    this->parent = from;
    this->G = G;
  }
}

int
A_star_node::getG() {
  return this->G;
}

void
A_star_node::setParent(NT nt) {
  this->parent = nt;
}

NT
A_star_node::getParent() {
  return this->parent;
}

void
A_star_node::setShapeEdge(bool b) {
  this->shapeEdge = b;
}

bool
A_star_node::getShapeEdge() {
  return this->shapeEdge;
}
