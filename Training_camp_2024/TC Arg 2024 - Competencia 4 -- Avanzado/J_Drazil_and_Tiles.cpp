#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const int N = 4e6 + 4;

int n, m;
char t[N];
int vis[N];
int cnt, total;
vector<int> vers[3];
int deg[N];
vector<int> arr;

bool is_edge(int a, int b) {
    if (a < 0 || b < 0 || n * m <= a || n * m <= b) return 0;
    if (t[a] == '*' || t[b] == '*') return 0;
    if (a % m != b % m && a / m != b / m) return 0;
    return 1;
}

void add_domino(int u, int v) {
    if (u > v) swap(u, v);
    if (u + m == v) {
        t[u] = '^';
        t[v] = 'v';
    } else {
        t[u] = '<';
        t[v] = '>';
    }

    vis[v] = vis[u] = 1;

    for (int x : arr) {
        if (is_edge(u, u + x) && !vis[u + x]) {
            deg[u + x]--;
            if (deg[u + x] <= 2) vers[deg[u + x]].push_back(u + x);
        }
    }

    for (int x : arr) {
        if (is_edge(v, v + x) && !vis[v + x]) {
            deg[v + x]--;
            if (deg[v + x] <= 2) vers[deg[v + x]].push_back(v + x);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n * m; i++) cin >> t[i];

    arr = {1, -1};
    if (m != 1) {
        arr.push_back(m);
        arr.push_back(-m);
    }
    for (int i = 0; i < n * m; i++) {
        if (t[i] == '*') continue;
        if (t[i] == '.') total++;
        for (int v : arr) {
            if (is_edge(i, i + v)) {
                deg[i]++;
            }
        }
        if (deg[i] <= 2) vers[deg[i]].push_back(i);
        // cout << i << "- > " << deg[i] << "\n";
    }

    while (cnt < total) { /*
        for (int id : {0, 1, 2}) {
            cout << id << " : ";
            for (int x : vers[id])
                if (!vis[x] && deg[x] == id) cout << x << " ";
            cout << "\n";
        }
        */

        while (vers[0].size() && (deg[vers[0].back()] != 0 || vis[vers[0].back()]))
            vers[0].pop_back();
        if (vers[0].size()) {
            cout << "Not unique\n";
            return 0;
        }

        while (vers[1].size() && (deg[vers[1].back()] != 1 || vis[vers[1].back()]))
            vers[1].pop_back();
        if (vers[1].size()) {
            int u = vers[1].back();
            vers[1].pop_back();
            int vv;
            for (int v : arr) {
                if (!vis[u + v] && is_edge(u, u + v)) {
                    vv = u + v;
                }
            }
            add_domino(u, vv);
            cnt += 2;
            continue;
        }

        cout << "Not unique\n";
        return 0;
        /*
                while (vers[2].size() && (deg[vers[2].back()] != 2 || vis[vers[2].back()]))
                    vers[2].pop_back();

                int u = vers[2].back();
                vers[2].pop_back();
                int vv;
                for (int v : {-1, +1, m, -m}) {
                    if (!vis[u + v] && is_edge(u, u + v)) {
                        vv = u + v;
                    }
                }
                add_domino(u, vv);
                cnt += 2; */
    }

    for (int i = 0; i < n * m; i++) {
        cout << t[i];
        if (i % m == m - 1) cout << "\n";
    }

    return 0;
}