#include <bits/stdc++.h>
#define MOD 1000000007
//7340033
using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(auto &it : (v))
#define all(v) (v).begin(), (v).end()
#define what_is(x) cerr << #x << " is " << x << endl;
#define sz(x) (int)(x).size()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

const ll mod = 1e9+7, root = 3;
const double PI = 3.141592653589793;
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}

ll inv(ll a){
	return modpow(a, mod-2);
}

typedef vector<ll> vl;

typedef valarray<complex<double> > carray;
void fft(carray& x, carray& roots) {
	int N = sz(x);
	if (N <= 1) return;
	carray even = x[slice(0, N/2, 2)];
	carray odd = x[slice(1, N/2, 2)];
	carray rs = roots[slice(0, N/2, 2)];
	fft(even, rs);
	fft(odd, rs);
	rep(k,0,N/2) {
		auto t = roots[k] * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

typedef vector<double> vd;
vd conv(const vd& a, const vd& b) {
	int s = sz(a) + sz(b) - 1, L = 32-__builtin_clz(s), n = 1<<L;
	if (s <= 0) return {};
	carray av(n), bv(n), roots(n);
	rep(i,0,n) roots[i] = polar(1.0, -2 * PI * i / n);
	copy(all(a), begin(av)); fft(av, roots);
	copy(all(b), begin(bv)); fft(bv, roots);
	roots = roots.apply(conj);
	carray cv = av * bv; fft(cv, roots);
	vd c(s); rep(i,0,s) c[i] = cv[i].real() / n;
	return c;
}

vl conv(const vl& a, const vl&b){
	const int tmpMod = 8000;
	vd an[2], bn[2];
	for(auto A : a){
		an[0].push_back(((double)(A%tmpMod)));
		an[1].push_back(((double)(A/tmpMod)));
	}
	for(auto B : b){
		bn[0].push_back(((double)(B%tmpMod)));
		bn[1].push_back(((double)(B/tmpMod)));
	}
	vl ret(sz(a)+sz(b)-1);
	rep(i,0,2)
		rep(j,0,2){
			vd c = conv(an[i], bn[j]);
			ll mul = 1;
			if(i) mul *= tmpMod;
			if(j) mul *= tmpMod;
			rep(k,0,sz(ret)){
				ret[k] += ((ll)round(c[k]))*mul;
				ret[k] %= MOD;
			}
		}
	return ret;
}

/*ll binom(ll a, ll b){
	if(b < 0 || b > a)
		return 0;
	if(b == 0 || b == a)
		return 1;
	return (binom(a-1, b-1)+binom(a-1, b))%MOD;
}*/

int main(){
	ios::sync_with_stdio(0);
	ll n, a, b, c;
	cin >> n >> a >> b >> c;
	vector<ll> Acoeff;
	vector<ll> Bcoeff;
	ll binom = 1;
	rep(i,0,a+1){
		int s = (i%2 == a%2)?1:-1;
		Acoeff.push_back(s*binom);
		binom = (binom*(a-i))%MOD;
		binom = (binom*inv(i+1))%MOD;
	}
	binom = 1;
	rep(i,0,b+1){
		Bcoeff.push_back(binom);
		binom = (binom*(b-i))%MOD;
		binom = (binom*inv(i+1))%MOD;
	}
	vector<ll> cv = conv(Acoeff, Bcoeff);
	ll ans = 0;
	rep(i,0,sz(cv)){
		ll exponent = 2*i-a-b+c;
		ll add = (cv[i] * modpow(exponent, n))%MOD;
		add = (add * modpow((MOD+1)/2, a+b))%MOD;
		ans = (ans + add)%MOD;
	}
	if(ans < 0)
		ans += MOD;
	cout << ans << endl;
}
