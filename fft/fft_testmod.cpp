/*
correct fft if no overflow
 */
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a);i<(int)(b);++i) 
#define REP(i,a)    FOR(i,0,a) 
#define sp << " " <<
#define all(x)      x.begin(),x.end() 
#define PB          push_back 
#define sz(x)       (int)x.size() 
#define MP          make_pair 
#define X           first 
#define Y           second
typedef long long ll;
typedef vector<int> vi;
typedef complex < double > base ;
const double PI = 4*atan(1);
const int M = 10;
const int MAXN = 1<<M;
const int mod = 1e9+7;
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
I power_mod(I bas, unsigned int exp) {
  I result = 1;
  while (exp > 0) {
    if (exp & 1) result = mult(result,bas);//(result*base)%mod;
    bas = mult(bas,bas);//(base*base)%mod;
    exp >>=1;
  }
  return result;
}

template <typename I>
I inverse(I a) {
  return power_mod(a, mod-2);
}

int factorial[MAXN], invfact[MAXN];

void pre() {
    factorial[0] = invfact[0] = 1;
    FOR (i, 1, MAXN) {
      factorial[i] = mult(factorial[i-1] , i);
      invfact[i] = mult(inverse(i), invfact[i-1]);
    }
}

//Third version further optimization
void fft ( vector < base > & a, bool invert ) {
	int n = ( int ) a. size ( ) ;
 
	for ( int i = 1 , j = 0 ; i < n ; ++i ) {
		int bit = n >> 1 ;
		for ( ; j >= bit ; bit >>= 1 )
			j -= bit ;
		j += bit ;
		if ( i < j )
			swap ( a [ i ] , a [ j ] ) ;
	}
 
	for ( int len = 2 ; len <= n ; len <<= 1 ) {
		double ang = 2 * PI / len * ( invert ? - 1 : 1 ) ;
		base wlen ( cos ( ang ) , sin ( ang ) ) ;
		for ( int i = 0 ; i < n ; i += len ) {
			base w ( 1 ) ;
			for ( int j = 0 ; j < len / 2 ; ++ j ) {
				base u = a [ i + j ] ,  v = a [ i + j + len / 2 ] * w ;
				a [ i + j ] = u + v ;
				a [ i + j + len / 2 ] = u - v ;
				w *= wlen ;
			}
		}
	}
	if ( invert )
		for ( int i = 0 ; i < n ; ++ i )
			a [i] /= n ;
}

void multiply ( const vector < int > & a, const vector < int > & b, vector < int > & res ) {
	vector < base > fa ( a. begin ( ) , a. end ( ) ) ,  fb ( b. begin ( ) , b. end ( ) ) ;
	size_t n = 1 ;
	while ( n < max ( a. size ( ) , b. size ( ) ) )  n <<= 1 ;
	n <<= 1 ;
	fa. resize ( n ) ,  fb. resize ( n ) ;
 
	fft ( fa, false ) ,  fft ( fb, false ) ;
	for ( size_t i = 0 ; i < n ; ++i )
		fa [ i ] *= fb [ i ] ;
	fft ( fa, true ) ;
 
	res. resize ( n ) ;
	for ( size_t i = 0 ; i < n ; ++ i ) {
	  res [ i ] =  fa[i].real()+0.5;
	  res[i] %= mod;
	}
}

void print(const vi& v, const string& s) {
  cout << s << endl;
  for (auto e : v) cout << e << ' ';
  cout << endl;
}

int main() {
  pre();
  vi A;
  //REP(i,6) A.PB(invfact[i]);
  REP(i,3) A.PB(i+1);
  
  vi C;
  multiply(A, A, C);
  print(A, "A:");
  REP(i,sz(A)) cout << mult(A[i], factorial[i]) << ' ';
  cout << endl;
  print(C, "C:");
  REP(i,sz(C)) cout << mult(C[i], factorial[i]) << ' ';
  cout << endl;
}
