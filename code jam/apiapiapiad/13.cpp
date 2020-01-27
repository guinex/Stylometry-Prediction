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

const int N=10100;
int _,__,n,e[N],t[N],l[N],p[N];
VI f[N],g[N];
int cost(int x,int y) {
	if (x==-1) return l[y]+t[y];
	int r=l[y];
	while (r<l[x]+t[x]) r+=24;
	return r+t[y]-(l[x]+t[x]);
}
int find(int x) { return p[x]==x?x:p[x]=find(p[x]); }
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d",&n);
		rep(i,0,n) f[i].clear(),g[i].clear();
		rep(i,0,2*n) {
			scanf("%d%d%d",e+i,l+i,t+i),--e[i];
			f[e[i]].pb(i);
			g[i/2].pb(i);
			p[i]=i;
		}
		int ret=0;
		vector<VI> eg;
		rep(i,0,n) {
			int v1=cost(f[i][0],g[i][0])+cost(f[i][1],g[i][1]);
			int v2=cost(f[i][1],g[i][0])+cost(f[i][0],g[i][1]);
			if (i==0) {
				v1=min(cost(-1,g[i][0])+cost(f[i][1],g[i][1]),cost(f[i][0],g[i][0])+cost(-1,g[i][1]));
				v2=min(cost(-1,g[i][0])+cost(f[i][0],g[i][1]),cost(f[i][1],g[i][0])+cost(-1,g[i][1]));
			}
			ret+=min(v1,v2);
			if (v1<=v2) {
				p[find(f[i][0])]=find(g[i][0]);
				p[find(f[i][1])]=find(g[i][1]);
//				printf("%d %d %d %d %d\n",v1,f[i][0],g[i][0],f[i][1],g[i][1]);
				eg.pb(VI{v2-v1,f[i][0],f[i][1]});
			} else {
				p[find(f[i][0])]=find(g[i][1]);
				p[find(f[i][1])]=find(g[i][0]);
//				printf("%d %d %d %d %d\n",v2,f[i][0],g[i][1],f[i][1],g[i][0]);
				eg.pb(VI{v1-v2,f[i][0],f[i][1]});
			}
		}
		sort(eg.begin(),eg.end());
		rep(i,0,n) {
			int u=eg[i][1],v=eg[i][2];
			if (find(u)!=find(v)) {
				ret+=eg[i][0];
				p[find(u)]=find(v);
			}
		}
		printf("Case #%d: %d\n",++__,ret);
	}
}
