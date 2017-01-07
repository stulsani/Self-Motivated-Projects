class First
{
  void display(String msg)
  {
    System.out.print ("["+msg);
    try
    {
       Thread.sleep(500);
    }
    catch(InterruptedException e)
    {
       e.printStackTrace();
    }
    System.out.println ("]");
  }
}

class Second extends Thread
{
  First fobj;
  String msg;
  Second(First obj, String m)
  {
    msg = m;
    fobj = obj;
    start();
  }
  public void run()
  {
    fobj.display(msg);
  }
}

public class WithoutSyncDemo
{
  public static void main(String[] args)
  {
    First fobj = new First();
    Second s1 = new Second(fobj,"1st Message");
    Second s2 = new Second(fobj,"2nd Message");
    Second s3 = new Second(fobj,"3rd Message");
  }
}
