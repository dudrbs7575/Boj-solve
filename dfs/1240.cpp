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

#define INF 0x3f3f3f3f
#define MAX 501

int N, M;
vector<vector<pair<int,int>>> tree;
vector<bool> chk;
int answer;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	tree.resize(N + 1);
	chk.resize(N + 1);
	int s, e, c;
	for (int i = 0; i < N - 1; i++) {
		cin >> s >> e >> c;
		tree[s].push_back({ e,c });
		tree[e].push_back({ s,c });
	}
}

void dfs(int cur, int end, int c) {
	if (cur == end) {
		answer = c;
		return;
	}
	chk[cur] = true;
	for (int i = 0; i < tree[cur].size(); i++) {
		int next = tree[cur][i].first;
		int cost = tree[cur][i].second;
		if (chk[next])
			continue;
		dfs(next, end, c + cost);
	}
}

void solve() {
	int n1, n2;
	while (M--) {
		cin >> n1 >> n2;
		fill(chk.begin(), chk.end(), false);
		answer = 0;
		dfs(n1, n2,0);
		cout<<answer << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}