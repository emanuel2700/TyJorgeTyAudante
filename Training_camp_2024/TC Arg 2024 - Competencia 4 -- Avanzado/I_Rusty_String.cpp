#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;
using Complex = complex<ld>;

#define pb push_back
#define pf push_front
#define debug(x) cout << #x << " = " << x << endl

const ld PI = acos(-1);

int bitReverse(int x, int lg) { // O(lg)
    int ans = 0;
    for (int i = 0; i < lg; i++) {
        ans = ans * 2 + x % 2;
        x /= 2;
    }
    return ans;
}

void fft(vector<Complex> &a, bool invert) { // O(n log n)
    // n must be a power of 2
    int n = a.size();
    int lg = 31 - __builtin_clz(n);
    for (int i = 0; i < n; i++) {
        int target = bitReverse(i, lg);
        if (i < target) swap(a[i], a[target]);
    }
    int sgn = 1;
    if (invert) sgn = -1;
    for (int len = 2; len <= n; len *= 2) {
        Complex wn = polar((ld)1, sgn * 2.0 * PI / len);
        for (int l = 0; l < n; l += len) {
            Complex w(1);
            for (int d = 0; d < len / 2; d++) {
                Complex even = a[l + d];
                Complex odd = a[l + d + len / 2] * w;
                a[l + d] = even + odd;
                a[l + d + len / 2] = even - odd;
                w *= wn;
            }
        }
    }
}

using poly = vector<ll>;

poly operator*(const poly &a, const poly &b) { // O(n log n)
    vector<Complex> fa(a.begin(), a.end());
    vector<Complex> fb(b.begin(), b.end());
    ll n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
        fa[i] /= n; // inverse
    }
    fft(fa, true);

    poly ans(a.size() + b.size() - 1);
    for (int i = 0; i < ans.size(); i++) ans[i] = round(fa[i].real());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        vl ans(n + 1, 1);
        poly a(n), b(n);
        for (int i = 0; i < n; i++) a[i] = s[i] == 'V';
        for (int i = n - 1; i >= 0; i--) b[n - 1 - i] = s[i] == 'K';
        poly m = a * b;
        for (int i = 0; i < n; i++) {
            if (m[i]) ans[n - i - 1] = 0;
        }

        for (int i = 0; i < n; i++) a[i] = s[i] == 'K';
        for (int i = n - 1; i >= 0; i--) b[n - 1 - i] = s[i] == 'V';
        m = a * b;
        for (int i = 0; i < n; i++) {
            if (m[i]) ans[n - i - 1] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i)
                if (!ans[j]) ans[i] = 0;
        }

        vl res;
        for (int i = 1; i <= n; i++)
            if (ans[i]) res.pb(i);
        cout << res.size() << '\n';
        for (auto i : res) cout << i << " ";
        cout << '\n';
    }

    return 0;
}