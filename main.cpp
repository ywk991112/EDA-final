#include <iostream>
#include "netParser.h"
#include "graph.h"
using namespace std;

netParser netMgr;

static void usage()
{
  cout << "Usage: net_open_finder <input.txt> <output.txt>\n";
}

static void myexit()
{
  usage();
  exit(-1);
}

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cerr << "Error: illegal number of argument (" << argc << ")\n";
    myexit();
  }
  if(!netMgr.openDofile(argv[1]))
  {
    cerr << "Error: can't open file \"" << argv[1] << "\"\n";
    myexit();
  }
  else
  {
    cout << "Reading file \"" << argv[1] << "\"\n";
  }
#if 0
  cout << "*************************************\n"
       << "Reporting netMgr\n\n"
       << netMgr
       << "\nEnd reporting netMgr\n"
       << "*************************************\n";
  return 0;
#endif

  cout << "Start global routing\n";
  netMgr.global_routing();

  cout << "Start detailed routing\n";
  netMgr.detailed_routing();

}
