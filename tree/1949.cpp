#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

int N;
vector<int> town;
vector<vector<int>> tree;
vector<bool> visited;
int dp[10001][2];

void init() {
	cin >> N;
	town.resize(N + 1);
	tree.resize(N + 1);
	visited.resize(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> town[i];
	int start, end;
	for (int i = 1; i < N; i++) {
		cin >> start >> end;
		tree[start].push_back(end);
		tree[end].push_back(start);
	}
}

void dfs(int cur) {
	dp[cur][0] = 0;
	dp[cur][1] = town[cur];
	visited[cur] = true;

	for (int i = 0; i < tree[cur].size(); i++) {
		int next = tree[cur][i];
		if (visited[next])
			continue;
		dfs(next);
		dp[cur][0] += max(dp[next][1],dp[next][0]);
		dp[cur][1] += dp[next][0];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	init();
	dfs(1);
	cout << max(dp[1][0], dp[1][1]);
	return 0;
}