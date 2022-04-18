#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>
#include <sstream>
#include <queue>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 801

vvii graph;
int N, E;
int dist[MAX];
int a, b;
bool flag = false;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> E;
	graph.resize(N + 1);
	int start, end, cost;
	while (E--) {
		cin >> start >> end >> cost;
		graph[start].push_back({ end,cost });
		graph[end].push_back({ start,cost });
	}
	cin >> a >> b;
}

void make_INF() {
	for (int i = 1; i <= N; i++)
		dist[i] = INF;
}

int dijkstra(int start, int end) {
	priority_queue<pair<int, int>> pq;
	pq.push({ 0,start });
	dist[start] = 0;
	while (!pq.empty()) {
		int c = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		if (dist[cur] < c)
			continue;
		for (int i = 0; i < graph[cur].size(); i++) {
			int nextNode = graph[cur][i].first;
			int cost = c + graph[cur][i].second;
			if (dist[nextNode] > cost) {
				dist[nextNode] = cost;
				pq.push({ -cost,nextNode });
			}
		}
	}
	if (dist[end] == INF)
		flag = true;
	return dist[end];
}

void solve() {
	int res = 0;
	int res2 = 0;
	if (N <= 3) {
		cout << -1 << "\n";
		return;
	}

	make_INF();
	res += dijkstra(1,a);
	if (flag) {
		cout << -1 << '\n';
		return;
	}

	make_INF();
	res += dijkstra(a, b);
	if (flag) {
		cout << -1 << '\n';
		return;
	}

	make_INF();
	res += dijkstra(b, N);
	if (flag) {
		cout << -1 << '\n';
		return;
	}

	make_INF();
	res2 += dijkstra(1, b);
	if (flag) {
		cout << -1 << '\n';
		return;
	}

	make_INF();
	res2 += dijkstra(b, a);
	if (flag) {
		cout << -1 << '\n';
		return;
	}

	make_INF();
	res2 += dijkstra(a, N);
	if (flag) {
		cout << -1 << '\n';
		return;
	}
	cout << min(res, res2) << '\n';
	//flag ? cout << -1 << '\n' : cout << min(res, res2) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
