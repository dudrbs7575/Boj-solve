#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <functional>
#include <string>
#include <stack>
#include <queue>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define MAX 501
#define INF 0x3f3f3f3f3f3f3f3f

vector<pair<pii,ll>> edge;
ll dist[MAX];
int N, M;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++)
		dist[i] = INF;

	int start, end;
	ll cost;
	for (int i = 0; i < M; i++) {
		cin >> start >> end >> cost;
		edge.push_back({ {start,end }, cost });
	}
}

bool bellman_ford(int startNode) {
	dist[startNode] = 0;
	for (int i = 1; i <= N - 1; i++) {
		for (int j = 0; j < edge.size(); j++) {
			int from = edge[j].first.first;
			int to = edge[j].first.second;
			ll cost = edge[j].second;

			if (dist[from] == INF)
				continue;
			if (dist[to] > dist[from] + cost)
				dist[to] = dist[from] + cost;
		}
	}

	for (int i = 0; i < edge.size(); i++) {
		int from = edge[i].first.first;
		int to = edge[i].first.second;
		ll cost = edge[i].second;

		if (dist[from] == INF)
			continue;
		if (dist[to] > dist[from] + cost) {
			return false;
		}
	}
	return true;
}

void solve() {
	if (N == 1)
		return;
	if (!bellman_ford(1)) {
		cout << -1 << '\n';
		return;
	}
	for (int i = 2; i <= N; i++) {
		if (dist[i] == INF)
			cout << -1 << '\n';
		else
			cout << dist[i] << '\n';
	}
	return;
}

int main(){
	init();
	solve();
	return 0;
}
