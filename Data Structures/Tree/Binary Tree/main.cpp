#include "tree.h"

int main()
{
  int choice;
  char ch;
  Tree tree;
  do
  {
    cout << "1.Insert 2.Print 3.Find 4.Delete 5.Quit" << endl;
    cout << "Enter you choice" << endl;
    cin >> choice;
    switch(choice)
    {
      case 1:
        int x;
        cout << "Enter the value you want to insert" << endl;
        cin >> x;
        tree.insert(x);
        break;
      case 2:
        tree.print();
        break;
      case 3:
        int f;
        cout << "Enter the value you want to search" << endl;
        cin >> f;
        if(tree.find(f))
          cout << "Element found!!!" << endl;
        else
          cout << "Element not found!!!" << endl;
        break;
      case 4:
        int d;
        cout << "Enter the value you want to delete" << endl;
        cin >> d;
        if(tree.deletetree(d))
          cout << "Element deleted!!!" << endl;
        else
          cout << "Element not found!!!" << endl;
        break;
      case 5:
        exit(0);
      default:
        cout << "Wrong option!!" << endl;
    }
    cout << "Do you wanna continue??" << endl;
    cin >> ch;
  }while(ch == 'y' || ch == 'Y');
  return 0;
}
