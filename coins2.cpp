#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template <class I>
void print(I first, I last) {
  ostream_iterator<int> oi(cout, " ");
  copy(first, last, oi);
  cout << endl;
}

struct wave {
  int length;
  int current;
  wave(int l):length(l), current(0) {}
  int operator()() { return (current++ % length == 0);}
};

int main() {
  cout << "Enter values of different coins:\n";
  string strCoins;
  getline(cin, strCoins);
  stringstream iss(strCoins);
  istream_iterator<int> ii(iss);
  istream_iterator<int> eos;
  vector<int> coins(ii, eos);
  sort(coins.begin(), coins.end());
  cout << "Enter amount in cents:\n";
  int amount;
  cin >> amount;
  vector<int> genfunc(amount+1);
  vector<int>::iterator ci = coins.begin();
  vector<int>::iterator gfi;
  generate(genfunc.begin(), genfunc.end(), wave(*ci));
  //  print(genfunc.begin(), genfunc.end());
  for (++ci;ci != coins.end(); ++ci) {
    transform(genfunc.begin()+(*ci), genfunc.end(), genfunc.begin(),
	      genfunc.begin()+(*ci), plus<int>());
    //    print(genfunc.begin(), genfunc.end());
  }
  cout << "There are " << genfunc[amount] << " ways to pay this amount." << endl;
}
