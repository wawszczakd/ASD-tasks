#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'000;

struct fenwick_tree {
private:
	int n;
	vector<int> sum;
	
public:
	fenwick_tree() {
		n = 0;
		sum.clear();
	}
	
	fenwick_tree(int _n) {
		n = _n;
		sum.clear();
		sum.resize(n + 1);
	}
	
	void add(int i, int value) {
		for (; i <= n; i = (i | (i - 1)) + 1) {
			sum[i] = (sum[i] + value) % MOD;
		}
	}
	
	int get(int l, int r) {
		int result = 0;
		for (; r > 0; r &= r - 1) {
			result = (result + sum[r]) % MOD;
		}
		for (l--; l > 0; l &= l - 1) {
			result = (result + MOD - sum[l]) % MOD;
		}
		return result;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k;
	cin >> n >> k;
	
	vector<fenwick_tree> dp(k, fenwick_tree(n));
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		dp[0].add(a, 1);
		for (int j = 0; j < k - 1; j++) {
			dp[j + 1].add(a, dp[j].get(a + 1, n));
		}
	}
	cout << dp[k - 1].get(1, n) << '\n';
	
	return 0;
}