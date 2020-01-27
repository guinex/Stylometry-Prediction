#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
// Returns -1 for unmatched items.
// Complexity: O(V*E)
VI BipartiteMatch(const VVI &mat, VI *back_match = NULL) {
  int max_item = -1;
  VI fmat(mat.size(), -1), seen(mat.size(), -1), prev(mat.size());
  for (int i = 0; i < mat.size(); i++) if (mat[i].size())
    max_item = max(max_item, *max_element(mat[i].begin(), mat[i].end()));
  VI bmat(max_item+1, -1);

  for (int i = 0; i < mat.size(); i++) {
    VI q(1, i);
    seen[i] = i; prev[i] = -1;
    int x, y;
    while (!q.empty()) {
      x = q.back(); q.pop_back();
      for (VI::const_iterator it = mat[x].begin(); it != mat[x].end(); ++it) {
        int bm = bmat[*it];
        if (bm == -1) {y = *it; goto found_match;}
        if (seen[bm] < i) {
          seen[bm] = i; prev[bm] = x;
          q.push_back(bm);
        }
      }
    }
    continue;
found_match:
    while (x != -1) {
      bmat[y] = x;
      swap(y, fmat[x]);
      x = prev[x];
    }
  }

  if (back_match) *back_match = bmat;
  return fmat;
}

int main() {
  int T, N, M, prob=1;
  for (cin >> T; T--;) {
    cin >> N;
    vector<string> g(N, string(N, '.'));
    for (cin >> M; M--;) {
      char ch;
      int x, y;
      cin >> ch >> y >> x;
      x--; y--;
      g[y][x] = ch;
    }
    vector<string> og = g;

    {
      vector<vector<int>> mat(N);
      for (int y = 0; y < N; y++)
      for (int x = 0; x < N; x++) if (g[y][x] == '+' || g[y][x] == '.') {
        bool conflict = false;
        for (int x2 = 0; x2 < N; x2++) {
          if (g[y][x2] == 'x' || g[y][x2] == 'o') conflict = true;
        }
        for (int y2 = 0; y2 < N; y2++) {
          if (g[y2][x] == 'x' || g[y2][x] == 'o') conflict = true;
        }
        if (!conflict) mat[y].push_back(x);
      }
      vector<int> v = BipartiteMatch(mat);
      for (int y = 0; y < v.size(); y++) if (v[y] != -1) {
        char& ch = g[y][v[y]];
        ch = (ch == '.') ? 'x' : 'o';
      }
    }

    {
      vector<vector<int>> mat(2*N-1);
      for (int y = 0; y < N; y++)
      for (int x = 0; x < N; x++) if (g[y][x] == 'x' || g[y][x] == '.') {
        bool conflict = false;
        for (int a = -N; a < N; a++) {
          if (x+a < 0 || x+a >= N || y+a < 0 || y+a >= N) continue;
          if (g[y+a][x+a] == '+' || g[y+a][x+a] == 'o') conflict = true;
        }
        for (int a = -N; a < N; a++) {
          if (x+a < 0 || x+a >= N || y-a < 0 || y-a >= N) continue;
          if (g[y-a][x+a] == '+' || g[y-a][x+a] == 'o') conflict = true;
        }
        if (!conflict) mat[y-x+N-1].push_back(y+x);
      }
      vector<int> v = BipartiteMatch(mat);
      for (int i = 0; i < v.size(); i++) if (v[i] != -1) {
        char& ch = g[(i+v[i]-(N-1))/2][(v[i]-i+(N-1))/2];
        ch = (ch == '.') ? '+' : 'o';
      }
    }

    int style = 0, diff = 0;
    for (int y = 0; y < N; y++)
    for (int x = 0; x < N; x++)
      style += (g[y][x] == 'o') ? 2 : (g[y][x] != '.') ? 1 : 0;
    for (int y = 0; y < N; y++)
    for (int x = 0; x < N; x++)
      diff += (g[y][x] != og[y][x]);
    cout << "Case #" << prob++ << ": " << style << ' ' << diff << endl;
    for (int y = 0; y < N; y++)
    for (int x = 0; x < N; x++) if (g[y][x] != og[y][x]) {
      cout << g[y][x] << ' ' << y+1 << ' ' << x+1 << endl;
    }
  }
}
