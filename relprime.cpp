#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
#define all(c) begin(c), end(c)
#define x first
#define y second

const int N = 100000;

void show_event(string s, clock_t& tm) {
  tm = clock()-tm;
  cerr <<  "\t" << s << " " << (double) tm/CLOCKS_PER_SEC << " s "<< endl;
}

void print(const vector<pair<int,int>>& v) {
  for (auto p : v)  cout << p.first << '\t' << p.second << endl;
}
//this program creates relatively prime pairs but not all in a range
int main() {
  vector<pair<int,int>> v {{2,1}, {3,1}};
  clock_t tm=clock();
  for (int i = 0;; i++) {
    v.push_back(make_pair(2*v[i].x-v[i].y, v[i].x));
    v.push_back(make_pair(2*v[i].x+v[i].y, v[i].x));
    if (v.back().x>=N) break;
    v.push_back(make_pair(v[i].x+2*v[i].y, v[i].y));
  }
  cout << v.size() << endl;
  //sort(all(v));
  //print(v);
  show_event("total time", tm);
}
