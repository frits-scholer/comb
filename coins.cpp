#include <iostream>
using namespace std;
int main() {
  int N, M;//amount and nr of coin types
  long long dp[50][251];
  long long C[50];
  cin >> N >> M;
  //input values
  for (int i = 0; i < M; i++) cin >> C[i];
  //ways to change amounts with first coin type
  for (int j = 1; j <= N; j++)
    if (j % C[0] == 0) dp[0][j] = 1;
  //ways to get 0 with i coin types    
  for (int i = 0; i < M; i++) dp[i][0] = 1;  
  //ways to change amounts with i coin types    
  for (int i = 1; i < M; i++) {
    for (int j = 1; j < C[i]; j++) dp[i][j] = dp[i-1][j];
    for (int j = C[i]; j <= N; j++)
      dp[i][j] = dp[i-1][j] + dp[i][j-C[i]];
  }
  //ways to change N with M coin types 
  cout << dp[M-1][N] << endl;
  
  return 0;
}
