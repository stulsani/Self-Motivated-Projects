#include <iostream>

using namespace std;

void divide(int x,int y,int z)
{
  cout << "We are in the divide function" << endl;
  if(x-y != 0)
  {
    int r = x-y;
    int result = z/r;
    cout << "The division for (x-y)/z is-->" << result << endl;
  }
  else
  {
    throw(x-y);    //throw point
  }
}

int main()
{
  try
  {
    cout << "We are in try block" << endl;
    divide(10,20,20);    //invokes divide() function
    divide(10,10,30);    //invokes divide() function
  }
  catch(int i)
  {
    cout << "Exception Caught" << endl;
  }
  return 0;
}
