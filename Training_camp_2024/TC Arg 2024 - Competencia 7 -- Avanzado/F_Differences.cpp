#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define REP(i, n) for (ll i = 0; i < (ll)n; i++)
#define debug(x) cout << #x << " = " << x << endl;
#define pb push_back
#define pf push_front
#define all(x) x.begin(), x.end()
#define FIN                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main() {
    FIN;
    ll n, m, k;
    cin >> n >> m >> k;
    mt19937 rng(2137);

    string s[n];
    REP(i, n) cin >> s[i];

    vector<ll> hash(n);
    REP(i, n) hash[i] = rng();

    vector<ll> Dif(n);
    REP(j, m) {
        vector<ll> L(4);
        ll S = 0;
        REP(i, n) {
            L[s[i][j] - 'A'] += hash[i];
            S += hash[i];
        }
        REP(i, n) {
            Dif[i] += S - L[s[i][j] - 'A'];
        }
    }

    ll sum = accumulate(all(hash), 0LL);

    REP(i, n) {
        if ((sum - hash[i]) * k == Dif[i]) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    return 0;
}