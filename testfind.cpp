#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string buf;

int main() {
  getline(cin, buf);
  cout << buf << '\n';
  string::iterator bufi = adjacent_find(buf.begin(),buf.end());
  if (bufi != buf.end()) cout << "two " << *bufi << " chars at position " << int(bufi-buf.begin()) << '\n';
  else cout << "no two characters in a row" << '\n';

}
