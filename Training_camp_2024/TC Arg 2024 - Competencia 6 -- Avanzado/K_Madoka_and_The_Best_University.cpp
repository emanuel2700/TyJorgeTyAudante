#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const ll MX = 1e5 + 5;
bool isPrime[MX];
ll fact[MX]; // smallest prime factor
vector<ll> primes;

void sieve() { // O(MX)
    // x = i * p. p is the smallest prime factor
    fill(isPrime, isPrime + MX, true);
    isPrime[1] = false;
    for (ll i = 2; i < MX; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            fact[i] = i;
        }
        for (ll j = 0; j < primes.size() && i * primes[j] < MX; j++) {
            isPrime[i * primes[j]] = false;
            fact[i * primes[j]] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

vector<ll> getDivisors(ll x) {
    vector<ll> ans = {1};
    while (x > 1) {
        ll f = fact[x];
        ll num = 1;
        ll sz = ans.size();
        while (x % f == 0) {
            num *= f;
            x /= f;
            for (ll i = 0; i < sz; i++) {
                ans.push_back(num * ans[i]);
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

ll phi[MX];

void calculate() { // O(n log log n)
    for (int i = 0; i < MX; i++) phi[i] = i;
    for (int i = 2; i < MX; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MX; j += i) phi[j] -= phi[j] / i;
        }
    }
}

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sieve();
    calculate();

    ll n;
    cin >> n;
    ll ans = 0;
    for (ll c = 1; c < n - 1; c++) {
        ll k = n - c;
        auto div = getDivisors(k);
        for (auto d : div) {
            if (d == k) continue;
            ans = (ans + (c / gcd(c, d) * d) % MOD * phi[k / d] % MOD) % MOD;
        }
    }
    cout << ans << '\n';

    return 0;
}