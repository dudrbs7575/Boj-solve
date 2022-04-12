#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>

using namespace std;

#define MAX 5

int M, S;
vector<int> fish[MAX][MAX], copyBoard[MAX][MAX];	//칸 종류, 물고기 수, 방향, 냄새 
int smell[MAX][MAX];
int dx[] = { 0,0,-1,-1,-1,0,1,1,1 };	//북 시작 45도 반 시계 회전
int dy[] = { 0,-1,-1,0,1,1,1,0,-1 };
int shark_dx[] = { -1,0,1,0 };
int shark_dy[] = { 0,-1,0,1 };
pair<int, int> shark_loc;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> M >> S;
	int x, y, d;
	while (M--) {
		cin >> x >> y >> d;
		fish[x-1][y-1].push_back(d);
	}
	int sx, sy;
	cin >> sx >> sy;
	shark_loc = { sx-1,sy-1 };
}

void copy_board() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copyBoard[i][j].clear();
			copyBoard[i][j] = fish[i][j];
		}
	}
}

bool isRange(int x, int y) {
	return 0 <= x && x < 4 && 0 <= y && y < 4;
}

tuple<int,int,int> get_next(int x, int y, int dir) {
	int rx, ry, rdir;
	int cnt = 0;
	while (true) {
		if (cnt == 8)
			break;
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (isRange(nx, ny) && smell[nx][ny] == 0 && !(nx == shark_loc.first&&ny == shark_loc.second)) {
			rx = nx;
			ry = ny;
			rdir = dir;
			break;
		}
		dir = dir - 1;
		if (dir == 0)
			dir = 8;
		cnt++;
	}
	if (cnt == 8)
		return { x,y,dir };

	return { rx,ry,rdir };
}

void move_fish() {
	vector<int> tmp[MAX][MAX];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if(!fish[i][j].size())
				continue;
			for (int k = 0; k < fish[i][j].size(); k++) {
				tuple<int, int, int> next=get_next(i,j,fish[i][j][k]);
				tmp[get<0>(next)][get<1>(next)].push_back(get<2>(next));
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fish[i][j].clear();
			fish[i][j] = tmp[i][j];
		}
	}
}

void move_shark(int time) {
	int iIdx;
	int jIdx;
	int kIdx;
	int fishCnt = -1;
	vector<int> tmpBoard[MAX][MAX];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {

				for (int q = 0; q < 4; q++) {
					for (int w = 0; w < 4; w++) {
						tmpBoard[q][w].clear();
						tmpBoard[q][w] = fish[q][w];
					}
				}

				int tmp = 0;
				int nx = shark_loc.first + shark_dx[i];
				int ny = shark_loc.second + shark_dy[i];
				if (!isRange(nx, ny))
					continue;
				tmp += tmpBoard[nx][ny].size();
				tmpBoard[nx][ny].clear();
				nx += shark_dx[j];
				ny += shark_dy[j];
				if (!isRange(nx, ny))
					continue;
				tmp += tmpBoard[nx][ny].size();
				tmpBoard[nx][ny].clear();
				nx += shark_dx[k];
				ny += shark_dy[k];
				if (!isRange(nx, ny))
					continue;
				tmp += tmpBoard[nx][ny].size();
				tmpBoard[nx][ny].clear();
				if (fishCnt < tmp) {
					iIdx = i;
					jIdx = j;
					kIdx = k;
					fishCnt = tmp;
				}
			}
		}
	}
	int nx = shark_loc.first + shark_dx[iIdx];
	int ny = shark_loc.second + shark_dy[iIdx];
	if (fish[nx][ny].size()) {
		smell[nx][ny] = time;
		fish[nx][ny].clear();
	}
	nx += shark_dx[jIdx];
	ny += shark_dy[jIdx];
	if (fish[nx][ny].size()) {
		smell[nx][ny] = time;
		fish[nx][ny].clear();
		fish[nx][ny].clear();
	}
	nx += shark_dx[kIdx];
	ny += shark_dy[kIdx];
	if (fish[nx][ny].size()) {
		smell[nx][ny] = time;
		fish[nx][ny].clear();
		fish[nx][ny].clear();
	}
	shark_loc = { nx,ny };
}

void copy_fish() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < copyBoard[i][j].size(); k++)
				fish[i][j].push_back(copyBoard[i][j][k]);
		}
	}
}

void smell_clear(int time) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!smell[i][j])
				continue;
			if (time-smell[i][j] == 2)
				smell[i][j] = 0;
		}
	}
}

void solve() {
	for (int i = 1; i <= S;i++) {
		copy_board();
		move_fish();
		move_shark(i);
		smell_clear(i);
		copy_fish();
	}

	int answer = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer += fish[i][j].size();
		}
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}