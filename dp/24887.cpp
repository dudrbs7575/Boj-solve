#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector < pair<int, int>>;
using vvi = vector<vector<int>>;
using tiii = tuple<int, int, int>;

#define INF 0x3f3f3f3f
#define MAX 222222

int N, doWork;
vi work;
int dp[MAX];
bool check = false;
int sum;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> doWork;
	int w;
	for (int i = 0; i < N; i++) {
		cin >> w;
		work.push_back(w);
		if (w >= doWork)
			check = true;
		sum += w;
	}
}

int go(int idx,int minLen) {
	if (idx >= N || idx < 0)
		return 0;

	int& ret = dp[idx];
	if (ret != -1)
		return ret;

	ret = 0;
	ret = max(go(idx + 1, minLen), go(idx + minLen + 1, minLen) + work[idx]);
	return ret;
}

bool is_ans(int minLen) {
	memset(dp, -1, sizeof(dp));
	int subAns = go(0,minLen);
	if (subAns >= doWork) 
		return true;
	return false;
}

int bs(int l, int r) {
	if (l > r)
		return -1;
	int mid = (l + r) / 2;
	if (is_ans(mid)) 
		return max(mid, bs(mid + 1, r));
	return bs(l, mid - 1);
}

void solve() {
	if (check) {
		cout << "Free!" << '\n';
		return;
	}
	int answer=bs(0, N);
	if (answer==-1)
		cout << -1 << '\n';
	else
		cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}