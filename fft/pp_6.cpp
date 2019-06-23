//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<char> vc;
typedef pair<int, int> pii;
typedef vector<pii> vii;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()

const int mod = 7340033;

int mult (int a, int b)
{
    return (ll)a * b % mod;
}
void add (int &a, int b)
{
    a += b;
    if (a >= mod)
        a -= mod;
}
void sub (int &a, int b)
{
    a -= b;
    if (a < 0)
        a += mod;
}
int powmod (int a, int pw)
{
    int res = 1;
    while (pw)
    {
        if (pw & 1)
            res = mult(res, a);
        a = mult(a, a);
        pw >>= 1;
    }
    return res;
}

const int N = (int)1e5;
int fact[N], ifact[N], inv[N];

void precalc ()
{
    fact[0] = ifact[0] = 1;
    forn (i, N) if (i)
    {
        inv[i] = powmod(i, mod - 2);
        fact[i] = mult(i, fact[i - 1]);
        ifact[i] = mult(inv[i], ifact[i - 1]);
    }
}

int C (int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return mult(fact[n], mult(ifact[k], ifact[n - k]));
}

vi mult (const vi &l, const vi &r)
{
//    vi ans(sz(l) + sz(r) - 1);
//    forn (i, sz(l)) forn (j, sz(r))
//        add(ans[i + j], mult(l[i], r[j]));
//    return ans;

    vi ans(sz(l) + sz(r) - 1);
    forn (to, sz(ans))
    {
        ll cur = 0;

        int mx = min(to + 1, sz(l));
        int mn = max(0, to - sz(r) + 1);

        for (int i = mn; i < mx; i++)
            cur += (ll)l[i] * r[to - i];
        ans[to] = cur % mod;
    }
    return ans;
}

void solve (int n)
{
    int a, b, c;
    cin >> a >> b >> c;

    vi l(a + 1), r(b + 1);
    forn (i, sz(l))
    {
        l[i] = C(a, i);
        if (i & 1)
            l[i] = mod - l[i];
    }

    forn (i, sz(r))
        r[i] = C(b, i);

    vi res = mult(l, r);
    int ans = 0;
    forn (s, a + b + 1)
    {
        int ct = a + b + c;
        sub(ct, 2 * s);
        int cur = mult(res[s], powmod(ct, n));
        add(ans, cur);
    }

    const int inv2 = (mod + 1) / 2;
    ans = mult(ans, powmod(inv2, a + b));
    cout << ans << endl;
}

int main()
{
#ifdef LOCAL
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "w", stdout);
#endif // ONLINE_JUDGE

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precalc();

    int n;
    while (cin >> n)
        solve(n);
}
