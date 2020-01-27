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

int _,__;
ll n,k;
map<ll,ll> hs
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%lld%lld",n,k);
		hs.clear();
		hs[n]=1;
		while (1) {
			ll len=hs.rbegin()->fi,cnt=hs.rbegin()->se;
			hs.erase(--hs.end());
			assert(len>0);
			k-=cnt;
			ll m1=len/2,m2=(len-1)/2;
			if (k<=0) {
				printf("Case #%d: %lld %lld\n",++__,m1,m2);
				break;
			}
			hs[m1]+=cnt; hs[m2]+=cnt;
		}
	}
}
