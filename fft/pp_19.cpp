#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll mod = 7340033;

long long expo(long long a, ll n) {
    long long b = a;
    long long ret = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            ret *= b;
            ret = ret % mod;
        }
        b = b * b % mod;
        n = n / 2;
    }
    return ret;
}

long long inv(long long a, long long m) {
	long long x = a % m;
	long long y = m;
	// x = xa * a (mod m)
	// y = ya * a (mod m)
	long long xa = 1;
	long long ya = 0;
	while (x > 0) {
		long long quotient = y / x;
		ya -= quotient *  xa;
		ya %= m;
        ya = (ya + m) % m;
		y -= quotient * x;
		x ^= y ^= x ^= y;
		xa ^= ya ^= xa ^= ya;
	}
	if (y != 1) {
		return -1;
	} else {
		return ya;
	}
}

vector<ll> fft(const vector<ll>& freq_domain, const vector<ll>& roots_of_unity) {
    int N = 1 << 20;
    int k = 20;
    vector<ll> * signal = new vector<ll>(N, 0);
    vector<ll> * signalTmp = new vector<ll>(N, 0);
    vector<ll> ret(N, 0);

    // Divide the polynomial into groups of N. Pad with 0s at the high degree
    // to allow whole groups of N. Add the results together at the end.
    for (int j = 0; j < N; j++)
    {
        int reverse_j = 0; // reverse_j stores j but with the bits reversed
        for (int v = 0; v < k; v++) {
            reverse_j |= ((j >> v) & 1) << (k - 1 - v);
        }
        (*signal)[reverse_j] = freq_domain[j];
    }
    // Use butterfly circuit method to compute each layer.
    for (int layer = 0; layer < k; layer++) {
        int rou = 1 << (k - 1 - layer);
        for (int j = 0; j < N; j++) {
            int j_other = j ^ (1 << layer);
            if (j_other > j) {
                int p = ~(~0 << layer) & j;
                (*signalTmp)[j] = ((*signal)[j] + roots_of_unity[rou * p] * (*signal)[j_other]) % mod;
                (*signalTmp)[j] = ((*signalTmp)[j] + mod) % mod;
            } else {
                int p = ~(~0 << layer) & j_other;
                (*signalTmp)[j] = ((*signal)[j_other] - roots_of_unity[rou * p] * (*signal)[j]) % mod;
                (*signalTmp)[j] = ((*signalTmp)[j] + mod) % mod;
            }
        }
        swap(signalTmp, signal);
    }

    for (int j = 0; j < N; j++)
    {
        ret[j] = (*signal)[j];
    }

    delete signalTmp;
    delete signal;
    return ret;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ll n, a, b, c;
    cin >> n >> a >> b >> c;

    ll len = (mod - 1) / 7;
    vector<ll> my_gen_func(len);
    vector<ll> my_gen_func_fd(len);

    vector<ll> roots_of_unity(len);
    ll omega = 2187;
    ll base = 1;
    for (int i = 0; i < len; i++) {
        my_gen_func_fd[i] = expo(base + 1, b) * expo(1 - base, a) % mod;
        my_gen_func_fd[i] = (my_gen_func_fd[i] + mod) % mod; // I'm OCD and need this to be positive XD
        // cout << my_gen_func_fd[i] << endl;
        base = base * omega % mod;
        roots_of_unity[i] = base;
    }
    reverse(roots_of_unity.begin(), roots_of_unity.end());

    // Now to perform the inverse FFT on this my_gen_func_fd
    my_gen_func = fft(my_gen_func_fd, roots_of_unity);
    for (int i = 0; i < len; i++) {
        my_gen_func[i] = my_gen_func[i] * inv(len, mod) % mod;
    }

    // We have the polynomial!!!!!!!
    ll ans = 0;
    for (int i = 0; i <= a+b; i++) {
        ans += expo(a + b + c - 2 * i, n) * my_gen_func[i] % mod;
        ans %= mod;
        // cout << ans << endl;
    }
    ans = inv(expo(2, a+b), mod) * ans % mod;
    ans = (ans + mod) % mod;
    cout << ans << endl;
    return 0;
}
