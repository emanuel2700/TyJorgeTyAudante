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

    int t;
    cin >> t;
    ll s[t], e[t];

    for (int i = 0; i < t; i++) cin >> s[i] >> e[i];

    int a1 = 0, a2 = 0;
    int b1 = 0, b2 = 0;
    for (int i = t - 1; i >= 0; i--) {
        a1 ^= 1, b1 ^= 1;
        a2 ^= 1, b2 ^= 1;
        ll l = (e[i] + 2) / 2, r = e[i];

        while (s[i] < l) {
            int aux1 = !(a1 & a2);
            int aux2 = !(a1 & aux1);
            a1 = ((r % 2) ? aux2 : aux1);
            a2 = ((r % 2 == l % 2) ? aux1 : aux2);
            int bux1 = !(b1 | b2);
            int bux2 = !(b1 | bux1);
            b1 = ((r % 2) ? bux2 : bux1);
            b2 = ((r % 2 == l % 2) ? bux1 : bux2);
            r = l - 1;
            l = (l + 1) / 2;
        }

        int aux1 = !(a1 & a2);
        int aux2 = !(a1 & aux1);
        a1 = a2 = ((r % 2 == s[i] % 2) ? aux1 : aux2);
        int bux1 = !(b1 | b2);
        int bux2 = !(b1 | bux1);
        b1 = b2 = ((r % 2 == s[i] % 2) ? bux1 : bux2);
        // cout << a1 << " - " << b1 << "\n";
    }

    cout << a1 << " " << (b1 ^ 1) << "\n";

    return 0;
}