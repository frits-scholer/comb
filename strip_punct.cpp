#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;

#define all(t) begin(t), end(t)

string StripPunctuation(string input) {
	input.erase(remove_if(all(input),[](int n) {return ispunct(n);}), end(input));
	return input;
}

int main() {
string s;
getline(cin,s);
cout << StripPunctuation(s) << endl;
}