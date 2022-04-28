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
#define MAX 10
#define GREEN_ROW_START 4
#define GREEN_ROW_END 9
#define BLUE_COL_START 4
#define BLUE_COL_END 9

//t = 1: 크기가 1×1인 블록을(x, y)에 놓은 경우
//t = 2 : 크기가 1×2인 블록을(x, y), (x, y + 1)에 놓은 경우
//t = 3 : 크기가 2×1인 블록을(x, y), (x + 1, y)에 놓은 경우
//행 or 열 1줄 당 1점 획득
//그린, 파랑 0,1번 행, 열은 특별한 줄. 
//이 공간에 블록이 있으면 있는 행,열 수만큼 마지막 행,열이 사라지고 평행이동.
//행,열 가득찬 경우랑 연한 칸에 블록있는 경우 동시발생 가능. 이럴 땐 행,열 가득찬거 처리후, 블록 처리

int N;
vvi board;
int answer = 0;


void print() {
	cout << '\n';
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			cout << board[i][j];
		}
		cout << '\n';
	}
	for (int i = 4; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			cout << board[i][j];
		}
		cout << '\n';
	}
}


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	board.resize(10);
	for (int i = 0; i < 4; i++)
		board[i].resize(10);
	for (int i = 4; i < 10; i++)
		board[i].resize(4);
	cin >> N;
}

bool is_blue_valid(int x, int y, int x2,int y2) {
	if (y == 10||y2==10)
		return false;
	if (board[x][y] || board[x2][y2])
		return false;
	return true;
}

bool is_green_valid(int x, int y, int x2, int y2) {
	if (x == 10 || x2 == 10)
		return false;
	if (board[x][y] || board[x2][y2])
		return false;
	return true;
}

void block_move_to_blueZone(int t,int x,int y) {
	vii block;
	y = 0;
	if (t == 1) {
		block.push_back({ x,y }); block.push_back({ x,y });
	}
	else if (t == 2) {
		block.push_back({ x,y }); block.push_back({ x,y + 1 });
	}
	else {
		block.push_back({ x,y }); block.push_back({ x + 1,y });
	}
	int idx = 4;
	while (true) {
		if (!is_blue_valid(block[0].first, block[0].second+idx, block[1].first, block[1].second+idx)) {
			idx--;
			break;
		}
		idx++;
	}
	board[block[0].first][block[0].second + idx] = 1;
	board[block[1].first][block[1].second + idx] = 1;
}

void block_move_to_greenZone(int t, int x, int y) {
	vii block;
	x = 0;
	if (t == 1) {
		block.push_back({ x,y }); block.push_back({ x,y });
	}
	else if (t == 2) {
		block.push_back({ x,y }); block.push_back({ x,y + 1 });
	}
	else {
		block.push_back({ x,y }); block.push_back({ x + 1,y });
	}
	int idx = 4;
	while (true) {
		if (!is_green_valid(block[0].first+idx, block[0].second, block[1].first+idx, block[1].second)) {
			idx--;
			break;
		}
		idx++;
	}
	board[block[0].first + idx][block[0].second] = 1;
	board[block[1].first + idx][block[1].second] = 1;
}

void erase_blueZone() {
	vi idx;
	for (int c = BLUE_COL_END; c >= BLUE_COL_START+2; c--) {
		int cnt = 0;
		for (int r = 0; r < 4; r++) {
			if (board[r][c])
				cnt++;
		}
		if (cnt == 4) {
			for (int r = 0; r < 4; r++)
				board[r][c] = 0;
			idx.push_back(c);
		}
	}

	answer += idx.size();	
	if (idx.size()) {
		for (int c = idx[0]; c >= BLUE_COL_START + idx.size(); c--) {
			for (int r = 0; r < 4; r++) {
				board[r][c] = board[r][c - idx.size()];
				board[r][c - idx.size()] = 0;
			}
		}
	}
	
	int specialCnt = 0;
	for (int c = 5; c >= 4; c--) {
		for (int r = 0; r < 4; r++) {
			if (board[r][c]) {
				specialCnt++;
				break;
			}
		}
	}
	if (!specialCnt)
		return;

	for (int c = BLUE_COL_END; c >= BLUE_COL_END - specialCnt + 1; c--) {
		for (int r = 0; r < 4; r++)
			board[r][c] = 0;
	}

	for (int c = BLUE_COL_END; c >= BLUE_COL_START + specialCnt; c--) {
		for (int r = 0; r < 4; r++) {
			board[r][c] = board[r][c - specialCnt];
			board[r][c - specialCnt] = 0;
		}
	}
	/*
	for (int c = BLUE_COL_START; c <= BLUE_COL_START + specialCnt - 1; c++) {
		for (int r = 0; r < 4; r++)
			board[r][c] = 0;
	}
	*/
}

void erase_greenZone() {
	vi idx;
	for (int r = GREEN_ROW_END; r >= GREEN_ROW_START + 2; r--) {
		int cnt = 0;
		for (int c = 0; c < 4; c++) {
			if (board[r][c])
				cnt++;
		}
		if (cnt == 4) {
			for (int c = 0; c < 4; c++)
				board[r][c] = 0;
			idx.push_back(r);
		}
	}

	answer += idx.size();
	if (idx.size()) {
		for (int r = idx[0]; r >= GREEN_ROW_START + idx.size(); r--) {
			for (int c = 0; c < 4; c++) {
				board[r][c] = board[r - idx.size()][c];
				board[r-idx.size()][c] = 0;
			}
		}
	}

	int specialCnt = 0;
	for (int r = 5; r >= 4; r--) {
		for (int c = 0; c < 4; c++) {
			if (board[r][c]) {
				specialCnt++;
				break;
			}
		}
	}
	if (!specialCnt)
		return;

	for (int r = GREEN_ROW_END; r >= GREEN_ROW_END - specialCnt + 1; r--) {
		for (int c = 0; c < 4; c++)
			board[r][c] = 0;
	}

	for (int r = GREEN_ROW_END; r >= GREEN_ROW_START + specialCnt; r--) {
		for (int c = 0; c < 4; c++) {
			board[r][c] = board[r-specialCnt][c];
			board[r - specialCnt][c] = 0;
		}
	}

	/*
	for (int r = GREEN_ROW_START; r <= GREEN_ROW_START + specialCnt - 1; r++) {
		for (int c = 0; c < 4; c++)
			board[r][c] = 0;
	}
	*/
}

int get_block() {
	int ans = 0;
	for (int r = 0; r < 4; r++) {
		for (int c = 4; c < 10; c++) {
			if (board[r][c])
				ans++;
		}
	}
	for (int r = 4; r < 10; r++) {
		for (int c = 0; c < 4; c++) {
			if (board[r][c])
				ans++;
		}
	}
	return ans;
}

void solve() {
	int blockType, x, y;
	while (N--) {
		cin >> blockType >> x >> y;
		block_move_to_blueZone(blockType,x,y);
		block_move_to_greenZone(blockType,x,y);
		print();
		erase_blueZone();
		erase_greenZone();
	}
	cout << answer << '\n';
	cout << get_block() << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
