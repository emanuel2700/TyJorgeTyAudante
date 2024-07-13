#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl
const int N = 1e2 + 4;

struct Dsu {
    int n;
    int t[N];

    void build(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) t[i] = i;
    }

    int find(int x) {
        return x == t[x] ? x : t[x] = find(t[x]);
    }

    void join(int a, int b) {
        a = find(a);
        b = find(b);
        t[a] = b;
    }
} dsu[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) dsu[i].build(n);

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        dsu[c].join(a, b);
    }

    int q;
    cin >> q;

    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        for (int c = 1; c <= m; c++)
            if (dsu[c].find(a) == dsu[c].find(b)) ans++;
        cout << ans << "\n";
    }

    return 0;
}