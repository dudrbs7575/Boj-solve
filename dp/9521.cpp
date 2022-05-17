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

#define MAX 1001

string s1, s2;
int len1, len2;
int dp[MAX][MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> s1 >> s2;
}

int go(int i, int j) {
	if (i >= len1 || j >= len2)
		return 0;

	int& ret = dp[i][j];
	if (ret != -1)
		return ret;

	ret = 0;
	if (s1[i] == s2[j])
		ret = max({ ret,go(i + 1,j + 1) }) + 1;
	else
		ret = max({ ret,go(i,j + 1),go(i + 1,j) });
	return ret;
}

void solve() {
	len1 = s1.length();
	len2 = s2.length();
	memset(dp, -1, sizeof(dp));
	cout << go(0, 0) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}