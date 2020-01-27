#include <bits/stdc++.h>

using namespace std;

vector <int> cnt;
int a[123];

map <int, int> mp;
int p;
int ans;

void dfs(int v) {
  if (v == p) {
    int state = 0;
    int sum = 0;
    for (int j = 0; j < p; j++) {
      state = state * 101 + a[j];
      sum += j * a[j];
    }
    int res = 0;
    int z = 1;
    for (int j = p - 1; j >= 0; j--) {
      if (a[j] > 0) {
        int new_state = state - z;
        int cur = mp[new_state];
        if ((sum - j) % p == 0) {
          cur++;
        }
        res = max(res, cur);
      }
      z *= 101;
    }
    mp[state] = res;
    ans = res;
    return;
  }
  for (int j = 0; j <= cnt[v]; j++) {
    a[v] = j;
    dfs(v + 1);
  }
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n;
    scanf("%d %d", &n, &p);
    cnt = vector <int>(p, 0);
    for (int i = 0; i < n; i++) {
      int foo;
      scanf("%d", &foo);
      cnt[foo % p]++;
    }
    mp.clear();
    ans = -1;
    dfs(0);
    printf("%d\n", ans);
  }
  return 0;
}
