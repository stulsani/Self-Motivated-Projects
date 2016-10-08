#include <iostream>
#include <string.h>

#define MAXIMUM 4

using namespace std;

class Book
{
  char *author,*publisher,*title;
  double price;
  int copies;
public:
  Book();
  void searchbook();
  void totalcost(int,int);
  void numofcopies(int);
};

Book arr[MAXIMUM];

Book::Book()
{
    for(int i = 0;i < MAXIMUM;i++)
    {
      arr[i].author = new char[80];
      arr[i].title = new char[80];
      arr[i].publisher = new char[80];
    }
    arr[0].author = "Ryan";
    arr[0].title = "TheLion";
    arr[0].publisher = "T Series";
    arr[0].price = 1000;
    arr[0].copies = 5;

    arr[1].author = "Jeff";
    arr[1].title = "ThePirates";
    arr[1].publisher = "tata";
    arr[1].price = 1000.44;
    arr[1].copies = 5;

    arr[2].author = "Rohan";
    arr[2].title = "Thenewsreporter";
    arr[2].publisher = "T Series";
    arr[2].price = 105;
    arr[2].copies = 5;

    arr[3].author = "Dude";
    arr[3].title = "TheGymer";
    arr[3].publisher = "T Series";
    arr[3].price = 100.45;
    arr[3].copies = 2;
}

void Book::searchbook()
{
  int trigger = 0;
  char* search_author = new char[80];
  char* search_title = new char[80];
  cout << "Enter the author name and title to search the book" << endl;
  cin >> search_author >> search_title;
  for(int i = 0;i < MAXIMUM;i++)
  {
    if( (!(strcmp(search_author, arr[i].author)))  && (!(strcmp(search_title, arr[i].title))) )
    {
      numofcopies(i);
      break;
    }
    else if(i == MAXIMUM - 1)
      trigger = 1;
  }
  if(trigger == 1)
    cout << "This book is not available, Sorry!!!" << endl;
}

void Book::numofcopies(int i)
{
  int copy;
  cout << "How many copies you want??" << endl;
  cin.clear();
  cin >> copy;
  if(arr[i].copies >= copy)
  {
    totalcost(i,copy);
  }
  else
  {
    std::cout << "Sorry We don't have those many copies available" << std::endl;
  }
}

void Book::totalcost(int i,int copy)
{
  double price = arr[i].price;
  double total = price * copy;
  cout << "Price is-->" << total << endl;
}

int main()
{
  Book obj;
  obj.searchbook();
  return 0;
}
