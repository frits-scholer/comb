#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  long y;
  cout << "Input a number: "; cin >> y;
  unsigned int lam(0);

  for (int k=5;k>=0;k--) {
    if (y>>(1<<k) != 0) {lam += (1<<k); y = y>>(1<<k);}
  }
  cout << "Lambda = " << lam << endl;
}
