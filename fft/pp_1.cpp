#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define vll vector<ll>
#define vi vector<int>
#define pb push_back
#define eb emplace_back
const int N = 1e5 + 10, mod = 7340033;
int fact[N], invfact[N];
inline int add(int x, int y){ x += y; if(x >= mod) x -= mod; return x;}
inline int sub(int x, int y){ x -= y; if(x < 0) x += mod; return x;}
inline int mul(int x, int y){ return (((ll) x) * y) % mod;}
inline int powr(int a, ll b){
	int x = 1 % mod;
	while(b){
		if(b & 1) x = mul(x, a);
		a = mul(a, a);
		b >>= 1;
	}
	return x;
}
inline int inv(int a){ return powr(a, mod - 2);}
void prefact(){
	fact[0] = invfact[0] = 1;
	for(int i = 1;i < N; i++) fact[i] = mul(i, fact[i - 1]);
	invfact[N - 1] = inv(fact[N - 1]);
	for(int i = N - 2; i >= 1; i--) invfact[i] = mul(invfact[i + 1], i + 1);
	assert(invfact[1] == 1);
}
inline int C(int n, int k){
	if(n < k || k < 0) return 0;
	return mul(fact[n], mul(invfact[k], invfact[n - k]));
}

struct base{
    ld x,y;
    base(){x=y=0;}
    base(ld _x, ld _y){x = _x,y = _y;}
    base(ld _x){x = _x, y = 0;}
    void operator = (ld _x){x = _x,y = 0;}
    ld real(){return x;}
    ld imag(){return y;}
    base operator + (const base& b){return base(x+b.x,y+b.y);}
    void operator += (const base& b){x+=b.x,y+=b.y;}
    base operator * (const base& b){return base(x*b.x - y*b.y,x*b.y+y*b.x);}
    void operator *= (const base& b){ld p = x*b.x - y*b.y, q = x*b.y+y*b.x; x = p, y = q;}
    void operator /= (ld k){x/=k,y/=k;}
    base operator - (const base& b){return base(x - b.x,y - b.y);}
    void operator -= (const base& b){x -= b.x, y -= b.y;}
};

double PI = 2.0*acos(0.0);
const int MAXN = 19;
const int maxn = (1<<MAXN);
base W[maxn],invW[maxn];
void precompute_powers(){
    for(int i = 0;i<maxn/2;i++){
        double ang = (2*PI*i)/maxn; 
        ld _cos = cos(ang), _sin = sin(ang);
        W[i] = base(_cos,_sin);
        invW[i] = base(_cos,-_sin);
    }
}
void fft (vector<base> & a, bool invert) {
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
        for (int i=0; i<n; i+=len) {
            int ind = 0,add = maxn/len;
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = (a[i+j+len/2] * (invert?invW[ind]:W[ind]));
                a[i+j] = (u + v);
                a[i+j+len/2] = (u - v);
                ind += add;
            }
        }
    }
    if (invert) for (int i=0; i<n; ++i) a[i] /= n;
}
void multiply (vll & a, vll b) {
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    int fsz = a.size()+b.size()-1;
    int n = 1;
    while (n < (int)max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);
 
    fft (fa, false),  fft (fb, false);
    for (int i=0; i<n; ++i) fa[i] *= fb[i];
    fft (fa, true);
 
    a.resize (fsz);
    for(int i = 0;i<fsz;i++)
        a[i] = ( (ll) (fa[i].real() + 0.5));
}
inline ll mul(ll a, ll b, ll mod){
    return (a*b)%mod;
}
void mul_big_mod(vll &a, vll b, ll mod){
    int n1 = a.size(),n2 = b.size();
    vll a1(n1),a2(n1),b1(n2),b2(n2),a3(n1),b3(n2);
    int base = (int)sqrt(mod)+10;
    for(int i = 0;i<n1;i++)
        a1[i] = a[i]/base,a2[i] = a[i]%base,a3[i] = (a1[i]+a2[i]);
    for(int i = 0;i<n2;i++)
         b1[i] = b[i]/base, b2[i] = b[i]%base, b3[i] = (b1[i]+b2[i]);
    multiply(a1,b1);
    multiply(a2,b2);
    multiply(a3,b3);
    int _sz = n1+n2-1;
    a.resize(_sz);
    for(int i = 0;i<_sz;i++){
        // a[i] = base * base * a1[i] + base * (a3[i] - a1[i] - a2[i]) + a2[i]
        a[i] = (mul(base*base,a1[i]%mod,mod)+mul(base,(a3[i]-a1[i] - a2[i])%mod,mod)+a2[i])%mod;
        if(a[i]<0) a[i]+=mod;
    }
}

vll v1(N);
vll v2(N);
int main(){
	precompute_powers();
	prefact();
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	for(int i = 0; i <= a; i++){
		v1[2 * i] = C(a, i);
		if((a - i) % 2 == 1) v1[2 * i] = sub(0, v1[2 * i]);
	}
	for(int i = 0; i <= b; i++)v2[2 * i] = C(b, i);
	mul_big_mod(v1, v2, mod);
	int ans = 0;
	for(int i = 0; i < (int)v1.size(); i++){
		ans = add(ans, mul(v1[i], powr((mod + i + c - a - b) % mod, n)));
	}
	ans = mul(ans, inv(powr(2, a + b)));
	cout << ans << endl;
}
