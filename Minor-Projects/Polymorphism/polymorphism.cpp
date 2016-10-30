#include <iostream>
#include <string.h>

using namespace std;

class Shape
{
protected:
  double a,b;
public:
  void get_data()
  {
    cout << "Enter values of a and b-->" << endl;
    cin >> a >> b;
  }
  virtual void display_area() = 0;
};

class Rectangle: public Shape
{
public:
  void display_area()
  {
    cout << "Area of rectangle is-->" << a*b << endl;
  }
};

class Triangle: public Shape
{
public:
  void display_area()
  {
    cout << "Area of trianle is-->" << (a*b)/2 << endl;
  }
};

class Circle:public Shape
{
public:
  void get_data()
  {
    cout << "Enter the radius" << endl;
    cin >> a;
  }
  void display_area()
  {
    cout << "Area of circle is-->" << 3.14*(a*a) << endl;
  }
};

int main()
{
  Shape *ptr[3];
  Rectangle rect;
  ptr[1] = &rect;
  rect.get_data();
  rect.display_area();
  Triangle tri;
  ptr[2] = &tri;
  tri.get_data();
  tri.display_area();
  Circle cir;
  ptr[3] = &cir;
  cir.get_data();
  cir.display_area();
  return 0;
}
