#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define INF 0x3f3f3f3f
#define pii pair<int,int>

int T, N, M;
vvii tree;
vvii v;
int dp[1010];
bool visited[1010];

int dfs(int cur, int cost) {
	if (!tree[cur].size())
		return cost;

	int& ret = dp[cur];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int i = 0; i < tree[cur].size(); i++) {
		pii next = tree[cur][i];
		ret += dfs(next.first, next.second);
	}

	return min(ret,cost);
}

void make_tree(int node) {
	visited[node] = true;
	for (int i = 0; i < v[node].size(); i++) {
		pii next = v[node][i];
		if (visited[next.first])
			continue;
		tree[node].push_back(next);
		make_tree(next.first);
	}
}

void solve() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	while (T--) {
		cin >> N >> M;
		if (N == 1) {
			cout << 0 << '\n';
			continue;
		}
		tree.clear();
		v.clear();
		tree.resize(N + 1);
		v.resize(N + 1);
		int s, e, c;
		while (M--) {
			cin >> s >> e >> c;
			v[s].push_back({ e,c });
			v[e].push_back({ s,c });
		}
		memset(visited, false, sizeof(visited));
		make_tree(1);
		memset(dp, -1, sizeof(dp));
		cout << dfs(1, INF) << '\n';
	}
}

int main() {
	solve();
	return 0;
}