#include <iostream>
#include <string.h>

using namespace std;

class String
{

public:
  char *str;
  int length;
  String()
  {
    length = 0;
    str = new char[length + 1];
  }

  String(char *s)
  {
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str,s);
  }

  void concatenate(char *,char *);
  void display();
};

void String::concatenate(char *s1,char *s2)
{
  int len = strlen(s1) + strlen(s2);
  delete str;
  str = new char[len + 1];
  strcpy(str,s1);
  strcat(str,s2);
}

void String::display()
{
  std::cout << "String is-->" << str << std::endl;
}

int main()
{
  String obj;
  String str1("Sumeet");
  String str2("Tulsani");
  str1.display();
  str2.display();
  obj.concatenate(str1.str,str2.str);
  obj.display();
}
