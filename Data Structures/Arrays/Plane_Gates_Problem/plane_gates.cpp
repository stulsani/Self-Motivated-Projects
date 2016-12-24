#include <algorithm>
#include <iostream>

using namespace std;

int mingates(int arr[],int dep[],int n)
{
  int gatesrequired = 1,totalgates = 1,i = 1,j = 0;
  sort(arr,arr + n);
  sort(dep,dep + n);
  while(i < n && j < n)
  {
    if(arr[i] < dep[j])
    {
      gatesrequired++;
      i++;
    }
    else
    {
      gatesrequired--;
      j++;
    }
    if(totalgates < gatesrequired)
    {
      totalgates = gatesrequired;
    }
  }
  return totalgates;
}

int main()
{
  int arr[] = {900, 940, 950, 1100, 1500, 1800};
  int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
  int n = sizeof(arr)/sizeof(arr[0]);
  cout << "Minimum gates required:" << mingates(arr,dep,n) << endl;
  return 0;
}
