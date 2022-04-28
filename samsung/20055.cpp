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
#define MAX 222

int durability[MAX];
bool robot[MAX];

//�κ��� 1���� �ø��� N������ ����
//��Ʈ �κ��� �Բ� ȸ��
//���� ��Ʈ�� �ö� �κ����� ������ �� ĭ �̵�,������ ����
//�ø��� ��ġ ������ 0 �ƴϸ� �κ� �ø���, ������ 1 ����
//�������� 0�� ĭ�� ������ K�� �̻��̸� ���� ����

int N, K;
int len;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	len = 2 * N;
	for (int i = 1; i <= len; i++)
		cin >> durability[i];
}

bool is_zero_k() {
	int cnt = 0;
	for (int i = 1; i <= len; i++) {
		if (!durability[i])
			cnt++;
	}
	if (cnt >= K)
		return true;
	return false;
}

void rounding() {
	int tmp = durability[len];
	bool tmp2 = robot[len];
	for (int i = len; i >= 2; i--) {
		durability[i] = durability[i - 1];
		robot[i] = robot[i - 1];
	}
	if (robot[N])
		robot[N] = false;	//�κ� ������
	durability[1] = tmp;
	robot[1] = tmp2;
}

void move_robot() {
	for (int i = N-1; i >= 1; i--) {
		if (!robot[i])
			continue;
		if (durability[i+1] && !robot[i+1]) {	//�������� 1�̻�, robot�� ����X
			robot[i + 1] = true;
			durability[i+1] -= 1;
			robot[i] = false;
		}
	}
	if (robot[N])
		robot[N] = false;
}

void put_robot() {
	if (!robot[1] && durability[1]) {
		robot[1] = true;
		durability[1] -= 1;
	}
}

void print() {
	cout << '\n';
	for (int i = 1; i <= len; i++)
		cout << durability[i] << " ";
	cout << '\n';
	for (int i = 1; i <= len; i++)
		cout << robot[i] << " ";
}

void solve() {
	int cnt = 1;
	while (true) {
		rounding();
		move_robot();
		put_robot();
		if (is_zero_k())
			break;
		cnt++;
	}
	cout << cnt << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
