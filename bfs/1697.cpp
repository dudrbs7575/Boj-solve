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

#define INF 0x3f3f3f3f

bool visited[111'111];
int N, K;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
}

bool is_range(int x) {
	return 0 <= x && x <= 100'000;
}

int bfs(int start) {
	visited[start] = true;
	queue<int> qu;
	qu.push(start);
	int time = 0;
	while (!qu.empty()) {
		int qSize = qu.size();
		while (qSize--) {
			int cur = qu.front();
			qu.pop();
			if (cur == K)
				return time;
			if (is_range(cur + 1)&&!visited[cur + 1]) {
				visited[cur + 1] = true;
				qu.push(cur + 1);
			}
			if (is_range(cur - 1)&&!visited[cur - 1]) {
				visited[cur - 1] = true;
				qu.push(cur - 1);
			}
			if (is_range(cur * 2) && !visited[cur * 2]) {
				visited[cur * 2] = true;
				qu.push(cur * 2);
			}
		}
		time++;
	}
}

void solve() {
	cout << bfs(N) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}