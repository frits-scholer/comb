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
const int M = 20;
const int MAXN = 1<<M;

//First version
// void fft ( vector < base > & a, bool invert ) {
//   int n = ( int ) a. size ( ) ;
//   if ( n == 1 )  return ;
 
//   vector < base > a0 ( n / 2 ) ,  a1 ( n / 2 ) ;
//   for ( int i = 0 , j = 0 ; i < n ; i + = 2 , ++ j ) {
//     a0 [ j ] = a [ i ] ;
//     a1 [ j ] = a [ i + 1 ] ;
//   }
//   fft ( a0, invert ) ;
//   fft ( a1, invert ) ;
 
//   double ang = 2 * PI / n * ( invert ? - 1 : 1 ) ;
//   base w ( 1 ) ,  wn ( cos ( ang ) , sin ( ang ) ) ;
//   for ( int i = 0 ; i < n / 2 ; ++ i ) {
//     a [ i ] = a0 [ i ] + w * a1 [ i ] ;
//     a [ i + n / 2 ] = a0 [ i ] - w * a1 [ i ] ;
//     if ( invert )
//       a [ i ] / = 2 ,  a [ i + n / 2 ] / = 2 ;
//     w * = wn ;
//   }
// }

//Second optimized with bit reversal
// int rev ( int num, int lg_n ) {
// 	int res = 0 ;
// 	for ( int i = 0 ; i < lg_n ; ++ i )
// 		if ( num & ( 1 << i ) )
// 			res | = 1 << ( lg_n - 1 - i ) ;
// 	return res ;
// }

// void fft ( vector < base > & a, bool invert ) {
// 	int n = ( int ) a. size ( ) ;
// 	int lg_n = 0 ;
// 	while ( ( 1 << lg_n ) < n )  ++ lg_n ;
 
// 	for ( int i = 0 ; i < n ; ++ i )
// 		if ( i < rev ( i,lg_n ) )
// 			swap ( a [ i ] , a [ rev ( i,lg_n ) ] ) ;
 
// 	for ( int len = 2 ; len <= n ; len <<= 1 ) {
// 		double ang = 2 * PI / len * ( invert ? - 1 : 1 ) ;
// 		base wlen ( cos ( ang ) , sin ( ang ) ) ;
// 		for ( int i = 0 ; i < n ; i + = len ) {
// 			base w ( 1 ) ;
// 			for ( int j = 0 ; j < len / 2 ; ++ j ) {
// 				base u = a [ i + j ] ,  v = a [ i + j + len / 2 ] * w ;
// 				a [ i + j ] = u + v ;
// 				a [ i + j + len / 2 ] = u - v ;
// 				w * = wlen ;
// 			}
// 		}
// 	}
// 	if ( invert )
// 		for ( int i = 0 ; i < n ; ++ i )
// 			a [ i ] / = n ;
// }

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
			a [ i ] /= n ;
}

//Fourth version ultimate optimization
// int rev [ MAXN ] ;
// base wlen_pw [ MAXN ] ;
 
// void fft ( base a [ ] , int n, bool invert ) {
// 	for ( int i = 0 ; i < n ; ++ i )
// 		if ( i < rev [ i ] )
// 			swap ( a [ i ] , a [ rev [ i ] ] ) ;
 
// 	for ( int len = 2 ; len <= n ; len <<= 1 ) {
// 		double ang = 2 * PI / len * ( invert ? - 1 : + 1 ) ;
// 		int len2 = len >> 1 ;
 
// 		base wlen ( cos ( ang ) , sin ( ang ) ) ;
// 		wlen_pw [ 0 ] = base ( 1 , 0 ) ;
// 		for ( int i = 1 ; i < len2 ; ++i )
// 			wlen_pw [ i ] = wlen_pw [ i - 1 ] * wlen ;
 
// 		for ( int i = 0 ; i < n ; i += len ) {
// 			base t,
// 				*pu = a + i,
// 				*pv = a + i + len2, 
// 				*pu_end = a + i + len2,
// 				*pw = wlen_pw ;
// 			for ( ; pu != pu_end ; ++pu, ++pv, ++pw ) {
// 				t = *pv * *pw ;
// 				*pv = *pu - t ;
// 				*pu += t ;
// 			}
// 		}
// 	}
 
// 	if ( invert )
// 		for ( int i = 0 ; i < n ; ++i )
// 			a [ i ] /= n ;
// }
 
// void calc_rev ( int n, int log_n ) {
// 	for ( int i = 0 ; i < n ; ++i ) {
// 		rev [ i ] = 0 ;
// 		for ( int j = 0 ; j < log_n ; ++j )
// 			if ( i & ( 1 << j ) )
// 				rev [ i ] |= 1 << ( log_n - 1 - j ) ;
// 	}
// }

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
	for ( size_t i = 0 ; i < n ; ++ i )
		res [ i ] = int ( fa [ i ] . real ( ) + 0.5 ) ;
}
void print(const vi& v, const string& s) {
  cout << s << endl;
  for (auto e : v) cout << e << ' ';
  cout << endl;
}
int main() {
  vi A {1,2,6,24,120};
  vi B {1,1,1,1,1};
  vi C;
  multiply(A, B, C);
  print(A, "A:");
  print(B, "B:");
  print(C, "C:");
}
