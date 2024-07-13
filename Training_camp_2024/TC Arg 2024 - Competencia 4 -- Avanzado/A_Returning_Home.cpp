#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Long = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

Long n, m;
struct Point {
    ll x, y;
};

Point ini, fin;

using Path = pair<Long, int>;
const Long INF = 1e18;

struct Graph {
    vector<vector<pair<int, Long>>> adj;
    vector<int> parent;
    vector<Long> d;

    Graph(int n) {
        adj.resize(n);
    }

    void addEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int s) { // O(E log V)
        int n = adj.size();
        parent = vector<int>(n, -1);
        d = vector<Long>(n, INF);
        priority_queue<Path, vector<Path>, greater<Path>> q;
        d[s] = 0;
        q.push({d[s], s});
        while (!q.empty()) {
            auto [weight, u] = q.top();
            q.pop();
            if (weight != d[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    parent[v] = u;
                    q.push({d[v], v});
                }
            }
        }
    }

    vector<int> getPath(int u) {
        if (d[u] == INF) return {};
        vector<int> path;
        while (u != -1) {
            path.push_back(u);
            u = parent[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    cin >> ini.x >> ini.y;
    cin >> fin.x >> fin.y;

    vector<Point> v(m);
    for (int i = 0; i < m; i++) {
        cin >> v[i].x >> v[i].y;
    }
    Graph G = Graph(m + 4);
    // ini -> tp
    for (int i = 0; i < m; i++) {
        ll tam;
        tam = min(abs(v[i].x - ini.x), abs(v[i].y - ini.y));
        G.addEdge(0, i + 1, tam);
    }
    // tp -> fin
    for (int i = 0; i < m; i++) {
        ll tam;
        tam = abs(v[i].x - fin.x) + abs(v[i].y - fin.y);
        G.addEdge(m + 2, i + 1, tam);
    }
    // ini -> fin
    ll tam = abs(ini.x - fin.x) + abs(ini.y - fin.y);
    G.addEdge(0, m + 2, tam);

    vector<pair<ll, ll>> tpx;
    vector<pair<ll, ll>> tpy;
    for (int i = 0; i < m; i++) {
        tpx.pb({v[i].x, i});
        tpy.pb({v[i].y, i});
    }

    sort(tpx.begin(), tpx.end());
    sort(tpy.begin(), tpy.end());

    for (int i = 0; i < m; i++) {
        // x
        pair<ll, ll> a = make_pair(v[i].x, i);
        Long pos = lower_bound(tpx.begin(), tpx.end(), a) - tpx.begin();
        if (pos > 0) {
            Long ant = tpx[pos - 1].second;
            Long tm = abs(v[ant].x - v[i].x);
            G.addEdge(i + 1, ant + 1, tm);
        }
        if (pos < m - 1) {
            Long p = tpx[pos + 1].second;
            Long tm = abs(v[p].x - v[i].x);
            G.addEdge(i + 1, p + 1, tm);
        }
        // debug(i);

        // y
        a = make_pair(v[i].y, i);
        pos = lower_bound(tpy.begin(), tpy.end(), a) - tpy.begin();
        if (pos > 0) {
            Long ant = tpy[pos - 1].second;
            Long tm = abs(v[ant].y - v[i].y);
            G.addEdge(i + 1, ant + 1, tm);
        }
        if (pos < m - 1) {
            Long p = tpy[pos + 1].second;
            Long tm = abs(v[p].y - v[i].y);
            G.addEdge(i + 1, p + 1, tm);
        }
    }

    G.dijkstra(0);
    cout << G.d[m + 2] << endl;

    return 0;
}