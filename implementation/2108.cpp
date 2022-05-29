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

#define INF 0x3f3f3f3f
int N;
int chk[8001];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

void solve() {
	int val;
	int minVal = INF;
	int maxVal = -INF;
	int most_frequency = -1;
	int sum = 0;
	vector<int> store;
	for (int i = 0; i < N; i++) {
		cin >> val;
		sum += val;
		if (val >= 0) {
			chk[val+4000]++;
			most_frequency = max(most_frequency, chk[val+4000]);
		}
		else {
			chk[-val]++;
			most_frequency = max(most_frequency, chk[-val]);
		}
		store.push_back(val);
		minVal = min(minVal, val);
		maxVal = max(maxVal, val);
	}
	sort(store.begin(), store.end());
	
	float avg = (float)sum / (float)N;
	round(avg) != 0 ? cout << round(avg) << '\n' : cout << 0 << '\n';
	cout << store[N / 2] << '\n';

	bool flag = false;
	int idx;
	int result_idx;
	for (int i = -4000; i <= 4000; i++) {
		if (i < 0)
			idx = -i;
		else
			idx = i + 4000;

		if (chk[idx] == most_frequency) {
			result_idx = i;
			if (flag)
				break;
			flag = true;
		}
	}
	cout << result_idx << '\n';
	cout << maxVal - minVal << '\n';
}

int main() {
	init();
	solve();
	return 0;
}