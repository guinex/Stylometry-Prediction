#include <iostream>
#include <map>
using namespace std;

int main() {
  int T, prob=1;
  for (cin >> T; T--;) {
    long long N, K;
    cin >> N >> K;
    map<long long, long long, greater<long long>> m;
    m[N] = 1;
    for (auto it = m.begin(); it != m.end(); ++it) {
      long long mx = it->first / 2, mn = (it->first-1)/2;
      //cout << it->first << ',' << it->second << ' ' << mx << ' ' << mn << endl;
      if (K <= it->second) {
        cout << "Case #" << prob++ << ": " << mx << ' ' << mn << endl;
        break;
      } else {
        K -= it->second;
        m[mn] += it->second; m[mx] += it->second;
      }
    }
  }
}
