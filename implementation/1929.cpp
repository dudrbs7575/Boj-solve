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

int M, N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> M >> N;
}

bool is_prime(int k) {
	if (k == 1)
		return false;
	for (int i = 2; i <= sqrt(k); i++) {
		if (k % i == 0)
			return false;
	}
	return true;
}

void solve() {
	for (int i = M; i <= N; i++) {
		if (is_prime(i))
			cout << i << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}