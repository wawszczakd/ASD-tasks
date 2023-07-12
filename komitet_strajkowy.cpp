#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'007, INF = 500'000;

struct segment_tree {
private:
	int base;
	vector<int> min_size, ways;
	
public:
	segment_tree() {
		base = 0;
		min_size.clear();
		ways.clear();
	}
	
	segment_tree(int n) {
		base = 1;
		while (base < n) {
			base <<= 1;
		}
		min_size.clear();
		min_size.resize(base << 1, INF);
		ways.clear();
		ways.resize(base << 1, 0);
	}
	
	void insert(int i, int x, int y) {
		i += base;
		min_size[i] = x;
		ways[i] = y;
		for (i >>= 1; i > 0; i >>= 1) {
			if (min_size[i << 1] < min_size[i << 1 ^ 1]) {
				min_size[i] = min_size[i << 1];
				ways[i] = ways[i << 1];
			}
			else if (min_size[i << 1] > min_size[i << 1 ^ 1]) {
				min_size[i] = min_size[i << 1 ^ 1];
				ways[i] = ways[i << 1 ^ 1];
			}
			else {
				min_size[i] = min_size[i << 1];
				ways[i] = (ways[i << 1] + ways[i << 1 ^ 1]) % MOD;
			}
		}
	}
	
	pair<int, int> query(int l, int r) {
		pair<int, int> result = make_pair(INF, 0);
		for (l += base, r += base + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
				if (min_size[l] < result.first) {
					result = make_pair(min_size[l], ways[l]);
				}
				else if (min_size[l] == result.first) {
					result.second = (result.second + ways[l]) % MOD;
				}
				l++;
			}
			if (r & 1) {
				r--;
				if (min_size[r] < result.first) {
					result = make_pair(min_size[r], ways[r]);
				}
				else if (min_size[r] == result.first) {
					result.second = (result.second + ways[r]) % MOD;
				}
			}
		}
		return result;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k, l;
	cin >> n >> k >> l;
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	
	segment_tree tree(n);
	for (int i = 0; i < n; i++) {
		if (a[i] - a[0] <= k) {
			tree.insert(i, 1, 1);
		}
		else if (a[i] - a[0] >= l) {
			int left = lower_bound(a.begin(), a.end(), a[i] - k) - a.begin();
			if (left > 0) {
				left = lower_bound(a.begin(), a.end(), a[left - 1] - k) - a.begin();
			}
			
			int right = prev(upper_bound(a.begin(), a.end(), a[i] - l)) - a.begin();
			if (right == i) {
				right--;
			}
			
			if (left <= right) {
				auto [x, y] = tree.query(left, right);
				tree.insert(i, x + 1, y);
			}
		}
	}
	
	int last_pos = lower_bound(a.begin(), a.end(), a[n - 1] - k) - a.begin();
	auto [x, y] = tree.query(last_pos, n - 1);
	cout << x << ' ' << y << '\n';
	
	return 0;
}