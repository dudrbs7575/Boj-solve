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
using pii = pair<int, int>;

int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

void solve() {
	int i = N / 5;
	int answer = -1;
	for (; i >= 0; i--) {
		int tmp = N - i * 5;
		if (tmp % 3 == 0) {
			answer = i + (tmp / 3);
			break;
		}
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}