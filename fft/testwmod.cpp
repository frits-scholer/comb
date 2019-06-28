#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a);i<(int)(b);++i) 
#define REP(i,a)    FOR(i,0,a) 
#define SP << " " <<
#define ALL(x)      x.begin(),x.end() 
#define PB          push_back 
#define S           size() 
#define MP          make_pair 
#define X           first 
#define Y           second
typedef long long ll;
typedef vector<int> VI;

const int mod = 7340033;//1e9+7;

const int r = 2187;
const int K = 21;
const int M = 20;
const int N = 1 << M;

int rPower[2][K];
int reversedBits[N];
int A[N], B[N];

void show_event(string s, clock_t& tm) {
  tm = clock()-tm;
  cerr <<  "\t" << s << " " << (double) tm/CLOCKS_PER_SEC << " s "<< endl;
}

template <typename I>
I mult(const I a, const I b) {
  return (ll) a * b % mod;
}
template <typename I>
I add(const I a, const I b) {
  return (a + b) % mod;
}

template <typename I>
I sub(const I a, const I b) {
  I result =  a - b;
  if (result < 0) result = mod - (-result % mod); 
  return result % mod; 
}

template <typename I>
I power_mod(I base, unsigned int exp) {
  I result = 1;
  while (exp > 0) {
    if (exp & 1) result = mult(result,base);//(result*base)%mod;
    base = mult(base,base);//(base*base)%mod;
    exp >>=1;
  }
  return result;
}

template <typename I>
I inverse(I a) {
  return power_mod(a, mod-2);
}

int factorial[N], invfact[N];

void pre() {
    rPower[0][K - 1] = r;
    rPower[1][K - 1] = inverse(r);
    for (int j = 0; j < 2; ++j)
    for (int i = K - 2; i >= 0; --i)
        rPower[j][i] = power_mod(rPower[j][i + 1], 2);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if ((i >> j) & 1)
                reversedBits[i] |= (1 << (M - j));

    factorial[0] = invfact[0] = 1;
    FOR (i, 1, N) {
      factorial[i] = mult(factorial[i-1] , i);
      invfact[i] = mult(inverse(i), invfact[i-1]);
    }
}

int reverseBits(int x, int ns) {
    return reversedBits[x] >> (M - ns + 1);
}

void fft(int *a, int n, int ns, int *power) {
    for (int i = 0; i < n; ++i)
        if (reverseBits(i, ns) > i)
            swap(a[i], a[reverseBits(i, ns)]);

    for (int j = 0; j < ns; ++j)
        for (int i = 0; i < n; i += (1 << (j + 1))) {
            int p = 1, e = power[j + 1];
            for (int k = 0; k < (1 << j); ++k) {
                int x = a[i + k], y = a[i + k + (1 << j)];
                a[i + k] = add(x, mult(p, y));
                a[i + k + (1 << j)] = sub(x, mult(p, y));
                p = mult(p, e);
            }
        }
}

void mul(int *a, int *b, int *c, int ns) {
    fft(a, 1 << ns, ns, rPower[0]);
    fft(b, 1 << ns, ns, rPower[0]);
    for (int i = 0; i < (1 << ns); ++i)
      c[i] = mult(a[i], b[i]);
    fft(c, 1 << ns, ns, rPower[1]);
    int in = inverse(1 << ns);
    for (int i = 0; i < (1 << ns); ++i) {
      c[i] = mult(c[i], in);
    }
}


int binom(int n, int k) {
  return mult(factorial[n], mult(invfact[k], invfact[n-k]));
}

void print_vi(int *v, int l) {
  REP(i, l) cout << mult(v[i], factorial[i]) << " ";
  //  REP(i, l) cout << v[i] << " ";
  cout << endl;
}

int main() {
  pre();
  clock_t tm=clock();
  REP(i, 8) {
    A[i] = invfact[i];
    B[i] = invfact[i];
  }
  //print_vi(A, max_len);
  //print_vi(B, max_len);
  mul(A, B, B, 10); //B = A*A
  print_vi(B, 20);
  // REP(i, (1<<ns)+1) {
  //   A[i] = B[i];
  // }
  // mul(A, B, B, ns); //B = B*B
  // //print_vi(B, max_len+1);
  // REP(i, m+1) {
  //   A[i] = invfact[i];
  // }
  // FOR(i, m+1, N) {
  //   A[i] = 0;
  // }
  // mul(A, B, B, ns); //B = A*B
  // //print_vi(B, max_len+1);
  // REP(i, N) {
  //   A[i] = B[i];
  // }
  // mul(A, B, B, ns); //B = B*B
  // //print_vi(B, max_len+1);
  // const int nine_tenth = mult(9, inverse(10));
  // REP(i, T) {
  //   cout << mult(nine_tenth,mult(B[digits[i]], factorial[digits[i]])) << endl;
  // }
  show_event("total time", tm);
  return 0;
}
