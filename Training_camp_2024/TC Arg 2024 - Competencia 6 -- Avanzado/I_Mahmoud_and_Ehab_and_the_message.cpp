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

    int n, m, k;
    cin >> n >> m >> k;
    map<string, int> id;
    vi val(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        id[s] = i + 1;
    }
    for (auto &i : val) cin >> i;
    priority_queue<int> pq[m];
    int group[n];
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        while (a--) {
            int x;
            cin >> x;
            pq[i].push(-val[x - 1]);
            group[x - 1] = i;
        }
    }
    int cnt[m];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        cnt[group[id[s] - 1]]++;
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        while (cnt[i] > 0) {
            ll res = -pq[i].top();
            ans += res;
            cnt[i]--;
        }
    }
    cout << ans << '\n';

    return 0;
}