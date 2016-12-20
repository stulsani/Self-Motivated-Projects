import java.io.*;

class instanceOfOperator
{}

  public class car extends instanceOfOperator
  {
    public static void main(String []args)
    {
      instanceOfOperator A = new car();
      boolean result = A instanceof car;
      System.out.println(result);
    }
  }
