#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>
#include <sstream>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 10000010

int A, B, C, M;
int answer = 0;
int pirodo = 0;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> A >> B >> C >> M;
	if (A > M) {
		cout << 0 << '\n';
		return 0;
	}
	int time = 24;
	while (time--) {
		if (pirodo + A > M) {
			pirodo -= C;
			if (pirodo < 0)
				pirodo = 0;
			continue;
		}
		answer += B;
		pirodo += A;
	}
	cout << answer << '\n';
	return 0;
}
