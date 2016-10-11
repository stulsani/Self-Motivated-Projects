#include <iostream>
#include <vector>
#define size 3

using namespace std;

int x[size] = {2,3,4};

class Vector
{
  int v[size];
public:
  Vector();
  Vector(int *);
  friend istream & operator >> (istream &,Vector &);
  friend ostream & operator << (ostream &,Vector &);
  friend Vector operator * (int,Vector);
  friend Vector operator * (Vector,int);
};

Vector::Vector()
{
  for(int i = 0;i < size;++i)
    v[i] = 0;
}

Vector::Vector(int* x)
{
  for(int i = 0;i < size;++i)
    v[i] = x[i];
}

istream & operator >> (istream & in,Vector & a)
{
  for(int i = 0;i < size;i++)
    in >> a.v[i];
  return (in);
}

ostream & operator << (ostream & out,Vector & b)
{
  out << "(" << b.v[0];
  for(int i = 1;i < size;i++)
    out << " ," << b.v[i];
  out << ")";
}

Vector operator * (int num,Vector b)
{
  Vector c;
  for(int i = 0;i < size;i++)
    c.v[i] = b.v[i] * num;
  return c;
}

Vector operator * (Vector b,int num)
{
  Vector c;
  for(int i = 0;i < size;i++)
    c.v[i] = b.v[i] * num;
  return c;
}

int main()
{
  Vector a;
  Vector b = x;
  cout << "Enter the elements of vector" << endl;
  cin >> a;
  cout << "Vector elements are::" << a << endl;
  Vector m = 2 * b;
  Vector n = a * 2;
  cout << "vector after multiplication, m::" << m << endl;
  cout << "vector after multiplication, n::" << n << endl;
  return 0;
}
