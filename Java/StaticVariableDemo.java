public class StaticVariableDemo
{
  int empId;
  String empName;
  static String companyName = "IT Company";
  StaticVariableDemo(int empId, String empName)
  {
    this.empId = empId;
    this.empName = empName;
  }
  void display()
  {
    System.out.println(empId+" "+empName+" "+companyName );
  }
  public static void main(String[] args)
  {
      StaticVariableDemo emp1 = new StaticVariableDemo(1111,"Sumeet");
      StaticVariableDemo emp2 = new StaticVariableDemo(2222,"Tulsani");
      emp1.display();
      emp2.display();
  }
}
