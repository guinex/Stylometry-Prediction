#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int T, N, P, x, prob=1;
  for (cin >> T; T--;) {
    int ret = 0, tot = 0;
    cin >> N >> P;
    vector<int> v(P);
    for (int i = 0; i < N; i++) {
      cin >> x;
      v[x%P]++;
      tot += x;
    }

    if (P == 2) {
      ret = v[1]/2 + v[0];
    } else if (P == 3) {
      for (int a = 0; a <= v[1] && a <= v[2]; a++) {
        ret = max(ret, a + (v[1]-a)/3 + (v[2]-a)/3 + v[0]);
      }
    } else {
      for (int a = 0; a <= v[1] && a <= v[3]; a++)
      for (int b = 0; b+b <= v[2]; b++)
      for (int c = 0; a+c+c <= v[1] && b+b+c <= v[2]; c++)
      for (int d = 0; b+b+c+d <= v[2] && a+d+d <= v[3]; d++) {
        ret = max(ret, a+b+c+d +
                  (v[1]-a-c-c)/4 +
                  (v[2]-b-b-c-d)/4 +
                  (v[3]-a-d-d)/4 + v[0]);
      }
    }

    cout << "Case #" << prob++ << ": " << ret + (tot%P != 0) << endl;
  }
}
