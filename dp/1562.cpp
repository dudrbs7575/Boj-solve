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

#define MOD 1'000'000'000
#define FULLBIT (1<<10)-1

int N;
int dp[111][11][(1<<10)];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

int go(int idx, int k, int bit) {
	if (idx == N) {
		if (bit == FULLBIT)
			return 1;
		else
			return 0;
	}


	int& ret = dp[idx][k][bit];
	if (ret != -1)
		return ret;

	ret = 0;
	if(k-1>=0)
		ret += go(idx + 1, k - 1, bit | (1 << (k - 1))) % MOD;
	if(k+1<=9)
		ret += go(idx + 1, k + 1, bit | (1 << (k + 1))) % MOD;
	return ret%MOD;
}

void solve() {
	if (N < 10)
		cout << 0 << '\n';
	else {
		memset(dp, -1, sizeof(dp));
		int ans = 0;
		for (int i = 1; i <= 9; i++) {
			ans += go(1, i, 1 << i);
			ans %= MOD;
		}
		cout << ans << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}