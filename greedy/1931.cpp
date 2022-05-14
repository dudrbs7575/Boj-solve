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

#define MAX 111'111
vector<pii> meeting;	//끝나는 시간, 시작 시간.
int dp[MAX];
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		meeting.push_back({ e,s });
	}
	sort(meeting.begin(), meeting.end());
}

void solve() {
	int answer = 0;
	int endTime = -1;
	for (auto m : meeting) {
		int et = m.first;
		int st = m.second;
		if (endTime <= st) {
			answer++;
			endTime = et;
		}
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}