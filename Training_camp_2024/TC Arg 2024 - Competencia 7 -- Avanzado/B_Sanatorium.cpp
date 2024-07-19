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

    ll a[3];
    cin >> a[0] >> a[1] >> a[2];
    ll ans = 3e18 + 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ll b[3];
            ll r = 0;
            for (int k = 0; k < 3; k++) b[k] = a[k];
            if (i <= j) {
                for (int k = i; k <= j; k++) {
                    if (b[k] != 0) b[k]--;
                    else r++;
                }
                ll res = *max_element(b, b + 3);
                for (int k = 0; k < 3; k++) r += res - b[k];
            } else {
                for (int k = j + 1; k < i; k++) b[k]++;
                ll res = *max_element(b, b + 3);
                for (int k = 0; k < 3; k++) r += res - b[k];
            }
            ans = min(ans, r);
            // cout << i << " " << j << " " << r << endl;
        }
    }
    cout << ans << '\n';

    return 0;
}