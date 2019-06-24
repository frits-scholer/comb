#define _USE_MATH_DEFINES
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>
#include <cmath>
#include <numeric>
#include <bitset>

using namespace std;

#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}

typedef long long int64;
typedef int atom;
typedef pair<int, int> ii;
const int INF = 1 << 30;
const int MOD = 7340033;
const int G = 3;

const int N = 1 << 17;
int F[N], H[N];

int64 power_mod(int64 a, int64 n) {
  a %= MOD;
  if (a < 0) a += MOD;
  int64 ret = 1;
  for (; n; n >>= 1) {
    if (n & 1) ret = ret * a % MOD;
    a = a * a % MOD;
  }
  return ret;
}

int64 inv_mod(int64 a) {
  return power_mod(a, MOD - 2);
}

void bit_reverse(vector<atom>& a) {
  int n = a.size();
  for (int i = 1, j = n / 2; i < n - 1; ++i) {
    if (i < j) {
      swap(a[i], a[j]);
    }
    int k = n / 2;
    while (j >= k) {
      j -= k;
      k /= 2;
    }
    if (j < k) j += k;
  }
}

void fft(vector<atom>& a, int flag) {
  int n = a.size();
  bit_reverse(a);
  vector<atom> wn(n);
  wn[0] = 1;
  wn[1] = power_mod(G, flag == 1 ? (MOD - 1) / n : MOD - 1 - (MOD - 1) / n);
  for (int i = 2; i < n; ++i) {
    wn[i] = (int64)wn[i - 1] * wn[1] % MOD;
  }
  for (int k = 2; k <= n; k <<= 1) {
    for (int i = 0; i < n; i += k) {
      int wi = 0, step = n / k;
      for (int j = i; j < i + k / 2; ++j) {
        atom u = a[j];
        atom v = (int64)wn[wi] * a[j + k / 2] % MOD;
        a[j] = (u + v) % MOD;
        a[j + k / 2] = (u + MOD - v) % MOD;
        wi += step;
      }
    }
  }
  if (flag < 0) {
    int64 inv_n = inv_mod(n);
    for (int i = 0; i < n; ++i) {
      a[i] = a[i] * inv_n % MOD;
    }
  }
}

int comb(int n, int m) {
  return (int64)F[n] * H[m] % MOD * H[n - m] % MOD;
}

int main() {
  F[0] = H[0] = 1;
  for (int i = 1; i < N; ++i) {
    F[i] = (int64)F[i - 1] * i % MOD;
    H[i] = inv_mod(F[i]);
  }
  int n, A, B, C;
  scanf("%d", &n);
  scanf("%d%d%d", &A, &B, &C);
  vector<int> a(N), b(N);
  for (int i = 0; i <= A; ++i) {
    a[A - i] = comb(A, i);
    if (i % 2 == 1) {
      a[A - i] = MOD - a[A - i];
    }
  }
  for (int i = 0; i <= B; ++i) {
    b[B - i] = comb(B, i);
  }
  // for (int i = 0; i <= A; ++i) {
  //   trace(i, a[i]);
  // }
  // for (int i = 0; i <= B; ++i) {
  //   trace(i, b[i]);
  // }

  fft(a, 1);
  fft(b, 1);
  for (int i = 0; i < N; ++i) {
    a[i] = (int64)a[i] * b[i] % MOD;
  }
  fft(a, -1);
  // for (int i = 0; i <= A + B; ++i) {
  //   trace(i, a[i]);
  // }
  C -= A + B;
  int ret = 0;
  for (int i = 0; i <= A + B; ++i) {
    ret += a[i] * power_mod(2 * i + C, n) % MOD;
    ret %= MOD;
  }
  ret = ret * inv_mod(power_mod(2, A + B)) % MOD;
  printf("%d\n", ret);
  return 0;
}
