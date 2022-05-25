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
#include <stack>

using namespace std;
using pii = pair<int, int>;

#define MAX 1001

int N;
int arr[MAX];
int dp[MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
}

int go(int idx) {
	int& ret = dp[idx];
	if (ret != -1)
		return ret;

	ret = 1;
	for (int i = idx+1; i < N; i++) {
		if (arr[idx] < arr[i])
			ret = max(ret, go(i) + 1);
	}
	return ret;
}

void solve() {
	int answer = 0;
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < N; i++)
		answer = max(answer, go(i));
	(answer == 1) ? cout << 0 << '\n' : cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}