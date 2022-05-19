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

using namespace std;
using pii = pair<int, int>;

int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

bool is_valid(int k) {
	if (k <= 1)
		return false;
	for (int i = 2; i <= sqrt(k); i++) {
		if (k % i == 0)
			return false;
	}
	return true;
}

void solve() {
	int k;
	int answer = 0;
	while (N--) {
		cin >> k;
		if (is_valid(k))
			answer++;
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}