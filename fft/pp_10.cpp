#include <iostream>
#include <tuple>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef pair<i64, i64> pi64;
typedef double ld;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

const int P = 7340033;
const i64 omega0 = 25;
int DEG = 19;

i64 deg(i64 x, i64 d) {
    x %= P;
    d %= P - 1;
    if (d < 0) d += P - 1;
    if (!d) return 1;
    i64 y = 1;
    while (d) {
        if (d % 2) (y *= x) %= P;
        (x *= x) %= P;
        d /= 2;
    }
    return y;
}

i64 omega[20], omega_1[20];

int br(int x, int n) {
    int y = 0;
    forn(i, n) {
        y |= ((x >> i) & 1) << (n - i - 1);
    }
    return y;
}

void bitrev(i64 *a, int n) {
    forn(i, 1 << n) {
        int j = br(i, n);
        if (j < i) swap(a[j], a[i]);
    }
}

void fft(i64 *a, int n, bool inv) {
    if (!n) return;
    fft(a, n - 1, inv);
    fft(a + (1 << (n - 1)), n - 1, inv);
    i64 w0 = inv ? omega_1[n] : omega[n];
    i64 w = 1;
    forn(i, (1 << (n - 1))) {
        i64 x = a[i], y = a[i + (1 << (n - 1))];
        a[i] = (x + w * y) % P;
        a[i + (1 << (n - 1))] = (x - w * y) % P;
        w = (w * w0) % P;
    }
    if (inv) forn(i, 1 << n) a[i] = (a[i] * (P + 1) / 2) % P;
}

i64 a[1 << 19], b[1 << 19];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#endif

    int n, A, B, C;
    cin >> n >> A >> B >> C;
    forn(i, 20) {
        omega[i] = deg(omega0, 1 << (DEG - i));
        omega_1[i] = deg(omega[i], -1);
    }

    int L = 19;
    a[0] = a[2] = deg(2, -1);
    bitrev(a, L);
    fft(a, L, false);
    forn(i, 1 << L) a[i] = deg(a[i], B);
    b[0] = -deg(2, -1);
    b[2] = deg(2, -1);
    bitrev(b, L);
    fft(b, L, false);
//    forn(i, 1 << L) if (b[i]) cerr << i << ' ' << b[i] << '\n';
    forn(i, 1 << L) (a[i] *= deg(b[i], A)) %= P;
    bitrev(a, L);
    fft(a, L, true);
//    forn(i, 1 << L) if (a[i]) cerr << i << ' ' << a[i] << '\n';

    int x = C - A - B;
    i64 ans = 0;
    forn(i, 1 << L) {
        (ans += a[i] * deg(i + x, n)) %= P;
    }
    if (ans < 0) ans += P;
    cout << ans << '\n';


#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
