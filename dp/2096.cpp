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

#define INF 0x3f3f3f3f

int board[100'001][3];
int max_dp[2][3];
int min_dp[2][3];
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int a, b, c;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> board[i][j];
		}
	}
}
void solve() {
	max_dp[0][0] = min_dp[0][0] = board[0][0];
	max_dp[0][1] = min_dp[0][1] = board[0][1];
	max_dp[0][2] = min_dp[0][2] = board[0][2];
	for (int i = 1; i < N; i++) {
		max_dp[1][0] = board[i][0] + max(max_dp[0][0], max_dp[0][1]);
		max_dp[1][1] = board[i][1] + max({ max_dp[0][0], max_dp[0][1],max_dp[0][2] });
		max_dp[1][2] = board[i][2] + max(max_dp[0][1], max_dp[0][2]);

		max_dp[0][0] = max_dp[1][0];
		max_dp[0][1] = max_dp[1][1];
		max_dp[0][2] = max_dp[1][2];

		min_dp[1][0] = board[i][0] + min(min_dp[0][0], min_dp[0][1]);
		min_dp[1][1] = board[i][1] + min({ min_dp[0][0], min_dp[0][1], min_dp[0][2] });
		min_dp[1][2] = board[i][2] + min(min_dp[0][1], min_dp[0][2]);

		min_dp[0][0] = min_dp[1][0];
		min_dp[0][1] = min_dp[1][1];
		min_dp[0][2] = min_dp[1][2];
	}
	cout << max({ max_dp[0][0],max_dp[0][1],max_dp[0][2] }) << " ";
	cout << min({ min_dp[0][1],min_dp[0][1],min_dp[0][2] }) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}