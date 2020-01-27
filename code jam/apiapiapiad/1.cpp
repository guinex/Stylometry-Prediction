#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const int N=1010;
int _,__,k,n,g[N];
char s[N];
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%s",s)
		scanf("%d",&k)
		n=strlen(s)
		rep(i,0,n) g[i]=s[i]=='-';
		int t=0
		rep(i,0,n) if (i+k<=n&&g[i]) {
			t++
			rep(j,0,k) g[i+j]^=1;
		}
		bool val=0;
		rep(i,0,n) val|=g[i];
		printf("Case #%d: ",++__);
		if (val) puts("IMPOSSIBLE");
		else printf("%d\n",t);
	}
}
