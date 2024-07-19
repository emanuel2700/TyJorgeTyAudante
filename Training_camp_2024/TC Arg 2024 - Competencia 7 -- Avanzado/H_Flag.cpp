#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const int N = 1e3 + 4;

int n, m;

struct Segment_Tree {
    int n;
    int t[N * 2];

    void build(int _n, int l, int a[]) {
        n = _n;
        for (int i = 0; i < n; i++, l += m) t[i + n] = a[l];
        for (int i = n - 1; i >= 1; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    int query(int l, int r) {
        int ans = N;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = min(ans, t[l++]);
            if (r & 1) ans = min(ans, t[--r]);
        }
        return ans;
    }
} sgt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    char flag[n * m];
    int sz_down[n * m];
    int sz_right[n * m];

    for (int i = 0; i < n * m; i++) cin >> flag[i];

    for (int i = n * m - 1; i >= 0; i--) {
        if (i % m == m - 1) sz_right[i] = 1;
        else sz_right[i] = (flag[i] == flag[i + 1] ? sz_right[i + 1] + 1 : 1);
        if (i / m == n - 1) sz_down[i] = 1;
        else sz_down[i] = (flag[i] == flag[i + m] ? sz_down[i + m] + 1 : 1);
        // cout << i << " -> " << sz_down[i] << "\n";
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        sgt.build(n, i, sz_right);
        for (int j = 0; j < n; j++) {
            int id = i + j * m;
            int h = sz_down[id];
            if (id + 3 * h * m - m >= n * m) continue;
            if (sz_down[id + h * m] != h) continue;
            if (sz_down[id + 2 * h * m] < h) continue;
            // cout << j << " " << i << " : " << h << "\n";
            ans += sgt.query(id / m, id / m + 3 * h);
        }
    }
    cout << ans << "\n";

    return 0;
}