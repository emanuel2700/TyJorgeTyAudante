#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const ll MOD = 998244353;

ll binpow(ll a, ll b, ll m) { // log(b)
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        ll z = 0, g = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') z++;
            else {
                ll o = 0;
                while (i < n && s[i] == '1') o++, i++;
                i--;
                g += o / 2;
            }
        }
        ll ans = 1;

        for (ll i = 1; i <= g; i++) {
            ans = (ans * (z + i)) % MOD * binpow(i, MOD - 2, MOD) % MOD;

            // ans = ans * (z + i) / i;
        }
        cout << ans << '\n';
    }

    return 0;
}