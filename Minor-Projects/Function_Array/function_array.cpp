#include <iostream>

using namespace std;

//int const m=10;

class item
{
  int itemcode[10];
  float itemprice[10];
  int count;
public:
  void cnt()
  {
    count = 0;
  }
  void getitem();
  void displayitem();
  void remove(int);
  void totalcost();
};

int main()
{
  item x;
  int ch;
  char choice;
  x.cnt();
  do
  {
    cout << "Select a option::" << endl;
    cout << "1. Add new item" << endl << "2. Delete item" << endl << "3. Display items"
    << endl << "4. Get total cost for items" << endl <<  "5. Quit" << endl;
    cin >> ch;
    switch(ch)
    {
      case 1:
        x.getitem();
        break;
      case 2:
        int itemid;
        cout << "Enter product id" << endl;
        cin >> itemid;
        x.remove(itemid);
        break;
      case 3:
        x.displayitem();
        break;
      case 4:
        x.totalcost();
        break;
      case 5:
        break;
      default:
        cout << "Invalid option" << endl;
    }
    cout << "Do u wanna continue::" << endl;
    cin >> choice;
  }while(choice == 'y' || choice == 'Y');
  return 0;
}

void item::getitem()
{
  cout << "Enter the product id" << endl;
  cin >> itemcode[count];
  cout << "Enter product price" << endl;
  cin >> itemprice[count];
  count++;
}

void item::remove(int itemcode)
{
  for(int i = 0;i < count;i++)
  {
    if(this-> itemcode[i] == itemcode)
    {
      this-> itemcode[i] = 0;
      itemprice[i] = 0;
    }
  }
}

void item::displayitem()
{
  for(int i = 0;i < count;i++)
  {
    cout << "Product id-->" << itemcode[i] << " Product price-->" << itemprice[i] << endl;;
  }
}

void item::totalcost()
{
  float total = 0;
  for(int i = 0;i < count;i++)
  {
    total = total + itemprice[i];
  }
  cout << "Total is-->" << total << endl;
}
