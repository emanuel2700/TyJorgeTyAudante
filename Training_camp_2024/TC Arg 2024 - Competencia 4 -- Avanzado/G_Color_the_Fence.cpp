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

    int v;
    cin >> v;

    const int N = 1e6 + 4;
    int pr[N];

    for (int i = 0; i < N; i++) pr[i] = 0;

    int a[10], min_price = 1e9;
    for (int i = 1; i < 10; i++) {
        cin >> a[i];
        min_price = min(min_price, a[i]);
        pr[a[i]] = max(pr[a[i]], i);
    }

    if (min_price > v) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 1; i < N; i++) {
        pr[i] = max(pr[i - 1], pr[i]);
    }

    int cnt = v / min_price;

    for (int i = cnt; i > 0; i--) {
        int _v = min_price * (cnt - 1);
        int val = v - _v;
        cout << pr[val];
        v -= a[pr[val]];
        cnt--;
    }

    return 0;
}