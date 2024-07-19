#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

using ordered_set =
    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set s;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, q;
    cin >> n >> m >> q;

    vl cnt(m + 1);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        cnt[a]++;
    }

    vector<pair<ll, ll>> querys;
    for (int i = 0; i < q; i++) {
        ll a;
        cin >> a;
        querys.pb({a, i});
    }
    sort(querys.begin(), querys.end());

    priority_queue<pair<ll, ll>> pq;
    for (int i = 1; i <= m; i++) {
        pq.push({-cnt[i], i});
    }

    ll ans[q];
    ll l = 0, r, m1 = n;
    while (!pq.empty() && l < q) {
        auto p = pq.top();
        while (!pq.empty() && pq.top().first == p.first) {
            s.insert(pq.top().second);
            pq.pop();
        }
        int sz = s.size();

        if (pq.empty()) r = q - 1;
        else {
            ll mx = sz * (p.first - pq.top().first);
            pair<ll, ll> pa = make_pair(mx + m1 + 1, -1LL);
            r = upper_bound(querys.begin(), querys.end(), pa) - querys.begin() - 1;
        }

        for (int i = l; i <= r; i++) {
            ll res = *s.find_by_order((querys[i].first - m1 - 1) % sz);
            ans[querys[i].second] = res;
        }

        if (!pq.empty()) {
            if (r >= l) l = r + 1;
            ll mx = sz * (p.first - pq.top().first);
            m1 += mx;
        }
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';

    return 0;
}