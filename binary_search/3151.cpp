#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <functional>
#include <string>
#include <stack>
#include <queue>

using namespace std;

int answer;
int arr[10010];
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr, arr + N);
}

void solve() {
	if (N <= 2)
		return;
	for (int i = 0; i <= N -3 ; i++) {
		for (int j = i + 1; j <= N - 2; j++) {
			int k = (-1) * (arr[i] + arr[j]);
			int s = lower_bound(arr + j + 1,arr+N, k) - arr;
			int e = upper_bound(arr + j + 1, arr + N, k) - arr;
			answer += (e - s);
		}
	}
}

int main(){
	init();
	solve();
	cout << answer << '\n';
	return 0;
}