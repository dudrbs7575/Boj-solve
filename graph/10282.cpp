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

int t, n, d, c;
int dist[10001];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
}

void get_ans(vector<vector<pair<int, int>>>& graph, int start, int n) {
	priority_queue<pair<int, int>> pq;
	fill(dist, dist + 10001, INF);
	dist[start] = 0;
	pq.push({ 0,start });
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		if (dist[cur] < cost)
			continue;
		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i].first;
			int nCost = cost + graph[cur][i].second;
			if (dist[next] > nCost) {
				dist[next] = nCost;
				pq.push({ -nCost,next });
			}
		}
	}

	int time = 0;
	int total = 0;
	for (int i = 1; i <= n; i++) {
		if (dist[i] != INF) {
			total++;
			time = max(time, dist[i]);
		}
	}
	cout << total << " " << time << '\n';
}

void solve() {
	while (t--) {
		cin >> n >> d >> c;
		vector<vector<pair<int,int>>> graph;
		graph.resize(n + 1);
		int a, b, s;
		for (int i = 0; i < d; i++) {
			cin >> a >> b >> s;
			graph[b].push_back({ a,s });
		}
		get_ans(graph, c,n);
	}
}

int main() {
	init();
	solve();
	return 0;
}