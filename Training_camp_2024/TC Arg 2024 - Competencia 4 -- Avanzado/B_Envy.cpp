#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const int N = 5e5 + 4;

struct Dsu {
    int n;
    int t[N];
    int sz[N];
    stack<pair<int, int>> ops;

    void build(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) t[i] = i, sz[i] = 1;
    }

    int find(int a) {
        return t[a] == a ? a : find(t[a]);
    }

    void join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        t[b] = a;
        ops.push({a, b});
    }

    void back() {
        auto [a, b] = ops.top();
        ops.pop();
        t[b] = b;
        sz[a] -= sz[b];
    }
} dsu;

int n, m, q;
vector<pair<int, int>> edges[N];
map<int, vector<pair<int, int>>> Qs[N];
pair<pair<int, int>, int> ed[N];
bool ans[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[w].push_back({a, b});
        ed[i + 1] = {{a, b}, w};
    }

    cin >> q;

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int id;
            cin >> id;
            Qs[ed[id].second][i].push_back(ed[id].first);
        }
        ans[i] = true;
    }

    dsu.build(n);

    for (int w = 0; w < N; w++) {
        for (auto &[id, vec] : Qs[w]) {
            int cnt = 0;
            for (auto &[a, b] : vec) {
                if (dsu.find(a) == dsu.find(b)) {
                    ans[id] = false;
                    break;
                }
                cnt++;
                dsu.join(a, b);
            }
            while (cnt--) dsu.back();
        }

        for (auto [a, b] : edges[w]) {
            if (dsu.find(a) == dsu.find(b)) continue;
            dsu.join(a, b);
        }
    }

    for (int i = 0; i < q; i++) cout << (ans[i] ? "YES\n" : "NO\n");

    return 0;
}