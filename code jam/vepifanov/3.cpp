#include <cstdio>
#include <numeric>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <queue>
#include <sstream>
#include <deque>
#include <cassert>

using namespace std;

#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); i++)
#define re return
#define fi first
#define se second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define y0 y3487465
#define y1 y8687969
#define fill(x,y) memset(x,y,sizeof(x))
#define prev PREV
                         
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef double D;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vi> vvi;

template<class T> T abs(T x) { re x > 0 ? x : -x; }

int n;
int m;
string s[25];
int g[30][30];

int calc (int i1, int j1, int i2, int j2) {
	re g[i1][j1] - g[i2][j1] - g[i1][j2] + g[i2][j2];
}

int go (int i1, int j1, int i2, int j2) {
	if (calc (i1, j1, i2, j2) == 1) {
		char c = 0;
		for (int i = i1; i < i2; i++)
			for (int j = j1; j < j2; j++)
				if (s[i][j] != '?')
					c = s[i][j];
		for (int i = i1; i < i2; i++)
			for (int j = j1; j < j2; j++) {
				assert (s[i][j] == '?' || s[i][j] == c);
				s[i][j] = c;
			}
		re 0;
	}
	for (int k = i1 + 1; k < i2; k++)
		if (calc (i1, j1, k, j2) > 0 && calc (k, j1, i2, j2) > 0) {
			go (i1, j1, k, j2);
			go (k, j1, i2, j2);
			re 0;
		}
	for (int k = j1 + 1; k < j2; k++)
		if (calc (i1, j1, i2, k) > 0 && calc (i1, k, i2, j2) > 0) {
			go (i1, j1, i2, k);
			go (i1, k, i2, j2);
			re 0;
		}
	assert (false);
	re 0;
}

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) cin >> s[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				g[i][j] = 0;
				g[i][j] = int (s[i][j] != '?');
			}
		for (int i = n - 1; i >= 0; i--)	
			for (int j = m - 1; j >= 0; j--)
				g[i][j] += g[i + 1][j] + g[i][j + 1] - g[i + 1][j + 1];
		go (0, 0, n, m);
		cout << "Case #" << it << ": " << endl;
		for (int i = 0; i < n; i++) cout << s[i] << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}