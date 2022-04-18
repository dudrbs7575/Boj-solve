#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>
#include <sstream>
#include <queue>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 100001

int V;
vvii tmp;
vvii tree;
bool visited[MAX];
int dp[MAX];
int rootNode;
int val = -1;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> V;
	tmp.resize(V + 1);
	tree.resize(V + 1);
	for (int i = 1; i <= V; i++) {
		int node = 0;
		int a = 0;
		int b = 0;
		int cnt = 0;
		while (a != -1) {
			if (cnt == 0) {
				cin >> node;
				cnt++;
				continue;
			}
			if (cnt != 0 && cnt % 2 == 1) {
				cin >> a;
			}
			else if (cnt != 0 && cnt % 2 == 0) {
				cin >> b;
				tmp[node].push_back({ a,b });
			}
			cnt++;
		}
	}
}

void make_tree(int cur) {
	visited[cur] = true;
	for (int i = 0; i < tmp[cur].size(); i++) {
		int next = tmp[cur][i].first;
		int cost = tmp[cur][i].second;
		if (visited[next])
			continue;
		tree[cur].push_back({ next,cost });
		make_tree(next);
	}
}

int go(int cur, int cost) {
	if (!tree[cur].size()) 
		return cost;

	int &ret = dp[cur];
	if (ret != -1)
		return ret;

	ret = cost;
	int maxLoad = 0;
	int totalLoad = 0;
	for (int i = 0; i < tree[cur].size(); i++) {
		int next = tree[cur][i].first;
		int c = tree[cur][i].second;
		maxLoad = max(maxLoad, go(next, c));
		totalLoad += go(next, c);
	}
	ret += maxLoad;
	return ret;
}

void dfs(int cur, int cost) {
	if (!tree[cur].size()) {
		if (cost > val) {
			val = cost;
			rootNode = cur;
		}
		return;
	}

	for (int i = 0; i < tree[cur].size(); i++) {
		int next = tree[cur][i].first;
		int nextCost = tree[cur][i].second;
		dfs(next, cost + nextCost);
	}
}

void solve() {
	make_tree(1);
	dfs(1, 0);
	tree.clear();
	tree.resize(V + 1);
	memset(visited, false, sizeof(visited));
	make_tree(rootNode);
	memset(dp, -1, sizeof(dp));
	int ans = go(rootNode,0);
	cout << ans << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
