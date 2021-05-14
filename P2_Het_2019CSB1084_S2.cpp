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
lld cycle(lld source, vector<vector<lld>> adj, vector<lld> &visited)
{

    lld res = 0;
    for (auto i = adj[source].begin(); i != adj[source].end(); i++)
    {
        lld theta = *i;
        if (visited[theta] == 0)
        {
            visited[theta] = 1;
            res += dfs(theta, adj, visited);
        }
        else
        {
            res = 1;
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
void print(vector<vector<pair<lld, lld>>> dp)
{
    lld a = dp.size();

    for (lld i = 0; i < a; i++)
    {
        lld b = dp[i].size();
        for (lld j = 0; j < b; j++)
        {
            ps2(dp[i][j].first, dp[i][j].second);
        }
        p("");
    }
}
void print_first(vector<vector<pair<lld, lld>>> dp)
{
    lld a = dp.size();

    for (lld i = 0; i < a; i++)
    {
        lld b = dp[i].size();
        for (lld j = 0; j < b; j++)
        {
            ps(dp[i][j].first);
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
void renew(vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        v[i] = 0;
    }
}
void red_black()
{
    lld n, d, s;
    cin >> n >> d >> s;
    vector<vector<lld>> v(n + 1, vector<lld>(n + 1));
    vector<vector<pair<lld, lld>>> adj(n + 1);
    vector<pair<lld, pair<lld, lld>>> edges;
    vector<lld> toll(n + 1);
    vector<vector<lld>> gamma;
    for (lld i = 1; i <= n; i++)
    {
        for (lld j = 1; j <= n; j++)
        {
            cin >> v[i][j];
        }
    }
    for (lld i = 1; i < toll.size(); i++)
    {
        cin >> toll[i];
    }
    for (lld i = 1; i <= n; i++)
    {
        for (lld j = 1; j <= n; j++)
        {

            if (v[i][j] > 0)
            {
                lld weight = v[i][j] + toll[j];
                pair<lld, lld> e = {v[i][j] + toll[j], j};
                pair<lld, pair<lld, lld>> et = {weight, {i, j}};
                edges.pb(et);
                adj[i].pb(e);
            }
        }
    }
    vector<lld> visited(n + 1);
    lld source = s;
    lld count_nodes = dfs(source, gamma, visited);
    sort(edges.begin(), edges.end());
    lld itr = 0;
    while (count_nodes < n - 1)
    {
        pair<lld, pair<lld, lld>> et = edges[itr];
        lld wt = et.first;
        lld par = et.second.first;
        lld childa = et.second.second;
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