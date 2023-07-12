#include <bits/stdc++.h>
using namespace std;

struct segment_tree {
private:
	int base, l, r, value;
	vector<int> sum;
	
	void propagate(int v, int len) {
		if (sum[v] == 0) {
			sum[v << 1] = sum[v << 1 ^ 1] = 0;
		}
		else if (sum[v] == len) {
			sum[v << 1] = sum[v << 1 ^ 1] = len >> 1;
		}
	}
	
	void update(int v) {
		sum[v] = sum[v << 1] + sum[v << 1 ^ 1];
	}
	
	void insert_rec(int v, int v_l, int v_r) {
		if (l <= v_l && v_r <= r) {
			sum[v] = value * (v_r - v_l + 1);
			return;
		}
		
		propagate(v, v_r - v_l + 1);
		
		int v_mid = (v_l + v_r) >> 1;
		if (l <= v_mid) {
			insert_rec(v << 1, v_l, v_mid);
		}
		if (v_mid < r) {
			insert_rec(v << 1 ^ 1, v_mid + 1, v_r);
		}
		
		update(v);
	}
	
	int query_rec(int v, int v_l, int v_r) {
		if (l <= v_l && v_r <= r) {
			return sum[v];
		}
		
		propagate(v, v_r - v_l + 1);
		
		int v_mid = (v_l + v_r) >> 1, result = 0;
		if (l <= v_mid) {
			result += query_rec(v << 1, v_l, v_mid);
		}
		if (v_mid < r) {
			result += query_rec(v << 1 ^ 1, v_mid + 1, v_r);
		}
		
		return result;
	}
	
public:
	segment_tree() {
		base = 0;
		sum.clear();
	}
	
	segment_tree(int n) {
		base = 1;
		while (base < n) {
			base <<= 1;
		}
		sum.clear();
		sum.resize(base << 1);
	}
	
	void insert(int _l, int _r, int _value) {
		l = _l;
		r = _r;
		value = _value;
		insert_rec(1, 0, base - 1);
	}
	
	int query(int _l, int _r) {
		l = _l;
		r = _r;
		return query_rec(1, 0, base - 1);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, q;
	cin >> n >> q;
	
	segment_tree tree(n + 1);
	
	while (q--) {
		int l, r, value = 1;
		char type;
		cin >> l >> r >> type;
		
		if (type == 'C') {
			value = 0;
		}
		tree.insert(l, r, value);
		
		cout << tree.query(1, n) << '\n';
	}
	
	return 0;
}