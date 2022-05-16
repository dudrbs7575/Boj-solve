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

#define MAX 10'001

vector<vector<pii>> tree;
bool visited[MAX];
int N;
int ans_node = 1;
int dist = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	tree.resize(MAX);
	int s, e, c;
	for (int i = 0; i < N-1;i++) {
		cin >> s >> e >> c;
		tree[s].push_back({ e,c });
		tree[e].push_back({ s,c });
	}
}

void dfs(int cur, int cost) {
	visited[cur] = true;
	for (int i = 0; i < tree[cur].size(); i++) {
		int next = tree[cur][i].first;
		int nCost = tree[cur][i].second;
		if (visited[next])
			continue;
		dfs(next, cost + nCost);
	}

	if (dist < cost) {
		ans_node = cur;
		dist = cost;
	}
}

void solve() {
	dfs(ans_node, 0);
	memset(visited, false, sizeof(visited));
	dfs(ans_node, 0);
	cout << dist << '\n';
}

int main() {
	init();
	solve();
	return 0;
}