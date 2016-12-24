#include "concatenated.h"

using namespace std;

//this function is used to insert a word(i.e.alphabet of the word) in a treeNode
//if the alphabet already exists it forms a new root for that alphabet
// if alphabet is already present in the tree then it continues on that branch
//and adds charcaters for the string accordingly
void wordTree::insertWord(const char* word, int size)
{
  shared_ptr<class treeNode> node = root;
  char *c = "a";
  int index = *word - *c;
  if(node->children[index] != NULL)
  {
    node = node->children[index];
  }
  else
  {
    node->children[index].reset(new treeNode);
    node = node->children[index];
    node->x = *word;
    node->isWordEnd = false;
  }
  for(int i=1; i<size; ++i)
  {
    index = *(word+i) - *c;
    if(node->children[index] != NULL)
    {
      node = node->children[index];
    }
    else
    {
      node->children[index].reset(new treeNode);
      node = node->children[index];
      node->x = *(word+i);
      node->isWordEnd = false;
    }
  }
  node->isWordEnd = true;
}

//this function checks if a given word(string) is a part of other word in the tree
//if yes it returns true or else it returns false
bool wordTree::containString(const char* cstr,int start,int end,vector<vector<char> >& resultMatrix)
{
  shared_ptr<class treeNode> node = root;
  char *c = "a";
  for(int i=start; i<end; ++i)
  {
    if(resultMatrix[start][i] == 0)
    {
      containString(cstr, start, i, resultMatrix);
    }
    if(resultMatrix[i+1][end] == 0)
    {
      containString(cstr, i+1, end, resultMatrix);
    }
    if(resultMatrix[start][i] == 1 && resultMatrix[i+1][end] == 1)
    {
      resultMatrix[start][end] = 1;
      return true;
    }
  }
  int pos = start;
  int index = *(cstr + pos) - *c;
  while(node->children[index])
  {
    node = node->children[index];
    pos++;
    if(pos > end)
    {
      break;
    }
    index = *(cstr + pos) - *c;
  }
  if(node->isWordEnd == true && pos > end)
  {
    resultMatrix[start][end] = 1;
    return true;
  }
  else
  {
    resultMatrix[start][end] = -1;
    return false;
  }
}

//this function calls containString function for every letter in the alphabet
//and checks if the alphabet is part of a string(tree), if yes it repeats
//other alphabets in the words to see it is part of some string in tree
bool wordTree::checkIfCompound(const char* cstr,int size)
{
  bool result = false;
  vector<vector<char> > resultMatrix;
  resultMatrix.resize(size);
  for(int i=0; i<size; ++i)
  {
    resultMatrix[i].resize(size);
    for(int j=0; j<size; ++j)
    {
      resultMatrix[i][j] = 0;
    }
  }
  for(int i=0; i<size-1; ++i)
  {
    if(containString(cstr,0,i,resultMatrix) && containString(cstr,i+1,size-1,resultMatrix))
    {
      result = true;
      break;
    }
  }
  return result;
}

//printing stats
void wordTree::printstats(string longestStr,string secondLongestStr,int numOfWords)
{
  cout << "Longest String------> " << longestStr << endl;
  cout << "Second Longest String-----> " << secondLongestStr << endl;
  cout << "The total count of concatenated words in the file-----> " << numOfWords << endl;
}
