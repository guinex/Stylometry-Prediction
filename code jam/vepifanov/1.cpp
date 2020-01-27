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
int v[4];
int was[101][101][101][4];
int res[101][101][101][4];
int ct = 0;

int go (int cur) {
	cur %= m;
	if (v[1] + v[2] + v[3] == 0) re 0;
	if (was[v[1]][v[2]][v[3]][cur] == ct) re res[v[1]][v[2]][v[3]][cur];
	was[v[1]][v[2]][v[3]][cur] = ct;
	int ans = 0;
	if (v[1] > 0) {
		v[1]--;
		ans = max (ans, go (cur + 1));
		v[1]++;
	}	
	if (v[2] > 0) {
		v[2]--;
		ans = max (ans, go (cur + 2));
		v[2]++;
	}	
	if (v[3] > 0) {
		v[3]--;
		ans = max (ans, go (cur + 3));
		v[3]++;
	}
	ans += int (cur == 0);
	re res[v[1]][v[2]][v[3]][cur] = ans;
}

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> n >> m;
		memset (v, 0, sizeof (v));
		for (int i = 0; i < n; i++) {
			int x;
			scanf ("%d", &x);
			v[x % m]++;
		}
		ct++;
		cout << "Case #" << it << ": " << v[0] + go (0);
		cout << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}