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

const int N=10010;
int _,__,n,m,u,v,vis[N],mark[N],pe[N],f[N],ins[N];
vector<PII> e[N];
PII E[N],mE[N];
void dfs(int u,int fe) {
	vis[u]=1; ins[u]=1;
	for (auto p:e[u]) {
		if (p.se==fe) continue;
		int v=p.fi;
		if (!vis[v]) {
			pe[v]=p.se; f[v]=u;
			dfs(v,p.se);
			mE[p.se]=mp(u,v);
		} else if (ins[v]) {
//			printf("%d %d %d %d\n",u,v,p.se,ins[v]);
			int x=u;
			mE[p.se]=mp(u,v); mark[p.se]=1;
			while (1) {
				mark[pe[x]]++;
				x=f[x];
				if (x==v) break;
			}
		}
	}
	ins[u]=0;
}
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d%d",&n,&m);
		rep(i,1,n+1) e[i].clear();
		rep(i,0,m) {
			scanf("%d%d",&u,&v);
			e[u].pb(mp(v,i));
			e[v].pb(mp(u,i));
			E[i]=mp(u,v);
			mark[i]=0;
		}
		rep(i,1,n+1) vis[i]=0;
		rep(i,1,n+1) if (!vis[i]) dfs(i,-1);
		bool valid=1;
		rep(i,0,m) {
			if (E[i]!=mE[i]) mark[i]*=-1;
			if (mark[i]==0) valid=0;
		}
		printf("Case #%d: ",++__);
		if (!valid) puts("IMPOSSIBLE");
		else {
			rep(i,0,m) printf("%d ",mark[i]); puts("");
		}

	}
}
