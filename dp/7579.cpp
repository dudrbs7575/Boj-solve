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

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 10000010

int N, M;
int memory[MAX];
int cost[MAX];
vii info;
int dp[101][2][10001];	//각 cost마다 확보할 수 있는 최대 memory
int ans = 0;
int len;

bool cmp(pii &p1, pii&p2) {
	if (p1.first == p2.first)
		return p1.second > p2.second;
	return p1.first < p2.first;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> memory[i];
	for (int i = 0; i < N; i++)
		cin >> cost[i];

}

int go(int idx, int state, int total) {
	if (idx == N)
		return 0;

	int& ret = dp[idx][state][total];
	if (ret!=-1)
		return ret;
	if (state) {
		if (total - info[idx].first < 0)
			return 0;
		ret = info[idx].second;
		ret += max(go(idx + 1, 0, total - info[idx].first), go(idx + 1, 1, total - info[idx].first));
	}
	else {
		ret = 0;
		ret += max(go(idx + 1, 0, total), go(idx + 1, 1, total));
	}
	
	return ret;
}

void solve() {
	for (int i = 0; i < N; i++) 
		info.push_back({cost[i],memory[i]});
	sort(info.begin(), info.end(), cmp);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i <= 10000; i++) {
		int res1 = go(0, 0, i);
		int res2 = go(0, 1, i);
		if (max(res1, res2) >= M) {
			cout << i << '\n';
			break;
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}