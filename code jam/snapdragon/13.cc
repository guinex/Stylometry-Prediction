#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int T, X, Y, prob=1;
  for (cin >> T; T--;) {
    cin >> Y >> X;
    vector<string> g(Y);
    for (int i = 0; i < Y; i++) cin >> g[i];
    for (int y = 0; y < Y; y++) {
      for (int x = 0; x+1 < X; x++) if (g[y][x] != '?' && g[y][x+1] == '?') {
        g[y][x+1] = g[y][x];
      }
      for (int x = X-1; x > 0; x--) if (g[y][x] != '?' && g[y][x-1] == '?') {
        g[y][x-1] = g[y][x];
      }
    }
    for (int y = 0; y+1 < Y; y++) if (g[y][0] != '?' && g[y+1][0] == '?') {
      g[y+1] = g[y];
    }
    for (int y = Y-1; y > 0; y--) if (g[y][0] != '?' && g[y-1][0] == '?') {
      g[y-1] = g[y];
    }
    cout << "Case #" << prob++ << ":" << endl;
    for (int y = 0; y < Y; y++) cout << g[y] << endl;
  }
}
