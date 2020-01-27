#include <bits/stdc++.h>

using namespace std;

int main() {
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    string s;
    int k;
    cin >> s >> k;
    int ans = 0;
    for (int i = 0; i <= (int) s.length() - k; i++) {
      if (s[i] == '-') {
        for (int j = i; j < i + k; j++) {
          s[j] = '-' + '+' - s[j];
        }
        ans++;
      }
    }
    if (s != string(s.length(), '+')) {
      puts("IMPOSSIBLE");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}
