/*
Program to solve instant insanity cube puzzle by backtracking algorithm
Data structure
cube is a string of 6 colors APTBLR=012345
*/
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

enum faces {A, P, T, B, L, R};

string turn_bottom(const string& cubestr) {
  string retstr(cubestr);
  retstr[L]=cubestr[A];
  retstr[P]=cubestr[L];
  retstr[R]=cubestr[P];
  retstr[A]=cubestr[R];
  return retstr;
}

string roll_left(const string& cubestr) {
  string retstr(cubestr);
  retstr[L]=cubestr[T];
  retstr[B]=cubestr[L];
  retstr[R]=cubestr[B];
  retstr[T]=cubestr[R];
  return retstr;
}

string roll_right(const string& cubestr) {
  string retstr(cubestr);
  retstr[T]=cubestr[L];
  retstr[L]=cubestr[B];
  retstr[B]=cubestr[R];
  retstr[R]=cubestr[T];
  return retstr;
}

string roll_forward(const string& cubestr) {
  string retstr(cubestr);
  retstr[B]=cubestr[A];
  retstr[P]=cubestr[B];
  retstr[T]=cubestr[P];
  retstr[A]=cubestr[T];
  return retstr;
}

bool Prop(const string& s, const vector<string>& v, int k) {
  if (k==0) return true;
  for (int j=1;j <= k; j++)
    for (int i=0; i<4; ++i)
      if (s[i]==v[j][i]) return false;
  return true;
} 

int main() {
  vector<string> cube {"BRWRGW", "RGRRWB", "WBGGBR", "GWWBRG"};
  cout << "The 4 cubes:\t";
  for (auto s: cube) cout << s << '\t';
  cout << endl;
  vector<unordered_set<string> > cubes(4);
  //create states for cube 1
  string cube_init = cube[0];
  string next_cube(cube_init);
  cubes[0].insert(string(next_cube.begin(), next_cube.begin()+4));
  next_cube = turn_bottom(cube_init);
  cubes[0].insert(string(next_cube.begin(), next_cube.begin()+4));
  next_cube = roll_right(cube_init);
  cubes[0].insert(string(next_cube.begin(), next_cube.begin()+4));
  //create states
  for (int l = 1;l < 4; ++l) {
    next_cube = cube[l];
    for (int j=0; j<4; ++j) {
      for (int i=0; i<4; ++i) {
	cubes[l].insert(string(next_cube.begin(), next_cube.begin()+4));
	next_cube = turn_bottom(next_cube);
      }
      if (j != 3) next_cube = roll_forward(next_cube);
    }
    for (int j=0; j<2; ++j) {
      next_cube = (j==0?roll_right(cube[l]):roll_left(cube[l]));
      for (int i=0; i<4; ++i) {
	cubes[l].insert(string(next_cube.begin(), next_cube.begin()+4));
	if (i != 3) next_cube = turn_bottom(next_cube);
      }
    }
  }
  vector<unordered_set<string> > S(4);
  vector<string> x(5);
  //Here starts the algorithm
  //B1 Initialize
  int k = 0;
  //B2 Compute the successors
  //Set Sk to the elements of cubes[k] (=x_k+1) with P(x_1,.. ,x_k+1) is true
B2:
  copy_if(cubes[k].begin(), cubes[k].end(), inserter(S[k], S[k].begin())
	    , [&](string str) {return Prop(str, x, k);});
  //B3 Have all successors been tried?
B3:
  do {
    if (S[k].empty()) continue;
    //B4 Advance
    x[k+1] = (*S[k].begin());
    for (auto kk=1;kk <= k+1; ++kk) cout << x[kk] << " ";
    cout << endl;
    S[k].erase(S[k].begin());
    ++k;
    //B5 Solution found?
    if (k < 4) goto B2;
    for (auto kk=1;kk < 5; ++kk) cout << x[kk] << " ";
    cout << " is a solution" << endl;
    //B6 Backtrack
  } while (--k >= 0);
}
