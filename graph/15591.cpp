#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int N, Q;
vector<vector<pair<int, int>>> graph;
bool visited[5001];

void init() {
    cin >> N >> Q;
    graph.resize(N + 1);
    int start, end, value;
    for (int i = 0; i < N - 1; i++) {
        cin >> start >> end >> value;
        graph[start].push_back({ end,value });
        graph[end].push_back({ start,value });
    }
}

void bfs(int usado, int startNode) {
    int cnt = 0;
    queue<int> qu;
    visited[startNode] = true;
    qu.push(startNode);
    while (!qu.empty()) {
        int curNode = qu.front();
        qu.pop();
        for (int i = 0; i < graph[curNode].size(); i++) {
            int next = graph[curNode][i].first;
            int cost = graph[curNode][i].second;
            if (visited[next] == false && cost >= usado) {
                cnt++;
                visited[next] = true;
                qu.push(next);
            }
        }
    }
    cout << cnt << '\n';
}

void solution() {
    int usado, startNode;
    for (int i = 0; i < Q; i++) {
        memset(visited, 0, sizeof(visited));
        cin >> usado >> startNode;
        bfs(usado, startNode);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solution();
    return 0;
}