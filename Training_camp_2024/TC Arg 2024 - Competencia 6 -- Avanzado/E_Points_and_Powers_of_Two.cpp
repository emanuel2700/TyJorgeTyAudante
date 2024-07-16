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

    int n;
    cin >> n;
    int a[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);

    vector<int> ans = {a[0]};

    for (int e = 0; e <= 30; e++) {
        int w = 1 << e;
        for (int i = 0, l = 0, r = i + 1; i < n; i++) {
            while (a[i] - a[l] > w) l++;
            while (r < n && a[r] - a[i] < w) r++;
            vector<int> aux = {a[i]};
            if (a[i] - a[l] == w) aux.pb(a[l]);
            if (r < n && a[r] - a[i] == w) aux.pb(a[r]);
            if (aux.size() > ans.size()) ans = aux;
        };
    }

    cout << ans.size() << "\n";
    for (int x : ans) cout << x << " ";
    cout << "\n";

    return 0;
}