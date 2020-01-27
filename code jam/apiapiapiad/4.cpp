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

const int inf=0x20202020;
typedef int flowt;
namespace flow {
	const int M=1000000,N=100000;
	int y[M],gap[N] fst[N],c[N],pre[N],q[N],dis[N];
	flowt f[M];
	int S,T,tot,Tn;
	void init(int s,int t,int tn) {
		tot=1; assert(tn<N);
		rep(i,0,tn) fst[i]=0;
		S=s;T=t;Tn=tn;
	
	int add(int u,int v,flowt c1,flowt c2=0) {
		tot++;y[tot]=v;f[tot]=c1;nxt[tot]=fst[u];fst[u]=tot;
		tot++;y[tot]=u;f[tot]=c2;nxt[tot]=fst[v];fst[v]=tot;
		return tot;
	}
	flowt sap() {
		int u=S,t=1;flowt flow=0;
		rep(i,0,Tn) c[i]=fst[i],dis[i]=Tn,gap[i]=0;
		q[0]=T;dis[T]=0;pre[S]=0;
		rep(i,0,t) {
			int u=q[i];
			for (int j=fst[u];j;j=nxt[j]) if (dis[y[j]]>dis[u]+1&&f[j^1]) 
				q[t++]=y[j],dis[y[j]]=dis[u]+1;
		}
		rep(i,0,Tn) gap[dis[i]]++;
		while (dis[S]<=Tn) {
			while (c[u]&&(!f[c[u]]||dis[y[c[u]]]+1!=dis[u])) c[u]=nxt[c[u]];
			if (c[u]) {
				pre[y[c[u]]]=c[u]^1;
				u=y[c[u]];
				if (u==T) {
					flowt minf=inf;
					for (int p=pre[T];p;p=pre[y[p]]) minf=min(minf,f[p^1]);
					for (int p=pre[T];p;p=pre[y[p]]) f[p^1]-=minf,f[p]+=minf;
					flow+=minf;u=S;
				}
			} else {
				if (!(--gap[dis[u]])) break;
				int mind=Tn;
				c[u]=fst[u];
				for (int j=fst[u];j;j=nxt[j]) if (f[j]&&dis[y[j]]<mind) 
					mind=dis[y[j]],c[u]=j;
				dis[u]=mind+1;
				gap[dis[u]]++;
				if (u!=S) u=y[pre[u]];
			}
		}
		return flow;
	


const int N=110,M=101000;
int _,__,n,m,r,c;
int vx[N][N],vp[N][N],row[N],col[N],dia[N*2],aid[N*2],vis[M],Ex[N][N],Ep[N][N];
char op[10];
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d%d",&n,&m);
		int id=0;
		rep(i,0,n) rep(j,0,n) vx[i][j]=vp[i][j]=0;
		rep(i,0,n) row[i]=id++;
		rep(i,0,n) col[i]=id++;
		rep(i,0,2*n-1) dia[i]=id++;
		rep(i,0,2*n-1) aid[i]=id++;
		rep(i,0,id) vis[i]=0;
		int ret=0;
		rep(i,0,m) {
			scanf("%s%d%d",op,&r,&c);
			r--; c--;
			if (op[0]=='x'||op[0]=='o') vis[row[r]]=vis[col[c]]=1,ret+=1,vx[r][c]=1;
			if (op[0]=='+'||op[0]=='o') vis[dia[r+c]]=vis[aid[r-c+n-1]]=1,ret+=1,vp[r][c]=1;
		}
		flow::init(id,id+1,id+2);
		rep(i,0,n) rep(j,0,n) {
			if (!vis[row[i]]&&!vis[col[j]]) Ex[i][j]=flow::add(row[i],col[j],1); else Ex[i][j]=0;
			if (!vis[dia[i+j]]&&!vis[aid[i-j+n-1]]) Ep[i][j]=flow::add(dia[i+j],aid[i-j+n-1],1); else Ep[i][j]=0;
		}
		rep(i,0,n) {
			if (!vis[row[i]]) flow::add(id,row[i],1);
			if (!vis[col[i]]) flow::add(col[i],id+1,1);
		}
		rep(i,0,2*n-1) {
			if (!vis[dia[i]]) flow::add(id,dia[i],1);
			if (!vis[aid[i]]) flow::add(aid[i],id+1,1);
		}
		ret+=flow::sap();
		vector<pair<char,PII>> way;
		rep(i,0,n) rep(j,0,n) {
			if (flow::f[Ex[i][j]]||flow::f[Ep[i][j]]) {
				vx[i][j]|=flow::f[Ex[i][j]];
				vp[i][j]|=flow::f[Ep[i][j]];
				if (vx[i][j]&&vp[i][j]) way.pb(mp('o',mp(i+1,j+1)));
				else if (vx[i][j]) way.pb(mp('x',mp(i+1,j+1)));
				else if (vp[i][j]) way.pb(mp('+',mp(i+1,j+1)));
				else assert(0);
			}
		}
		printf("Case #%d: %d %d\n",++__,ret,SZ(way));
		for (auto p:way) printf("%c %d %d\n",p.fi,p.se.fi,p.se.se);
	}
}
