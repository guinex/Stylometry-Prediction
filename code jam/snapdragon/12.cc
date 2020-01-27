#include <iostream>
#include <string>
using namespace std;

int main() {
  int T, K, prob=1;
  for (cin >> T; T--;) {
    string s;
    cin >> s >> K;
    int ret = 0;
    for (int i = 0; i+K <= s.size(); i++) if (s[i] == '-') {
      ret++;
      for (int j = i; j < i+K; j++) s[j] = (s[j] == '-') ? '+' : '-';
    }

    if (s == string(s.size(), '+')) {
      cout << "Case #" << prob++ << ": " << ret << endl;
    } else {
      cout << "Case #" << prob++ << ": IMPOSSIBLE" << endl;
    }
  }
}
