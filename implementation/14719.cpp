#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 501

int H, W;
int arr[MAX];
int ans = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> H >> W;
	for (int i = 0; i < W; i++) 
		cin >> arr[i];
}

void solve() {
	if (W == 2) {
		cout << 0 << '\n';
		return;
	}
	for (int i = 1; i < W-1; i++) {
		int curHeight = arr[i];
		int leftMaxHeight = 0;
		int rightMaxHeight = 0;
		for (int j = i - 1; j >= 0; j--)
			leftMaxHeight = max(leftMaxHeight, arr[j]);
		for (int j = i + 1; j < W; j++)
			rightMaxHeight = max(rightMaxHeight, arr[j]);
		int gap = min(leftMaxHeight, rightMaxHeight) - curHeight;
		if (gap < 0)
			continue;
		ans += gap;
	}
	cout << ans << '\n';
}

int main() {
	init();
	solve();
	return 0;
}