#include <iostream>
#include "graph.h"
using namespace std;

int main() {
  Graph g("./case/case1");
  g.testParse();
  cout << (g.getNodeType(610, 2251, 0) == shape) << endl;
  cout << (g.getNodeType(2958, 2200, 2) == obstacle) << endl;
  cout << (g.getViaPos(447, 1411, 1) == up) << endl;

  return 0;
}
