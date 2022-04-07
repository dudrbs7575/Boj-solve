#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <functional>
#include <string>
#include <stack>
#include <queue>

using namespace std;

int N, rootNode;
int gigaNode;
int gigaCnt;
int branchCnt;
vector<vector<pair<int,int>>> tree;
vector<bool> visited;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> rootNode;
	tree.resize(N + 1);
	visited.resize(N + 1, false);
	int start, end, cost;
	for (int i = 0; i < N-1; i++) {
		cin >> start >> end >> cost;
		tree[start].push_back({ end,cost });
		tree[end].push_back({ start,cost });
	}
}

void giga_dfs(int curNode, int cnt) {
	visited[curNode] = true;
	gigaNode = curNode;
	gigaCnt = cnt;
	int tmp = 0;
	for (int i = 0; i < tree[curNode].size(); i++) {
		if (!visited[tree[curNode][i].first])
			tmp++;
	}
	if(tmp>=2)
		return;
	for (int i = 0; i < tree[curNode].size(); i++) {
		int next = tree[curNode][i].first;
		int cost = tree[curNode][i].second;
		if (!visited[next])
			giga_dfs(next, cnt + cost);
	}
}

void branch_dfs(int curNode, int cnt) {
	visited[curNode] = true;
	for (int i = 0; i < tree[curNode].size(); i++) {
		int next = tree[curNode][i].first;
		int cost = tree[curNode][i].second;
		if (!visited[next])
			branch_dfs(next, cnt + cost);
	}
	branchCnt = max(branchCnt, cnt);
	return;
}

void solve() {
	giga_dfs(rootNode, 0);
	branch_dfs(gigaNode, 0);
	cout << gigaCnt << " " << branchCnt << '\n';
}

int main(){
	init();
	solve();
	return 0;
}