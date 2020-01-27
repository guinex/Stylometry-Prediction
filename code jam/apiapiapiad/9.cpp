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
int _,__,n,c,m,cw[N],cp[N],p[N],b[N];
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d%d%d",&n,&c,&m);
		rep(i,1,n+1) cw[i]=0;
		rep(i,1,c+1) cp[i]=0;
		rep(i,0,m) {
			scanf("%d%d",b+i,p+i);
			cp[p[i]]++; cw[b[i]]++;
		}
		int ret=*max_element(cp+1,cp+c+1);
		int s=0;
		rep(i,1,n+1) {
			s+=cw[i];
			ret=max(ret,(s+i-1)/i);
		}
		int t=0;
		rep(i,1,n+1) t+=max(cw[i]-ret,0);
		printf("Case #%d: %d %d\n",++__,ret,t);
	}
}
