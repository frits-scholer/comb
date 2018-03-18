#include<iostream>
#include<iomanip>
#include<tuple>
using namespace std;
typedef tuple<int,int,int> tijd;
ostream& operator << (ostream& os, const tijd& t) {
  os << "tijd: ";
  int hr, min, sec;
  tie(hr, min, sec) = t;
  os << setw(2) << setfill('0') << hr << ':' << setw(2) << setfill('0')
     << min << ':' << setw(2) << setfill('0') << sec ;
  return os;
}

int main() {
  //tuple(int,int,int) s;
  tijd t(1,42,23);
  cout << t << endl;
  get<2>(t)=0;
  cout << t << endl;
}
