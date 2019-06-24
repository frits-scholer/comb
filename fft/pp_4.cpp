#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <complex>
#include <map>
#include <queue>
#include <array>
#include <bitset>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<vi> vvi;
typedef long double ld;
typedef vector<double> vd;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef vector<string> vs;
//typedef long long int
const int mod = 7340033;

ll mpow(ll x, ll n, int mod) {
  ll r = 1;
  while (n) {
    if (n & 1) r = r * x % mod;
    x = x * x % mod;
    n /= 2;
  }
  return r;
}

int dw(int x, int mod) {
  if (x < mod) return x;
  return x - mod;
}

int g;
int root = 1;
int root_1 = mpow(root, mod-2, mod);
int root_pw = 0;
const int max_root_pw = 1 << 17;
int W[2][max_root_pw];
void precalcw() {
  for (g = 2; g < mod - 1; ++g) {
    if (mpow(g, (mod - 1) / 2, mod) != 1) {
      break;
    }
  }
  root = mpow(g, (mod - 1) / root_pw, mod);
  root_1 = mpow(root, mod-2, mod);
  unsigned long long r[2] = {root, root_1};
  for (int t = 0; t < 2; ++t) {
    W[t][0] = 1;
    for (int i = 1; i < root_pw; ++i) {
      W[t][i] = W[t][i-1] * r[t] % mod;
    }
  }
}
void fft (vector<int> & a, int invert) {
  int n = (int) a.size();
  if (n != root_pw) {
    root_pw = n;
    precalcw();
  }
  for (int i = 0; i < n; ++i) if (a[i] < 0) a[i] += mod;

  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1)
      j -= bit;
    j += bit;
    if (i < j)
      swap (a[i], a[j]);
  }

  for (int len=2, t = n/len; len<=n; len<<=1, t/=2) {
    for (int i=0; i<n; i+=len) {
      for (int j=0, pw = 0; j<len/2; ++j, pw += t) {
        int u = a[i+j];
        int v = a[i+j+len/2] * (unsigned long long)W[invert][pw] % mod;
        a[i+j] = dw(u+v, mod);
        a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
      }
    }
  }
  if (invert) {
    unsigned long long nrev = mpow(n, mod-2, mod);
    for (int i=0; i<n; ++i)
      a[i] = a[i] * nrev % mod;
  }
}

vi smul(vi a, vi b) {
  int pw = a.size() + b.size();
  vi c(pw);
  for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b.size(); ++j) {
    c[i+j] = (c[i+j] + a[i] *(ll)b[j]) % mod;
  }
  return c;
}

vi fmul(vi a, vi b) {
  int pw = a.size() + b.size();
  assert(pw < max_root_pw);
  while (a.size() < max_root_pw) a.push_back(0);
  while (b.size() < max_root_pw) b.push_back(0);
  fft(a, 0);
  fft(b, 0);
  for (int i = 0; i < a.size(); ++i) a[i] = a[i] * (ll)b[i] % mod;
  fft(a, 1);
  for (int i = pw; i < a.size(); ++i) assert(a[i] == 0);
  a.resize(pw);
  return a;
}

vi fac(mod, 1);

ll fc(int n) {
  if (n < fac.size()) return fac[n];
  return 0;
//  return fac[n % mod] * fc(n / mod) % mod;
}

void out(vi v) {
  for (int x : v) cerr << x << ' ';
  cerr << endl;
}

int solve(int n, int a, int b, int c) {
  ll mul = mpow(2, mod - 1 - a - b, mod) % mod;
//  assert(mod > n);
/*  if (mod <= n) {
    cout << 0 << endl;
    return 0;
  }*/
  ll res = 0;
  vi x(a+1), y(b+1);
  for (int i = 0; i <= a; ++i) {
    x[i] = fac[a] * mpow(fac[i] * (ll)fac[a-i] % mod, mod-2, mod) % mod;
    if ((a-i) % 2) x[i] = dw(mod - x[i], mod);
  }
  for (int i = 0; i <= b; ++i) {
    y[i] = fac[b] * mpow(fac[i] * (ll)fac[b-i] % mod, mod-2, mod) % mod;
  }
  vi z = fmul(x, y);
  out(x); out(y); out(z);
  for (int i = 0; i < z.size(); ++i) {
    int pw = c - a - b + 2 * i;
    res = (res + z[i] * mpow(pw, n, mod)) % mod;
  }
  return (res % mod * mul % mod + mod) % mod;
}

int stupid(int n, int a, int b, int c) {
  ll res = 0;
  return (res % mod + mod) % mod;
}

int main() {
  std::ios::sync_with_stdio(false);
  for (int i = 2; i < fac.size(); ++i) {
    fac[i] = fac[i-1] * (ll)i % mod;  
  }
  int n,a,b,c;
  cin >> n >> a >> b >> c;
  cout << solve(n, a, b, c) << endl;
  return 0;
}
