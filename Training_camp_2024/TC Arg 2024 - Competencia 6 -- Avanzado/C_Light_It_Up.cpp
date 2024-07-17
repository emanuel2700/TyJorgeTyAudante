#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (ll i = 0; i < (ll)n; i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;

    vector<ll> v;
    v.pb(0);
    REP(i, n) {
        ll a;
        cin >> a;
        v.pb(a);
    }
    v.pb(m);

    ll pre_on[n + 5];
    ll pre_of[n + 5];
    fill(pre_on, pre_on + n + 5, 0);
    fill(pre_of, pre_of + n + 5, 0);

    for (int i = 1; i < n + 2; i++) {
        if (i & 1) { // impar
            pre_on[i] = pre_on[i - 1] + v[i] - v[i - 1];
            pre_of[i] = pre_of[i - 1];
        } else { // par
            pre_on[i] = pre_on[i - 1];
            pre_of[i] = pre_of[i - 1] + v[i] - v[i - 1];
        }
    }
    ll INF = 1e18;
    ll ma = pre_on[n + 1];
    for (int i = 1; i < n + 1; i += 2) {
        if (v[i] - v[i - 1] > 1) {
            ll add = v[i] - 1;
            ma = max(ma, pre_on[i] - 1 + pre_of[n + 1] - pre_of[i]);
        }
        if (v[i + 1] - v[i] > 1) {
            ll add = v[i] + 1;
            ma = max(ma, pre_on[i] + pre_of[n + 1] - pre_of[i] - 1);
        }
    }
    cout << ma << endl;

    return 0;
}