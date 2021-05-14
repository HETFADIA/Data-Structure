#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define lld long long
#define p(x) cout << x << "\n";
#define p2(x, y) cout << x << " " << y << "\n";
#define p3(x, y, z) cout << x << " " << y << " " << z << "\n";
#define ps(x) cout << x << " ";
#define ps2(x, y) cout << x << " " << y << " ";
#define ps3(x, y, z) cout << x << " " << y << " " << z << " ";
#define ps4(x, y, z, a) cout << x << " " << y << " " << z << " " << a << " ";
#define ps5(x, y, z, a, b) cout << x << " " << y << " " << z << " " << a << " " << b << " ";
#define pns(x) cout << x;
#define inp(x) cin >> x;
#define inp2(x, y) cin >> x >> y;
#define inp3(x, y, z) cin >> x >> y >> z;
#define endl "\n"
#define all(x) x.begin(), x.end()
#define dll(x) x.begin(), x.end(), greater<lld>()
#define vect(x, n) vector<lld> x(n, 0);
#define matrix(x, n, m) vector<vector<lld>> x(n, vector<lld>(m, 0));
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) (a * b) / gcd(a, b)
#define lb lower_bound
#define ub upper_bound
#define pb(x) push_back(x);
#define pf(x) push_front(x);
#define mkp(x, y) make_pair(x, y)
#define inf 1e14
void add_edge(vector<vector<lld>> &adj, lld i, lld j)
{
}
lld dfs(lld source, vector<vector<lld>> adj, vector<lld> &visited)
{

    lld res = 1;
    for (auto i = adj[source].begin(); i != adj[source].end(); i++)
    {
        lld theta = *i;
        if (visited[theta] == 0)
        {
            visited[theta] = 1;
            res += dfs(theta, adj, visited);
        }
    }
    return res;
}
void print(vector<vector<lld>> dp)
{
    lld a = dp.size();

    for (lld i = 0; i < a; i++)
    {
        lld b = dp[i].size();
        for (lld j = 0; j < b; j++)
        {
            ps(dp[i][j]);
        }
        p("");
    }
}
lld find_one(vector<lld> visited)
{
    lld count = 0;
    for (lld i = 0; i < visited.size(); i++)
    {
        if (visited[i] == 1)
        {
            count += 1;
        }
    }
    return count;
}
void red_black()
{
    lld n, source;
    cin >> n >> source;
    vector<vector<lld>> v(n + 1, vector<lld>(n + 1));
    vector<vector<lld>> adj(n + 1);
    for (lld i = 1; i <= n; i++)
    {
        for (lld j = 1; j <= n; j++)
        {
            cin >> v[i][j];
            if (v[i][j] < 0)
            {
                adj[i].pb(j);
            }
        }
    }

    vector<lld> visited(n + 1);

    dfs(source, adj, visited);
    lld nodes = find_one(visited);
    if (nodes < n - 1)
    {
        p2(0, 0);
        return;
    }
    else
    {
        p(1);
    }
}
signed main()
{
    lld t;
    cin >> t;
    while (t--)
    {
        red_black();
    }
}