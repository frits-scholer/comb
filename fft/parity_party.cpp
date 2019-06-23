#include <bits/stdc++.h>

using namespace std;

const int mod = 7340033;
const int r = 2187;
const int K = 21;
const int M = 20;
const int N = 1 << M;

#define long long long

long rPower[2][K];
int reversedBits[N];
long A[N], B[N];

long bin(long x, long a) {
    x %= mod;
    long y = 1;
    while (a) {
        if (a & 1)
            y = (y * x) % mod;
        x = (x * x) % mod;
        a >>= 1;
    }
    return y;
}

long inv(long x) {
    return bin(x, mod - 2);
}

void pre() {
    rPower[0][K - 1] = r;
    rPower[1][K - 1] = inv(r);
    for (int j = 0; j < 2; ++j)
    for (int i = K - 2; i >= 0; --i)
        rPower[j][i] = bin(rPower[j][i + 1], 2);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if ((i >> j) & 1)
                reversedBits[i] |= (1 << (M - j));
}

int reverseBits(int x, int ns) {
    return reversedBits[x] >> (M - ns + 1);
}

void fft(long *a, int n, int ns, long *power) {
    for (int i = 0; i < n; ++i)
        if (reverseBits(i, ns) > i)
            swap(a[i], a[reverseBits(i, ns)]);

    for (int j = 0; j < ns; ++j)
        for (int i = 0; i < n; i += (1 << (j + 1))) {
            long p = 1, e = power[j + 1];
            for (int k = 0; k < (1 << j); ++k) {
                long x = a[i + k], y = a[i + k + (1 << j)];
                a[i + k] = (x + p * y) % mod;
                a[i + k + (1 << j)] = (x - p * y) % mod;
                p = (p * e) % mod;
            }
        }
}

void mul(long *a, long *b, long *c, int ns) {
    fft(a, 1 << ns, ns, rPower[0]);
    fft(b, 1 << ns, ns, rPower[0]);
    for (int i = 0; i < (1 << ns); ++i)
        c[i] = (a[i] * b[i]) % mod;
    fft(c, 1 << ns, ns, rPower[1]);
    long in = inv(1 << ns);
    for (int i = 0; i < (1 << ns); ++i) {
        c[i] = (c[i] * in) % mod;
        if (c[i] < 0)
            c[i] += mod;
    }
}

int n, a, b, c;
long f[N], fr[N];

long binom(long n, long k) {
    if (k < 0 || n < k)
        return 0;
    return (f[n] * fr[k] % mod) * fr[n - k] % mod;
}

void kill() {
    cin >> n >> a >> b >> c;

    f[0] = fr[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = (i * f[i - 1]) % mod;
        fr[i] = inv(f[i]);
    }

    for (int i = 0; i <= a; ++i)
        A[i] = (i % 2 == 0 ? 1 : -1) * binom(a, i);

    for (int i = 0; i <= b; ++i)
        B[i] = binom(b, i);

    int ns = 0;
    while ((1 << ns) <= a + b)
        ++ns;

    for (int i = 0; i <= a; ++i)
        cerr << A[i] << " ";
    cerr << endl;

    for (int i = 0; i <= b; ++i)
        cerr << B[i] << " ";
    cerr << endl;

    mul(A, B, A, ns);


    for (int i = 0; i <= a + b; ++i)
        cerr << A[i] << " ";
    cerr << endl;

    long ans = 0;
    for (int i = 0; i <= a + b; ++i) {
        long x = a + b + c - 2 * i;
        ans = (ans + A[i] * bin(x, n)) % mod;
    }

    ans *= bin(inv(2), a + b);
    ans %= mod;

    if (ans < 0)
        ans += mod;
    cout << ans << endl;
}

int main() {
    pre();
    kill();
    return 0;
}
