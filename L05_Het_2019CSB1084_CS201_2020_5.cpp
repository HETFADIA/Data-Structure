#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define int long long
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
//here inf is used for null ie if a=inf is used for like a=null
void copy(set<pair<lld, lld>> real, set<pair<lld, lld>> &virtuala)
{
    //to copy first set lldo another
    set<pair<lld, lld>>::iterator i;
    for (i = real.begin(); i != real.end(); i++)
    {
        lld fi = i->first;
        lld se = i->second;
        virtuala.insert({fi, se});
    }
}
struct sec_then_first
{
    //sorts the pair by second value first and then first
    bool operator()(const pair<lld, lld> &x, const pair<lld, lld> &y) const
    {
        return x.second < y.second || (x.second == y.second && x.first < y.first);
    }
};
lld min(vector<lld> v)
{
    //returns min element in vector v
    lld res = 0;
    if (v.size())
    {
        res = v[0];
    }
    for (lld i = 0; i < v.size(); i++)
    {
        if (res > v[i])
        {
            res = v[i];
        }
    }
    return res;
}
lld index(vector<lld> v, lld val)
{
    //returns the index of val in vector v
    for (lld i = 0; i < v.size(); i++)
    {
        if (v[i] == val)
        {
            return i;
        }
    }
    return 0;
}
lld get(map<lld, lld> pi, lld val)
{
    //as the name suggests it returns pi[val] if it is found else it returns inf
    map<lld, lld>::iterator finder;
    finder = pi.find(val);
    if (finder == pi.end())
    {
        return inf;
    }
    return pi[val];
}
lld present(set<lld> seta, lld val)
{
    //as the name suggests it returns 1 if val is found in set else it returns 0
    set<lld>::iterator finder;
    finder = seta.find(val);
    if (finder == seta.end())
    {
        return 0;
    }
    return 1;
}
lld present(set<pair<lld, lld>> seta, pair<lld, lld> tuple)
{
    //as the name suggests it returns 1 if tuple is found in set else it returns 0
    set<pair<lld, lld>>::iterator finder;
    finder = seta.find(tuple);
    if (finder == seta.end())
    {
        return 0;
    }

    return 1;
}
lld present(map<lld, lld> mapa, lld val)
{
    //as the name suggests it returns 1 if val is found in map else it returns 0
    map<lld, lld>::iterator finder;
    finder = mapa.find(val);
    if (finder == mapa.end())
    {
        return 0;
    }
    return 1;
}
void print(vector<lld> v)
{
    //prints the vector
    for (lld i = 0; i != v.size(); i++)
    {
        ps(v[i]);
    }
    p("");
}
void prints(vector<lld> v)
{
    //prints the vector from 1st index
    for (lld i = 1; i != v.size(); i++)
    {
        ps(v[i]);
    }
}
void print(set<pair<lld, lld>> seta)
{
    //prints the set it is used for debuggging
    set<pair<lld, lld>>::iterator i;
    for (i = seta.begin(); i != seta.end(); i++)
    {
        ps2(i->first, i->second);
    }
    p("");
}
void print(map<lld, lld> mapa)
{
    //prints the map it is used for debuggging
    map<lld, lld>::iterator i;
    for (i = mapa.begin(); i != mapa.end(); i++)
    {
        ps4("{", i->first, i->second, "}");
    }
    p("");
}
void print(set<lld> seta)
{
    //prints the set it is used for debuggging
    set<lld>::iterator i;
    for (i = seta.begin(); i != seta.end(); i++)
    {
        ps(*i);
    }
    p("");
}
void print(map<pair<lld, lld>, pair<lld, lld>> mapa)
{
    //prints the map it is used for debuggging
    map<pair<lld, lld>, pair<lld, lld>>::iterator i;
    for (i = mapa.begin(); i != mapa.end(); i++)
    {
        ps4(i->first.first, i->first.second, i->second.first, i->second.second);
    }
}
void print(map<pair<lld, lld>, lld> mapa)
{
    //prints the map it is used for debuggging
    map<pair<lld, lld>, lld>::iterator i;
    for (i = mapa.begin(); i != mapa.end(); i++)
    {
        ps5("{", i->first.first, i->first.second, i->second, "}");
    }
    p("");
}
void print(pair<lld, lld> tuple)
{
    //prints the tuple it is used for debuggging
    p2(tuple.first, tuple.second);
}
lld min_index(vector<lld> cost)
{
    //returns the index of the min element of cost ie if min(cost)=4 then it returns index(4) in cost vector
    lld index = 0;
    lld min_cost = 0;
    if (cost.size())
    {
        min_cost = cost[0];
    }
    for (lld i = 0; i < cost.size(); i++)
    {
        if (min_cost > cost[i])
        {
            min_cost = cost[i];
            index = i;
        }
    }
    return index;
}
lld inrange(lld theta, lld n)
{
    //returns 1 if 0<=theta<=n;
    if (theta >= 0 && theta <= n)
    {
        return 1;
    }
    return 0;
}
void minimum_arbo(set<lld> V, set<pair<lld, lld>> E, lld r, map<pair<lld, lld>, lld> w, set<pair<lld, lld>> &answer, lld n, lld &times)
{
    //First step Removing all edges that lead back to the root
    //to do it we have to make copy of edges
    set<pair<lld, lld>>::iterator i;
    if (times == 0)
    {
        times++;
        //we will do this job only once as all the edges leading back to source are removed they will never appear again
        set<pair<lld, lld>> edges_copy;

        //first I will copy Edges E lldo edges_copy
        for (i = E.begin(); i != E.end(); i++)
        {
            lld u = i->first;
            lld v = i->second;
            edges_copy.insert({u, v});
        }
        //now i will delete edges that lead back to parent r
        for (i = edges_copy.begin(); i != edges_copy.end(); i++)
        {
            lld u = i->first;
            lld v = i->second;
            if (v == r)
            {
                //we delete the edge leading to vertex from both edges and weights
                E.erase({u, v});
                w.erase({u, v});
            }
        }
    }
    map<lld, set<pair<lld, lld>>> parent;
    for (i = E.begin(); i != E.end(); i++)
    {
        lld u = i->first;
        lld v = i->second;

        lld weighta = w[{u, v}];
        //we copy E to parent
        parent[v].insert({weighta, u});
    }

    // in this next step we find the minimum incoming edge for every vertex
    map<lld, lld> pi;
    set<lld>::iterator is;
    set<pair<lld, lld>>::iterator begina;
    //since it is given that in supernode the destination vertex having less lable is to be removed i am starting from V.begin
    for (is = V.begin(); is != V.end(); is++)
    {
        lld v = *is;
        if (parent[v].empty() == 0)
        {
            //if parent[v] is empty ie there are no parent so we return
            begina = parent[v].begin();
            lld parenta = begina->second;
            pi[v] = parenta;
            //pi[v] maps v to parent[v]
        }
    }

    //in this step we find cycles in the graph
    //if cycle is not found cycle_vertex will be still inf
    lld cycle_vertex = inf;
    lld next_v;
    for (is = V.begin(); is != V.end(); is++)
    {
        lld v = *is;
        if (cycle_vertex != inf)
        {
            break;
        }
        set<lld> visited;
        next_v = get(pi, v);

        while (next_v != inf && next_v != 0)
        {
            //when next_v is inf meaning null or it is 0 we break from loop
            set<lld>::iterator finder;
            finder = visited.find(next_v);
            if (finder != visited.end())
            {
                cycle_vertex = next_v;
                visited.erase(next_v);
                break;
            }
            visited.insert(next_v);
            next_v = get(pi, next_v);
            //get function returns pi[next_v] if it is found else returns inf
        }
    }

    //in this set if there is no cycle, return all the minimum edges pi(v)
    if (cycle_vertex == inf)
    {
        // set<pair<lld, lld>> answera;
        answer.clear();
        map<lld, lld>::iterator i;
        for (i = pi.begin(); i != pi.end(); i++)
        {
            lld v = i->first;
            pair<lld, lld> e = {pi[v], v};
            answer.insert(e);
        }
        return;
        //no cycle is found so we return
    }
    //if we do not return no cylce is found
    // so in set C we store the cylce vertices in it
    set<lld> C;
    C.insert(cycle_vertex);
    next_v = get(pi, cycle_vertex);
    //get function returns inf if vertex cycle_vertex is found in map pi else returns inf (inf == null here)
    while (next_v != cycle_vertex)
    {
        C.insert(next_v);
        next_v = get(pi, next_v);
        //get functions returns pi[next_v] ie parent of next_v if it is found else it returns inf and we break out of the loop
    }

    lld v_c = -cycle_vertex * cycle_vertex;
    //making v_c the supernode vertex negative so that it does not conflice with any other vertex
    set<lld> V_prime;
    set<lld>::iterator theta;
    for (theta = V.begin(); theta != V.end(); theta++)
    {
        lld v = *theta;
        if (present(C, v) == 0)
        {
            //if v is not present in cycle v then we add it
            V_prime.insert(v);
        }
    }
    V_prime.insert(v_c); //we also insert the cycle vertex renamed v_c

    set<pair<lld, lld>> E_prime;
    //E_prime will contain edges of supernode
    map<pair<lld, lld>, lld> w_prime;
    //w_prime will contain weights of edges of supernode
    map<pair<lld, lld>, pair<lld, lld>> correspondance;
    pair<lld, lld> e;
    set<pair<lld, lld>>::reverse_iterator iter;
    for (iter = E.rbegin(); iter != E.rend(); iter++)
    {
        lld u = iter->first;
        lld v = iter->second;
        lld wt = w[{u, v}];
        if (present(C, u) == 0 && present(C, v) == 1)
        {
            //if u is not present in cycle and v is present then we insert u->v_c where v_c is cycle vertex(vertex representing cycle)
            e = {u, v_c};
            if (present(E_prime, e) == 1)
            {
                if (w_prime[e] < wt - w[{pi[v], v}])
                {
                    //if the weight is more we continue with next iteration
                    continue;
                }
            }
            w_prime[e] = wt - w[{pi[v], v}];
            correspondance[e] = {u, v};
            E_prime.insert(e);
        }
        else if (present(C, u) == 1 && present(C, v) == 0)
        {
            //if u is present in cycle and v is not present in cylce then we replace the u with v_c (v_c is vertex representing cylce)
            e = {v_c, v};
            if (present(E_prime, e) == 1)
            {
                pair<lld, lld> elementa;
                elementa = correspondance[e];
                lld old_u = elementa.first;
                if (w[{old_u, v}] < wt)
                {

                    continue;
                }
            }
            E_prime.insert(e);
            w_prime[e] = wt;
            correspondance[e] = {u, v};
        }
        else if (present(C, u) == 0 && present(C, v) == 0)
        {
            //if both are absent from cycle then we insert them lldo E_prime
            e = {u, v};
            E_prime.insert(e);
            w_prime[e] = wt;
            correspondance[e] = {u, v};
        }
    }
    //calling it again as cycle is found to make it recursive
    //we pass V_prime the vertices after supernode is combined to v_c
    minimum_arbo(V_prime, E_prime, r, w_prime, answer, n, times);
    //we just make a temporary edge cycle_edge as {inf,inf} here also inf represents null
    pair<lld, lld> cycle_edge = {inf, inf};
    // set<pair<lld, lld>>::iterator i;
    for (i = answer.begin(); i != answer.end(); i++)
    {
        lld u = i->first;
        lld v = i->second;
        if (v == v_c)
        {
            e = {u, v_c};
            pair<lld, lld> elementa = correspondance[e];
            lld old_v = elementa.second;
            cycle_edge = {pi[old_v], old_v};
            break;
        }
    }
    set<pair<lld, lld>> ret;
    //the ret will contain the edges of minimum cost arborescence
    for (i = answer.begin(); i != answer.end(); i++)
    {
        lld u = i->first;
        lld v = i->second;
        // we insert the corresponding edge in ret the corresponding edge is the edge replacing the vertex in cycle with v_c(v_c is used for representing cycle)
        ret.insert(correspondance[{u, v}]);
    }
    set<lld>::iterator itr;
    for (itr = C.begin(); itr != C.end(); itr++)
    {
        //we have to also insert parent of all the vertices in the cycle lldo ret
        lld v = *itr;
        lld u = pi[v];
        ret.insert({u, v});
    }
    //we remove that temporary edge cycle_edge from ret
    ret.erase(cycle_edge);
    //we clear unnecessary edges in answer
    answer.clear();
    //to copy the answer from ret to answer
    copy(ret, answer);
}
lld sum_finder(vector<set<pair<lld, lld>>> child, lld source, vector<lld> &distance)
{
    //returns the total sum of arborescence
    lld suma = 0;
    set<pair<lld, lld>>::iterator i;
    for (i = child[source].begin(); i != child[source].end(); i++)
    {
        lld wt = i->first;
        distance[i->second] = distance[source] + wt;
        suma += wt;
        suma += sum_finder(child, i->second, distance);
    }
    return suma;
}
void transfer_set_to_vector(set<pair<lld, lld>> answer, vector<set<pair<lld, lld>>> &child, vector<set<pair<lld, lld>>> &directparent, map<pair<lld, lld>, lld> weight)
{
    //copies the set answer to vector child and directparent
    set<pair<lld, lld>>::iterator i;
    for (i = answer.begin(); i != answer.end(); i++)
    {
        lld u = i->first;
        lld v = i->second;
        lld w = weight[{u, v}];
        child[u].insert({w, v});
        directparent[v].insert({w, u});
    }
}
void print_parent(vector<set<pair<lld, lld>>> directparent, lld n, lld s)
{
    //prints the parent of every node
    set<pair<lld, lld>>::iterator j;
    for (lld i = 1; i <= n; i++)
    {
        if (directparent[i].size() != 0)
        {
            //we print the parent of i
            j = directparent[i].begin();
            ps(j->second);
        }
        else
        {
            if (i == s)
            {
                //if it is source we print 0
                ps(0);
            }
            else
            {
                //if no parent implies unreachable so we print -1
                ps(-1);
            }
        }
    }
}
lld get(map<pair<lld, lld>, lld> weight, pair<lld, lld> e)
{
    //as the name suggests it returns weight[e] if e is found in weight else it returns inf (inf = null here)
    map<pair<lld, lld>, lld>::iterator finder;
    finder = weight.find(e);
    if (finder == weight.end())
    {
        //if not found we return inf;
        return inf;
    }
    return weight[e];
}
void find_unnecessary_edges(lld r, vector<set<lld>> &all_edges, vector<lld> &visited)
{
    //finds disconnected edges;
    visited[r] = 1;
    set<lld>::iterator i;
    for (i = all_edges[r].begin(); i != all_edges[r].end(); i++)
    {
        lld t = *i;
        if (visited[t] == 0)
        {
            find_unnecessary_edges(t, all_edges, visited);
        }
    }
}
void remove_unnecessary_edges(lld r, vector<set<lld>> &all_edges, vector<lld> &visited, set<pair<lld, lld>> &edges)
{
    //removes disconnected edges as they are useless;
    for (lld i = 0; i < visited.size(); i++)
    {
        if (visited[i] == 0)
        {
            set<lld>::iterator theta;
            for (theta = all_edges[i].begin(); theta != all_edges[i].end(); theta++)
            {
                lld childa = *theta;
                //we erase unnecessary edges from the graph
                edges.erase({i, childa});
            }
        }
    }
}
void arborescence()
{
    lld n, m, s;
    lld u, v, w;
    cin >> n >> m >> s;
    set<lld> vertex;
    //in this set vertex we will store vertices
    set<pair<lld, lld>> edges;
    //in this set of pair edges we store the edges in the paired form
    vector<set<lld>> all_edges(n + 1);
    map<pair<lld, lld>, lld> wt;
    //negative edge found variable below line is 0 when none edge weight is <=0
    bool negative_edge_found = 0;
    //we take m edges in input using below for loop
    for (lld i = 0; i < m; i++)
    {
        //we take input in this for loop
        cin >> u >> v >> w;
        if (w < get(wt, {u, v})) //in case of multiple edges i select the edge with min wt
        {
            vertex.insert(v);
            edges.insert({u, v});
            all_edges[u].insert(v);
            wt[{u, v}] = w;
            if (w < 0)
            {
                negative_edge_found = 1;
                //if negative edge wt is found we make the above variable 1
            }
        }
    }
    if (negative_edge_found == 1)
    {
        //negative edge is found so we print -1 and return
        p(-1);
        return;
    }
    set<pair<lld, lld>> answer;
    vector<set<pair<lld, lld>>> child(n + 1);
    vector<set<pair<lld, lld>>> directparent(n + 1);
    lld times = 0; //to make sure the edges to source are remvoed only once
    vector<lld> visited(n + 1);
    find_unnecessary_edges(s, all_edges, visited); //these edges are not rechable so they are found here
    //then they are removed in the below code
    remove_unnecessary_edges(s, all_edges, visited, edges);
    //we call arborescence function
    minimum_arbo(vertex, edges, s, wt, answer, n, times);
    transfer_set_to_vector(answer, child, directparent, wt);
    //we initialize the distance of every vertex as -1
    vector<lld> distance(n + 1, -1);

    distance[s] = 0;                          //we make the distance of source 0
    lld sum = sum_finder(child, s, distance); //finds the total sum of arborescence as well as distance of each vertex from source
    ps(sum);                                  //we print the total sum
    prints(distance);                         //we print the distance of every vertex from source
    ps("#");                                  //we print #
    print_parent(directparent, n, s);         //prints the parents of every vertex
    p("");                                    //used to print "\n"
}

signed main()
{
    fastio; //for making the code fast
    // clock_t start, end;
    // start = clock();
    lld t;
    cin >> t;
    //for t input test cases
    while (t--)
    {
        arborescence();
    }
    // end = clock();
    // double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    // cout << "Time taken by program is : " << fixed
    //      << time_taken << setprecision(5);
    // cout << " sec " << endl;
}