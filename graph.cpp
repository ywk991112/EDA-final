#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
using namespace std;

Graph::Graph(const char* filename) {
  this->parseCase(filename);
  this->graph = new Node**[this->width];
  for(int i = 0; i < this->width; ++i) {
    this->graph[i] = new Node*[this->length];
    for(int j = 0; j < this->length; j++) {
      this->graph[i][j] = new Node[this->height];
    }
  }
}

Graph::~Graph() {
  for(int i = 0; i < this->width; ++i) {
    for(int j = 0; j < this->length; ++j)
      delete [] this->graph[i][j];
    delete [] this->graph[i];
  }
  delete [] this->graph;
}

void
Graph::parseCase(const char* filename) {
  ifstream ifs;
  ifs.open(filename);
  if (ifs.is_open()) {
    string line;
    // from ViaCost to #Obstacles
    for(int i = 0; i < 7; ++i) {
      getline(ifs, line);
      for(int j = 0; j < 2; ++j) {
        line.erase(0, line.find(" ")+1);
      }
      this->parseLine(line, i);
    }
    // RoutedShape
    for(int i = 0; i < this->nShapes; ++i) {
      getline(ifs, line);
      this->parseShape(line);
    }
    // RoutedVia
    for(int i = 0; i < this->nVias; ++i) {
      getline(ifs, line);
      this->parseVia(line);
    }
    // Obstacle
    for(int i = 0; i < this->nObstacles; ++i) {
      getline(ifs, line);
      this->parseObstacle(line);
    }
    while(getline(ifs, line)) {
      cerr << "There is something not being parsed." << endl;
    }
    ifs.close();
  } else {
    cerr << "File " << filename << " does not exists." << endl;
  }
}

/*************************************************************************
 * For each line of the first seven lines in test case  
 * parse them into private members in Graph 
 ************************************************************************/
void
Graph::parseLine(string line, int l) {
  int* tuple1;
  int* tuple2;
  if(l == 2) {
    string line1 = line.substr(0, line.find(" "));
    string line2 = line.erase(0, line.find(" ")+1);
    tuple1 = parseTuple(line1);
    tuple2 = parseTuple(line2);
  }
  switch(l) {
    case 0:
      this->viaCost = stoi(line);
      break;
    case 1:
      this->spacing = stoi(line);
      break;
    case 2:
      this->width = ((tuple2[0] - tuple1[0]) + 1);
      this->length = ((tuple2[1] - tuple1[1]) + 1);
      this->llx = tuple1[0];
      this->lly = tuple1[1];
      this->urx = tuple2[0];
      this->ury = tuple2[1];
      break;
    case 3:
      this->height = stoi(line);
      break;
    case 4:
      this->nShapes = stoi(line);
      break;
    case 5:
      this->nVias = stoi(line);
      break;
    case 6:
      this->nObstacles = stoi(line);
      break;
    default:
      break;
  }
  if(l == 2) {
    delete [] tuple1;
    delete [] tuple2;
  }
}

/*************************************************************************
 * input a string "(123,456)", output an int array [123, 456] pointer
 * remember to delete [] v
 ************************************************************************/
int*
Graph::parseTuple(string tuple) {
  int* v = new int[2];
  string s1 = tuple.substr(1, tuple.find(","));
  string tem = tuple.erase(0, tuple.find(",")+1);
  string s2 = tem.substr(0, tem.find(")"));
  v[0] = stoi(s1);
  v[1] = stoi(s2);
  return v;
}

void
Graph::parseShape(string line) {
  string s[3];
  line = line.erase(0, line.find(" ")+1);
  for(int i = 0; i < 3; ++i) {
    s[i]= line.substr(0, line.find(" "));
    line = line.erase(0, line.find(" ")+1);
  }
  int layer = stoi(s[0].substr(1, s[0].size()));
  int* tuple1 = parseTuple(s[1]);
  int* tuple2 = parseTuple(s[2]);
  //TODO: i should be tuple1[0] - this->llx
  for(int i = tuple1[0]; i <= tuple1[1]; ++i) {
    for(int j = tuple2[0]; j <= tuple2[1]; ++j) {
      //TODO: set Node
    }
  }
  //TODO: record center
  delete [] tuple1;
  delete [] tuple2;
}

void
Graph::parseVia(string line) {
  string s[2];
  line = line.erase(0, line.find(" ")+1);
  for(int i = 0; i < 2; ++i) {
    s[i]= line.substr(0, line.find(" "));
    line = line.erase(0, line.find(" ")+1);
  }
  int layer = stoi(s[0].substr(1, s[0].size()));
  int* tuple = parseTuple(s[1]);
  //TODO: i should be tuple1[0] - this->llx
  //TODO: record via 
  delete [] tuple;
}

void
Graph::parseObstacle(string line) {
  string s[3];
  line = line.erase(0, line.find(" ")+1);
  for(int i = 0; i < 3; ++i) {
    s[i]= line.substr(0, line.find(" "));
    line = line.erase(0, line.find(" ")+1);
  }
  int layer = stoi(s[0].substr(1, s[0].size()));
  int* tuple1 = parseTuple(s[1]);
  int* tuple2 = parseTuple(s[2]);
  //TODO: i should be tuple1[0] - this->llx
  for(int i = tuple1[0]; i <= tuple1[1]; ++i) {
    for(int j = tuple2[0]; j <= tuple2[1]; ++j) {
      //TODO: set Node
    }
  }
  //TODO: record center
  delete [] tuple1;
  delete [] tuple2;
}

void
Graph::testParse() {
  cout <<  "width : "      <<  this->width      << endl;   
  cout <<  "length : "     <<  this->length     << endl;    
  cout <<  "height : "     <<  this->height     << endl;    
  cout <<  "llx : "        <<  this->llx        << endl; 
  cout <<  "lly : "        <<  this->lly        << endl; 
  cout <<  "urx : "        <<  this->urx        << endl; 
  cout <<  "ury : "        <<  this->ury        << endl; 
  cout <<  "viaCost : "    <<  this->viaCost    << endl;     
  cout <<  "spacing : "    <<  this->spacing    << endl;     
  cout <<  "nShapes : "    <<  this->nShapes    << endl;     
  cout <<  "nVias : "      <<  this->nVias      << endl;   
  cout <<  "nObstacles : " <<  this->nObstacles << endl;                   
}                                      
