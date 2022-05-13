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

using namespace std;
using pii = pair<int, int>;

int N;
bool chk[22];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}


void solve() {
	string s;
	int val;
	while (N--) {
		cin >> s;
		if (s == "all") {
			fill(chk, chk + 22, true);
		}
		else if(s=="empty"){
			memset(chk, false, sizeof(chk));
		}
		else {
			cin >> val;
			if (s == "add")
				chk[val] = true;
			else if (s == "remove")
				chk[val] = false;
			else if (s == "check") 
				chk[val] ? cout << 1 << '\n' : cout << 0 << '\n';
			else 
				chk[val] ? chk[val] = false : chk[val] = true;
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}