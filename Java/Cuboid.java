import java.io.*;

public class Cuboid
{
  int length,breath,height;
  Cuboid()
  {
    this(10,10);
  }
  Cuboid(int l,int b)
  {
    this(l,b,5);
    length = l;
    breath = b;
  }
  Cuboid(int l,int b,int h)
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
  public static void main(String[] args)
  {
    Cuboid obj1 = new Cuboid();
    Cuboid obj2 = new Cuboid(5,5);
    Cuboid obj3 = new Cuboid(2,2,2);
    int result1 = obj1.getVolume();
    int result2 = obj2.getVolume();
    int result3 = obj3.getVolume();
    System.out.println("The volume of cuboid 1 is: " + result1);
    System.out.println("The volume of cuboid 2 is: " + result2);
    System.out.println("The volume of cuboid 3 is: " + result3);
  }
}
