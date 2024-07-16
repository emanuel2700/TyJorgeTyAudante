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

    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
    }

    for (int i = 0; i < n; i++) {
        if (i & 1) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    cout << endl;

    return 0;
}