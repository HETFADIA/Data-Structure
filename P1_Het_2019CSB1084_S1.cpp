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
typedef struct node
{
    struct node *left;
    struct node *right;
    lld color;
    lld data;
    lld black;
}(node);
node *bst_insertion(node *head, lld data, lld color)
{
    if (head == NULL)
    {
        node *newnode = new node;
        newnode->data = data;
        newnode->color = color;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->black = 0;
        return newnode;
    }
    if (data < head->data)
    {
        head->left = bst_insertion(head->left, data, color);
    }
    else if (data > head->data)
    {
        head->right = bst_insertion(head->right, data, color);
    }
    return head;
}
void preorder(node *head)
{
    if (head)
    {
        preorder(head->left);
        preorder(head->right);
        if (head->color == 0)
        {

            ps(head->data);
        }
        else if (head->color == 1)
        {
            ps(-1 * head->data)
        }
    }
}
lld count_black(node *head)
{
    lld res = 0;
    if (head)
    {
        res += count_black(head->left);
        if (head->color == 0)
        {
            res += 1;
        }
    }
    return res;
}
lld black_vector(node *head)
{
    if (head)
    {
        if (black_vector(head->left) != black_vector(head->right))
        {
            return -10000;
        }
        head->black = black_vector(head->left);
        if (head->color == 0)
        {
            head->black += 1;
        }
        return head->black;
    }
    return 0;
}
lld red_node(node *head)
{
    lld res = 0;
    if (head)
    {
        if (head->left)
        {
            if (head->color == 1 && head->left->color == 1)
            {
                return -10000;
            }
            res += red_node(head->left);
        }
        if (head->right)
        {
            if (head->color == 1 && head->right->color == 1)
            {
                return -10000;
            }
            res += red_node(head->right);
        }
    }
    return res;
}
void red_black()
{
    lld n;
    cin >> n;
    node *head = NULL;
    vector<lld> v(n + 1);
    vector<lld> color(n + 1);
    vector<lld> black(n + 1);
    for (lld i = 0; i < n; i++)
    {
        cin >> v[i];
        if (v[i] < 0)
        {
            v[i] = -v[i];
            head = bst_insertion(head, v[i], 1); //1 for red
            color[i] = 1;
        }
        else
        {
            head = bst_insertion(head, v[i], 0); //0 for black
            color[i] = 0;
        }
    }
    //check for R2;
    lld blacknodes = count_black(head);
    lld blackeach = black_vector(head);
    lld adj_red = red_node(head);
    if (color[0] == 1)
    {
        p2(-1, "R2");
        return;
    }
    if (adj_red < 0)
    {
        p2(-1, "R3") return;
    }
    if (blackeach < 0)
    {
        p2(-1, "R4");
        return;
    }
    ps(blacknodes);
    preorder(head);
    p("");
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
// First of all we want delete max in order 1.

// So we have to atlest have a pointer to min element.

// we will make the stack using linked list based implementation and we will have a pointer to delete max so when we delete it