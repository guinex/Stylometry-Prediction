#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
  map<long long, int> m[10];

  /*ofstream fout("A.tmp");
  long long p10 = 10;
  for (int n = 1; n <= 9; n++, p10 *= 10) {
    int all = 0;
    for (long long z = 1; z < p10; z++) {
      vector<long long> seen(1, z);
      for (long long x = z;;) {
        int nd[10];
        bool fail = false;
        memset(nd, 0, sizeof(nd));
        for (long long y = x; y; y /= 10) {
          int d = y%10;
          if (d > n) fail = true;
          nd[d]++;
        }
        if (fail) break;

        long long y = 0;
        for (int j = 1; j <= n; j++) y = y*10 + nd[j];

        bool done = false;
        for (int j = 0; j < seen.size(); j++) if (seen[j] == y) done = true;
        if (done) break;
        seen.push_back(y);
        m[n][y]++;
        x = y;
      }
    }
    fout << n << ' ' << m[n].size() << endl;
    for (auto it : m[n]) fout << ' ' << it.first << ' ' << it.second << endl;
  }
  fout.close();
  return 0;*/

  ifstream fin("A.tmp");
  for (int n = 1; n <= 9; n++) {
    long long dummy, all, x, y;
    fin >> dummy >> all;
    for (int i = 0; i < all; i++) {
      fin >> x >> y;
      m[n][x] = y;
    }
  }

  int T, x, prob=1;
  for (cin >> T; T--;) {
    string s;
    cin >> s;
    istringstream sin(s);
    long long x;
    sin >> x;
    cout << "Case #" << prob++ << ": " << m[s.size()][x]+1 << endl;
  }
}
