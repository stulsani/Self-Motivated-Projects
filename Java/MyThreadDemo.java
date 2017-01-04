class MyThread extends Thread
{
  public void run()
  {
    System.out.println("Thread is up and running in class extension method");
  }
}

class MyThreadFromInterface implements Runnable
{
  public void run()
  {
    System.out.println("Thread is up and running in interface implemented method");
  }
}

public class MyThreadDemo
{
  public static void main(String[] args)
  {
    MyThread mt = new MyThread();
    mt.start();   //calling start method on instance of class extended
    MyThreadFromInterface mti = new MyThreadFromInterface();
    Thread t = new Thread(mti);
    t.start();    //calling start method on instance of interface implemented
  }
}
