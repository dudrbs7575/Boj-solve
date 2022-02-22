#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

#define INF 1e9

vector <int> dist;
vector < vector<pair<int, int>>> graph;
bool chk[20001];
int V, E;
int startNode;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> V >> E >> startNode;
	dist.resize(V+1, INF);
	graph.resize(V+1);
	
	int start, end, cost;
	while (E--) {
		cin >> start >> end >> cost;
		graph[start].push_back({ end,cost });
	}
	
}

void dij() {
	priority_queue<pair<int, int>> pq;
	pq.push({ 0,startNode });
	dist[startNode] = 0;

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int node = pq.top().second;
		pq.pop();

		if (dist[node] < cost)
			continue;

		for (int i = 0; i < graph[node].size(); i++) {
			int nextCost = cost + graph[node][i].second;

			if (nextCost < dist[graph[node][i].first]) {
				dist[graph[node][i].first] = nextCost;
				pq.push({ -nextCost,graph[node][i].first });
			}
		}
	}
}

void solve() {
	for (int i = 1; i <= V; i++) {
		if (dist[i] == INF)
			cout << "INF" << '\n';
		else
			cout << dist[i] << "\n";
	}
}

int main() {
	init();
	dij();
	solve();
	return 0;
}