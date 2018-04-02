#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
#define all(c) begin(c), end(c)
#define d first
#define n second
typedef pair<int,int> frac;

const int N = 10;

void show_event(string s, clock_t& tm) {
  tm = clock()-tm;
  cerr <<  "\t" << s << " " << (double) tm/CLOCKS_PER_SEC << " s "<< endl;
}

void print(const vector<pair<int,int>>& v) {
  for (auto p : v)  cout << p.first << '\t' << p.second << endl;
}
//this program creates all relatively prime pairs in a range
int main() {
  clock_t tm=clock();
  vector<frac> v {{0,1},{1,N}};
  frac f1{v[0]}, f2{v[1]};
  while (f2.n > 1) {
    int k = (N + f1.n) / f2.n;
    frac t = f1;
    f1 = f2, f2 = (frac) {f2.d * k - t.d, f2.n * k - t.n};
    v.push_back(f2);
  }
  //sort(all(v));
  print(v);
  cout << "length: " << v.size() << endl;
  show_event("total time", tm);
}
