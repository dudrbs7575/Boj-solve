#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define INF 1e9
int N, M;
int dist[101][101];


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j) {
				dist[i][j] = 0;
				continue;
			}
			dist[i][j] = INF;
		}
	}
	int start, end, cost;
	while (M--) {
		cin >> start >> end >> cost;
		if (dist[start][end] < cost)
			continue;
		dist[start][end] = cost;
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

void solve() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dist[i][j] == INF)
				cout << 0 << " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	init();
	floyd();
	solve();
	return 0;
}