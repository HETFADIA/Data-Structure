#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define lld long long
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
#define same(a, b) a == b
#define inf 999999
void print(vector<vector<lld>> v)
{
    for (lld i = 0; i < v.size(); i++)
    {
        for (lld j = 0; j < v[i].size(); j++)
        {
            ps(v[i][j]);
        }
        p("");
    }
}
void print(vector<vector<pair<lld, lld>>> v)
{
    for (lld i = 0; i < v.size(); i++)
    {
        for (lld j = 0; j < v[i].size(); j++)
        {
            ps2(v[i][j].first, v[i][j].second);
        }
        p("");
    }
}
void bellman(lld n, vector<vector<pair<lld, lld>>> adj, vector<lld> &distance, lld &negative_cycle_found)
{
    lld s = n + 1;
    lld relax_edge_modification = 0;
    distance[s] = 0;
    vector<lld> times_pushed_in_queue(n + 2, 0);
    vector<lld> count(n + 2, 0);
    queue<lld> queue;
    queue.push(s);
    times_pushed_in_queue[s]++;
    lld previous_element = s;
    lld previous_relax_modification = 0;
    lld element, adjacent, dista;
    vector<pair<lld, lld>>::iterator i;
    for (lld times = 1; times <= n + 1; times++)
    {
        //we will run the loop n times
        previous_relax_modification = relax_edge_modification;
        while (queue.empty() == 0)
        {
            element = queue.front();
            if ((times_pushed_in_queue[element] - 1) / 2 > times)
            {
                //our next iteration must start so we break here;
                break;
            }
            queue.pop();
            times_pushed_in_queue[element]++;

            for (i = adj[element].begin(); i != adj[element].end(); i++)
            {
                adjacent = i->second;
                dista = i->first;
                //we increase relax_edge operation as we are checking the distance
                if (distance[adjacent] > dista + distance[element])
                {
                    //we increase the relax_edge modification as we changed the distance
                    distance[adjacent] = dista + distance[element];
                    relax_edge_modification++;
                    count[adjacent] = count[element] + 1;
                    if (count[adjacent] > n - 1 + 1)
                    {
                        negative_cycle_found = 1;
                        p(-1);
                        return;
                    }
                    if (times_pushed_in_queue[adjacent] % 2 == 0)
                    {
                        queue.push(adjacent);
                        times_pushed_in_queue[adjacent]++;
                    }
                }
            }
            previous_element = element;
        }
        if (times == n + 1)
        {
            if (previous_relax_modification < relax_edge_modification)
            {
                p(-1);
                return;
            }
        }
    }
}
pair<lld, lld> begin(lld seta[], lld n)
{
    lld min = inf;
    pair<lld, lld> e = {inf, inf};
    for (lld i = 0; i <= n; i++)
    {
        if (seta[i] < min)
        {
            min = seta[i];
            e = {min, i};
        }
    }
    return e;
}
void erase(lld seta[], lld element)
{
    seta[element] = inf;
}
void array_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    lld size = 0;
    lld seta[n + 2];
    lld size_of_seta = sizeof(seta) / sizeof(seta[0]);
    for (lld i = 0; i < size_of_seta; i++)
    {
        seta[i] = inf;
    }
    vector<lld> present(n + 2);
    seta[s] = 0;
    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    present[s] = 1;
    size++;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    while (size)
    {
        pair<lld, lld> top_element;
        top_element = begin(seta, n);
        lld element = top_element.second;
        lld dist = top_element.first;
        erase(seta, element);
        present[element] = 0;
        size--;
        vector<pair<lld, lld>>::iterator i;
        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                if (present[adjacent] == 0)
                {
                    present[adjacent] = 1;
                    size++;
                }
                distance[adjacent] = dista + distance[element];
                seta[adjacent] = distance[adjacent];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
void change(vector<vector<pair<lld, lld>>> &adj_changed, vector<lld> distance)
{
    for (lld i = 0; i < adj_changed.size(); i++)
    {
        for (lld j = 0; j < adj_changed[i].size(); j++)
        {
            if (adj_changed[i][j].first != inf)
                adj_changed[i][j].first += distance[i] - distance[adj_changed[i][j].second];
        }
    }
}
void print(vector<pair<lld, lld>> v, lld n)
{
    for (lld i = 0; i < n; i++)
    {
        ps2(v[i].first, v[i].second);
    }
    p("");
}
void minimum_heapify(vector<pair<lld, lld>> &v, lld n, lld i)
{
    lld smallest = i;
    lld left = 2 * smallest + 1;
    lld right = 2 * smallest + 2;
    lld a = left < n;
    if (left < n && v[smallest] > v[left])
    {
        smallest = left;
    }
    lld b = right < n;
    if (right < n && v[smallest] > v[right])
    {
        smallest = right;
    }
    lld go = smallest != i;
    if (go)
    {
        pair<lld, lld> e = v[i];
        v[i] = v[smallest];
        v[smallest] = e;
        // swap(v[i],v[smallest]);
        minimum_heapify(v, n, smallest);
    }
}
lld parent(lld i)
{

    return (i - 1) / 2;
}
void shift_up(vector<pair<lld, lld>> &v, lld n, lld i)
{
    while (i > 0 && v[parent(i)] > v[i])
    {

        // Swap parent and current node
        swap(v[parent(i)], v[i]);

        // Update i to parent of i
        i = parent(i);
    }
}
void min_heapify(vector<pair<lld, lld>> &v, lld n)
{

    for (lld i = n - 1; i >= 0; i--)
    {
        minimum_heapify(v, n, i);
    }
}
pair<lld, lld> get_min(vector<pair<lld, lld>> v)
{
    return v[0];
}
void swaps(pair<lld, lld> &a, pair<lld, lld> &b)
{
    pair<lld, lld> e = a;
    a = b;
    b = e;
}
pair<lld, lld> extract_min(vector<pair<lld, lld>> &v, lld &size)
{
    static pair<lld, lld> maxa = v[0];
    swaps(v[0], v[size - 1]);
    v[size - 1].first = inf;
    size--;

    minimum_heapify(v, size, 0);
    return maxa;
}
void push_back(vector<pair<lld, lld>> &v, lld &size, pair<lld, lld> data)
{

    v[size++] = data;
    shift_up(v, size, size - 1);
}
void decrease_key(vector<pair<lld, lld>> &v, lld &size, lld n, pair<lld, lld> data, pair<lld, lld> new_data)
{
    for (lld i = 0; i < n; i++)
    {
        if (v[i] == data)
        {
            v[i] = new_data;
            shift_up(v, n, i);
        }
    }
}
lld empty(vector<pair<lld, lld>> v, lld n)
{
    if (v[0].first != inf)
    {
        return 0;
    }
    return 1;
}
void binary_heap_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    lld input;
    vector<pair<lld, lld>> v(n + 2);
    lld size = 0;
    lld size_of_seta = v.size();
    for (lld i = 0; i < size_of_seta; i++)
    {
        if (i == s)
        {
            pair<lld, lld> data = {0, s};
            push_back(v, size, data);
        }
        else
        {
            pair<lld, lld> data = {inf, i};
            push_back(v, size, data);
        }
    }
    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    vector<lld> present(n + 2);
    while (empty(v, n) == 0)
    {
        pair<lld, lld> top_element;
        top_element = get_min(v);
        lld element = top_element.second;
        lld dist = top_element.first;
        extract_min(v, size);
        vector<pair<lld, lld>>::iterator i;
        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                decrease_key(v, size, n + 2, {distance[adjacent], adjacent}, {dista + distance[element], adjacent});
                distance[adjacent] = dista + distance[element];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
typedef struct node
{
    lld vertex;
    lld val, degree;
    node *parent, *child, *sibling;
}(node);

node *root = NULL;
lld value(node *head)
{
    return head->val;
}
node *getparent(node *head)
{
    return head->parent;
}
node *get(node *head)
{
    return head;
}
void binomialLink(node *h1, node *h2)
{
    h1->parent = get(h2);
    h1->sibling = h2->child;
    h2->child = h1;
    h2->degree = h2->degree + 1;
}

// create a Node
lld ret(lld a)
{
    return a;
}
node *createnode(lld n, lld vertex)
{
    node *new_node = new node;
    new_node->parent = NULL;
    new_node->val = ret(n);
    new_node->sibling = NULL;
    new_node->child = NULL;
    new_node->vertex = ret(vertex);
    new_node->degree = 0;
    return new_node;
}
lld exists(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 2;
}
lld bigger(lld a, lld b)
{
    return a > b;
}
lld lesser(lld a, lld b)
{
    return a < b;
}
lld equals(lld a, lld b)
{
    return a == b;
}
node *sibling(node *head)
{
    return head->sibling;
}
node *mergeBHeaps(node *h1, node *h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    vector<node *> v;
    // define a Node
    node *res = NULL;
    while (h1 != NULL && h2 != NULL)
    {
        // if degree of h1 is smaller, increment h1
        if (h1->degree < h2->degree)
        {
            v.pb(h1);
            h1 = h1->sibling;
        }

        // Link h1 with h2 in case of equal degree
        else if (h1->degree == h2->degree)
        {
            v.pb(h1);
            h1 = h1->sibling;
        }

        // if h2 is greater
        else
        {
            v.pb(h2);
            h2 = h2->sibling;
        }
    }
    if (h1 == NULL)
    {
        while (h2)
        {
            v.pb(h2);
            h2 = h2->sibling;
        }
    }
    if (h2 == NULL)
    {
        while (h1)
        {
            v.pb(h1);
            h1 = h1->sibling;
        }
    }
    lld i = 0;
    for (i = 0; i < v.size() - 1; i++)
    {
        v[i]->sibling = v[i + 1];
    }
    v[i]->sibling = NULL;
    res = v[0];
    return res;
}
node *unionBHeaps(node *h1, node *h2)
{
    lld alpha = !h1 && h2 == NULL;
    if (alpha)
        return NULL;

    node *res = mergeBHeaps(h1, h2);

    // Traverse the merged list and set
    // values according to the degree of
    // Nodes
    node *prev = NULL;
    node *curr = res;
    node *next = curr->sibling;
    while (next)
    {
        alpha = (curr->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == curr->degree);
        if (alpha)
        {
            prev = curr;
            curr = next;
        }

        else
        {
            alpha = curr->val <= next->val;
            lld beta = prev == NULL;
            if (alpha)
            {
                curr->sibling = next->sibling;
                binomialLink(next, curr);
            }
            else
            {
                if (beta)
                    res = get(next);
                else
                    prev->sibling = get(next);
                binomialLink(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return res;
}
void binomialHeapInsert(lld x, lld vertex, vector<node *> &address)
{
    // Create a new node and do union of
    // this node with root
    address[vertex] = createnode(x, vertex);
    root = unionBHeaps(root, address[vertex]);
}
void display(node *h)
{
    while (1)
    {
        if (h == NULL)
        {
            break;
        }
        ps(h->val);
        display(h->child);
        h = h->sibling;
    }
}
void revertList(node *h)
{
    if (h->sibling)
    {
        revertList(h->sibling);
        (h->sibling)->sibling = h;
    }
    else
        root = h;
}

node *extractMinBHeap(node *h)
{
    if (exists(h) == 0)
        return NULL;

    node *min_node_prev = NULL;
    node *min_node = h;

    // Find minimum value
    lld min = h->val;
    node *curr = h;
    while (curr->sibling)
    {
        if (lesser((curr->sibling)->val, min))
        {
            min = (curr->sibling)->val;
            min_node_prev = curr;
            min_node = curr->sibling;
        }
        curr = curr->sibling;
    }
    lld theta = min_node_prev == NULL && min_node->sibling == NULL;
    lld gamma = min_node_prev == NULL;
    // If there is a single Node
    if (theta)
        h = NULL;

    else if (gamma)
        h = min_node->sibling;

    // Remove min node from list
    else
        min_node_prev->sibling = min_node->sibling;

    // Set root (which is global) as children
    // list of min node
    theta = min_node->child != NULL;
    if (theta)
    {
        revertList(min_node->child);
        (min_node->child)->sibling = NULL;
    }
    else
    {
        root = NULL;
    }
    node *temp = root;
    while (temp != NULL)
    {
        temp->parent = NULL;
        temp = temp->sibling;
    }
    // Do union of root h and children
    return unionBHeaps(h, root);
}
node *findNode(node *h, lld val, lld vertex)
{
    if (h == NULL)
        return NULL;

    // check if key is equal to the root's data
    if (h->val == val && h->vertex == vertex)
        return h;

    // Recur for child
    node *res = findNode(h->child, val, vertex);
    if (res != NULL)
        return res;

    return findNode(h->sibling, val, vertex);
}

void decreaseKeyBHeap(node *H, lld old_val, lld vertex, lld new_val, vector<node *> &address)
{
    // First check element present or not
    node *newnode = address[vertex];

    // return if Node is not present
    if (exists(newnode) == 0)
        return;

    // Reduce the value to the minimum
    newnode->val = new_val;
    node *parent = newnode->parent;

    // Update the heap according to reduced value
    while (parent && newnode->val < parent->val)
    {
        swap(newnode->val, parent->val);
        swap(newnode->vertex, parent->vertex);
        newnode = get(parent);
        parent = getparent(parent);
    }
}
node *binomialHeapDelete(node *h, lld val, lld vertex, vector<node *> &address)
{
    if (h == NULL)
        return NULL;

    // Reduce the value of element to minimum
    decreaseKeyBHeap(h, val, vertex, INT_MIN, address);

    // Delete the minimum element from heap
    return extractMinBHeap(h);
}
pair<lld, lld> get_min(node *h)
{
    if (h == NULL)
        return {inf, inf};
    node *min_node = h;
    lld min = h->val;
    lld vertex = h->vertex;
    node *curr = h;
    while (curr->sibling)
    {
        lld theta = (curr->sibling)->val < min;
        if (theta)
        {
            min = (curr->sibling)->val;
            vertex = (curr->sibling)->vertex;
            min_node = curr->sibling;
        }
        curr = curr->sibling;
    }
    return {min, vertex};
}
void binomial_heap_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    lld input;
    root = NULL;
    vector<lld> present(n + 2);
    present[s] = 1;
    vector<node *> address(n + 2);
    binomialHeapInsert(0, s, address);

    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    while (root != NULL)
    {
        // set<pair<lld, lld> >::iterator top_element;
        pair<lld, lld> top_element;
        // top_element = seta.begin();
        // top_element = begin(seta, n);
        top_element = get_min(root);

        // lld element = top_element->second;
        lld element = top_element.second;
        present[element] = 0;
        address[element] = NULL;
        // lld dist = top_element->first;
        lld dist = top_element.first;
        // seta.erase(pair<lld, lld>(dist, element));
        // erase(seta, element);
        root = extractMinBHeap(root);
        vector<pair<lld, lld>>::iterator i;
        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                // seta.erase(pair<lld, lld>(distance[adjacent], adjacent));
                if (present[adjacent] == 1)
                    decreaseKeyBHeap(root, distance[adjacent], adjacent, dista + distance[element], address);
                else
                {
                    binomialHeapInsert(distance[element] + dista, adjacent, address);
                    present[element] = 1;
                }
                distance[adjacent] = dista + distance[element];
                // seta.insert(pair<lld, lld>(distance[adjacent], adjacent));
                // seta[adjacent] = distance[adjacent];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
template <class V>
class FibonacciHeap;

template <class V>
struct fibonode
{
public:
    fibonode<V> *prev;
    fibonode<V> *next;
    fibonode<V> *child;
    fibonode<V> *parent;
    V value;
    lld vertex;
    lld degree;
    bool marked;

public:
    friend class FibonacciHeap<V>;
    fibonode<V> *getPrev() { return prev; }
    fibonode<V> *getNext() { return next; }
    fibonode<V> *getChild() { return child; }
    fibonode<V> *getParent() { return parent; }
    V getValue() { return value; }
    bool isMarked() { return marked; }

    bool hasChildren() { return child; }
    bool hasParent() { return parent; }
};

template <class V>
class FibonacciHeap
{
protected:
    fibonode<V> *heap;
    vector<fibonode<V> *> fib_address;

public:
    FibonacciHeap(lld n)
    {
        for (lld i = 0; i < n + 2; i++)
        {
            fib_address.push_back(NULL);
        }
        heap = _empty();
    }
    virtual ~FibonacciHeap()
    {
        if (heap)
        {
            _deleteAll(heap);
        }
    }
    fibonode<V> *insert(V value, lld vertex)
    {
        fibonode<V> *ret = _singleton(value, vertex);
        fib_address[vertex] = ret;
        heap = _merge(heap, ret);
        return ret;
    }
    void merge(FibonacciHeap &other)
    {
        heap = _merge(heap, other.heap);
        other.heap = _empty();
    }

    bool isEmpty()
    {
        return heap == NULL;
    }

    V getMinimum()
    {
        return heap->value;
    }
    pair<lld, lld> get_min()
    {
        return {heap->value, heap->vertex};
    }

    V removeMinimum()
    {
        fibonode<V> *old = heap;
        heap = _removeMinimum(heap);
        V ret = old->value;
        fib_address[old->vertex] = NULL;
        delete old;
        return ret;
    }

    void decreaseKey(fibonode<V> *n, V value, lld vertex)
    {
        heap = _decreaseKey(heap, n, value, vertex);
    }

    fibonode<V> *find(V value, lld vertex)
    {
        return fib_address[vertex];
    }

    void display() const
    { // function code adapted from GO code just below C++
        fibonode<V> *p = heap;
        if (p == NULL)
        {
            cout << "The Heap is Empty" << endl;
            return;
        }
        cout << "The root fibonodes of Heap are: " << endl;
        _display_tree(heap, "");
        cout << endl;
    }
    pair<lld, lld> valvertex(fibonode<V> *a)
    {
        return {a->value, a->vertex};
    }

public:
    fibonode<V> *_empty()
    {
        return NULL;
    }

    fibonode<V> *_singleton(V value, lld vertex)
    {
        fibonode<V> *n = new fibonode<V>;
        n->value = value;
        n->vertex = vertex;
        n->prev = n->next = n;
        n->degree = 0;
        n->marked = false;
        n->child = NULL;
        n->parent = NULL;
        return n;
    }

    fibonode<V> *_merge(fibonode<V> *a, fibonode<V> *b)
    {
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;
        // if(a->value>b->value) {
        if (valvertex(a) > valvertex(b))
        {
            fibonode<V> *temp = a;
            a = b;
            b = temp;
        }
        fibonode<V> *an = a->next;
        fibonode<V> *bp = b->prev;
        a->next = b;
        b->prev = a;
        an->prev = bp;
        bp->next = an;
        return a;
    }

    void _deleteAll(fibonode<V> *n)
    {
        if (n != NULL)
        {
            fibonode<V> *c = n;
            do
            {
                fibonode<V> *d = c;
                c = c->next;
                _deleteAll(d->child);
                delete d;
            } while (c != n);
        }
    }

    void _addChild(fibonode<V> *parent, fibonode<V> *child)
    {
        child->prev = child->next = child;
        child->parent = parent;
        parent->degree++;
        parent->child = _merge(parent->child, child);
    }

    void _unMarkAndUnParentAll(fibonode<V> *n)
    {
        if (n == NULL)
            return;
        fibonode<V> *c = n;
        do
        {
            c->marked = false;
            c->parent = NULL;
            c = c->next;
        } while (c != n);
    }

    fibonode<V> *_removeMinimum(fibonode<V> *n)
    {
        _unMarkAndUnParentAll(n->child);
        if (n->next == n)
        {
            n = n->child;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n = _merge(n->next, n->child);
        }
        if (n == NULL)
            return n;
        fibonode<V> *trees[64] = {NULL};

        while (true)
        {
            if (trees[n->degree] != NULL)
            {
                fibonode<V> *t = trees[n->degree];
                if (t == n)
                    break;
                trees[n->degree] = NULL;
                t->prev->next = t->next;
                t->next->prev = t->prev;
                // if(n->value<t->value) {
                if (valvertex(n) < valvertex(t))
                {
                    _addChild(n, t);
                }
                else
                {
                    if (n->next == n)
                    {
                        t->next = t->prev = t;
                    }
                    else
                    {
                        n->prev->next = t;
                        n->next->prev = t;
                        t->next = n->next;
                        t->prev = n->prev;
                    }
                    _addChild(t, n);
                    n = t;
                }
                continue;
            }
            else
            {
                trees[n->degree] = n;
            }
            n = n->next;
        }
        fibonode<V> *min = n;
        do
        {
            // if(n->value<min->value)min=n;
            if (valvertex(n) < valvertex(min))
                min = n;
            n = n->next;
        } while (n != min);
        return min;
    }

    fibonode<V> *_cut(fibonode<V> *heap, fibonode<V> *n)
    {
        if (n->next == n)
        {
            n->parent->child = NULL;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n->parent->child = n->next;
        }
        n->next = n->prev = n;
        n->marked = false;
        n->parent->degree--;
        return _merge(heap, n);
    }

    fibonode<V> *_decreaseKey(fibonode<V> *heap, fibonode<V> *n, V value, lld vertex)
    {
        if (n->value < value)
            return heap;
        n->value = value;
        fibonode<V> *parent = n->parent;
        // if(parent != nullptr && n->value < parent->value) {
        if (parent != nullptr && valvertex(n) < valvertex(parent))
        {
            heap = _cut(heap, n);
            n->parent = NULL;
            while (parent != NULL && parent->marked)
            {
                heap = _cut(heap, parent);
                n = parent;
                parent = n->parent;
                n->parent = NULL;
            }
            if (parent != NULL && parent->parent != NULL)
                parent->marked = true;
            // if (n->value < heap->value)heap = n;
            if (valvertex(n) < valvertex(heap))
                heap = n;
        }
        fibonode<V> *min = heap;
        n = heap;
        if (heap)
        {

            do
            {
                // if(n->value<min->value)min=n;
                if (valvertex(n) < valvertex(min))
                    min = n;
                n = n->next;
            } while (n != min);
        }
        heap = min;
        return heap;
    }

    fibonode<V> *_find(fibonode<V> *heap, V value, lld vertex)
    {
        fibonode<V> *n = heap;
        if (n == NULL)
            return NULL;
        do
        {
            if (n->value == value && n->vertex == vertex)
                return n;
            fibonode<V> *ret = _find(n->child, value, vertex);
            if (ret)
                return ret;
            n = n->next;
        } while (n != heap);
        return NULL;
    }

    void _display_tree(fibonode<V> *n, string pre) const
    {
        string pc = "│  ";
        fibonode<V> *x = n;
        do
        {
            if (x->next != n)
            {
                cout << pre << "├─";
            }
            else
            {
                cout << pre << "└─";
                pc = "   ";
            }
            if (x->child == nullptr)
            {
                cout << "─" << x->value << endl;
            }
            else
            {
                cout << "┐" << x->value << endl;
                _display_tree(x->child, pre + pc);
            }
            //      cout << endl;
            x = x->next;
        } while (x != n);
    }
};
void reduce_value(FibonacciHeap<lld> &fh, lld old_val, lld vertex, lld new_val)
{
    fibonode<lld> *n = fh.find(old_val, vertex);
    fh.decreaseKey(n, new_val, vertex);
}
void fibo_heap_based_dijkstra(lld n, vector<vector<pair<lld, lld>>> adj, lld s, vector<lld> changed_distance)
{
    lld input;
    FibonacciHeap<lld> fh(n);
    vector<lld> present(n + 2);
    present[s] = 1;
    fh.insert(0, s);
    vector<lld> distance(n + 2, inf);
    distance[s] = 0;
    vector<lld> shortest_path_fount(n + 2, 0);
    shortest_path_fount[s] = 1;
    while (fh.isEmpty() == 0)
    {
        pair<lld, lld> top_element;
        top_element = fh.get_min();
        lld element = top_element.second;
        present[element] = 0;
        lld dist = top_element.first;
        fh.removeMinimum();
        vector<pair<lld, lld>>::iterator i;

        for (i = adj[element].begin(); i != adj[element].end(); i++)
        {
            lld adjacent = i->second;
            lld dista = i->first;
            if (shortest_path_fount[adjacent] == 0 && distance[element] != inf && distance[adjacent] > dista + distance[element])
            {
                if (present[adjacent] == 1)
                {
                    fibonode<lld> *n = fh.find(distance[adjacent], adjacent);
                    // fibonode<V> * n=fib_address[adjacent];
                    fh.decreaseKey(n, dista + distance[element], adjacent);
                }

                else
                {
                    fh.insert(distance[element] + dista, adjacent);
                    present[adjacent] = 1;
                }
                distance[adjacent] = dista + distance[element];
            }
        }
        shortest_path_fount[element] = 1;
    }
    for (lld i = 1; i < n + 1; i++)
    {
        if (same(i, s))
        {
            ps(0);
        }
        else if (same(distance[i], inf))
        {
            ps(inf);
        }
        else
        {
            lld corrected = distance[i] - changed_distance[s] + changed_distance[i];
            ps(corrected);
        }
    }
    p("");
}
void directed_johnson(lld n, lld d, lld argc, char **argv)
{
    if (n == 0)
    {
        p("");
        return;
    }
    vector<vector<pair<lld, lld>>> adj(n + 2);
    vector<vector<pair<lld, lld>>> adj_changed(n + 2);
    lld negative_cycle_found = 0;
    lld negative_edge_found = 0;
    lld input;
    for (lld i = 1; i <= n; i++)
    {
        for (lld j = 1; j <= n; j++)
        {
            cin >> input;
            if (input < 0)
            {
                negative_edge_found = 1;
                if (d < 0)
                {

                    negative_cycle_found = 1;
                }
            }
            adj[i].push_back(pair<lld, lld>(input, j));
            adj_changed[i].push_back(pair<lld, lld>(input, j));
        }
        adj[i].push_back({inf, n + 1});
        adj_changed[i].push_back({inf, n + 1});
    }
    if (negative_cycle_found == 1)
    {
        p(-1);
        return;
    }
    for (lld j = 1; j <= n; j++)
    {
        input = 0;
        adj[n + 1].push_back(pair<lld, lld>(input, j));
        adj_changed[n + 1].push_back(pair<lld, lld>(input, j));
    }
    adj[n + 1].push_back({inf, n + 1});
    adj_changed[n + 1].push_back({inf, n + 1});

    vector<lld> distance(n + 2, inf);
    if (negative_edge_found)
    {

        bellman(n, adj, distance, negative_cycle_found);
    }
    if (negative_cycle_found == 1)
    {
        return;
    }
    change(adj_changed, distance);
    for (lld i = 1; i <= n; i++)
    {
        if (argc == 1)
        {
            fibo_heap_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '1')
        {
            array_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '2')
        {
            binary_heap_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '3')
        {
            binomial_heap_based_dijkstra(n, adj_changed, i, distance);
        }
        else if (*argv[1] == '4')
        {
            fibo_heap_based_dijkstra(n, adj_changed, i, distance);
        }
    }
}

signed main(int argc, char **argv)
{
    fastio;
    lld t;
    cin >> t;
    clock_t start[t], end[t];
    lld iteration = 0;
    while (t--)
    {
        start[iteration] = clock();
        lld n, d;
        cin >> n >> d;
        if (d == 0)
        {
            directed_johnson(n, d, argc, argv);
        }
        else
        {

            directed_johnson(n, d, argc, argv);
        }
        end[iteration++] = clock();
    }
    for (lld i = 0; i < iteration; i++)
    {
        double time_taken = double(end[i] - start[i]) / double(CLOCKS_PER_SEC);
        cout << fixed
             << time_taken << setprecision(5) << " ";
    }
}