#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int T, N, P, prob=1;
  for (cin >> T; T--;) {
    cin >> N >> P;
    vector<int> R(N);
    for (int i = 0; i < N; i++) cin >> R[i];
    vector<vector<pair<int, int>>> Q(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        int v;
        cin >> v;
        int mn = (v*10 + (11*R[i]-1)) / (11*R[i]);
        int mx = (v*10) / (9*R[i]);
        //cout << v << ' ' << R[i] << "  " << mn << '-' << mx << endl;
        Q[i].push_back(make_pair(mn, mx));
      }
      sort(Q[i].begin(), Q[i].end());
    }
    int ret = 0;
    for (;;) {
redo:
      int cur = -1;
      for (int i = 0; i < N; i++) {
        if (!Q[i].size()) goto done;
        //cout << Q[i][0].first << ',' << Q[i][0].second  << ' ';
        cur = max(cur, Q[i][0].first);
      }
      //cout << "  " << cur << endl;
      for (int i = 0; i < N; i++) {
        if (Q[i][0].second < cur) {
          Q[i].erase(Q[i].begin());
          goto redo;
        }
      }
      ret++;
      for (int i = 0; i < N; i++) {
        Q[i].erase(Q[i].begin());
      }
    }
done:
    cout << "Case #" << prob++ << ": " << ret << endl;
  }
}
