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

int dist[MAX][MAX];
int ans[MAX];
int N, M;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			(i == j) ? dist[i][j] = 0 : dist[i][j] = INF;
		}
	}
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		dist[a][b] = 1;
	}
}

void floyd() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

int get_ans() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j||dist[i][j]==INF)
				continue;
			if (++ans[i] == N - 1)
				answer++;
			if (++ans[j] == N - 1)
				answer++;
		}
	}
	return answer;
}

void solve() {
	floyd();
	cout << get_ans() << '\n';
}

int main() {
	init();
	solve();
	return 0;
}