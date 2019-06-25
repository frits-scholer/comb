#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a);i<(int)(b);++i) 
#define REP(i,a)    FOR(i,0,a) 
#define sp << " " <<
#define all(x)      x.begin(),x.end() 
#define PB          push_back 
#define sz(x)       x.size() 
#define MP          make_pair 
#define X           first 
#define Y           second
typedef long long ll;
typedef vector<int> vi;

const int mod = 1e9+7;

void show_event(string s, clock_t& tm) {
  tm = clock()-tm;
  cerr <<  "\t" << s << " " << (double) tm/CLOCKS_PER_SEC << " s "<< endl;
}

int main() {
  int n1, n2;
  //input 2 polynomials
  cin >> n1 >> n2;
  vi p1(n1), p2(n2);
  REP(i, n1) cin >> p1[i];
  REP(i, n2) cin >> p2[i];
  clock_t tm=clock();
  int N = 1;
  while(N < max(n1, n2)) N <<= 1;
  
  show_event("total time", tm);
}
