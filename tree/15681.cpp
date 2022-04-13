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
#define MAX 100001

int N, R, Q;
vvi tree;
int dp[MAX];
bool visited[MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> R >> Q;
	tree.resize(N + 1);
	int f, t;
	for (int i = 0; i < N - 1; i++) {
		cin >> f >> t;
		tree[f].push_back(t);
		tree[t].push_back(f);
	}
	memset(dp, -1, sizeof(dp));
}

int go(int curNode) {
	visited[curNode] = true;
	if (!tree[curNode].size()) 
		return 1;

	int& ret = dp[curNode];
	if (ret != -1)
		return ret;
	ret = 1;

	for (int i = 0; i < tree[curNode].size(); i++) {
		int next = tree[curNode][i];
		if (visited[next])
			continue;
		ret += go(next);
	}
	return ret;
}

void solve() {
	go(R);
	while (Q--) {
		int root;
		cin >> root;
		cout << dp[root] << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}