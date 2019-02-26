#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

#define FOR(i,a,b)  for(int i=(a);i<(b);++i) 
#define REP(i,a)    FOR(i,0,a) 
#define SP << " "
#define ALL(x)      x.begin(),x.end() 
#define PB          push_back 
#define S           size() 
#define MP          make_pair 
#define X           first 
#define Y           second 
#define VC          vector 
#define VI          VC<int> 

void show_event(string s, clock_t& tm) {
  tm = clock()-tm;
  cerr <<  "\t" << s << " " << (double) tm/CLOCKS_PER_SEC << " s "<< endl;
}

void basep(VI& vp, int p, int a) {
  while (a > 0) {
    vp.PB(a%p);
    a /= p;
  }
}

void print(const VI& v) {
  for (const auto e : v) cout SP << e;
  cout << endl;
}

int main() {
  int n, m, p;
  cin >> n >> m >> p;
  VI np, mp;
  basep(np, p, n);
  basep(mp, p, m);
  print(np);
  print(mp);
}
