#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

#define INF 987654321
int TC;
int N, M, W;
int dist[501][501];

void distInit() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j) {
				dist[i][j] = 0;
				continue;
			}
			dist[i][j] = INF;
		}
	}
}

bool solve() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		if (dist[i][i] < 0)
			return true;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> TC;
	while (TC--) {
		cin >> N >> M >> W;
		vector<vector<pair<int, int>>> graph;
		graph.resize(N + 1);
		int start, end, cost;
		distInit();
		while (M--) {
			cin >> start >> end >> cost;
			if (dist[start][end] > cost)
				dist[start][end] = cost;
			if (dist[end][start] > cost)
				dist[end][start] = cost;
		}
		while (W--) {
			cin >> start >> end >> cost;
			dist[start][end] = -cost;
		}
		if (solve())
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
	return 0;
}