#include<iostream>
#include<iomanip>
#include<tuple>
#include "printtuple.hpp"
using namespace std;
typedef tuple<int,int,int> tijd;

int main() {
  //tuple(int,int,int) s;
  tijd t(1,42,23);
  cout << t << endl;
  get<2>(t)=0;
  cout << t << endl;
}
