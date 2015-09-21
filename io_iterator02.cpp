#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  do {
  istreambuf_iterator<char> ii(cin);
  istreambuf_iterator<char> eos;
  string line(ii,eos);
  cout << line << endl;
  } while (cin.peek() != EOF);
  return !cin && !cout;
}
