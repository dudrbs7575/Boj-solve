#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

int answer = 0;
int board[12][12];
int chk_i[12];	//������ � �����ǿ� ��Ī�Ǵ���.
bool chk_j[12];
int C;

int get_ans() {
	int let = 0;
	for (int i = 1; i <= 11; i++) {
		let += board[i][chk_i[i]];
	}
	return let;
}

void dfs(int idx,int cnt,int sum) {
	if (cnt == 11) {
		answer = max(answer, sum);
		return;
	}
	for (int i = idx; i <= 11; i++) {	//���� ����
		int tmp = 0;
		for (int j = 1; j <= 11; j++) {	//������ ����
			if (tmp == 5)
				return;
			if (chk_i[i]!=0)	//������ �������� �Ҵ� �޾��� ��
				break;
			if (board[i][j] == 0)	//������ �ش� �������� ������ 0�϶�
				continue;
			if (chk_j[j]==true)		//�������� �Ҵ���� ��
				continue;
			if (j == 11 && board[i][j] == 0)	//������ ������ �Ҵ��� ������ �� �޾��� ��
				return;
			chk_i[i] = j;
			chk_j[j] = true;
			tmp++;
			dfs(idx+1,cnt + 1,sum+board[i][j]);
			chk_i[i] = 0;
			chk_j[j] = false;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> C;
	while (C--) {
		memset(chk_i, 0, sizeof(chk_i));
		memset(chk_j, 0, sizeof(chk_j));
		answer = 0;
		for (int i = 1; i < 12; i++) {
			for (int j = 1; j < 12; j++) {
				cin >> board[i][j];
			}
		}
		dfs(1,0,0);
		cout << answer << '\n';
	}
}