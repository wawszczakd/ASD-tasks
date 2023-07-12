#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	string s;
	cin >> s;
	
	int result = s.size() - 1;
	vector<int> last_pos(256, -1);
	for (int i = 0; i < (int) s.size(); i++) {
		if (s[i] != '*') {
			last_pos[s[i]] = i;
			for (int j = 'A'; j <= 'Z'; j++) {
				if (j != s[i] && last_pos[j] != -1) {
					result = min(result, i - last_pos[j] - 1);
				}
			}
		}
	}
	
	cout << s.size() - result << '\n';
	
	return 0;
}