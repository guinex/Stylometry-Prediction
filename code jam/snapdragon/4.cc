#include <iostream>
#include <string>
using namespace std;

int main() {
  int T, prob=1;
  for (cin >> T; T--;) {
    string s;
    cin >> s;
    int i, n = 0;
    for (i = 0; i+1 < s.size(); i++) {
      if (s[i+1] < s[i]) break;
      if (s[i+1] > s[i]) n = i+1;
    }
    if (i+1 < s.size()) {
      s[n]--;
      for (int i = n+1; i < s.size(); i++) s[i] = '9';
      while (s[0] == '0') s = s.substr(1);
    }
    cout << "Case #" << prob++ << ": " << s << endl;
  }
}
