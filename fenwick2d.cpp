struct FenwickTree2D {
    vector<vector<int> > a;
    int n, m;
 
    FenwickTree2D(int n, int m) : n(n), m(m), a(n, vector<int>(m)) {
 
    }
 
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
