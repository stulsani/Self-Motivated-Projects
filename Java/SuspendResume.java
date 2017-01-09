class NewThread implements Runnable
{
  String name;
  Thread t;
  boolean suspendFlag;

  NewThread(String threadname)
  {
    name = threadname;
    t = new Thread(this,name);
    System.out.println("New thread: " + t);
    suspendFlag = false;
    t.start();
  }

  public void run()
  {
    try
    {
      for(int i = 5; i > 0; i--)
      {
        System.out.println(name + ": " + i);
        Thread.sleep(200);
        synchronized(this)
        {
          while(suspendFlag)
          {
            wait();
          }
        }
      }
    }
    catch(Exception e)
    {
      System.out.println("Exception occured");
    }
    System.out.println(name + " exiting.");
  }

  void mysuspend()
  {
    suspendFlag = true;
  }

  synchronized void myresume()
  {
    suspendFlag = false;
    notify();
  }
}

public class SuspendResume
{
  public static void main(String[] args)
  {
    NewThread obj1 = new NewThread("One");
    NewThread obj2 = new NewThread("Two");
    try
    {
      Thread.sleep(100);
      obj1.mysuspend();
      System.out.println("Suspending thread One");
      Thread.sleep(100);
      obj1.myresume();
      System.out.println("Resuming thread One");
      Thread.sleep(100);
      obj2.mysuspend();
      System.out.println("Suspending thread Two");
      Thread.sleep(100);
      obj2.myresume();
      System.out.println("Resuming thread One");
    }
    catch (InterruptedException e)
    {
       System.out.println("Main thread Interrupted");
    }
    try
    {
      System.out.println("Waiting for threads to finish.");
      obj1.t.join();
      obj2.t.join();
    }
    catch (InterruptedException e)
    {
      System.out.println("Main thread Interrupted");
    }
    System.out.println("Main thread exiting.");
  }
}
