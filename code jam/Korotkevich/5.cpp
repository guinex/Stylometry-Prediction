#include <bits/stdc++.h>

using namespace std;

int main() {
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    string s;
    cin >> s;
    string z = "";
    for (int i = 0; i < (int) s.length(); i++) {
      int bound = (i == 0 ? 0 : (int) (z.back() - '0'));
      for (int d = 9; d >= bound; d--) {
        string zz = z;
        for (int j = i; j < (int) s.length(); j++) {
          zz += (char) ('0' + d);
        }
        if (zz <= s) {
          z += (char) ('0' + d);
          break;
        }
      }
    }
    while (z[0] == '0') {
      z = z.substr(1);
    }
    cout << z << endl;
  }
  return 0;
}
