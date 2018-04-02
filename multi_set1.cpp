#include <iostream>
#include <string>
#include <set>
using namespace std;
int main() {
  multiset<string> family {"Robert","Jan","Annette","Frits"};
  family.insert({"Ana","Lucia","Eliane","Eduvirgem","Dete","Vilmar","Tina","Du"
	,"Iolanda","Helena","Robson"});
  for (const auto& naam : family) cout << naam << endl;
}
