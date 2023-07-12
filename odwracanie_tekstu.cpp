#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, q;
	string s;
	cin >> n >> q >> s;
	
	vector<pair<int, int>> queries(q);
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		queries[i] = make_pair(l - 1, r - 1);
	}
	sort(queries.begin(), queries.end());
	
	for (int i = 0; i < q; i++) {
		auto [l, r] = queries[i];
		int bound;
		if (i == q - 1 || r < queries[i + 1].first) {
			bound = (l + r) / 2 + 1;
		}
		else {
			bound = queries[i + 1].first;
			i++;
		}
		for (int j = l; j < bound; j++) {
			swap(s[j], s[l + r - j]);
		}
	}
	
	cout << s << '\n';
	
	return 0;
}