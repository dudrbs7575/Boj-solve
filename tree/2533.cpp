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

#define vvi vector<vector<int>>
#define MAX 1000001
#define INF 0x3f3f3f3f

int N;
vvi v;
vvi tree;
int dp[MAX][2];
bool visited[MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	v.resize(N + 1);
	tree.resize(N + 1);
	int f, t;
	for (int i = 0; i < N - 1; i++) {
		cin >> f >> t;
		v[f].push_back(t);
		v[t].push_back(f);
	}
	memset(dp, -1, sizeof(dp));
	memset(visited, false, sizeof(visited));
}

void make_tree(int node) {
	visited[node] = true;
	for (int i = 0; i < v[node].size(); i++) {
		int next = v[node][i];
		if (visited[next])
			continue;
		tree[node].push_back(next);
		make_tree(next);
	}
}

int go(int curNode, int state) {
	int& ret = dp[curNode][state];
	if (ret != -1)
		return ret;

	if (state) {
		ret = 1;
		for (int i = 0; i < tree[curNode].size(); i++) {
			int next = tree[curNode][i];
			ret += min(go(next, 0), go(next, 1));
		}
	}
	else {
		ret = 0;
		for (int i = 0; i < tree[curNode].size(); i++) {
			int next = tree[curNode][i];
			ret += go(next, 1);
		}
	}
	return ret;
}

void solve() {
	make_tree(2);
	int res = go(2, 0);
	int res2 = go(2, 1);
	cout << min(res, res2) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}