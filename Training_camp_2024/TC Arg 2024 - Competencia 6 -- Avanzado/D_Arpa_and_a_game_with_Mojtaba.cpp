#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const int N = 1 << 20;
int G1[N];
map<int, int> G2;

int G(int mask) {
    if (mask < N) return G1[mask];
    if (G2.find(mask) != G2.end()) return G2[mask];
    int k = 31 - __builtin_clz(mask);
    int mex = 0, aux = 0;
    int vis[31];
    for (int i = 0; i <= k + 1; i++) vis[i] = 0;
    for (int i = 1; i <= k + 1; i++) {
        int _mask = mask & aux;
        _mask |= mask >> i;
        vis[G(_mask)] = 1;
        aux |= (1 << (i - 1));
    }
    while (vis[mex]) mex++;
    G2[mask] = mex;
    return mex;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int vis[31];
    G1[0] = 0;
    for (int mask = 1; mask < (1 << 20); mask++) {
        int k = 31 - __builtin_clz(mask);
        int mex = 0;
        for (int i = 0; i <= k + 1; i++) vis[i] = 0;
        int aux = 0;
        for (int i = 1; i <= k + 1; i++) {
            int _mask = mask & aux;
            _mask |= mask >> i;
            vis[G1[_mask]] = 1;
            aux |= (1 << (i - 1));
        }
        while (vis[mex]) mex++;
        G1[mask] = mex;
    }
    int n;
    cin >> n;
    map<int, int> mp;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int d = 2; d * d <= x; d++) {
            if (x % d) continue;
            int e = 0;
            while (x % d == 0) x /= d, e++;
            mp[d] |= 1 << (e - 1);
        }
        if (x > 1) mp[x] |= 1;
    }

    int ans = 0;
    for (auto [p, mask] : mp) {
        // cout << p << " " << mask << " - \n";
        ans ^= G(mask);
        // cout << G(mask) << " <- \n";
    }

    cout << (ans ? "Mojtaba\n" : "Arpa\n");
    return 0;
}