#include <bits/stdc++.h>
using namespace std;

class segment_tree {
private:
	int base;
	vector<int> minn;
	
public:
	segment_tree() {
		base = 0;
		minn.clear();
	}
	
	segment_tree(int n) {
		base = 1;
		while (base < n) {
			base <<= 1;
		}
		
		minn.clear();
		minn.resize(base << 1, INT_MAX);
	}
	
	void insert(int i, int value) {
		i += base;
		minn[i] = value;
		for (i >>= 1; i > 0; i >>= 1) {
			minn[i] = min(minn[i << 1], minn[i << 1 ^ 1]);
		}
	}
	
	int query(int l, int r) {
		int result = INT_MAX;
		for (l += base, r += base + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
				result = min(result, minn[l++]);
			}
			if (r & 1) {
				result = min(result, minn[--r]);
			}
		}
		return result;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, q;
	cin >> n >> q;
	
	segment_tree tree(n);
	for (int i = 0; i < n; i++) {
		int z;
		cin >> z;
		tree.insert(i, z);
	}
	
	while (q--) {
		long long c;
		cin >> c;
		
		int low = 0, high = n - 1;
		while (low < high) {
			int mid = (low + high) >> 1;
			
			long long sum = 0;
			for (int i = 0; i < n; i++) {
				sum += tree.query(max(0, i - mid), min(n - 1, i + mid));
			}
			
			if (sum <= c) {
				high = mid;
			}
			else {
				low = mid + 1;
			}
		}
		cout << high << '\n';
	}
	
	return 0;
}