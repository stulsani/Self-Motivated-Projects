class A
{
  int x;
  int y;
  int get(int p, int q)
  {
    x=p;
    y=q;
    return(0);
  }
  void Show()
  {
   System.out.println(x);
  }
}

class singleInheritance extends A
{
  public static void main(String [] args)
  {
    A obj = new A();
    obj.get(5,6);
    obj.Show();
  }
}
