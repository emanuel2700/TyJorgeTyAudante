#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl
const int N = 1e5 + 4;

struct Dsu {
    int n;
    int t[N];
    int sz[N];

    void build(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) t[i] = i, sz[i] = 1;
    }

    int find(int x) {
        return x == t[x] ? x : t[x] = find(t[x]);
    }

    void join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        t[a] = b;
        sz[b] += sz[a];
    }
} dsu;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    dsu.build(n);
    int cap[N];
    int vis[N];

    for (int i = 0; i < n; i++) vis[i + 1] = 0;

    for (int i = 0; i < k; i++) {
        cin >> cap[i];
        vis[cap[i]] = 1;
    }

    ll ans = 0;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dsu.join(a, b);
    }

    ll super_sz = 0;
    ll mx = 0;

    for (int i = 0; i < k; i++) {
        int rt = dsu.find(cap[i]);
        ll sz = dsu.sz[rt];
        ans += sz * (sz - 1) / 2;
        mx = max(mx, sz);
        vis[rt] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (i != dsu.find(i) || vis[i]) continue;
        super_sz += dsu.sz[i];
    }

    ans += super_sz * (super_sz - 1) / 2;
    ans += super_sz * mx;
    cout << ans - m << "\n";

    return 0;
}