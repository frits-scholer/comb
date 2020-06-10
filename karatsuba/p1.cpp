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
int degree(const vi& p) {
  return sz(p)-1;
}

vi add(const vi& A, const vi& B) {
  vi ret(max(sz(A), sz(B)));
  REP(i, min(sz(A), sz(B))) ret[i] = A[i] + B[i];
  if (sz(A)>sz(B)) copy(begin(A)+sz(B), end(A), begin(ret)+sz(B));
  if (sz(B)>sz(A)) copy(begin(B)+sz(A), end(B), begin(ret)+sz(A));
  return ret;
}

vi sub(const vi& A, const vi& B) {
  vi ret(max(sz(A), sz(B)));
  REP(i, min(sz(A), sz(B))) ret[i] = A[i] - B[i];
  if (sz(A)>sz(B)) copy(begin(A)+sz(B), end(A), begin(ret)+sz(B));
  if (sz(B)>sz(A)) copy(begin(B)+sz(A), end(B), begin(ret)+sz(A));
  return ret;
}

vi mult(const vi& A, int N) {
  vi ret(sz(A)+N);
  copy(all(A), begin(ret)+N);
  return ret;
}

vi KA(const vi& A, const vi& B) {
  int N = max(degree(A), degree(B)) + 1;
  if (N == 1) return vi(1, A[0]*B[0]);
  vi Au(begin(A)+(N>>1), end(A));
  vi Al(begin(A), begin(A)+(N>>1));
  vi Bu(begin(B)+(N>>1), end(B));
  vi Bl(begin(B), begin(B)+(N>>1));
  vi D0 = KA(Al, Bl);
  vi D1 = KA(Au, Bu);
  vi D0_1 = KA(add(Al, Au), add(Bl, Bu));
  return add(add(mult(D1, N), mult(sub(D0_1,add(D0, D1)), N>>1)), D0);
}

void print(const vi& v) {
  for (auto n:v) cout << n << ' ';
  cout << endl;
}

int main() {
  int d1, d2;
  //input 2 polynomials of degree d1 and d2
  cin >> d1 >> d2;
  vi p1(d1+1), p2(d2+1);
  REP(i, d1+1) cin >> p1[i];
  REP(i, d2+1) cin >> p2[i];
  clock_t tm=clock();
  int N = 1;
  while(N < max(d1, d2)+1) N <<= 1;
  p1.resize(N);p2.resize(N);
  print(p1);
  print(p2);
  vi rslt = KA(p1, p2);
  print(rslt);
  show_event("total time", tm);
}
