#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector < pair<int, int>>;
using vvi = vector<vector<int>>;
using tiii = tuple<int, int, int>;

#define MAX 111

int N, T;
pii arr[MAX];
int dp[MAX][11111];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> T;
	int k, s;
	for (int i = 1; i <= N; i++) {
		cin >> k >> s;
		arr[i] = { k,s };
	}
}

int go(int idx, int time) {
	if (idx > N || time > T)
		return 0;

	int &ret = dp[idx][time];
	if (ret != -1)
		return ret;
	
	ret = 0;
	int tmp = go(idx+1,time);
	int tmp2 = 0;
	if (time + arr[idx].first <= T)
		tmp2 = go(idx + 1, time + arr[idx].first) + arr[idx].second;
	
	ret = max(tmp, tmp2);
	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	cout << go(1,0) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}