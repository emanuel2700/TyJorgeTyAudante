#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl
using Cap = long long;
using Cost = long long;

const int MX = 5000;
const Cap INF_CAP = 1e18;
const Cost INF_COST = 1e18;

struct Edge {
    int to;
    Cap flow, cap;
    Cost cost;
    int rev; // index of the backward edge in the adj list of to
    Edge(int to, Cap cap, Cost cost, int rev)
        : to(to), flow(0), cap(cap), cost(cost), rev(rev) {}
};

struct Graph {
    vector<Edge> adj[MX];
    int parentEdge[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) adj[i].clear();
    }

    void addEdge(int u, int v, Cap w, Cost cost, bool dir = 1) {
        adj[u].push_back(Edge(v, w, cost, adj[v].size()));
        adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
        if (!dir) addEdge(v, u, w, cost, true);
    }

    void pushFlow(int s, int t, Cap inc) {
        int v = t;
        while (v != s) {
            Edge &backward = adj[v][parentEdge[v]];
            int u = backward.to;
            Edge &forward = adj[u][backward.rev];
            forward.flow += inc;
            backward.flow -= inc;
            v = u;
        }
    }

    pair<Cap, Cost> spfa(int s, int t, int n) { // O(E V)
        //<flow, cost>
        vector<Cost> d(n, INF_COST);
        vector<bool> inQueue(n, false);
        vector<Cap> residualCap(n, 0);
        queue<int> q;
        d[s] = 0;
        residualCap[s] = INF_CAP;
        inQueue[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            for (Edge e : adj[u]) {
                int v = e.to;
                Cap cf = e.cap - e.flow;
                if (cf > 0 && d[u] + e.cost < d[v]) {
                    d[v] = d[u] + e.cost;
                    if (!inQueue[v]) q.push(v);
                    parentEdge[v] = e.rev;
                    residualCap[v] = min(residualCap[u], cf);
                    inQueue[v] = true;
                }
            }
        }
        if (d[t] == INF_COST) return {0, 0};
        Cap cf = residualCap[t];
        pushFlow(s, t, cf);
        return {cf, d[t] * cf};
    }

    pair<Cap, Cost> minCostFlow(int s, int t, int n) {
        // O(E * V * maxFlow )
        // maxFlow <= V * U, where U is the maximum capacity
        // Assumption: Initially no negative cycles
        // <maxFlow, minCost>
        pair<Cap, Cost> inc;
        Cap flow = 0;
        Cost cost = 0;
        do {
            inc = spfa(s, t, n);
            flow += inc.first;
            cost += inc.second;
        } while (inc.first > 0);
        return {flow, cost};
    }
} G;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    int n;

    cin >> s;
    cin >> n;

    vi freq(26);
    for (int i = 0; i < s.size(); i++) freq[s[i] - 'a']++;

    int f[n][26];
    memset(f, 0, sizeof f);
    int mx[n];

    for (int i = 0; i < n; i++) {
        string si;
        cin >> si >> mx[i];
        for (char c : si) f[i][c - 'a']++;
    }

    for (int i = 0; i < n; i++) {
        G.addEdge(0, i + 1, mx[i], 0);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (f[i][j] == 0) continue;
            G.addEdge(i + 1, n + j + 1, f[i][j], i + 1);
        }
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) continue;
        G.addEdge(n + i + 1, n + 27, freq[i], 0);
    }

    auto ans = G.minCostFlow(0, n + 27, n + 28);

    if (ans.first != s.size()) cout << -1 << '\n';
    else cout << ans.second << '\n';

    return 0;
}