#include <iostream>
#include<cstdlib>

using namespace std;

struct Node
{
  int data;
  Node *left;
  Node *right;
};

class Tree
{
  Node *root;
public:
  Tree();
  void insert(int);
  void insert(Node*,int);
  void print();
  void print(Node*);
  bool find(int);
  bool find(Node*,int);
  bool deletetree(int);
  bool deletetree(Node*,int);
};
