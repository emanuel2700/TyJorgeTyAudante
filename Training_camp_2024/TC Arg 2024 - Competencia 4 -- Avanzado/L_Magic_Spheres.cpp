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

    int a, b, c, x, y, z;
    cin >> a >> b >> c;
    cin >> x >> y >> z;

    int changes = 0;
    int need = 0;
    if (a > x) {
        changes += (a - x) / 2;
    } else if (a < x) {
        need += (x - a);
    }

    if (b > y) {
        changes += (b - y) / 2;
    } else if (b < y) {
        need += (y - b);
    }

    if (c > z) {
        changes += (c - z) / 2;
    } else if (c < z) {
        need += (z - c);
    }

    cout << (changes >= need ? "Yes" : "No") << '\n';

    return 0;
}