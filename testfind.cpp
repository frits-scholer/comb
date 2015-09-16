#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string buf;

bool two_in_a_row (char c) {
  return (c == 'd');
}
int main() {
  getline(cin, buf);
  cout << buf << '\n';
  string::iterator bufi = find_if(buf.begin(),buf.end(),two_in_a_row);
  if (bufi != buf.end()) cout << *bufi << *bufi << " at " << int(bufi-buf.begin()) << '\n';
  else cout << "no two characters in a row" << '\n';

}
