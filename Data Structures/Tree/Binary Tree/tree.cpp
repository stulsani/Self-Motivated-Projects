#include "tree.h"

Tree::Tree()
{
  root = NULL;
}

void Tree::insert(int key)
{
  if(root == NULL)
  {
    Node *temp = new Node();
    temp-> left = NULL;
    temp-> right = NULL;
    temp-> data = key;
    root = temp;
  }
  else
    insert(root,key);
}

void Tree::insert(Node *leaf,int key)
{
  if(leaf-> data > key)
  {
    if(leaf-> left != NULL)
      insert(leaf-> left,key);
    else
    {
      leaf->left=new Node;
      leaf->left->data=key;
      leaf->left->left=NULL;    //Sets the left child of the child node to null
      leaf->left->right=NULL;
    }
  }
  else
  {
    if(leaf->right!=NULL)
      insert(leaf->right,key);
    else
    {
      leaf->right=new Node;
      leaf->right->data=key;
      leaf->right->left=NULL;
      leaf->right->right=NULL;
    }
  }
}

void Tree::print()
{
  cout << "Printing tree" << endl;
  print(root);
  cout << endl;
}

void Tree::print(Node *root)
{
  if(root != NULL)
  {
    cout << root-> data << " ";
    print(root-> left);
    print(root-> right);
  }
}

bool Tree::find(int key)
{
  if(root == NULL)
    return false;
  if(find(root,key))
    return true;
  else
    return false;
}

bool Tree::find(Node *leaf,int key)
{
  bool result = false;
  if(leaf-> data == key)
  {
    result = true;
    return result;
  }
  if(leaf-> data > key)
  {
    if(leaf-> left != NULL)
      find(leaf-> left,key);
  }
  else
  {
    if(leaf->right!=NULL)
      find(leaf->right,key);
  }
}

bool Tree::deletetree(int key)
{
  if(find(key))
    deletetree(root,key);
  else
    return false;
}

bool Tree::deletetree(Node *leaf,int key)
{
  bool result = false;
  if(leaf-> data == key)
  {
    result = true;
    if(leaf == root)
    {

    }
    else
    {
      leaf
      delete leaf;
    }
    return result;
  }
  if(leaf-> data > key)
  {
    if(leaf-> left != NULL)
      deletetree(leaf-> left,key);
  }
  else
  {
    if(leaf->right!=NULL)
      deletetree(leaf->right,key);
  }
}
