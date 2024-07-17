#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const int mod = 1e9 + 7;
const int N = 1e6 + 4;

int S(int a, int b) {
    return (0ll + a + b) % mod;
}
int P(int a, int b) {
    return 1ll * a * b % mod;
}
int BP(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = P(a, a))
        if (b & 1) ans = P(ans, a);
    return ans;
}

const int p = 43, q = 37;
int pe[N], qe[N], Ipe[N], Iqe[N];
int pr_p[N], pr_q[N];
int n, m, str_sz, s;
string str;

pair<int, int> val_str(int l, int sz) {
    int r = l + sz - 1;
    int val_p = P(S(pr_p[r], mod - pr_p[l - 1]), Ipe[l]);
    int val_q = P(S(pr_q[r], mod - pr_q[l - 1]), Iqe[l]);
    return {val_p, val_q};
}

struct Edge {
    int v, l, sz, id;

    bool operator<(Edge x) {
        if (sz == 0) return 1;
        if (x.sz == 0) return 0;
        int k = 31 - __builtin_clz(min(sz, x.sz));
        int aux = 0;
        for (int i = k; i >= 0; i--) {
            if (aux + (1 << i) > min(sz, x.sz)) continue;
            pair<int, int> p1 = val_str(l, aux + (1 << i));
            pair<int, int> p2 = val_str(x.l, aux + (1 << i));
            if (p1 == p2) aux += 1 << i;
        }
        if (aux == sz) return 1;
        if (aux == x.sz) return 0;
        return str[l + aux] < str[x.l + aux];
    }

    int caso(Edge x) {
        // sz >= x.sz
        return val_str(l, x.sz) == val_str(x.l, x.sz);
    }
};

vector<Edge> adj[N];
vector<pair<int, int>> path[N];
int vis[N];
vector<pair<int, int>> rec;
int cur, mcur;
int ver[N];
int up[N];

void pre_dfs(int u) {
    vis[u] = 1;
    sort(adj[u].begin(), adj[u].end());
    stack<int> stk;
    vector<Edge> aux;
    for (int i = 0; i < adj[u].size(); i++) {
        // cout << u << " -> " << adj[u][i].v << "\n";
        while (stk.size() && adj[u][i].caso(adj[u][stk.top()]) == 0) {
            aux.push_back(adj[u][stk.top()]);
            stk.pop();
        }
        if (stk.size()) {
            int id = stk.top();
            Edge e1 = adj[u][i];
            Edge e2 = adj[u][id];
            // cout << u << " -> " << cur + 1 << " -> " << e1.v << " id : " << mcur + 1 <<
            // "\n";
            adj[++cur].push_back({e1.v, e1.l + e2.sz, e1.sz - e2.sz, ++mcur});
            up[mcur] = e1.id;
            ver[cur] = ver[e2.v];

            for (auto edge : adj[e2.v]) {
                adj[cur].push_back({edge.v, edge.l, edge.sz, ++mcur});
            }
            aux.push_back({cur, e2.l, e2.sz, ++mcur});
            up[mcur] = up[e2.id];
        }
        stk.push(i);
    }
    while (stk.size()) {
        aux.push_back(adj[u][stk.top()]);
        stk.pop();
    }
    adj[u] = aux;
    for (auto [v, l, sz, id] : adj[u])
        if (!vis[v]) pre_dfs(v);
}

void dfs(int u, int ed_id) {
    // cout << "dfs : " << u << " " << pa << "\n";
    rec.pb({ver[u], ed_id});
    if (path[ver[u]].empty()) path[ver[u]] = rec;
    vis[u] = 1;
    for (auto [v, l, sz, id] : adj[u]) {
        // cout << u << " -> " << v << " : " << id << " \n";
        if (!vis[v]) {
            // cout << u << " -> " << v << " : ";
            // cout << "rec : ";
            // for (int vv : rec) cout << vv << " ";
            // cout << v << "\n";
            dfs(v, id);
        }
    }
    rec.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    pe[0] = qe[0] = 1;
    Ipe[0] = Iqe[0] = 1;
    Ipe[1] = BP(p, mod - 2);
    Iqe[1] = BP(q, mod - 2);

    for (int i = 1; i < N; i++) {
        pe[i] = P(pe[i - 1], p);
        qe[i] = P(qe[i - 1], q);
        Ipe[i] = P(Ipe[i - 1], Ipe[1]);
        Iqe[i] = P(Iqe[i - 1], Iqe[1]);
    }
    cin >> n >> m >> str_sz >> s >> str;
    str = '+' + str;

    pr_p[0] = pr_q[0] = 0;
    for (int i = 1; i <= str_sz; i++) {
        int w = str[i] - 'a' + 1;
        pr_p[i] = S(pr_p[i - 1], P(w, pe[i]));
        pr_q[i] = S(pr_q[i - 1], P(w, qe[i]));
    }
    for (int i = 0; i < N; i++) up[i] = -1;
    for (int i = 0; i < m; i++) {
        int a, b, l, sz;
        cin >> a >> b >> l >> sz;
        adj[a].pb({b, l, sz, i});
    }

    for (int i = 1; i <= n; i++) ver[i] = i;

    cur = n;
    mcur = m - 1;
    // cout << "gaa\n";
    pre_dfs(s);
    for (int i = 1; i <= cur; i++) vis[i] = 0;
    // for (int i = 1; i <= cur; i++) {
    //    cout << i << " : ";
    //    for (auto x : adj[i]) cout << x.v << " ";
    //    cout << "\n";
    //}
    dfs(s, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = int(path[i].size()) - 3; j >= 0; j--) {
            int padre = up[path[i][j + 2].second];
            if (padre != -1) {
                path[i].erase(path[i].begin() + j + 1);
                path[i][j + 1].second = padre;
            }
        }
        cout << path[i].size() << " ";
        for (auto x : path[i]) cout << x.first << " ";
        cout << "\n";
    }

    return 0;
}