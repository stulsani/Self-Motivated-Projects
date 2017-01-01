import java.io.*;

class InvalidAgeException extends Exception
{
  InvalidAgeException(String s)
  {
    super(s);
  }
  public String toString()
  {
    return "Candidate is less than 18 year is not allowed to vote.";
  }
}

class ValidateCandidate
{
  int age;
  ValidateCandidate(int a)
  {
    age = a;
  }
  void validate() throws InvalidAgeException
  {
    if(age < 18)
    {
      throw new InvalidAgeException("Invalid Candidate");
    }
    else
    {
      System.out.println("Welcome to voting!!!");
    }
  }
  public static void main(String[] args)
  {
    ValidateCandidate obj = new ValidateCandidate(13);
    try
    {
      obj.validate();
    }
    catch(Exception e)
    {
      System.out.println("Exception Occured: " + e);
    }
  }
}
