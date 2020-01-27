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

const int N=110;
int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int go[N][N][5],sel[N];
int _,__,id,rec[N][N],n,m;
char s[N][N];
int dfs(int x,int y,int dir) {
	if (go[x][y][dir]==-3) {
		return go[x][y][dir]=-1;
	}
	if (s[x][y]=='#') return go[x][y][dir]=-1;
	if (x<=0||x>n||y<=0||y>m) return go[x][y][dir]=-1;
	if (go[x][y][dir]!=-2) { return go[x][y][dir];}
	go[x][y][dir]=-3;
	if (rec[x][y]) return go[x][y][dir]=2*(rec[x][y]-1)+(dir%2);
	if (s[x][y]=='.') return go[x][y][dir]=dfs(x+dx[dir],y+dy[dir],dir);
	if (s[x][y]=='/') return go[x][y][dir]=dfs(x+dx[dir^3],y+dy[dir^3],dir^3);
	if (s[x][y]=='\\') return go[x][y][dir]=dfs(x+dx[dir^1],y+dy[dir^1],dir^1);
	assert(0);
	return 0;
}
namespace sat2 {
	const int N=2200;
	VI e[N];
	int n,cnt,dfn[N],low[N],st[N],bel[N],top,ind;
	bool ins[N];
	void init(int ct) {
		n=ct;
		cnt=0;top=0;ind=0;
		rep(i,0,n) e[i].clear();
	}  
	void add(int u,int v) { e[u].pb(v); } //printf("ee %d %d\n",u,v); }
	void tarjan(int u) {
		dfn[u]=low[u]=++ind;
		ins[u]=1;
		st[++top]=u;
		rep(i,0,SZ(e[u])) {
			int v=e[u][i];
			if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
			else if (ins[v]) low[u]=min(low[u],low[v]);
		} 
		if (dfn[u]==low[u]) {
			++cnt;
			while (1) {
				bel[st[top]]=cnt;
				ins[st[top]]=0;
				if (st[top--]==u) break;
			}
		}
	}
	bool solve() {
		rep(i,0,n) dfn[i]=0;
		rep(i,0,n) if (!dfn[i]) tarjan(i);
		rep(i,0,n) if (bel[i]==bel[i^1]) return 0;
		for (int i=0;i<n;i+=2) if (bel[i^1]>bel[i]) {
			sel[i/2+1]=1; }
		else {
			sel[i/2+1]=0;
		}
		// bel i>=bel i' ->i'
		return 1;
	}
}


bool gao() {
	sat2::init(2*id);
	rep(i,1,n+1) rep(j,1,m+1)  if (s[i][j]=='.') {
		rep(dir,0,4) dfs(i,j,dir);
		VI v1,v2;
		if (go[i][j][0]!=-1) v1.pb(go[i][j][0]);
		if (go[i][j][2]!=-1) v1.pb(go[i][j][2]);
		if (go[i][j][1]!=-1) v2.pb(go[i][j][1]);
		if (go[i][j][3]!=-1) v2.pb(go[i][j][3]);
		if (SZ(v1)!=1&&SZ(v2)!=1) return 0;
		if (SZ(v2)==1) swap(v1,v2);
		if (SZ(v2)==0) {
			sat2::add(v1[0]^1,v1[0]);
		} else if (SZ(v2)==1) {
			sat2::add(v1[0]^1,v2[0]);
			sat2::add(v2[0]^1,v1[0]);
		} else if (SZ(v2)==2) {
			sat2::add(v1[0]^1,v1[0]);
			sat2::add(v2[0],v2[0]^1);
			sat2::add(v2[1],v2[1]^1);
		}
	} else if (rec[i][j]) {
		rep(dir,0,4) {
			dfs(i+dx[dir],j+dy[dir],dir);
			int id=2*(rec[i][j]-1)+dir%2,id2=go[i+dx[dir]][j+dy[dir]][dir];
//			printf("ff %d %d\n",id,id2);
			if (id2!=-1) sat2::add(id,id^1),sat2::add(id2,id2^1);
		}
	}
	if (!sat2::solve()) {
		return 0;
	} else {
		rep(i,1,n+1) rep(j,1,m+1) if (rec[i][j]) {
			if (sel[rec[i][j]]) s[i][j]='|'; else s[i][j]='-';
		}
		puts("POSSIBLE");
		rep(i,1,n+1) puts(s[i]+1);
		return 1;
	}
}
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d%d",&n,&m);
		rep(i,1,n+1) scanf("%s",s[i]+1);
		printf("Case #%d: ",++__);
		rep(i,1,n+1) rep(j,1,m+1) {
			rec[i][j]=0;
			rep(d,0,4) go[i][j][d]=-2;
		}
		id=0;
		rep(i,1,n+1) rep(j,1,m+1) {
			if (s[i][j]=='|'||s[i][j]=='-') {
				rec[i][j]=++id;
			}
		}
		if (!gao()) puts("IMPOSSIBLE");
	}
}
