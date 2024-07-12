#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;

#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
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
    int n;
    cin >> n;
    vector<Long> tienda[n];
    REP(i, 2 * n) {
        int a;
        cin >> a;
        a--;
        tienda[a].pb(i);
    }

    Long dis = 0;
    REP(i, n - 1) {
        Long v1 = abs(tienda[i][0] - tienda[i + 1][0]) + abs(tienda[i][1] - tienda[i + 1][1]);
        Long v2 = abs(tienda[i][0] - tienda[i + 1][1]) + abs(tienda[i][1] - tienda[i + 1][0]);
        dis += min(v1, v2);
    }

    cout << dis + tienda[0][0] + tienda[0][1] << endl;

    return 0;
}