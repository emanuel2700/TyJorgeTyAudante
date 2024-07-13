#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl
const int N = 1e5 + 4;
const int mod = 1e9 + 7;

int S(int a, int b) {
    return (a + b) % mod;
}

int P(int a, int b) {
    return 1ll * a * b % mod;
}

int BP(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = P(a, a))
        if (b & 1) ans = P(ans, a);
    return ans;
}

int x, y;
int m;
map<int, int> dp;

int Dp(int m) {
    if (dp.find(m) != dp.end()) return dp[m];
    int val = S(BP(2, m - 1), mod - 1);
    for (int x = 2; x * x <= m; x++) {
        if (m % x == 0) {
            if (x * x == m) {
                val = S(val, mod - Dp(x));
            } else {
                val = S(val, mod - Dp(x));
                val = S(val, mod - Dp(m / x));
            }
        }
    }
    dp[m] = val;
    return dp[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> x >> y;

    if (y % x != 0) {
        cout << "0\n";
        return 0;
    }

    m = y / x;
    dp[1] = 1;

    cout << Dp(m) << "\n";

    return 0;
}