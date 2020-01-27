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
typedef vector<int> VI
typedef long long ll
typedef pair<int,int> PII
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

int _,__,n;
char dig[30],d2[30];
bool valid(char *s) {
	rep(i,1,n) if (s[i-1]>s[i]) return 0;
	return 1;
}
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%s",dig);
		printf("Case #%d: ",++__);
		n=strlen(dig);
		if (valid(dig)) {
			puts(dig);
			continue;
		}
		per(i,0,n) if (dig[i]!='0') {
			rep(j,0,n) d2[j]=dig[j]; d2[n]=0;
			d2[i]--;
			rep(j,i+1,n) d2[j]='9';
			if (valid(d2)) {
				puts(d2[0]=='0'?d2+1:d2);
				break;
			}
		
	}
}
