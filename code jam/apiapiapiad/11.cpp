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

int _,__,ret,L,fac[110];
set<VI> hs;
char s[110];
void dfs(VI v);
void dfs2(int d,VI a,VI b) {
	if (d==L) {
		dfs(b);
	} else {
		rep(i,0,L+1) if (a[i]) {
			a[i]-=1; b[d]=i;
			dfs2(d+1,a,b);
			a[i]+=1;
		}
	}
}
void dfs(VI v) {
	if (hs.count(v)) return;
	hs.insert(v);
//	for (auto p:v) printf("%d",p); puts("");
	int ds=0,cs=0;
	rep(i,0,L) ds+=v[i],cs+=i*v[i];
	ret+=1;
	if (ds>L) return;
	VI w=v; w.insert(w.begin(),L-ds);
	if (cs>L) {
		int way=fac[L];
		rep(i,0,L+1) way/=fac[w[i]];
		ret+=way;
		return;
	}
	dfs2(0,w,VI(L,0));
}
int main() {
	fac[0]=1;
	rep(i,1,11) fac[i]=fac[i-1]*i;
	for (scanf("%d",&_);_;_--) {
		scanf("%s",s);
		L=strlen(s);
		VI v;
		rep(i,0,L) v.pb(s[i]-'0');
		hs.clear();
		ret=0;
		dfs(v);
		printf("Case #%d: %d\n",++__,ret);
		fprintf(stderr,"Case #%d: %d\n",__,ret);
	}
}
