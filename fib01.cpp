#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

int main() {
  vector<unsigned long> v(2,1);
  cout << "How many Fibonacci numbers do you want? ";
  int N;
  cin >> N;
  if (N < 2) N=2;
  v.resize(N);
  adjacent_difference(v.begin(),v.end()-1,v.begin()+1,plus<unsigned long>());
  for (auto n : v) cout << n << ' ';
  cout << '\n';
}
