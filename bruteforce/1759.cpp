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

char aeiou[] = { 'a','e','i','o','u' };
int L, C;
vector<char> v;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> L >> C;
	char password;
	for (int i = 0; i < C; i++) {
		cin >> password;
		v.push_back(password);
	}
}

bool is_valid(string &ans) {
	int consonantCnt = 0;
	int vowelCnt = 0;//¸ðÀ½
	for (int i = 0; i < ans.length(); i++) {
		bool flag = false;
		for (int j = 0; j < 5; j++) {
			if (ans[i] == aeiou[j]) {
				flag = true;
				vowelCnt++;
				break;
			}
		}
		if (!flag)
			consonantCnt++;
	}
	if (vowelCnt >= 1 && consonantCnt >= 2)
		return true;
	return false;
}

void dfs(int idx, int cnt,string ans) {
	if (cnt == L) {
		if(is_valid(ans))
			cout << ans << '\n';
		return;
	}
	for (int i = idx; i < C; i++) 
		dfs(i + 1, cnt + 1, ans + v[i]);
}

void solve() {
	sort(v.begin(), v.end());
	dfs(0, 0, "");
}

int main() {
	init();
	solve();
	return 0;
}