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

int _,__,n,p,cnt[10],x,dp[110][110][110];
void upd(int &a,int b) { if (b>a) a=b; }
int main() {
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		scanf("%d%d",&n,&p);
		rep(i,0,p) cnt[i]=0;
		int s=0;
		rep(i,0,n) {
			scanf("%d",&x);
			cnt[x%p]++; s+=x;
		}
		int ans=(s%p!=0)+cnt[0];
		if (p==2) ans+=cnt[1]/2;
		else if (p==3) {
			ans+=min(cnt[1],cnt[2])+abs(cnt[1]-cnt[2])/3;
		} else {
			rep(i,0,cnt[1]+1) rep(j,0,cnt[2]+1) rep(k,0,cnt[3]+1) {
				dp[i][j][k]=0;
				if (i>=1&&k>=1) upd(dp[i][j][k],dp[i-1][j][k-1]+1);
				if (i>=2&&j>=1) upd(dp[i][j][k],dp[i-2][j-1][k]+1);
				if (j>=1&&k>=2) upd(dp[i][j][k],dp[i][j-1][k-2]+1);
				if (j>=2) upd(dp[i][j][k],dp[i][j-2][k]+1);
				if (i>=4) upd(dp[i][j][k],dp[i-4][j][k]+1);
				if (k>=4) upd(dp[i][j][k],dp[i][j][k-4]+1);
			}
			ans+=dp[cnt[1]][cnt[2]][cnt[3]];
		}
		printf("%d\n",ans);
	}
}