class A
{
  int x;
  int y;
  void Show()
  {
   System.out.println("The value of x in A class: " + x);
  }
}

class superInInheritance extends A
{
  int x;
  int y;
  superInInheritance(int p,int q)
  {
    super.x = p;
    y = q;
  }
  void Show()
  {
    super.Show();
    System.out.println("In derived class");
    System.out.println("x in super class:  " + super.x);
    System.out.println("y in derived class:  " + y);
  }
  public static void main(String[] args)
  {
    superInInheritance obj = new superInInheritance(5,7);
    obj.Show();
  }
}
