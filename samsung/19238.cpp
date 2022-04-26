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

using pii = pair<int, int>;
using piii = pair<pair<int, int>, int>;
using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;


#define INF 0x3f3f3f3f
#define MAX 22

//현재위치에서 가장 가까운 승객 탑승, 여러 명 이면 행, 열 가장 작은거
//택시랑 같은 위치면 거리0
//1칸마다 연료 1 소모, 목적지로 이동시키면 승객 탑승 후 목적지까지 소모된 양 * 2 충전

int N, M, gas;
int board[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
vector<tiiii> passenger;
vector<bool> passengerChk;
pii taxi;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> gas;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	int tx, ty;
	cin >> tx >> ty;
	taxi = { tx-1,ty-1 };
	int sx, sy, fx, fy;
	for (int i = 0; i < M; i++) {
		cin >> sx >> sy >> fx >> fy;
		passenger.push_back({ sx-1,sy-1,fx-1,fy-1 });
		passengerChk.push_back(false);
	}
}

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int find_passenger(int endX, int endY) {
	queue<piii> qu;
	qu.push({ { taxi.first,taxi.second },0 });
	visited[taxi.first][taxi.second] = true;
	while (!qu.empty()) {
		int x = qu.front().first.first;
		int y = qu.front().first.second;
		int cnt = qu.front().second;
		if (x == endX && y == endY)
			return cnt;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny)||board[nx][ny]||visited[nx][ny])
				continue;
			qu.push({ {nx,ny},cnt + 1 });
			visited[nx][ny] = true;
		}
	}
	return -1;
}

bool find_arrive(int endX, int endY) {
	queue<piii> qu;
	qu.push({ { taxi.first,taxi.second },0 });
	visited[taxi.first][taxi.second] = true;
	while (!qu.empty()) {
		int x = qu.front().first.first;
		int y = qu.front().first.second;
		int cnt = qu.front().second;
		if (x == endX && y == endY) {
			if (gas - cnt < 0)
				return false;
			gas -= cnt;
			gas += (cnt * 2);
			return true;
		}
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny) || board[nx][ny]||visited[nx][ny])
				continue;
			qu.push({ {nx,ny},cnt + 1 });
			visited[nx][ny] = true;
		}
	}
	return false;
}

void solve() {
	sort(passenger.begin(), passenger.end());
	while (M--) {
		int shortestPassenger = INF;
		int idx = -1;
		for (int i = 0; i < passenger.size(); i++) {
			if (passengerChk[i])
				continue;
			auto t = passenger[i];
			memset(visited, false, sizeof(visited));
			int dist = find_passenger(get<0>(t), get<1>(t));
			if (shortestPassenger > dist) {
				shortestPassenger = dist;
				idx = i;
			}
		}
		if (shortestPassenger == -1)
			break;
		if (gas < shortestPassenger)
			break;
		memset(visited, false, sizeof(visited));
		taxi = { get<0>(passenger[idx]),get<1>(passenger[idx]) };
		passengerChk[idx] = true;
		gas -= shortestPassenger;
		if (!find_arrive(get<2>(passenger[idx]), get<3>(passenger[idx])))
			break;
		taxi = { get<2>(passenger[idx]) ,get<3>(passenger[idx]) };
	}
	
	for (auto p : passengerChk) {
		if (!p) {
			cout << -1 << '\n';
			return;
		}
	}
	cout << gas << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
