abstract class Shape
{
  public static float pi = 3;
  protected float height;
  protected float width;
  abstract float area();
}

class Square extends Shape
{
  Square(float h,float w)
  {
    height = h;
    width = w;
  }
  float area()
  {
    return height * width;
  }
}

class Rectangle extends Shape
{
  Rectangle(float h,float w)
  {
    height = h;
    width = w;
  }
  float area()
  {
    return height * width;
  }
}

class Circle extends Shape
{
  float radius;
  Circle(float r)
  {
    radius = r;
  }
  float area()
  {
    return Shape.pi * radius * radius;
  }
}

class AbstractMethodDemo
{
  public static void main(String[] args)
  {
    Square sobj = new Square(4,3);
    Rectangle robj = new Rectangle(2,3);
    Circle cobj = new Circle(2);
    System.out.println("Area of Square is: " + sobj.area() );
    System.out.println("Area of Rectangle is: " + robj.area() );
    System.out.println("Area of Circle is: " + cobj.area() );
  }
}
