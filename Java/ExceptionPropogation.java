import java.io.*;


class ExceptionPropogation
{
  // Checked exception are not forwarded in calling chain
  void p()
  {
      //throw new java.io.IOException("device error");//checked exception
  }
  //unchecked exception are forwarded in calling chain
  void q()
  {
    int data = 15/0;
  }
  void n()
  {
    try
    {
      q();
      p();
    }
    catch(Exception e)
    {
      System.out.println("Exception caught");
    }
  }
  void m()
  {
    n();
  }
  public static void main(String[] args)
  {
    ExceptionPropogation obj = new ExceptionPropogation();
    obj.m();
    System.out.println("Normal flow");
  }
}
