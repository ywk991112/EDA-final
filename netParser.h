#ifndef NET_PARSER_H
#define NET_PARSER_H
 
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <vector>

using namespace std;

class Block{
  public:
    Block(int llx, int lly, int urx, int ury, int layer) : LLx(llx), LLy(lly), URx(urx), URy(ury), Layer(layer) {};
    ~Block() {};
    int* central();
  
  private:
    int LLx, LLy, URx, URy;
    int Layer; //Mn for shape and obstacle, Vn for via
};

class netParser{
  public:
    netParser();
    ~netParser();

    // parse
    bool openDofile(const string&);
    void parseCase(const char*);
    void parseLine(string, int);
    void parseShape(string);
    void parseVia(string);
    void parseObstacle(string);
    int* parseTuple(string);

    // test
    friend ostream& operator << (ostream&, const netParser&);
  
    //global routing: construst a graph each shape is a node, and run kruskal
    void global_routing();
  
    //detailed routing: determine port, run dijkstra
    void detailed_routing();

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
    
    vector<Block> Shapes_vector;
    vector<Block> Vias_vector;
    vector<Block> obstacles_vector;
    vector<Block> wires_vector;
};

#endif
