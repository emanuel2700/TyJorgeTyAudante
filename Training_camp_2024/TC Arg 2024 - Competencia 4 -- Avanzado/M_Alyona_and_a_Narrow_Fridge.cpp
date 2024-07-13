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

    ll n, h;
    cin >> n >> h;
    vl v(n);
    for (auto &i : v) cin >> i;

    ll lo = 0, hi = n + 1;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        bool f = true;
        priority_queue<ll> pq;
        for (int i = 0; i < mid; i++) {
            pq.push(v[i]);
        }
        ll res = 0;
        for (int i = 0; i < mid; i++) {
            if (i % 2 == 0) res += pq.top();
            pq.pop();
        }
        if (res <= h) lo = mid + 1;
        else hi = mid;
    }
    cout << lo - 1;

    return 0;
}