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
#define MAX 111

int board[MAX][MAX];
int tmpBoard[MAX][MAX];
int N, K;
int height = 100;
int subH;
int subW;
vvi bowl;
int dx[] = { 0,1 };	//µ¿, ³²
int dy[] = { 1,0 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	bowl.resize(MAX);
	int f;
	for (int i = 0; i < N; i++) {
		cin >> f;
		bowl[height].push_back(f);
	}
}

bool is_range(int x, int y) {
	return 0 <= x && x <= 100 && 0 <= y && y <= 100;
}

void insert_fish() {
	int minFish = INF;
	for (auto b : bowl[100]) 
		minFish = min(minFish, b);

	for (int i = 0; i < bowl[100].size(); i++) {
		if (bowl[100][i] == minFish)
			bowl[100][i] += 1;
	}
}

void one_fishbowl_up() {
	bowl[height - 1].push_back(bowl[height][0]);
	bowl[height].erase(bowl[height].begin());
}

bool get_height_width() {
	int height = 0;
	int width = 0;

	for (int i = 100; i >= 0; i--) {
		if (!bowl[i].size())
			break;
		height++;
	}
	width = bowl[100 - height+1].size();
	subH = height;
	subW = width;

	if (bowl[100].size() - width < height)
		return false;

	vvi tmp;
	tmp.resize(width);
	int cnt = 0;
	while (width--) {
		for (int i = 100; i > 100 - height; i--) {
			tmp[cnt].push_back(bowl[i][0]);
			bowl[i].erase(bowl[i].begin());
		}
		cnt++;
	}
	
	int idx = 99;
	for (int i = tmp.size() - 1; i >= 0; i--) {
		vi v = tmp[i];
		bowl[idx--] = v;
	}

	return true;
}

void seperate_fish() {
	memset(board, 0, sizeof(board));
	memset(tmpBoard, 0, sizeof(tmpBoard));
	for (int i = height - subH + 1; i <= 100; i++) {
		for (int j = 0; j < bowl[i].size(); j++) {
			board[i][j] = bowl[i][j];
		}
	}

	for (int i = height - subH + 1; i <= 100; i++) {
		for (int j = 0; j <= bowl[i].size(); j++) {
			if (!board[i][j])
				continue;
			for (int k = 0; k < 2; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!is_range(nx, ny) || board[nx][ny] == 0)
					continue;
				int d = abs(board[nx][ny] - board[i][j]) / 5;
				if(!d)
					continue;
				if (board[nx][ny] > board[i][j]) {
					tmpBoard[nx][ny] -= d;
					tmpBoard[i][j] += d;
				}
				else {
					tmpBoard[nx][ny] += d;
					tmpBoard[i][j] -= d;
				}
			}
		}
	}
	

	for (int i = height - subH + 1; i <= 100; i++) {
		for (int j = 0; j < bowl[i].size(); j++) {
			bowl[i][j] += tmpBoard[i][j];
		}
	}
}

void remake_bowl() {
	int width = bowl[100 - subH + 1].size();
	vi tmp;


	for (int w = 0; w < width; w++) {
		for (int h = 100; h > 100 - subH; h--) {
			tmp.push_back(bowl[h][w]);
		}
	}
	for (int w = width; w < bowl[100].size(); w++)
		tmp.push_back(bowl[100][w]);

	for (int h = 100 - subH; h <= 100; h++) 
		bowl[h].clear();
	
	for (auto t : tmp) 
		bowl[100].push_back(t);
}

void half_fishbowl_up() {
	vi tmp;
	for (int i = (N/2)-1; i >= 0; i--)
		tmp.push_back(bowl[100][i]);
	for (auto t : tmp)
		bowl[99].push_back(t);

	int half = (N / 2);
	while (half--) {
		bowl[100].erase(bowl[100].begin());
	}
}

void get_half_height_width() {
	int height = 0;
	int width = 0;

	for (int i = 100; i >= 0; i--) {
		if (!bowl[i].size())
			break;
		height++;
	}
	width = bowl[100].size() / 2;
	subH = height;

	vvi tmp;
	tmp.resize(height);
	int cnt = 0;
	int tmpHeight = height;
	int widthTmp = width;

	for (int i = 100 - subH + 1; i <= 100; i++) {
		widthTmp = width;
		while (widthTmp--) {
			tmp[cnt].push_back(bowl[i][0]);
			bowl[i].erase(bowl[i].begin());
		}
		cnt++;
	}

	int idx = 100-height;
	for (int i = 0; i < tmp.size(); i++) {
		for (int j = tmp[i].size() - 1; j >= 0; j--) {
			bowl[idx].push_back(tmp[i][j]);
		}
		idx--;
	}
	
	subH = 100 - idx;
}

bool can_break() {
	int minFish = INF;
	int maxFish = -1;
	for (auto b : bowl[100]) {
		minFish = min(minFish, b);
		maxFish = max(maxFish, b);
	}
	if (abs(minFish - maxFish) <= K)
		return true;
	return false;
}

void solve() {
	int cnt = 0;
	while (true) {
		if (can_break()) {
			cout << cnt << '\n';
			break;
		}
		insert_fish();
		one_fishbowl_up();
		while (true) {
			if (!get_height_width())
				break;
		}
		seperate_fish();
		remake_bowl();

		get_half_height_width();
		get_half_height_width();

		seperate_fish();
		remake_bowl();
		cnt++;
	}
}

int main() {
	init();
	solve();
	return 0;
}
