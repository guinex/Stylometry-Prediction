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

const int inf = 2e6;

int n;
int m;

vii v[50];
int x[50];

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)	{
			cin >> x[i];
			v[i].clear ();
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				int y;
				cin >> y;
				int a, b;
				{
					int l = 0, r = inf;
					while (r - l > 1) {
						int s = (l + r) / 2;
						if ((ll)s * x[i] * 9 <= y * 10) l = s; else r = s;
					}
					b = l;
				}
				{
					int l = 0, r = inf;
					while (r - l > 1) {
						int s = (l + r) / 2;
						if ((ll)s * x[i] * 11 >= y * 10) r = s; else l = s;
					}
					a = r;
				}
//				printf ("%d %d = %d %d\n", i, j, a, b);
				if (a <= b) v[i].pb (mp (a, b));
			}
		for (int i = 0; i < n; i++) sort (all (v[i]));
		int ans = 0;
		while (true) {
			int last = inf;
			for (int i = 0; i < n; i++)
				if (v[i].empty ())
					last = -1;
				else
					last = min (last, v[i][0].se);	
			if (last == -1) break;
			int ok = 1;
			for (int i = 0; i < n; i++)
				if (v[i][0].fi > last)
					ok = 0;
			if (ok) {
				ans++;
				for (int i = 0; i < n; i++) v[i].erase (v[i].begin ());
			} else {
				for (int i = 0; i < n; i++) 
					if (v[i][0].se == last)
						v[i].erase (v[i].begin ());
			}
		}
		cout << "Case #" << it << ": " << ans;
		cout << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}