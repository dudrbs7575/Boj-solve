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

int A, B, V;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> A >> B >> V;
}

void solve() {
	int answer = 1;
	(V - A) % (A - B) ? answer += (V - A) / (A - B) + 1 : answer += (V - A) / (A - B);
	(A == V) ? cout << 1 << '\n' : cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}