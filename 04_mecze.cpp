#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;
	
	vector<long long> bit_masks(n + 1);
	for (int bit = 0; bit < m; bit++) {
		for (int i = 0; i < n / 2; i++) {
			int a;
			cin >> a;
		}
		for (int i = 0; i < n / 2; i++) {
			int a;
			cin >> a;
			bit_masks[a] |= 1ll << bit;
		}
	}
	
	sort(bit_masks.begin() + 1, bit_masks.end());
	
	bool result = true;
	for (int i = 2; i <= n; i++) {
		if (bit_masks[i] == bit_masks[i - 1]) {
			result = false;
			break;
		}
	}
	cout << (result ? "TAK" : "NIE") << '\n';
	
	return 0;
}