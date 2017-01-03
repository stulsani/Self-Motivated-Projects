import java.io.*;

class Outer
{
  private int value = 70;
  private int number = 40;
  class Inner
  {
    void show()
    {
      System.out.println("The value is--> " + value);
    }
    void showNumber()
    {
      System.out.println("The number is--> " + number);
    }
  }
  void display()
  {
    Inner in = new Inner();
    in.show();
  }
  public static void main(String[] args)
  {
    Outer obj = new Outer();
    obj.display();
    Outer.Inner in = obj.new Inner();
    in.showNumber();
  }
}
