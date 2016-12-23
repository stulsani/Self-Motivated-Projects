#include <iostream>
#include <string.h>

using namespace std;

template <class T>
void display(T x)
{
  cout << "Overloaded template display 1 function" << endl;
}

template <class A,class B>
void display(A x,B y)
{
  cout << "Overloaded template display 2 function" << endl;
}

void display(int x)
{
  cout << "Overloaded generic display function" << endl;
}

int main()
{
  display(100);
  display(100.2);
  display('c',22.2);
  return 0;
}
