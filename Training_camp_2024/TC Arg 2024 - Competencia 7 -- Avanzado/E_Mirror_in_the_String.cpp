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
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        string ans = "";
        ans.pb(s[0]);
        for (int i = 1; i < n; i++) {
            if (i == 1 && s[i] == s[i - 1]) break;
            if (s[i] > s[i - 1]) break;
            ans.pb(s[i]);
        }
        cout << ans;
        reverse(ans.begin(), ans.end());
        cout << ans << '\n';
    }

    return 0;
}