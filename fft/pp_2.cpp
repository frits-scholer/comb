#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int MOD2 = (int) 1e8 + 7;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;
const ld PI = acos((ld) -1);
const ld EPS = 1e-9;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
inline int sign(ld x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(ld x, ld y) {return sign(x - y);}
#define db(x) cerr << #x << " = " << (x) << ", ";
#define endln cerr << "\n";
#define chkpt cerr << "-----\n";

const int maxn = 1 << 20;
const int mod = 7340033;
int n, a, b, c;
int x[maxn];
int y[maxn];
int z[maxn];

void fft(int a[], int p, int r, int n) {
    for (int m = n, h; h = m / 2, m >= 2; r = (long long) r * r % p, m = h) {
        for (int i = 0, w = 1; i < h; i++, w = (long long) w * r % p) {
            for (int j = i; j < n; j += m) {
                int k = j + h, x = (a[j] - a[k] + p) % p;
                a[j] += a[k];
                a[j] %= p;
                a[k] = (long long) w * x % p;
            }
        }
    }
    for (int i = 0, j = 1; j < n - 1; j++) {
        for (int k = n / 2; k > (i ^= k); k /= 2);
        if (j < i) swap(a[i], a[j]);
    }
}
void multiply(int a[], int b[], int c[], int na, int nb, int p, int prt) {
    static int fa[maxn], fb[maxn];
    int len = na + nb - 1;
    int k = 0; while ((1 << k) < na + nb - 1) k++;
    for (int i = 0; i < (1 << k); i++) fa[i] = fb[i] = 0;
    for (int i = 0; i < na; i++) fa[i] = a[i];
    for (int i = 0; i < nb; i++) fb[i] = b[i];
    int w = fpow(prt, (p - 1) / (1 << k), p);
    fft(fa, p, w, 1 << k);
    fft(fb, p, w, 1 << k);
    for (int i = 0; i < (1 << k); i++) c[i] = mult(fa[i], fb[i], p);
    fft(c, p, inv(w, p), 1 << k);
    int rem = inv(1 << k, p);
    for (int i = 0; i < (1 << k); i++) c[i] = mult(c[i], rem, p);
}

void solve() {
    cin >> n >> a >> b >> c;
    swap(a, b);
    int t = 1;
    FOR(i, 0, a + 1) {
        x[i] = t;
        t = mult(t, a - i, mod);
        t = mult(t, inv(i + 1, mod), mod);
    }
    t = 1;
    FOR(i, 0, b + 1) {
        if (!(b + i & 1)) {
            y[i] = t;
        }
        else {
            y[i] = (mod - t) % mod;
        }
        t = mult(t, b - i, mod);
        t = mult(t, inv(i + 1, mod), mod);
    }
    multiply(x, y, z, a + 1, b + 1, mod, 3);
    int ans = 0;
    FOR(i, 0, maxn) if (z[i]) {
        int k = i + i + (c - a - b);
        k = (k % mod + mod) % mod;
        addmod(ans, mult(z[i], fpow(k, n, mod), mod), mod);
    }
    ans = mult(ans, fpow(inv(2, mod), a + b, mod), mod);
    cout << ans << "\n";
}

int main() {
    int JUDGE_ONLINE = 1;
    if (fopen("in.txt", "r")) {
        JUDGE_ONLINE = 0;
        assert(freopen("in.txt", "r", stdin));
        //assert(freopen("out.txt", "w", stdout));
    }
    else {
        ios_base::sync_with_stdio(0), cin.tie(0);
    }
    solve();
    if (!JUDGE_ONLINE) {
        //cout << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    }
    return 0;
}
