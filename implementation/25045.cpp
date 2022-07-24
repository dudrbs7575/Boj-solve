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
using ll = long long;

#define INF 0x3f3f3f3f
#define MAX 501

int N, M;
vector<ll> satisfaction;
vector<ll> cost;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	satisfaction.resize(N);
	cost.resize(M);
	for (int i = 0; i < N; i++)
		cin >> satisfaction[i];
	for (int i = 0; i < M; i++)
		cin >> cost[i];
}

bool cmp(ll& v1, ll& v2) {
	return v1 > v2;
}

void solve() {
	int len = min(N, M);
	ll sum = 0;
	sort(satisfaction.begin(),satisfaction.end(),cmp);
	sort(cost.begin(), cost.end());
	for (int i = 0; i < len; i++) {
		int gap = satisfaction[i] - cost[i];
		if (gap)
			sum += gap;
		else
			break;
	}
	cout << sum << '\n';
}

int main() {
	init();
	solve();
	return 0;
}