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

vector<int> v;
bool chk[10];
int N, M;
set<string> se;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n;
		v.push_back(n);
	}
}

void dfs(int cnt, string s) {
	if (cnt == M) {
		if (se.find(s) == se.end()) {
			for (int i = 0; i < s.length(); i++) {
				cout << s[i] << " ";
			}
			cout << '\n';
			se.insert(s);
		}
	}
	for (int i = 0; i < N; i++) {
		if (chk[i])
			continue;
		chk[i] = true;
		dfs(cnt + 1, s + to_string(v[i]));
		chk[i] = false;
	}
}

void solve() {
	sort(v.begin(), v.end());
	dfs(0,"");
}

int main() {
	init();
	solve();
	return 0;
}