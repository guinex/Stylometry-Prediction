#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int a[55][55][2][55][55];
int x[55555], y[55555], color[55555];
int xx[55555], yy[55555];
int id[55][55];
vector < pair <int, int> > g[55555][2];
bool fail[55][55][2];
char s[55][55];
int h, w;

void go(int i, int j, int rot, int ii, int jj, int dir) {
  a[i][j][rot][ii][jj] = 1;
  ii += dx[dir];
  jj += dy[dir];
  if (ii < 0 || jj < 0 || ii >= h || jj >= w) {
    return;
  }
  if (s[ii][jj] == '#') {
    return;
  }
  if (s[ii][jj] == '-' || s[ii][jj] == '|') {
    fail[i][j][rot] = true;
    return;
  }
  if (s[ii][jj] == '\\') {
    if (dir == 0) dir = 1; else
    if (dir == 1) dir = 0; else
    if (dir == 2) dir = 3; else
    if (dir == 3) dir = 2;
  }
  if (s[ii][jj] == '/') {
    if (dir == 0) dir = 3; else
    if (dir == 1) dir = 2; else
    if (dir == 2) dir = 1; else
    if (dir == 3) dir = 0;
  }
  go(i, j, rot, ii, jj, dir);
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    scanf("%d %d", &h, &w);
    for (int i = 0; i < h; i++) {
      scanf("%s", s[i]);
    }
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        for (int rot = 0; rot < 2; rot++) {
          for (int ii = 0; ii < h; ii++) {
            for (int jj = 0; jj < w; jj++) {
              a[i][j][rot][ii][jj] = 0;
            }
          }
          fail[i][j][rot] = false;
          if (s[i][j] != '-' && s[i][j] != '|') {
            continue;
          }
          go(i, j, rot, i, j, 0 + rot);
          go(i, j, rot, i, j, 2 + rot);
        }
      }
    }
    int cnt = 0;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (s[i][j] == '-' || s[i][j] == '|') {
          id[i][j] = cnt;
          x[cnt] = i;
          y[cnt] = j;
          cnt++;
        }
      }
    }
    for (int i = 0; i < cnt; i++) {
      for (int rot = 0; rot < 2; rot++) {
        g[i][rot].clear();
      }
    }
    for (int i = 0; i < cnt; i++) {
      for (int rot = 0; rot < 2; rot++) {
        if (fail[x[i]][y[i]][rot]) {
          g[i][rot].emplace_back(i, rot ^ 1);
        }
      }
    }
    bool err = false;
    for (int ii = 0; ii < h; ii++) {
      for (int jj = 0; jj < w; jj++) {
        if (s[ii][jj] != '.') {
          continue;
        }
        vector < pair < pair <int, int>, int > > beat;
        set < pair <int, int> > st;
        for (int i = 0; i < h; i++) {
          for (int j = 0; j < w; j++) {
            for (int rot = 0; rot < 2; rot++) {
              if (!fail[i][j][rot] && a[i][j][rot][ii][jj]) {
                beat.emplace_back(make_pair(i, j), rot);
                st.insert(make_pair(i, j));
              }
            }
          }
        }
        if (st.size() == 0) {
          err = true;
          break;
        }
        if (st.size() == 1) {
          if (beat.size() == 1) {
            int i = beat[0].first.first;
            int j = beat[0].first.second;
            int rot = beat[0].second;
            g[id[i][j]][rot ^ 1].emplace_back(id[i][j], rot);
          }
          continue;
        }
        assert(st.size() == 2);
        int i1 = (*(st.begin())).first;
        int j1 = (*(st.begin())).second;
        int i2 = (*(--st.end())).first;
        int j2 = (*(--st.end())).second;
        for (int rot1 = 0; rot1 < 2; rot1++) {
          for (int rot2 = 0; rot2 < 2; rot2++) {
            if (!a[i1][j1][rot1][ii][jj] && !a[i2][j2][rot2][ii][jj]) {
              g[id[i1][j1]][rot1].emplace_back(id[i2][j2], rot2 ^ 1);
              g[id[i2][j2]][rot2].emplace_back(id[i1][j1], rot1 ^ 1);
            }
          }
        }
      }
      if (err) {
        break;
      }
    }
    if (!err) {
      for (int i = 0; i < cnt; i++) {
        xx[i] = x[i];
        yy[i] = y[i];
        color[i] = -1;
      }
      for (int i = 0; i < cnt; i++) {
        if (color[i] != -1) {
          continue;
        }
        for (int rot = 0; rot < 2; rot++) {
          color[i] = rot;
          int b = 0, e = 1;
          x[0] = i;
          bool bad = false;
          while (b < e) {
            for (auto p : g[x[b]][color[x[b]]]) {
              int ii = p.first;
              int cc = p.second;
              if (color[ii] != -1 && cc != color[ii]) {
                bad = true;
                break;
              }
              if (color[ii] == -1) {
                x[e] = ii;
                color[ii] = cc;
                e++;
              }
            }
            if (bad) break;
            b++;
          }
          if (!bad) {
            break;
          }
          for (int z = 0; z < e; z++) {
            color[x[z]] = -1;
          }
        }
        if (color[i] == -1) err = true;
        if (err) break;
      }
    }
    if (err) {
      puts("IMPOSSIBLE");
    } else {
      puts("POSSIBLE");
      for (int i = 0; i < cnt; i++) {
        if (color[i] == 0) {
          s[xx[i]][yy[i]] = '|';
        } else {
          s[xx[i]][yy[i]] = '-';
        }
      }
      for (int i = 0; i < h; i++) {
        puts(s[i]);
      }
    }
  }
  return 0;
}
