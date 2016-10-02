#include <iostream>

using namespace std;

class item
{
private:
  static int count;
  int num;
public:
  void getdata()
  {
    num = 5;
    count++;
  }
  void getcount()
  {
    cout << "Count is--->" << count << endl;
    //count++;
    //cout << "Count after is--->" << count << endl;
  }
};

int item:: count;

int main()
{
  item a,b,c;
  a.getdata();
  a.getcount();
  b.getdata();
  c.getdata();
  b.getcount();
  c.getcount();
  return 0;
}
