class Account
{
  synchronized static void accountdetails(String accountname)
  {
    System.out.println("Account Name is: " + accountname + " and account holders name is: " + Thread.currentThread().getName() );
    try
    {
      Thread.sleep(500);
    }
    catch(Exception e)
    {}
  }
}

class MyThread1 extends Thread
{
  public void run()
  {
    Account.accountdetails("Google.com");
  }
}

class MyThread2 extends Thread
{
  public void run()
  {
    Account.accountdetails("Apple.com");
  }
}

class MyThread3 extends Thread
{
  public void run()
  {
    Account.accountdetails("Facebook.com");
  }
}

class MyThread4 extends Thread
{
  public void run()
  {
    Account.accountdetails("Amazon.com");
  }
}

class StaticSyncDemo
{
  public static void main(String[] args)
  {
    MyThread1 t1 = new MyThread1();
    MyThread2 t2 = new MyThread2();
    MyThread3 t3 = new MyThread3();
    MyThread4 t4 = new MyThread4();
    t1.setName("Sumeet");
    t2.setName("Sagar");
    t3.setName("Kapil");
    t4.setName("Yash");
    t1.start();
    t2.start();
    t3.start();
    t4.start();
  }
}
