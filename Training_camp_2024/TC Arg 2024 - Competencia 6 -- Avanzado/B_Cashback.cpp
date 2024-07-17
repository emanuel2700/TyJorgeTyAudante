#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const ll MX2 = 2e3 + 2, MX = 2e5 + 7;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const double INF_DOUBLE = 1e18 / 1.0;
const double EPS = 1e-8;
const double PI = acos(-1.0);
ll operador(ll x, ll y) {
    return min(x, y);
}

struct SegmentTree {
    ll t[2 * MX];
    int n;

    void clear(int n) {
        for (int i = 1; i <= 2 * n; i++) {
            t[i] = 0;
        }
        this->n = n;
    }

    void build(vector<ll> &a, ll id, ll tl, ll tr) { // O(n)
        if (tl == tr) {
            t[id] = a[tl - 1];
        } else {
            ll tm = (tl + tr) / 2;
            ll left = id + 1;
            ll right = id + 2 * (tm - tl + 1);
            build(a, left, tl, tm);
            build(a, right, tm + 1, tr);
            t[id] = operador(t[left], t[right]);
        }
    }

    void build(vector<ll> &a) {
        n = a.size();
        build(a, 1, 1, n);
    }

    ll query(ll l, ll r, ll id, ll tl, ll tr) { // O(logn)
        // if (tr < l || tl > r || l>R) return 0; //Dependiendo lo que te pidan
        if (l <= tl && tr <= r) return t[id];
        ll tm = (tl + tr) / 2;
        ll left = id + 1;
        ll right = id + 2 * (tm - tl + 1);
        if (r < tm + 1) return query(l, r, left, tl, tm);
        else if (tm < l) return query(l, r, right, tm + 1, tr);
        else return operador(query(l, r, left, tl, tm), query(l, r, right, tm + 1, tr));
    }

    ll query(ll l, ll r) {
        assert(n > 0);
        return query(l, r, 1, 1, n);
    }

    void update(ll pos, ll val, ll id, ll tl, ll tr) { // O(logn)
        if (tl == tr) {
            t[id] += val;
        } else {
            ll tm = (tl + tr) / 2;
            ll left = id + 1;
            ll right = id + 2 * (tm - tl + 1);
            if (pos <= tm) update(pos, val, left, tl, tm);
            else update(pos, val, right, tm + 1, tr);
            t[id] = operador(t[left], t[right]);
        }
    }

    void update(ll pos, ll val) {
        assert(n > 0);
        update(pos, val, 1, 1, n);
    }
} st;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, c;
    cin >> n >> c;
    vl v(n);
    for (auto &i : v) cin >> i;
    if (c == 1) {
        cout << 0 << '\n';
        return 0;
    }
    st.build(v);

    vl pref(n + 1), mn(n + 1);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + v[i];
        mn[i] = st.query(i + 1, min(i + c, n));
        // debug(mn[i]);
    }

    vl dp(n + 2);
    for (int i = n; i >= 1; i--) {
        dp[i] = dp[i + 1] + v[i - 1];
        if (i + c - 1 <= n) {
            dp[i] = min(dp[i], dp[i + c] + pref[i + c - 1] - pref[i - 1] - mn[i - 1]);
        }
        // cout << i << " " << dp[i] << endl;
    }
    cout << dp[1] << '\n';

    return 0;
}