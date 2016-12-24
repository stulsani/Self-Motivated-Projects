#include "concatenated.h"

int main()
{
  ifstream inFile;   //create a file object
  inFile.open("wordsforproblem.txt");
  unique_ptr<class wordTree> wt(new wordTree);
  string str;
  if(inFile.is_open())
  {
    while (inFile >> str)
    {
      const char *cstr = str.c_str();  //converting string to c-style string
      wt->insertWord(cstr, str.length());
    }
  }
  else
    cout << "Unable to open file!!!!" << endl;

  //reset the file pointer to the header of the file
  inFile.clear();
  inFile.seekg(0, ios::beg);

  //parse file to get the longest string, second longest string and
  //number of words that can be conclassed
  string longestStr = "";
  string secondLongestStr = "";
  int numOfWords = 0;
  while (inFile >> str)
  {
    const char *cstr = str.c_str();
    if(wt->checkIfCompound(cstr, str.length()))
    {
      if(str.length() >= longestStr.length())
      {
        secondLongestStr = longestStr;
        longestStr = str;
      }
      else if(str.length() > secondLongestStr.length())
      {
        secondLongestStr = str;
      }
      numOfWords++;
    }
  }

  //close file
  inFile.close();
  wt->printstats(longestStr,secondLongestStr,numOfWords);

  return 0;
}
