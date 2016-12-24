#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <stdlib.h>

#define subNodeNum 26

using namespace std;

//Forming a tree according to the words i.e. letters forming a node
class treeNode
{
public:
  char x;
  bool isWordEnd;
  shared_ptr<class treeNode> children[subNodeNum];
};

//functions to form the tree
class wordTree
{
private:
  shared_ptr<class treeNode> root;

  public:
    wordTree(): root(new treeNode)
    {}
    void insertWord(const char*, int);
    bool containString(const char*, int, int, vector<vector<char> >&);
    bool checkIfCompound(const char*, int);
    void printstats(string,string,int);
};
