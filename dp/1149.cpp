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
#define MAX 1001

int N;
int color_cost[MAX][3];
int dp[MAX][3];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> color_cost[i][j];
		}
	}
}

int go(int idx, int color) {
	if (color < 0 || color>2)
		return INF;
	if (idx == N)
		return 0;

	int& ret = dp[idx][color];
	if (ret != -1)
		return ret;

	ret = color_cost[idx][color];
	ret += min({go(idx + 1, color - 1), go(idx + 1, color + 1), go(idx + 1, color - 2), go(idx + 1, color + 2)
});
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	int res1 = go(0, 0);
	cout << res1 << '\n';
	int res2 = go(0, 1);
	cout << res2 << '\n';
	int res3 = go(0, 2);
	cout << res3 << '\n';
	cout << min({ res1,res2,res3 }) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
