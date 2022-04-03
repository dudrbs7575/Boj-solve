#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#define INF 0x3f3f3f3f
int N;
int dp[333][3];
int p[333];

int go(int i, int j) {
	if (i >= N || j >= 2) {
		return -INF;
	}
	if (i == N - 1)
		return p[i];

	int& ret = dp[i][j];
	if (ret != -1)
		return ret;
	
	ret = p[i];
	ret += max(go(i + 1, j + 1), go(i + 2, 0));

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> p[i];
	}
	memset(dp, -1, sizeof(dp));
	cout << max(go(0,0),go(1,0)) << '\n';
	return 0;
}
