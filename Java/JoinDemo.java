public class JoinDemo extends Thread
{
  public void run()
  {
        for(int i = 0;i < 5;++i)
        {
          try
          {
            Thread.sleep(500);
          }
          catch(Exception e)
          {
            System.out.println("Exception caught: " + e );
          }
          System.out.println("Running thread is: " + Thread.currentThread().getName() + " : " + i);
        }
  }

  public static void main(String[] args)
  {
    JoinDemo j1 = new JoinDemo();
    JoinDemo j2 = new JoinDemo();
    JoinDemo j3 = new JoinDemo();
    System.out.println("id of J1:"+j1.getId());
    System.out.println("id of J2:"+j2.getId());
    System.out.println("id of J3:"+j3.getId());
    j1.setName("Thread 1");
    j2.setName("Thread 2");
    j3.setName("Thread 3");
    j1.start();
    try
    {
      j1.join(1500);
    }
    catch(Exception e)
    {
      System.out.println("Exception caught: " + e);
    }
    j2.start();
    j3.start();
  }
}
