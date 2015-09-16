#include <iostream>
#include <numeric>
int main() {
  int A[]={1,2,3,4,5};
  const int N=sizeof(A)/sizeof(int);
  std::cout << "sum of A " << std::accumulate(A,A+N,0)<<std::endl;
  std::cout << "product of A " << std::accumulate(A,A+N,1,std::multiplies<int>())<<std::endl;
}
