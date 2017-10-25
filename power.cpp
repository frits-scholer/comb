#include <iostream>
#include <algorithm>
using namespace std;

bool bit(int n, int f) {
  return n & (1<<f);
}

int main() {
  long y;
  int g, N;
  cout << "Input g and n to calculate g^n: "; cin >> g >> N;
  unsigned int lam(0);
  y = N;
  for (int k=5;k>=0;k--) {
    if (y>>(1<<k) != 0) {lam += (1<<k); y = y>>(1<<k);}
  }
  int z, f;
  if (N==0) {cout << 1 << endl;return 0;}
  z = g; y = z; f = lam;
  while (f != 0) {
    f--;
    y = y*y;
    if (bit(N, f)) y = y * z;
  }
  cout << "g^n: " <<  y << endl;
  return 0;
}
