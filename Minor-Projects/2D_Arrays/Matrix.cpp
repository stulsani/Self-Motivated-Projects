#include <iostream>

using namespace std;

class matrix
{
  int **p;
  int d1,d2;
public:
  matrix(int x,int y);
  void get_element(int i,int j,int value)
  {
    p[i][j] = value;
  }
  int & put_element(int i,int j)
  {
    return p[i][j];
  }
};

matrix::matrix(int x,int y)
{
  d1 = x;
  d2 = y;
  p = new int *[d1];
  for(int i = 0;i < d1;i++)
  {
    p[i] = new int[d2];
  }
}

int main()
{
  int m,n,value;
  cout << "Enter the size of matrix (m,n)-->" << endl;
  cin >> m >> n;
  matrix obj(m,n);
  cout << "Enter matrix elements row wise" << endl;
  for(int i = 0;i < m;i++)
  {
    for(int j = 0; j < n;j++)
    {
      cin >> value;
      obj.get_element(i,j,value);
    }
  }
  cout << endl << "Matrix at location 1,2 is-->" << obj.put_element(1,2) << endl;
  return 0;
}
