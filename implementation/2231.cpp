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

queue<int> qu;
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

bool is_valid(int k) {
	int sum = k;
	while (k) {
		sum += k % 10;
		k /= 10;
	}
	if (sum == N)
		return true;
	return false;
}

void solve() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		if (is_valid(i)) {
			answer = i;
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