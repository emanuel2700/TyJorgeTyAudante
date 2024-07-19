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
    string s;
    cin >> s;
    map<int, string> lv[5];
    lv[0][0] = "***";
    lv[1][0] = "*.*";
    lv[2][0] = "***";
    lv[3][0] = "*.*";
    lv[4][0] = "*.*";

    lv[0][1] = "***";
    lv[1][1] = "*.*";
    lv[2][1] = "***";
    lv[3][1] = "*.*";
    lv[4][1] = "***";

    lv[0][2] = "***";
    lv[1][2] = "*..";
    lv[2][2] = "*..";
    lv[3][2] = "*..";
    lv[4][2] = "***";

    lv[0][3] = "***";
    lv[1][3] = "*.*";
    lv[2][3] = "*.*";
    lv[3][3] = "*.*";
    lv[4][3] = "***";

    lv[0][4] = "***";
    lv[1][4] = "*..";
    lv[2][4] = "***";
    lv[3][4] = "*..";
    lv[4][4] = "***";

    for (int i = 0; i < 5; i++) {
        for (char c : s) {
            cout << lv[i][c - 'A'];
        }
        cout << '\n';
    }

    return 0;
}