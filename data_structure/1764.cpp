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
using ll = long long;

#define MAX 200'001

int N, M;
vector<string> answer;
map<string, int> ma;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
}

void solve() {
	int ans = 0;
	string s;
	for (int i = 0; i < N; i ++ ) {
		cin >> s;
		ma[s]++;
	}
	for (int i = 0; i < M; i++) {
		cin >> s;
		if (ma[s]) {
			ma[s]++;
			ans++;
		}
	}
	cout<<ans<<'\n';
	for (auto iter = ma.begin(); iter != ma.end(); iter++) {
		if (iter->second == 2)
			cout << iter->first << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}