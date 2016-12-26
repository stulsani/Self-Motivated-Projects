abstract class Shape
{
  abstract void display();
}

class Circle extends Shape
{
  void display()
  {
    System.out.println("This a Circle class display");
  }
}

class Triangle extends Shape
{
  void display()
  {
    System.out.println("This a Triangle class display");
  }
}

class AbstractDemo
{
  public static void main(String[] args)
  {
    Shape shp = new Circle();
    shp.display();
    shp = new Triangle();
    shp.display();
  }
}
