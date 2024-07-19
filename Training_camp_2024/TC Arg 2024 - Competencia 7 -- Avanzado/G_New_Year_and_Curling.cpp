#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const ll MX = 1e3 + 5;

struct Disco {
    ll x;
    ld y;
};

Disco d[MX];
ll r;

bool choca(Disco i, Disco o) {
    return i.x - r <= o.x + r && i.x + r >= o.x - r;
}

ld cal_h(Disco i, Disco o) {
    return sqrtl(4 * r * r - (i.x - o.x) * (i.x - o.x));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n >> r;

    for (int i = 0; i < n; i++) {
        cin >> d[i].x;
    }

    for (int i = 0; i < n; i++) {
        d[i].y = r;
        for (int j = i - 1; j >= 0; j--) {
            if (!choca(d[i], d[j])) {
                continue;
            } else {
                ld h = cal_h(d[i], d[j]);
                // debug(h);
                // debug(ch);
                d[i].y = max(d[j].y + h, d[i].y);
            }
        }
    }
    cout << fixed << setprecision(10);
    for (int i = 0; i < n; i++) {
        cout << d[i].y << " ";
    }
    cout << endl;

    return 0;
}