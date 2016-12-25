class Animal
{
  public static void testClassMethod()
  {
    System.out.println("In class method of Animal");
  }
  public void testInstanceMethod()
  {
    System.out.println("In instance method of Animal");
  }
}

public class Cat extends Animal
{
  public static void testClassMethod()
  {
    System.out.println("In class method of Cat");
  }
  public void testInstanceMethod()
  {
    System.out.println("In instance method of Cat");
  }
  public static void main(String[] args)
  {
    Cat myCat = new Cat();
    Animal myAnimal = myCat;
    myAnimal.testClassMethod();
    myAnimal.testInstanceMethod();
  }
}
