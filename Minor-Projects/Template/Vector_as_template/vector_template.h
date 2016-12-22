#include <iostream>

using namespace std;

const int size = 3;

template<class T>
class vector
{
  T* v;
public:
  vector(T* a)
  {
    v = new T[size];
    for(int i = 0;i < size;++i)
    {
      v[i] = a[i];
    }
  }
  int operator*(vector &y)
  {
    T sum = 0;
    for(int i = 0;i < size;++i)
    {
      sum += this-> v[i] * y.v[i];
    }
    return sum;
  }
  void display()
  {
      for(int i = 0;i < size;++i)
      {
        cout << v[i] << " ";
      }
      cout << endl;
  }
};
