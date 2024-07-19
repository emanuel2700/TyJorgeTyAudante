#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n, x;
    cin >> n >> x;
    vector<ll> v[n];
    if (n <= x) {
        cout << -1 << endl;
        return 0;
    }

    ll c = n * x;
    ll cont = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < x; j++) {
            v[i].pb(cont);
            cont++;
        }
    }
    vector<ll> v2[n];
    for (int i = 0; i < n; i++) {
        ll k = i + 1;
        for (ll a : v[i]) {
            if (k == i) continue;
            v2[k % n].pb(a);
            k++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (ll a : v2[i]) {
            v[i].pb(a);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * x; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}