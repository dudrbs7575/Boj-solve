#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

#define MOD 1000000000
int N;
long long dp[111][11]; // 길이, 숫자

long long go(int i, int j) {
	if (j < 0 || j>9)
		return 0;

	if (i == N) 
		return 1;
	
	long long& ret = dp[i][j];
	if (ret != -1)
		return ret;

	ret = go(i + 1, j + 1) % MOD + go(i + 1, j - 1) % MOD;
	
	return ret%MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	memset(dp, -1, sizeof(dp));
	long long ans = 0;
	for (int i = 1; i <= 9; i++) {
		ans += go(1, i) % MOD;
	}
	cout << ans%MOD;
	return 0;
}