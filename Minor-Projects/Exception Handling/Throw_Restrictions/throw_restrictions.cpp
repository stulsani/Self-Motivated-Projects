#include <iostream>

using namespace std;

void test(int x) throw(int,double)
{
  if(x == 0)
    throw('x');   //char
  if(x == 1)
    throw(x);     //int
  if(x == 2)
    throw(1.0);   //double
}

int main()
{
  try
  {
    cout << "x==0" << endl;
    test(0);
    cout << "x==1" << endl;
    test(1);
    cout << "x==2" << endl;
    test(2);
  }
  catch(char c)
  {
    cout << "In character catch block" << endl;
  }
  catch(int x)
  {
    cout << "In integer catch block" << endl;
  }
  catch(double y)
  {
    cout << "In double catch block" << endl;
  }
  catch(...)
  {
    cout << "Generic catch" << endl;
  }
  return 0;
}
