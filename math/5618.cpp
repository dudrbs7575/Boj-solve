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

int N;
vector<int> v;
vector<int> num;
int maxVal;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int a;
	for (int i = 0; i < N; i++) {
		cin >> a;
		num.push_back(a);
		maxVal = max(maxVal, a);
	}
	
	for (int i = 1; i <= maxVal; i++) {
		int cnt = 0;
		for (auto nu : num) {
			if (nu % i == 0)
				cnt++;
		}
		if (cnt == N)
			v.push_back(i);
	}
	sort(v.begin(), v.end());
	for (auto a : v) {
		cout << a << '\n';
	}
	return 0;
}
