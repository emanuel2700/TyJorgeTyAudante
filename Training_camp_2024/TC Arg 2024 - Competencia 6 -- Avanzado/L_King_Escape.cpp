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
    pair<int, int> a, b, c;
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    cin >> c.first >> c.second;

    if (b.first < a.first && c.first < a.first) {
        if (b.second > a.second && c.second > a.second) {
            cout << "YES\n";
        } else if (b.second < a.second && c.second < a.second) {
            cout << "YES\n";
        } else cout << "NO\n";
    } else if (b.first > a.first && c.first > a.first) {
        if (b.second > a.second && c.second > a.second) {
            cout << "YES\n";
        } else if (b.second < a.second && c.second < a.second) {
            cout << "YES\n";
        } else cout << "NO\n";
    } else cout << "NO\n";

    return 0;
}