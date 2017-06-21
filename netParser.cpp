#include <iostream>
#include <fstream>
#include <string>
#include "netParser.h"
#include "graph.h"
using namespace std;

int* Block::central()
{
  int* central = new int[2];
  central[0] = (LLx +URx)/2;
  central[1] = (LLy +URy)/2;
  return central;
}

netParser::netParser()
{
  viaCost = 0;
  spacing = 0;
  nShapes = 0;
  nVias = 0;
  nObstacles = 0;
}

netParser::~netParser()
{
}

bool
netParser::openDofile(const string& dof)
{
  
  ifstream dofile;
  dofile.open(dof);
  if (dofile.is_open())
  {
    string line;
    // from ViaCost to #Obstacles
    for(int i = 0; i < 7; ++i)
    {
      getline(dofile, line);
      for(int j = 0; j < 2; ++j)
      {
        line.erase(0, line.find(" ")+1);
      }
      this->parseLine(line, i);
    }
    // WARNING: crash if number defined previosly differs
    // RoutedShape
    for(int i = 0; i < this->nShapes; ++i)
    {
      getline(dofile, line);
      this->parseShape(line);
    }
#if 0
    if(nShapes != Shapes_vector.size())
    {
      cerr << "Error: Shape number";
      return false;
    }
#endif
    // RoutedVia
    for(int i = 0; i < this->nVias; ++i)
    {
      getline(dofile, line);
      this->parseVia(line);
    }
    // Obstacle
    for(int i = 0; i < this->nObstacles; ++i)
    {
      getline(dofile, line);
      this->parseObstacle(line);
    }
    while(getline(dofile, line)) {
      cerr << "There is something not being parsed." << endl;
    }
    dofile.close();
  }
  else
  {
    return dofile.is_open();
  }
  return true;
}

void
netParser::parseCase(const char* filename)
{
  
}

/*************************************************************************
 * For each line of the first seven lines in test case  
 * parse them into private members in netParser 
 ************************************************************************/
void
netParser::parseLine(string line, int l) {
  int* tuple1;
  int* tuple2;
  if(l == 2) {
    string line1 = line.substr(0, line.find(" "));
    string line2 = line.erase(0, line.find(" ")+1);
    tuple1 = parseTuple(line1);
    tuple2 = parseTuple(line2);
  }
  int temp;
  switch(l) {
    case 0:
      temp = stoi(line);
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
netParser::parseTuple(string tuple) {
  int* v = new int[2];
  string s1 = tuple.substr(1, tuple.find(","));
  string tem = tuple.erase(0, tuple.find(",")+1);
  string s2 = tem.substr(0, tem.find(")"));
  v[0] = stoi(s1);
  v[1] = stoi(s2);
  return v;
}

void
netParser::parseShape(string line) {
  string s[3];
  line = line.erase(0, line.find(" ")+1);
  for(int i = 0; i < 3; ++i) {
    s[i]= line.substr(0, line.find(" "));
    line = line.erase(0, line.find(" ")+1);
  }
  int layer = stoi(s[0].substr(1, s[0].size()));
  int* tuple1 = parseTuple(s[1]);
  int* tuple2 = parseTuple(s[2]);
  
  Block new_shape(tuple1[0], tuple1[1], tuple2[0], tuple2[1], layer);
  Shapes_vector.push_back(new_shape);
  
  delete [] tuple1;
  delete [] tuple2;
}

void
netParser::parseVia(string line) {
  string s[2];
  line = line.erase(0, line.find(" ")+1);
  for(int i = 0; i < 2; ++i) {
    s[i]= line.substr(0, line.find(" "));
    line = line.erase(0, line.find(" ")+1);
  }
  int layer = stoi(s[0].substr(1, s[0].size()));
  int* tuple = parseTuple(s[1]);
  
  Block new_Vias(tuple[0], tuple[1], tuple[0], tuple[1], layer);
  Vias_vector.push_back(new_Vias);
  
  delete [] tuple;
}

void
netParser::parseObstacle(string line) {
  string s[3];
  line = line.erase(0, line.find(" ")+1);
  for(int i = 0; i < 3; ++i) {
    s[i]= line.substr(0, line.find(" "));
    line = line.erase(0, line.find(" ")+1);
  }
  int layer = stoi(s[0].substr(1, s[0].size()));
  int* tuple1 = parseTuple(s[1]);
  int* tuple2 = parseTuple(s[2]);
  
  Block new_obstacle(tuple1[0], tuple1[1], tuple2[0], tuple2[1], layer);
  Vias_vector.push_back(new_obstacle);
  
  delete [] tuple1;
  delete [] tuple2;
}

ostream& operator << (ostream& out, const netParser& netMgr)
{
  out <<  "width : "      <<  netMgr.width      << endl;   
  out <<  "length : "     <<  netMgr.length     << endl;    
  out <<  "height : "     <<  netMgr.height     << endl;    
  out <<  "llx : "        <<  netMgr.llx        << endl; 
  out <<  "lly : "        <<  netMgr.lly        << endl; 
  out <<  "urx : "        <<  netMgr.urx        << endl; 
  out <<  "ury : "        <<  netMgr.ury        << endl; 
  out <<  "viaCost : "    <<  netMgr.viaCost    << endl;     
  out <<  "spacing : "    <<  netMgr.spacing    << endl;     
  out <<  "nShapes : "    <<  netMgr.nShapes    << endl;     
  out <<  "nVias : "      <<  netMgr.nVias      << endl;   
  out <<  "nObstacles : " <<  netMgr.nObstacles << endl;                   
}                                      
