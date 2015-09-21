#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  cin >> noskipws;
  do {
  istream_iterator<char> ii(cin);
  istream_iterator<char> eos;
  string line(ii,eos);
  cout << line << endl;
  } while (cin.peek() != EOF);
  return !cin && !cout;
}
