#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector < pair<int, int>>;
using vvi = vector<vector<int>>;
using tiii = tuple<int, int, int>;

#define INF 0x3f3f3f3f3f3f3f3f
#define MAX 222222

int N, M;
vector < vector<pair<int, long>>> graph;
bool visited[MAX];
bool note[MAX];
bool tmpNote[MAX];
ll dist[MAX];
int answer = 0;
vi answer_node_set;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	graph.resize(N+1);
	int s, e;
	ll c;
	for (int i = 0; i < M; i++) {
		cin >> s >> e >> c;
		graph[s].push_back({ e,c });
		graph[e].push_back({ s,c });
	}
	for (int i = 1; i <= N; i++) {
		cin >> note[i];
		tmpNote[i] = note[i];
	}
}

void dijkstra(int sNode) {
	priority_queue<pair<long, int>> pq;
	dist[sNode] = 0;
	pq.push({ 0,sNode });
	while (!pq.empty()) {
		ll cost = -pq.top().first;
		int node = pq.top().second;
		pq.pop();
		if (dist[node] < cost)
			continue;
		for (int i = 0; i < graph[node].size(); i++) {
			int next = graph[node][i].first;
			ll nextCost = cost + graph[node][i].second;
			if (dist[next] > nextCost) {
				dist[next] = nextCost;
				pq.push({ -nextCost,next });
			}
		}
	}
}

bool is_ans(vi &node_set) {
	for (int i = 1; i <= N; i++)
		note[i] = tmpNote[i];
	for (auto n : node_set)
		note[n] = false;
	for (int i = 1; i <= N; i++) {
		if (note[i])
			return false;
	}
	return true;
}

void dfs(int cur, int prev, ll cnt, vi node_set) {
	if (dist[cur] < cnt)
		return;
	node_set.push_back(cur);
	if (N == cur) {
		if (dist[N] == cnt) {
			if (is_ans(node_set)) {
				answer = cnt;
				answer_node_set.clear();
				answer_node_set = node_set;
			}
		}
		return;
	}
	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i].first;
		ll cost = graph[cur][i].second;
		if (next==prev)
			continue;
		dfs(next, cur, cnt + cost, node_set);
	}
}

void solve() {
	fill(dist, dist + MAX, INF);
	dijkstra(1);
	vi node_set;
	dfs(1,1, 0,node_set);
	if (dist[N] != answer)
		cout << -1 << '\n';
	else {
		cout << answer_node_set.size() << '\n';
		for (auto n : answer_node_set)
			cout << n << " ";
		cout << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}