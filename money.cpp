#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <class I>
void print(I first, I last) {
  ostream_iterator<int> oi(cout, " ");
  copy(first, last, oi);
  cout << endl;
}

int main() {
  cout << "Enter values of different coins\n";
  string strCoins;
  getline(cin, strCoins);
  stringstream iss(strCoins);
  istream_iterator<int> ii(iss);
  istream_iterator<int> eos;
  vector<int> coins(ii, eos);
  sort(coins.begin(), coins.end());
  print(coins.begin(), coins.end());
  cout << "Enter amount in cents\n";
  int amount;
  cin >> amount;
  vector<int> genfunc(amount+1);
  vector<int>::iterator ci = coins.begin();
  vector<int>::iterator gfi;
  for (gfi =  genfunc.begin(); gfi < genfunc.end(); gfi += *ci) {
    *gfi = 1;
  }
  print(genfunc.begin(), genfunc.end());
  for (++ci;ci != coins.end(); ++ci) {
    for (gfi =  genfunc.begin()+(*ci); gfi < genfunc.end(); ++gfi) {
      *gfi += *(gfi-*ci);
    }
    print(genfunc.begin(), genfunc.end());
  }
}
