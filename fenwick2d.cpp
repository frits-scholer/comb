#include <iostream>
#include <vector>
using namespace std;
struct FenwickTree2D {
    int n, m;
    vector<vector<int> > a;
    FenwickTree2D(int n, int m) : n(n), m(m), a(n, vector<int>(m)) {}
 
    void update(int x, int y, int val) {
        int y1;
        while (x < n) {
            y1 = y;
            while (y1 < m) {
                a[x][y1] += val;
                y1 |= y1 + 1;
            }
            x |= x + 1;
        }
    }
 
    int get(int x, int y) {
        int re = 0;
        int y1;
        while (x >= 0) {
            y1 = y;
            while (y1 >= 0) {
                re += a[x][y1];
                y1 = (y1 & (y1 + 1)) - 1;
            }
            x = (x & (x + 1)) - 1;
        }
        return re;
 
    }
 
    int get(int x1, int y1, int x2, int y2) {
        int re = get(x2, y2);
        re -= get(x1 - 1, y2);
        re -= get(x2, y1 - 1);
        re += get(x1 - 1, y1 - 1);
        return re;
    }
};
int main() {
  FenwickTree2D t(3,4);
  vector<vector<int>> b = {{1,2,3,4},{2,3,4,5},{3,4,5,6}};
  for (int i=0;i<t.n;i++)
    for (int j=0;j<t.m;j++) t.update(i, j, b[i][j]);
  cout << t.get(1,3) << endl;
    
}
