/*
read in array of ints 
and print them out sorted
the iterator way
*/
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;
#define all(t) begin(t), end(t)

int main() {
	int N;
	cin >> N;
	vector<int> v(N);
	copy_n(istream_iterator<int> (cin), N, begin(v));
	sort(all(v));
	ostream_iterator<int> os(cout, " ");
	cout << endl;
	copy (all(v), os);
	cout << endl;
}