#pragma comment(linker, "/STACK:512000000")
#define _CRT_SECURE_NO_WARNINGS
//#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
typedef long long li;
typedef long double ld;
void solve(bool);
void precalc();
clock_t start;
int main() {
#ifdef AIM
  freopen("/home/alexandero/ClionProjects/ACM/input.txt", "r", stdin);
  //freopen("/home/alexandero/ClionProjects/ACM/output.txt", "w", stdout);
  //freopen("out.txt", "w", stdout);
#else
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
#endif
  start = clock();
  int t = 1;
  cout.sync_with_stdio(0);
  cin.tie(0);
  precalc();
  cout.precision(10);
  cout << fixed;
  //cin >> t;
  int testNum = 1;
  while (t--) {
    //cout << "Case #" << testNum++ << ": ";
    //cerr << testNum << endl;
    solve(true);
    //cerr << testNum - 1 << endl;
  }
  cout.flush();
#ifdef AIM1
  while (true) {
      solve(false);
  }
#endif

#ifdef AIM
  cerr << "\n\n time: " << (clock() - start) / 1.0 / CLOCKS_PER_SEC << "\n\n";
#endif

  return 0;
}

//BE CAREFUL: IS INT REALLY INT?

template<typename T>
T binpow(T q, T w, T mod) {
  if (!w)
    return 1 % mod;
  if (w & 1)
    return q * 1LL * binpow(q, w - 1, mod) % mod;
  return binpow(q * 1LL * q % mod, w / 2, mod);
}

template<typename T>
T gcd(T q, T w) {
  while (w) {
    q %= w;
    swap(q, w);
  }
  return q;
}
template<typename T>
T lcm(T q, T w) {
  return q / gcd(q, w) * w;
}

void precalc() {

}

template<typename T>
void relax_min(T& cur, T val) {
  cur = min(cur, val);
}

template<typename T>
void relax_max(T& cur, T val) {
  cur = max(cur, val);
}

#define int li
//const int mod = 1000000007;

const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1<<20;

void fft (vector<int> & a, bool invert) {
  int n = (int) a.size();

  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1)
      j -= bit;
    j += bit;
    if (i < j)
      swap (a[i], a[j]);
  }

  for (int len=2; len<=n; len<<=1) {
    int wlen = invert ? root_1 : root;
    for (int i=len; i<root_pw; i<<=1)
      wlen = int (wlen * 1ll * wlen % mod);
    for (int i=0; i<n; i+=len) {
      int w = 1;
      for (int j=0; j<len/2; ++j) {
        int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
        a[i+j] = u+v < mod ? u+v : u+v-mod;
        a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
        w = int (w * 1ll * wlen % mod);
      }
    }
  }
  if (invert) {
    //int nrev = reverse (n, mod);
    int nrev = binpow(n, mod - 2, mod);
    for (int i=0; i<n; ++i)
      a[i] = int (a[i] * 1ll * nrev % mod);
  }
}

vector<int> multiply (const vector<int> & a, const vector<int> & b) {
  /*vector<int> res(a.size() + b.size());
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      res[i + j] += a[i] * b[j];
      res[i + j] %= mod;
    }
  }
  return res;*/

  vector<int> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
  size_t n = 1;
  while (n < max (a.size(), b.size()))  n <<= 1;
  n <<= 1;
  fa.resize (n),  fb.resize (n);

  fft (fa, false),  fft (fb, false);
  for (size_t i=0; i<n; ++i) {
    fa[i] *= fb[i];
    fa[i] %= mod;
  }
  fft (fa, true);

  vector<int> res(n);
  for (size_t i=0; i<n; ++i) {
    res[i] = fa[i] % mod;
    if (res[i] < 0) {
      res[i] += mod;
    }
  }
  while (res.size() > 1 && res.back() == 0) {
    res.pop_back();
  }
  return res;
}

vector<int> mult_pow(vector<int> cur, int w) {
  if (!w) {
    return vector<int>(1, 1);
  }
  if (w & 1) {
    return multiply(mult_pow(cur, w - 1), cur);
  }
  auto now = mult_pow(cur, w / 2);
  return multiply(now, now);
}

int n, a, b, c;

vector<int> num;

int rec(int pos) {
  if (pos == n) {
    bool f = true;
    for (int i = 0; i < a; ++i) {
      if (num[i] % 2 == 0) {
        f = false;
        break;
      }
    }
    for (int i = 0; i < b; ++i) {
      if (num[i + a] % 2) {
        f = false;
        break;
      }
    }
    return f;
  }
  int res = 0;
  for (int i = 0; i < a + b + c; ++i) {
    ++num[i];
    res += rec(pos + 1);
    --num[i];
  }
  return res;
}

int stupid_sol() {
  num.assign(a + b + c, 0);
  return rec(0);
}

void solve(bool read) {
  cin >> n >> a >> b >> c;
  vector<int> vec(3, 0);
  vec[0] = mod - 1;
  vec[2] = 1;
  vector<int> poly = mult_pow(vec, a);
  vec[0] = 1;
  poly = multiply(poly, mult_pow(vec, b));
  int coef = binpow(2LL, a + b, mod);
  coef = binpow(coef, mod - 2, mod);
  int res = 0;
  for (int i = 0; i < poly.size(); ++i) {
    int m = i + c - a - b;
    int add = poly[i] * binpow(m, n, mod) % mod * coef % mod;
    if (add < 0) add += mod;
    res += add;
    res %= mod;
  }
  if (res < 0) {
    res += mod;
  }
  cout << res << endl;
  //cout << binpow(2LL, n, mod) << endl;
  //cout << stupid_sol() << endl;
}
