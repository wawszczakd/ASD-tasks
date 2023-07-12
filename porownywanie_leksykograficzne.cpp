#include <bits/stdc++.h>
using namespace std;

struct KMR {
private:
	string s;
	vector<vector<int>> rows;
	
	vector<int> bucket_sort(const vector<pair<int, int>> &vec) {
		int m1 = 0, m2 = 0;
		for (int i = 0; i < (int) vec.size(); i++) {
			m1 = max(m1, vec[i].first + 1);
			m2 = max(m2, vec[i].second + 1);
		}
		
		vector<vector<int>> buckets1(m1), buckets2(m2);
		for (int i = 0; i < (int) vec.size(); i++) {
			buckets2[vec[i].second].emplace_back(i);
		}
		for (int i = 0; i < m2; i++) {
			for (int x: buckets2[i]) {
				buckets1[vec[x].first].emplace_back(x);
			}
		}
		
		vector<int> result(vec.size());
		for (int i = 0, last = -1; i < m1; i++) {
			for (int j = 0; j < (int) buckets1[i].size(); j++) {
				if (j == 0 || vec[buckets1[i][j - 1]].second != vec[buckets1[i][j]].second) {
					last++;
				}
				result[buckets1[i][j]] = last;
			}
		}
		
		return result;
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
			rows[row] = bucket_sort(pairs);
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