#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int v[1001][1001];
int np[1001][1001];
vector<vector<int>> e;

int seen[1001];
vector<int> path;
bool doit(int x, int y, int prev) {
  if (x == y) {
    path.push_back(y);
    return true;
  }
  if (seen[x]) return false;
  seen[x] = true;

  for (int i = 0; i < e[x].size(); i++) if (e[x][i] != prev) {
    if (doit(e[x][i], y, x)) {
      path.push_back(x);
      return true;
    }
  }
  return false;
}

int main() {
  int T, F, P, prob=1;
  for (cin >> T; T--;) {
    int ret = 0;
    cin >> F >> P;

    memset(v, 0, sizeof(v));
    memset(np, 0, sizeof(np));
    vector<int> ex(P), ey(P);

    e = vector<vector<int>>(F+1);
    for (int i = 0; i < P; i++) {
      cin >> ex[i] >> ey[i];
      e[ex[i]].push_back(ey[i]);
      e[ey[i]].push_back(ex[i]);
      np[ex[i]][ey[i]]++;
      np[ey[i]][ex[i]]++;
    }
    for (int i = 1; i <= F; i++) {
      random_shuffle(e[i].begin(), e[i].end());
    }

    vector<int> idx(P);
    for (int i = 0; i < P; i++) idx[i] = i;
    random_shuffle(idx.begin(), idx.end());
    for (int ii = 0; ii < P; ii++) {
      int i = idx[ii];
      if (v[ex[i]][ey[i]]) continue;

      memset(seen, 0, sizeof(seen));
      path.clear();
      if (!doit(ey[i], ex[i], (np[ex[i]][ey[i]] > 1) ? -1 : ex[i])) goto fail;
      path.push_back(ex[i]);

 
//for (int j = 0; j+1 < path.size(); j++) cout << path[j] << "->" << path[j+1] << "  ";
//cout << endl;
      int pp = 1, np = -1;
      for (int j = 0; j+1 < path.size(); j++) {
        if (v[path[j]][path[j+1]] == -pp) {pp++; j = -1; continue;}
        if (v[path[j]][path[j+1]] == -np) {np--; j = -1; continue;}
      }
      int val = (pp <= -np) ? pp : np;
      for (int j = 0; j+1 < path.size(); j++) {
        v[path[j]][path[j+1]] += val;
        v[path[j+1]][path[j]] -= val;
        if (v[path[j]][path[j+1]] > F*F-1) cerr << "WARNING!" << endl;
      }
    }

    cout << "Case #" << prob++ << ":";
    for (int i = 0; i < P; i++) {
      if (np[ex[i]][ey[i]] == 2) {
        if (ex[i] < ey[i]) {
          if (v[ex[i]][ey[i]] == 1) {
            cout << ' ' << -1;
          } else {
            cout << ' ' << 1;
          }
        } else {
          if (v[ey[i]][ex[i]] == 1) {
            cout << ' ' << v[ex[i]][ey[i]]-1;
          } else {
            cout << ' ' << v[ex[i]][ey[i]]+1;
          }
        }
      } else {
        cout << ' ' << v[ex[i]][ey[i]];
      }
    }
    cout << endl;
    continue;
fail:
    cout << "Case #" << prob++ << ": IMPOSSIBLE" << endl;
  }
}
