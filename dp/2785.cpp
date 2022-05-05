#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector < pair<int, int>>;
using vvi = vector<vector<int>>;
using tiii = tuple<int, int, int>;

#define INF 0x3f3f3f3f
#define MAX 2222

ll dp[MAX][20];
int T;
int N, M;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
}

ll go(int idx, int cnt) {
	if (cnt == N)
		return 1;
	if (idx > M)
		return 0;

	ll &ret = dp[idx][cnt];
	if (ret != -1)
		return ret;

	ret = 0;
	ret = go(idx*2,cnt+1)+go(idx+1,cnt);

	return ret;
}

void solve() {
	while (T--) {
		memset(dp, -1, sizeof(dp));
		cin >> N >> M;
		cout << go(1,0) << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}