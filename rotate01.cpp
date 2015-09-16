#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
char alpha[] = "abcdefghijklmnopqrstuvwxyz";
rotate(alpha, alpha + 13, alpha + 16);
 cout << string{alpha} << endl;
}
