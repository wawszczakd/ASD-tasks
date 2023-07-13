#include <bits/stdc++.h>
using namespace std;

struct KMR {
private:
	string s;
	vector<vector<int>> rows;
	
	vector<int> count_sort(const vector<pair<int, int>> &pairs, const vector<int> &order, bool by_first) { 
		int max_value = 0;
		for (auto [first, second] : pairs) {
			max_value = max(max_value, (by_first ? first : second) + 1);
		}
		
		vector<int> count(max_value);
		for (auto [first, second] : pairs) {
			count[by_first ? first : second]++;
		}
		for (int i = 1; i < max_value; i++) {
			count[i] += count[i - 1];
		}
		
		vector<int> new_order(order.size());
		for (int i = order.size() - 1; i >= 0; i--) {
			new_order[--count[by_first ? pairs[order[i]].first : pairs[order[i]].second]] = order[i];
		}
		return new_order;
	}
	
	vector<int> radix_sort(const vector<pair<int, int>> &pairs) {
		vector<int> order(pairs.size());
		iota(order.begin(), order.end(), 0);
		
		order = count_sort(pairs, order, false);
		order = count_sort(pairs, order, true);
		
		return order;
	}
	
	void build() {
		vector<int> scale_chars(256);
		for (auto c : s) {
			scale_chars[c] = 1;
		}
		for (int i = 0, last = 0; i < 256; i++) {
			if (scale_chars[i] == 1) {
				scale_chars[i] = last++;
			}
		}
		
		rows.resize(__lg(s.size()) + 1);
		rows[0].resize(s.size());
		for (int i = 0; i < (int) s.size(); i++) {
			rows[0][i] = scale_chars[s[i]];
		}
		
		for (int row = 1; row < (int) rows.size(); row++) {
			vector<pair<int, int>> pairs(s.size() + 1 - (1 << row));
			for (int i = 0; i < (int) s.size() + 1 - (1 << row); i++) {
				pairs[i] = make_pair(rows[row - 1][i], rows[row - 1][i + (1 << (row - 1))]);
			}
			
			vector<int> order = radix_sort(pairs);
			
			rows[row].resize(s.size() + 1 - (1 << row));
			for (int i = 0, last = 0; i < (int) order.size(); i++) {
				if (i > 0 && pairs[order[i]] != pairs[order[i - 1]]) {
					last++;
				}
				rows[row][order[i]] = last;
			}
		}
	}
	
public:
	KMR(string _s) {
		s = _s;
		rows.clear();
		build();
	}
	
	pair<int, int> query(int l, int r) {
		int len = r + 1 - l;
		return make_pair(rows[__lg(len)][l], rows[__lg(len)][r + 1 - (1 << __lg(len))]);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, q;
	string s;
	cin >> n >> q >> s;
	
	KMR kmr(s);
	
	while (q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--; b--; c--; d--;
		
		int len1 = b + 1 - a, len2 = d + 1 - c;
		int len = min(len1, len2);
		pair<int, int> x = kmr.query(a, a + len - 1), y = kmr.query(c, c + len - 1);
		if (x < y) {
			cout << "<\n";
		}
		else if (x > y) {
			cout << ">\n";
		}
		else {
			if (len1 < len2) {
				cout << "<\n";
			}
			else if (len1 > len2) {
				cout << ">\n";
			}
			else {
				cout << "=\n";
			}
		}
	}
	
	return 0;
}
