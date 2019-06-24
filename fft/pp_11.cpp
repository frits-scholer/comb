#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cstdlib>
#include <memory>
#include <queue>
#include <cassert>
#include <cmath>
#include <ctime>
#include <complex>
#include <bitset>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

using namespace std;

#define ws ws_____________________
#define y1 y1_____________________
#define y0 y0_____________________
#define left left_________________
#define right right_______________
#define next next_________________
#define prev prev_________________
#define hash hash_________________

#define pb push_back
#define fst first
#define snd second
#define mp make_pair 
#define sz(C) ((int) (C).size())
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; --i)
#define all(C) begin(C), end(C)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef long double ld;
typedef complex<double> cd;

#define FILE_NAME "a"


int n, a, b, c;

bool read() {
	if  (scanf("%d%d%d%d", &n, &a, &b, &c) < 4) {
		return 0;
	}
	return 1;
}

const int MOD = 7340033;

void add(int& x, int y) {
	((x += y) >= MOD) && (x -= MOD);
}

void sub(int& x, int y) {
	add(x, -y + MOD);
}

int mul(int x, int y) {
	return x * 1ll * y % MOD;
}

int mpow(int a, int p) {
	int res = 1;
	for (; p > 0; p >>= 1, a = mul(a, a)) {
		if  (p & 1) {
			res = mul(res, a);
		}
	}
	return res;
}

int inv(int x) {
	int y = mpow(x, MOD - 2);
	assert(mul(x, y) == 1);
	return y;
}

bool bit(int mask, int i) {
	return (mask >> i) & 1;
}

namespace FFT {
	const int ROOT = 4707492;
	const int DEG_ROOT = 20;

	bool check_root(int r, int n) {
		int x = 1;
		forn(i, n - 1) {
			x = mul(x, r);
			if  (x == 1) {
				printf("x==1, i=%d\n", i);
				return 0;
			}
		}
		x = mul(x, r);
		if  (x != 1) {
			printf("x != 1\n");
			return 0;
		}
		return 1;
	}

	void find_root() {
		while (1) {
			bool bad = 0;
			int x = rand() % MOD;
			const int r = x;
			forn(it, 20) {
				if  (x == 1) {
					bad = 1;
					break;
				}
				x = mul(x, x);
			}
			if  (x != 1 || bad) {
				continue;
			}
			assert(check_root(r, 1 << 20));
			printf("FOUND r=%d\n", r);
			break;
		}	
	}

	void fft(vi& a) {
		const int n = sz(a);
		
		int B = 0;
		while ((1 << B) < n) ++B;
		assert((1 << B) == n);

		vi inv(n, 0);
		int hb = -1;
		for (int i = 1; i < n; ++i) {
			if  (bit(i, hb + 1)) {
				++hb;
			}
			inv[i] = inv[i ^ (1 << hb)] ^ (1 << (B - hb - 1));
		}

		forn(i, n) {
			if  (i < inv[i]) {
				swap(a[i], a[inv[i]]);
			}
		}

		for (int len = 1; len * 2 <= n; len *= 2) {
			vi w(len * 2);
			w[0] = 1;
			int pw = 0;
			while (len * 2 * (1 << pw) < (1 << DEG_ROOT)) ++pw;
			w[1] = mpow(ROOT, (1 << pw));
			// assert(check_root(w[1], len * 2));
			for (int i = 2; i < sz(w); ++i) {
				w[i] = mul(w[i >> 1], w[(i + 1) >> 1]);
			}
			for (int i = 0; i < n; i += len * 2) {
				forn(j, len) {
					const int x = a[i + j];
					const int y = a[i + len + j];
					const int r = w[j];
					
					a[i + j] = x;
					add(a[i + j], mul(y, r));
					
					a[i + len + j] = x;
					sub(a[i + len + j], mul(y, r));
				}
			}
		}
	}

	void fft_inv(vi& a) {
		fft(a);
		reverse(a.begin() + 1, a.end());
		const int coef = inv(sz(a));
		forn(i, sz(a)) {
			a[i] = mul(a[i], coef);
		}
	}

	vi mult(vi a, vi b) {
		int sz = 1;
		while (sz < max(sz(a), sz(b))) sz *= 2;
		sz *= 2;

		a.resize(sz);
		b.resize(sz);

		fft(a);
		fft(b);
		forn(i, sz) {
			a[i] = mul(a[i], b[i]);
		} 

		fft_inv(a);
		while (!a.empty() && !a.back()) {
			a.pop_back();
		}
		return a;
	}

	vi brut_mult(vi a, vi b) {
		vi c(sz(a) + sz(b));
		forn(i, sz(a)) forn(j, sz(b)) {
			add(c[i + j], mul(a[i], b[j]));
		}
		return c;
	}
};

vi mpow(vi a, int p) {
	vi res(1, 1);
	for (; p > 0; p >>= 1, a = FFT::mult(a, a)) {
		if  (p & 1) {
			res = FFT::mult(res, a);
		}
	}
	return res;
}

int solve() {
	vi P{-1 + MOD, 0, 1};
	P = mpow(P, a);

	vi Q{1, 0, 1};
	Q = mpow(Q, b);

	int ans = 0;
	vi poly = FFT::mult(P, Q);
	const int shift = c - a - b;
	forn(i, sz(poly)) {
		int pos = i + shift;
		pos = (pos % MOD + MOD) % MOD;
		int cur = mpow(pos, n);
		cur = mul(cur, poly[i]);
		add(ans, cur);
	}
	ans = mul(ans, inv(mpow(2, a + b)));
	return ans;
}

int main() {
#ifdef LOCAL
	freopen(FILE_NAME ".in", "r", stdin);
	// freopen(FILE_NAME ".out", "w", stdout);
#endif

	// FFT::find_root();

	// {
	// 	vi a{1, 2, 3, 4, 5};
	// 	vi b{5, 4, 6, 3};
	
	// 	vi br = FFT::brut_mult(a, b);
	// 	vi my = FFT::mult(a, b);

	// 	for (int x : br) {
	// 		printf("%d ", x);
	// 	}
	// 	puts("");
	// 	for (int x : my) {
	// 		printf("%d ", x);
	// 	}
	// 	puts("");
	// }

	while (read()) {
		printf("%d\n", solve());
	}

#ifdef LOCAL
	cerr.precision(5);
	cerr << "Time: " << fixed << (double) clock() / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}

