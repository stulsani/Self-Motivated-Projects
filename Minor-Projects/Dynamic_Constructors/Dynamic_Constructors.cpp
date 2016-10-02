#include <iostream>

using namespace std;

class Fixed_Deposit
{
private:
  long int P_amount;
  int years;
  float rate;
  float R_value;
public:
  Fixed_Deposit()
  {}
  Fixed_Deposit(float,int,float);
  Fixed_Deposit(float,int,int);
  void display();
};

Fixed_Deposit:: Fixed_Deposit(float p,int y,float r)
{
  cout << "in float" << endl;
  P_amount = p;
  years = y;
  rate = r;
  R_value = P_amount;
  for(int i = 0;i < y;i++)
  {
    R_value = R_value * (1.0 + r);
  }
}

Fixed_Deposit:: Fixed_Deposit(float p,int y,int r)
{
  cout << "In int << endl" << endl;
  P_amount = p;
  years = y;
  rate = r;
  R_value = P_amount;
  for(int i = 0;i < y;i++)
  {
    R_value = R_value * (1.0 + float(r)/100);
  }
}

void Fixed_Deposit::display()
{
  cout << "Principal amount-->" << P_amount << endl << "Return value-->" << R_value << endl;
}


int main()
{
  Fixed_Deposit fd1,fd2,fd3;
  long int p;
  float y,r;
  int R;
  cout << "Enter principal amount, years, and return rate (percent form)" << endl;
  cin >> p >> y >> R;
  fd1 = Fixed_Deposit(p,y,R);
  cout << "Enter principal amount, years, and return rate (decimal form)" << endl;
  cin >> p >> y >> r;
  fd2 = Fixed_Deposit(p,y,r);
  cout << "Deposit1" << endl;
  fd1.display();
  cout << "Deposit2" << endl;
  fd2.display();
  return 0;
}
