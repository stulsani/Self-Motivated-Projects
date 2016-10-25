#include <iostream>

using namespace std;

class Account
{
protected:
  char name[50];
  int account_no;
  char account_type;
  double balance;
public:
  Account()
  {
    balance = 10000.00;
  }
  void getname();
  void getaccountno();
  void accounttype(char);
  void deposit(double);
  void withdrawal(double);
  void display();
  double getbalance();
};

class SavingAccount: virtual public Account
{
protected:
  double compoundinterest;
public:
  SavingAccount()
  {
    compoundinterest = 0.04;
  }
  void interest();
};

class CheckingAccount: virtual public SavingAccount,virtual public Account
{
  //bool cheque-book;
  double minimumbalance;
public:
  CheckingAccount()
  {
    minimumbalance = 1000;
  }
  void minimumcheck();
};

double Account::getbalance()
{
  return balance;
}

void Account::getname()
{
  cout << "Enter the name of account holder" << endl;
  cin >> name;
}

void Account::getaccountno()
{
  cout << "Enter the account no. of account holder" << endl;
  cin >> account_no;
}

void Account::accounttype(char c)
{
  account_type = c;
}

void Account::deposit(double deposit)
{
  balance += deposit;
}

void Account::withdrawal(double withdraw)
{
  balance -= withdraw;
}

void Account::display()
{
  cout << "The total balance is-->" << balance << endl;
}

void SavingAccount::interest()
{
  balance = balance + (balance * compoundinterest);
}

void CheckingAccount::minimumcheck()
{
  CheckingAccount ca;
  double bal = ca.getbalance();
  if(bal < minimumbalance)
  {
    cout << "balance is low then 1000$, which is below minimum" << endl;
  }
}

int main()
{
  CheckingAccount ca;
  ca.getname();
  ca.getaccountno();
  char c;
  cout << "Enter the account type of account holder(C/S)" << endl;
  cin >> c;
  ca.accounttype(c);
  if(c == 'S' || c == 's')
  {
    ca.interest();
  }
  if(c == 'C' || c == 'c')
  {
    ca.minimumcheck();
  }
  char ch,choice;
  do
  {
    cout << "What would you like to do(Deposit amount(D),Withdraw Amount(W),display balance(B))" << endl;
    cin >> ch;
    if(ch == 'D' || ch == 'd')
    {
      double deposit;
      cout << "Enter the amount you would like to deposit??" << endl;
      cin >> deposit;
      ca.deposit(deposit);
    }
    else if(ch == 'W' || ch == 'w')
    {
      double withdraw;
      cout << "Enter the amount you would like to withdraw??" << endl;
      cin >> withdraw;
      ca.withdrawal(withdraw);
    }
    else if(ch == 'b' || ch == 'B')
    {
      ca.display();
    }
    cout << "Do you want to continue(Y/N)-->" << endl;
    cin >> choice;
  }while(choice == 'y' || choice == 'Y');
  return 0;
}
