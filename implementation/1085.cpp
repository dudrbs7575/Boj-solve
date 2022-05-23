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

int x, y, w, h;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> x >> y >> w >> h;
}

void solve() {
	cout << min({ abs(x - w),abs(y - h),x,y }) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}