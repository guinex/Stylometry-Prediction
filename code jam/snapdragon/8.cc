#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> comp;
void un(int x, int y) {
  x = comp[x];
  y = comp[y];
  for (int i = 0; i < comp.size(); i++) if (comp[i] == y) comp[i] = x;
}
    
int main() {
  int T, C, x, prob=1;
  for (cin >> T; T--;) {
    int ret = 0;
    cin >> C;

    vector<vector<int>> ci(C), co(C), cot(C), cit(C);
    vector<int> X(C*2), Y(C*2), H(C*2), D(C*2);
    for (int i = 0; i < C*2; i++) {
      X[i] = i/2;
      cin >> Y[i] >> H[i] >> D[i];
      Y[i]--;
      co[X[i]].push_back(i);
      ci[Y[i]].push_back(i);
      cot[X[i]].push_back(H[i]);
      cit[Y[i]].push_back((H[i]+D[i])%24);
      ret += D[i];
    }
cerr << "Base trail cost = " << ret << endl;

    comp.resize(2*C);
    for (int i = 0; i < 2*C; i++) comp[i] = i;

    vector<int> swcost(C), succ(2*C);
    for (int i = 0; i < C; i++) {
      int cost1, cost2;
      if (i == 0) {
        cost1 = min(cot[i][1] + (cot[i][0]+24-cit[i][0])%24,
                    cot[i][0] + (cot[i][1]+24-cit[i][1])%24);
        cost2 = min(cot[i][1] + (cot[i][0]+24-cit[i][1])%24,
                    cot[i][0] + (cot[i][1]+24-cit[i][0])%24);
      } else {
        cost1 = (cot[i][0]+24-cit[i][0])%24 +
                (cot[i][1]+24-cit[i][1])%24;
        cost2 = (cot[i][0]+24-cit[i][1])%24 +
                (cot[i][1]+24-cit[i][0])%24;
      }
      if (cost2 < cost1) {
        swap(co[i][0], co[i][1]);
        swap(cot[i][0], cot[i][1]);
        swap(cost1, cost2);
      }
      ret += cost1;
      swcost[i] = cost2-cost1;
      un(ci[i][0], co[i][0]);
      un(ci[i][1], co[i][1]);
//cerr << ci[i][0] << " -> " << co[i][0] << endl;
//cerr << ci[i][1] << " -> " << co[i][1] << endl;
//cerr << "Switch cost at " << i << " = " << swcost[i] << endl;
    }
cerr << "Base trail+switch cost = " << ret << endl;

    vector<pair<int, pair<int, int>>> merge;
    for (int i = 0; i < 2*C; i++)
    for (int j = 0; j < 2*C; j++) if (X[i] == X[j] && comp[i] != comp[j]) {
      merge.push_back(make_pair(swcost[X[i]], make_pair(i, j)));
    }
    sort(merge.begin(), merge.end());
    for (int i = 0; i < merge.size(); i++) {
      int x = merge[i].second.first;
      int y = merge[i].second.second;
      if (comp[x] != comp[y]) {
        ret += merge[i].first;
        un(x, y);
      }
    }

    cout << "Case #" << prob++ << ": " << ret << endl;
  }
}
