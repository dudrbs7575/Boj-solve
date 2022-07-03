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
using ll = long long;

int N;
int maxVal = -1;
int minVal = 0x3f3f3f3f;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int val;
	for (int i = 0; i < N; i++) {
		cin >> val;
		maxVal = max(maxVal, val);
		minVal = min(minVal, val);
	}
	cout << minVal << " " << maxVal << '\n';
}

int main() {
	init();
	return 0;
}