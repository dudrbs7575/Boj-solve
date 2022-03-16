#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define INF 1e9
int N, K;
int dist[401][401];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = INF;
		}
	}
	int start, end;
	while (K--) {
		cin >> start >> end;
		dist[start][end] = 1;
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
	int T;
	cin >> T;
	int start, end;
	while (T--) {
		cin >> start >> end;
		int b = dist[start][end];
		int e = dist[end][start];
		if (b == INF && e == INF)
			cout << 0 << '\n';
		else if (b < e)
			cout << -1 << '\n';
		else
			cout << 1 << '\n';
	}
}

int main() {
	init();
	floyd();
	solve();
	return 0;
}