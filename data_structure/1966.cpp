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

#define INF 0x3f3f3f3f
int T;
int N, M;
priority_queue<int> pq;
queue<pii> qu;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
}

void solve() {
	while (T--) {
		cin >> N >> M;
		int importance;
		for (int i = 0; i < N; i++) {
			cin >> importance;
			pq.push(importance);
			qu.push({ importance,i });
		}

		int cnt = 0;
		while (!qu.empty()) {
			int imp = qu.front().first;
			int idx = qu.front().second;
			qu.pop();
			
			if (pq.top() == imp) {
				pq.pop();
				cnt++;
				if (M == idx) 
					cout << cnt << '\n';
			}
			else
				qu.push({ imp,idx });
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}