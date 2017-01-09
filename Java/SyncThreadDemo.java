class Customer
{
  int amount = 0;
  int flag = 0;

  public synchronized void withdraw(int amount)
  {
    System.out.println(Thread.currentThread().getName() + " is going to withdraw: " + amount);
    if(flag == 0)
    {
      try
      {
        wait();
      }
      catch(Exception e)
      {}
    }
    if(this.amount > amount)
    {
      this.amount -= amount;
    }
    else
    {
      System.out.println("The amount to be withdrawed is greater then the current balance: " + this.amount);
    }
    System.out.println("Withdraw Completed");
    System.out.println("Amount after withdraw is: " + this.amount);
  }

  public synchronized void deposit(int amount)
  {
    System.out.println(Thread.currentThread().getName() + " is going to deposit: " + amount);
    this.amount += amount;
    System.out.println("Deposit Completed");
    System.out.println("Amount after deposit is: " + this.amount);
    notifyAll();
    flag = 1;
  }
}

class SyncThreadDemo
{
  public static void main(String[] args)
  {
    Customer c = new Customer();
    Thread t1 = new Thread()
    {
      public void run()
      {
        c.deposit(50000);
      }
    };
    Thread t2 = new Thread()
    {
      public void run()
      {
        c.withdraw(10000);
      }
    };
    t1.setName("Sumeet");
    t2.setName("Sagar");
    t1.start();
    t2.start();
  }
}
