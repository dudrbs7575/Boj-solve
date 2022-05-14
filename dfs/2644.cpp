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

vector<vector<int>> graph;
vector<bool> visited;
int N, M;
int sa, ea;
int answer = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	cin >> sa >> ea;
	cin >> M;
	graph.resize(101);
	visited.resize(101, false);
	int s, e;
	while (M--) {
		cin >> s >> e;
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
}

void dfs(int cur, int end,int cnt) {
	visited[cur] = true;
	if (cur == end) {
		answer = cnt;
		return;
	}
	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];
		if (visited[next])
			continue;
		dfs(next, end, cnt + 1);
	}
}

void solve() {
	dfs(sa, ea,0);
	if (!answer)
		cout << -1 << '\n';
	else
		cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}