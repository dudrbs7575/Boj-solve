#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <queue>
#include <stack>

using namespace std;
using pii = pair<int, int>;

string s;

void solve() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (true) {
		cin >> s;
		if (s == "0")
			break;
		string reverseS = "";
		for (int i = s.length() - 1; i >= 0; i--)
			reverseS += s[i];
		(s == reverseS) ? cout << "yes" << '\n' : cout << "no" << '\n';
	}
}

int main() {
	solve();
	return 0;
}