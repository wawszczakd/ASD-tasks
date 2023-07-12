#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	
	vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2)));
	for (int i = 0; i < n; i++) {
		dp[i][i][0] = 1;
	}
	for (int len = 2; len <= n; len++) {
		for (int l = 0; l <= n - len; l++) {
			int r = l + len - 1;
			
			if (a[l] < a[l + 1]) {
				dp[l][r][0] += dp[l + 1][r][0];
			}
			if (a[l] < a[r]) {
				dp[l][r][0] += dp[l + 1][r][1];
			}
			dp[l][r][0] %= MOD;
			
			if (a[r] > a[r - 1]) {
				dp[l][r][1] += dp[l][r - 1][1];
			}
			if (a[r] > a[l]) {
				dp[l][r][1] += dp[l][r - 1][0];
			}
			dp[l][r][1] %= MOD;
		}
	}
	cout << (dp[0][n - 1][0] + dp[0][n - 1][1]) % MOD << '\n';
	
	return 0;
}