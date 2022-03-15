#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

vector<vector<int>> tree;
vector<int> nodeCost;
int N;
int dp[10001][2];		//i 번 째 노드가 포함됐는지 안됐는지
vector<int> path;
vector<bool> visited;

void init() {
	cin >> N;
	nodeCost.resize(N + 1);
	tree.resize(N + 1);
	visited.resize(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> nodeCost[i];
	int start, end;
	for (int i = 1; i < N;i++) {
		cin >> start >> end;
		tree[start].push_back(end);
		tree[end].push_back(start);
	}
}

void dfs(int curNode) {
	dp[curNode][0] = 0;	//독립 집합에 포함X
	dp[curNode][1] = nodeCost[curNode]; //독립 집합에 포함O
	visited[curNode] = true;

	for (int i = 0; i < tree[curNode].size(); i++) {
		int nextNode = tree[curNode][i];
		if (visited[nextNode])
			continue;
		dfs(nextNode);
		dp[curNode][0] += max(dp[nextNode][0], dp[nextNode][1]);
		dp[curNode][1] += dp[nextNode][0];
	}
}

void get_path(int cur, int prev) {
	if (dp[cur][1] > dp[cur][0] && !visited[prev]) {
		path.push_back(cur);
		visited[cur] = true;
	}
	for (int i = 0; i < tree[cur].size(); i++) {
		int next = tree[cur][i];
		if (next == prev)
			continue;
		get_path(next, cur);
	}
}

void solve() {
	dfs(1);
	visited = vector<bool>(N + 1, false);
	get_path(1,0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	init();
	solve();
	sort(path.begin(), path.end());
	cout << max(dp[1][0], dp[1][1]) << '\n';
	for (auto a : path)
		cout << a << " ";
	return 0;
}