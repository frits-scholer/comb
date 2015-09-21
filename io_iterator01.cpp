#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  string from;
  cin >> from;
  ifstream is(from.c_str());
  istream_iterator<string> ii(is);
  istream_iterator<string> eos;
  vector<string> b(ii, eos);
  sort(b.begin(), b.end());
  ostream_iterator<string> oo(cout, " ");
  unique_copy(b.begin(), b.end(), oo);
  cout << endl;
  return !is && !cout;
}
