#include <bits/stdc++.h>

using namespace std;

int main() {
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    long long n, k;
    cin >> n >> k;
    multiset < pair <long long, long long> > s;
    s.insert(make_pair(-n, 1LL));
    while (k > 0) {
      auto p = *(s.begin());
      s.erase(s.begin());
      long long len = -p.first;
      long long cnt = p.second;
      if (cnt >= k) {
        cout << len / 2 << " " << (len - 1) / 2 << endl;
        break;
      }
      k -= cnt;
      s.insert(make_pair(-(len / 2), cnt));
      s.insert(make_pair(-((len - 1) / 2), cnt));
    }
  }
  return 0;
}
