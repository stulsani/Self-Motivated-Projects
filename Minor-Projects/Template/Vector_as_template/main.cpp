#include<iostream>
#include "vector_template.h"

using namespace std;

int main()
{
  float x[3] = {1.1,2.2,3.3};
  float y[3] = {4.4,5.5,6.6};
  vector<float> v1(x);
  vector<float> v2(y);
  cout << "V1: ";
  v1.display();
  cout << "V2: ";
  v2.display();
  float r = v1 * v2;
  cout << "The sum for v1*v2 is: " << r << endl;
  return 0;
}
