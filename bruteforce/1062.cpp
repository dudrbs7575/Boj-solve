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

int N, K;
vector<string> v;
bool chk[26];
int answer;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	string s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		v.push_back(s);
	}
	chk['a' - 'a'] = chk['c' - 'a'] = chk['i' - 'a'] = chk['n' - 'a'] = chk['t' - 'a'] = true;
}

int get_ans() {
	int ret = 0;
	for (int i = 0; i < v.size(); i++) {
		string s = v[i];
		int len = s.length();
		int cnt = 0;
		for (int j = 0; j < len; j++) {
			if (chk[s[j] - 'a'])
				cnt++;
		}
		if (len == cnt)
			ret++;
	}
	return ret;
}

void dfs(int idx, int cnt) {
	if (cnt == K) {
		answer = max(answer, get_ans());
		return;
	}
	for (int i = idx; i < 26; i++) {
		if (chk[i])
			continue;
		chk[i] = true;
		dfs(i + 1, cnt + 1);
		chk[i] = false;
	}
}

void solve() {
	string tmp;
	if (K < 5) {
		cout << 0 << '\n';
		return;
	}
	for (int i = 0; i < v.size(); i++) {
		tmp = v[i];
		int len = tmp.length();
		if (len < 8) {
			cout << 0 << '\n';
			return;
		}
		int idx = tmp.find("anta");
		int idx2 = tmp.find("tica", len - 4);
		if (idx == -1 || idx2 == -1) {
			cout << 0 << '\n';
			return;
		}
		tmp.erase(len-4, 4);
		tmp.erase(0, 4);
		v[i] = tmp;
	}
	K -= 5;
	dfs(0, 0);
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}