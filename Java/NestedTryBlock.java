import java.io.*;

public class NestedTryBlock
{
  public static void main(String[] args)
  {
    int n1 = 15;
    int n2 = 0;
    int res = 0;
    try
    {
      FileInputStream fis = null;
      fis = new FileInputStream (new File (args[0]));
      try
      {
        res = n1/n2;
      }
      catch(ArithmeticException e)
      {
        System.out.println("ArithmeticException occured");
      }
    }
    catch(FileNotFoundException e)
    {
      System.out.println("File not found!!");
    }
    catch(ArrayIndexOutOfBoundsException e)
    {
      System.out.println("Array out of bound exception");
    }
    catch(Exception e)
    {
      System.out.println("Genereal exception occured");
    }
  }
}
