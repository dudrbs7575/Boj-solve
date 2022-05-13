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

priority_queue<pair<int, int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

void solve() {
	int cmd;
	while (N--) {
		cin >> cmd;
		if (cmd == 0) {
			if (pq.empty())
				cout << 0 << '\n';
			else {
				if (pq.top().second == 0)
					cout << -pq.top().first << '\n';
				else
					cout << pq.top().first << '\n';
				pq.pop();
			}
		}
		else {
			if (cmd < 0)
				pq.push({ -cmd,0 });
			else
				pq.push({ cmd,1 });
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}