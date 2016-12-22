import java.io.*;

class Cube
{
  int length,breath,height;
  Cube()
  {
    this(10,10);
  }
  Cube(int l,int b)
  {
    this(l,b,5);
    length = l;
    breath = b;
  }
  Cube(int l,int b,int h)
  {
    length = l;
    breath = b;
    height = h;
  }
  int getVolume()
  {
    int volume = length* breath* height;
    return volume;
  }
}

public class SpecialCube extends Cube
{
  int weight;
  SpecialCube()
  {
    super();
    weight = 10;
  }
  SpecialCube(int l,int b)
  {
    this(l,b,5);
    weight = 20;
  }
  SpecialCube(int l,int b,int h)
  {
    super(l,b,h);
    weight = 30;
  }
  int getWeigth()
  {
    return weight;
  }
  public static void main(String[] args)
  {
    SpecialCube obj1 = new SpecialCube();
    SpecialCube obj2 = new SpecialCube(5,5);
    SpecialCube obj3 = new SpecialCube(2,2,2);
    int result1 = obj1.getVolume();
    int result_w1 = obj1.getWeigth();
    int result2 = obj2.getVolume();
    int result_w2 = obj2.getWeigth();
    int result3 = obj3.getVolume();
    int result_w3 = obj3.getWeigth();
    System.out.println("The volume of cube 1 is: " + result1);
    System.out.println("The weigth of cube 1 is: " + result_w1);
    System.out.println("The volume of cube 2 is: " + result2);
    System.out.println("The weigth of cube 2 is: " + result_w2);
    System.out.println("The volume of cube 3 is: " + result3);
    System.out.println("The weigth of cube 3 is: " + result_w3);
  }
}
