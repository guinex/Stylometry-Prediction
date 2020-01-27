#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
	string num;
	cin >> num;
	char lo = '0';
	rep(i,0,sz(num)) {
		if (lo > num[i]) {
			for (int j = i-1; j >= 0; --j) {
				if (j == 0 || num[j] > num[j-1]) {
					num[j]--;
					rep(k,j+1,sz(num)) num[k] = '9';
					break;
				}
			}
			break;
		}
		else {
			lo = num[i];
		}
	}
	while (num[0] == '0') num.erase(num.begin());
	cout << num << endl;
}

int main() {
	cin.sync_with_stdio(false);
	cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
	cin.tie(0);
	int T;
	cin >> T;
	rep(i,0,T) {
		cout << "Case #" << i+1 << ": ";
		solve();
	}
}
