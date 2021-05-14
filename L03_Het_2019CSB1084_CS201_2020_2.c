#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}(node);
typedef struct tree
{
    int data;
    int height;
    struct tree *right;
    struct tree *left;
}(tree);
typedef struct stack
{
    node **data;
    struct stack *next;
}(stack);
typedef struct stack_data
{
    int data;
    struct stack_data *next;
}(stack_data);
typedef struct stack_avl
{
    tree **data;
    struct stack_avl *next;
}(stack_avl);
int eof_found = 0;
int top = -1;
int queue_top = -1;
int is_root_null(node *root)
{
    return root == NULL;
}
int equal(int a, int b) { return a == b; }
int greater(int a, int b) { return a > b; }
int less(int a, int b) { return a < b; }
void print(int data)
{
    printf("%d ", data);
}
struct node *new_node(int data)
{
    node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
struct tree *new_node_avl(int data)
{
    tree *newnode = (struct tree *)malloc(sizeof(struct tree));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 0;
    return newnode;
}
void add_node(node **root_ref, int a)
{
    node *root = *(root_ref);
    node *newnode = new_node(a);
    if (root == NULL)
    {
        root = newnode;
        *(root_ref) = root;
        return;
    }
    node *temp = *(root_ref);
    while (1)
    {
        if (temp->data == a)
        {
            break;
        }
        else if (temp->data < a)
        {
            if (temp->right == NULL)
            {
                temp->right = newnode;
                break;
            }
            else
            {
                temp = temp->right;
            }
        }
        else if (temp->data > a)
        {
            if (temp->left == NULL)
            {
                temp->left = newnode;
                break;
            }
            else
            {
                temp = temp->left;
            }
        }
    }
    *(root_ref) = root;
}
int exists(node *node)
{
    if (node)
    {
        return 1;
    }
    return 0;
}
int exists_avl(tree *node)
{
    if (node)
    {
        return 1;
    }
    return 0;
}
int no_children(node *node)
{
    return node->left == NULL && node->right == NULL;
}
int no_children_avl(tree *node)
{
    return node->left == NULL && node->right == NULL;
}
int both_children(node *node)
{
    return node->left && node->right;
}
int both_children_avl(tree *node)
{
    return node->left && node->right;
}
int left_children(node *node)
{
    return exists(node->left);
}
int left_children_avl(tree *node)
{
    return exists_avl(node->left);
}
int left_children_only(node *node)
{
    return node->left && node->right == NULL;
}
int left_children_only_avl(tree *node)
{
    return node->left && node->right == NULL;
}
int right_children_only(node *node)
{
    return node->left == NULL && node->right;
}
int right_children_only_avl(tree *node)
{
    return node->left == NULL && node->right;
}
int only_one_children(node *node)
{
    if (node->left && node->right == NULL)
    {
        return 1;
    }
    if (node->left == NULL && node->right)
    {
        return 1;
    }
    return 0;
}
int only_one_children_avl(tree *node)
{
    if (node->left && node->right == NULL)
    {
        return 1;
    }
    if (node->left == NULL && node->right)
    {
        return 1;
    }
    return 0;
}
void free_node(node **temp)
{
    node *node = *(temp);
    node->left = NULL;
    node->right = NULL;
    free(node);
    node = NULL;
    *(temp) = NULL;
}
void free_node_avl(tree **temp)
{
    tree *node = *(temp);
    node->left = NULL;
    node->right = NULL;
    free(node);
    node = NULL;
    *(temp) = NULL;
}
int delete_right_deepest_node(node **node_ref)
{
    node *current = *(node_ref);
    node *prev = *(node_ref);
    current = current->left;

    while (current->right != NULL)
    {
        prev = current;
        current = current->right;
    }
    int res = current->data;
    if (current->data > prev->data)
    {
        prev->right = current->left;
    }
    if (current->data < prev->data)
    {
        prev->left = current->left;
    }

    free_node(&current);
    return res;
}
int find_left_deepest_node_avl(tree **tree_ref)
{
    tree *current = *(tree_ref);
    tree *prev = *(tree_ref);
    current = current->left;
    while (current->right != NULL)
    {
        prev = current;
        current = current->right;
    }
    int res = current->data;
    return res;
}
void delete_node(node **root_ref, int a)
{
    node *root = *(root_ref);
    node *prev = *(root_ref);
    node *current = *(root_ref);
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        if (root->data == a)
        {
            *(root_ref) = NULL;
            return;
        }
        return;
    }
    node *to_be_freed;
    if (root->data == a)
    {
        if (right_children_only(root) == 1)
        {
            to_be_freed = root;
            root = root->right;
            *(root_ref) = root;
            free_node(&to_be_freed);
            return;
        }
        if (left_children_only(root) == 1)
        {
            to_be_freed = root;
            root = root->left;
            *(root_ref) = root;
            free_node(&to_be_freed);
            return;
        }
        if (both_children(root) == 1)
        {
            root->data = delete_right_deepest_node(&root);
            *(root_ref) = root;
            return;
        }
    }
    while (1)
    {
        if (current == NULL)
            return;
        else if (current->data == a)
        {
            if (no_children(current) == 1)
            {
                if (current->data < prev->data)
                {
                    prev->left = NULL;
                    free_node(&current);
                    *(root_ref) = root;
                    return;
                }
                if (current->data > prev->data)
                {
                    prev->right = NULL;
                    free_node(&current);
                    *(root_ref) = root;
                    return;
                }
            }
            else if (left_children_only(current) == 1)
            {
                if (current->data < prev->data)
                {
                    prev->left = current->left;
                    free_node(&current);
                    *(root_ref) = root;
                    return;
                }
                if (current->data > prev->data)
                {
                    prev->right = current->left;
                    free_node(&current);
                    *(root_ref) = root;
                    return;
                }
            }
            else if (right_children_only(current) == 1)
            {
                if (current->data < prev->data)
                {
                    prev->left = current->right;
                    free_node(&current);
                    *(root_ref) = root;
                    return;
                }
                if (current->data > prev->data)
                {
                    prev->right = current->right;
                    free_node(&current);
                    *(root_ref) = root;
                    return;
                }
            }
            else if (both_children(current) == 1)
            {
                current->data = delete_right_deepest_node(&current);
                *(root_ref) = root;
                return;
            }
        }
        else if (current->data < a)
        {
            prev = current;
            current = current->right;
        }
        else if (current->data > a)
        {
            prev = current;
            current = current->left;
        }
    }
}
void t_query(node **root_ref)
{
    char space;
    int a;
    char number[20];
    while (1)
    {
        if (scanf("%c", &space) == EOF)
        {
            eof_found = 1;
            break;
        }
        if (space == '\n')
        {
            break;
        }
        scanf("%s", number);
        a = atoi(number);
        if (a > 0)
        {
            add_node(root_ref, a);
        }
        else if (a < 0)
        {
            delete_node(root_ref, -a);
        }
    }
}
void inorder(node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
void inorder_tree(tree *root)
{
    if (root == NULL)
        return;
    inorder_tree(root->left);
    printf("%d ", root->data);
    inorder_tree(root->right);
}
void post_order(node *root)
{
    if (root == NULL)
        return;
    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->data);
}
void post_order_avl(tree *root)
{
    if (root == NULL)
        return;
    post_order_avl(root->left);
    post_order_avl(root->right);
    printf("%d ", root->data);
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int height(node *node)
{
    if (node == NULL)
        return -1;
    return 1 + max(height(node->left), height(node->right));
}
int height_avl(tree *node)
{
    if (!node)
    {
        return -1;
    }
    return node->height;
}
int leaves(node *node)
{
    if (node == NULL)
        return 0;

    if (no_children(node))
        return 1;
    return leaves(node->left) + leaves(node->right);
}
int leaves_avl(tree *node)
{
    if (!node)
        return 0;
    if (no_children_avl(node))
        return 1;
    return leaves_avl(node->left) + leaves_avl(node->right);
}
int count_nodes(node *node)
{
    if (node == NULL)
        return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}
int count_nodes_avl(tree *node)
{
    if (!node)
        return 0;
    return 1 + count_nodes_avl(node->left) + count_nodes_avl(node->right);
}
int present(node *node, int x)
{
    if (node == NULL)
        return 0;
    return (x == node->data) + present(node->left, x) + present(node->right, x);
}

int present_avl(tree *node, int x)
{
    if (!node)
        return 0;
    return (x == node->data) + present_avl(node->left, x) + present_avl(node->right, x);
}
void free_tree(node **node_ref)
{
    node *node = *(node_ref);
    if (node == NULL)
        return;
    free_tree(&node->left);
    free_tree(&node->right);
    free_node(&node);
    *node_ref = NULL;
}
void free_tree_avl(tree **node_ref)
{
    tree *node = *(node_ref);
    if (!node)
        return;
    free_tree_avl(&node->left);
    free_tree_avl(&node->right);
    free_node_avl(&node);
    *node_ref = NULL;
}
void push(node **head_ref, stack **stack_ref)
{
    stack *newnode = (stack *)malloc(sizeof(stack));
    newnode->data = head_ref;
    newnode->next = *(stack_ref);
    *(stack_ref) = newnode;
}
void push_avl(tree **head_ref, stack_avl **stack_ref)
{
    stack_avl *newnode = (stack_avl *)malloc(sizeof(stack_avl));
    newnode->data = head_ref;
    newnode->next = *(stack_ref);
    *(stack_ref) = newnode;
}
node **pop(stack **stack_ref)
{
    node **res;
    stack *temp = *(stack_ref);
    if (!temp)
    {
        return NULL;
    }
    *(stack_ref) = temp->next;
    res = temp->data;
    temp->next = NULL;
    free(temp);
    return res;
}
tree **pop_avl(stack_avl **stack_ref)
{
    tree **res;
    stack_avl *temp = *(stack_ref);
    if (!temp)
    {
        return NULL;
    }
    *(stack_ref) = temp->next;
    res = temp->data;
    temp->next = NULL;
    free(temp);
    return res;
}
int is_empty(stack *stack)
{
    return stack == NULL;
}
int is_empty_avl(stack_avl *stack)
{
    return stack == NULL;
}
void pre_order(node *root)
{
    stack *stack_root = (stack *)malloc(sizeof(stack));
    if (exists(root))
        push(&root, &stack_root);
    int count = count_nodes(root);
    for (int i = 0; i < count; i++)
    {
        node **temp = pop(&stack_root);
        node *node = *(temp);
        if (exists(node))
            printf("%d ", node->data);
        if (exists(node->right))
            push(&node->right, &stack_root);
        if (exists(node->left))
            push(&node->left, &stack_root);
    }
    printf("\n");
}
void pre_order_avl(tree *root)
{
    stack_avl *stack_root = (stack_avl *)malloc(sizeof(stack_avl));
    if (root)
        push_avl(&root, &stack_root);
    int count = count_nodes_avl(root);
    for (int i = 0; i < count; i++)
    {
        tree **temp = pop_avl(&stack_root);
        tree *node = *(temp);
        if (node)
        {
            printf("%d ", node->data);
        }
        if (node->right)
            push_avl(&node->right, &stack_root);
        if (node->left)
            push_avl(&node->left, &stack_root);
    }
    printf("\n");
}
void push_in_queue(node **head_ref, stack **head_of_queue_ref, stack **tail_of_queue_ref)
{
    stack *newnode = (stack *)malloc(sizeof(stack));
    newnode->data = head_ref;
    newnode->next = NULL;
    if (*(tail_of_queue_ref) == NULL)
    {
        *(head_of_queue_ref) = newnode;
        *(tail_of_queue_ref) = newnode;
        return;
    }
    stack *tail = *(tail_of_queue_ref);
    tail->next = newnode;
    *(tail_of_queue_ref) = newnode;
}
void push_in_queue_avl(tree **head_ref, stack_avl **head_of_queue_ref, stack_avl **tail_of_queue_ref)
{
    stack_avl *newnode = (stack_avl *)malloc(sizeof(stack_avl));
    newnode->data = head_ref;
    newnode->next = NULL;
    if (*(tail_of_queue_ref) == NULL)
    {
        *(head_of_queue_ref) = newnode;
        *(tail_of_queue_ref) = newnode;
        return;
    }
    stack_avl *tail = *(tail_of_queue_ref);
    tail->next = newnode;
    *(tail_of_queue_ref) = newnode;
}
node **pop_from_queue(stack **head_of_queue_ref, stack **tail_of_queue_ref)
{
    node **res;
    stack *temp = *(head_of_queue_ref);
    if (temp == NULL)
    {
        return NULL;
    }
    if (*(head_of_queue_ref) == *(tail_of_queue_ref))
    {
        *(tail_of_queue_ref) = temp->next;
    }
    *(head_of_queue_ref) = temp->next;
    res = temp->data;
    temp->next = NULL;
    free(temp);
    return res;
}
tree **pop_from_queue_avl(stack_avl **head_of_queue_ref, stack_avl **tail_of_queue_ref)
{
    tree **res;
    stack_avl *temp = *(head_of_queue_ref);
    if (temp == NULL)
    {
        return NULL;
    }
    if (*(head_of_queue_ref) == *(tail_of_queue_ref))
    {
        *(tail_of_queue_ref) = temp->next;
    }
    *(head_of_queue_ref) = temp->next;
    res = temp->data;
    temp->next = NULL;
    free(temp);
    return res;
}
void level_order_traversal(node *root)
{
    stack *head_of_queue = NULL;
    stack *tail_of_queue = NULL;
    if (root)
        push_in_queue(&root, &head_of_queue, &tail_of_queue);
    int count = count_nodes(root);
    for (int i = 0; i < count; i++)
    {
        node **temp = pop_from_queue(&head_of_queue, &tail_of_queue);
        node *node = *(temp);
        if (node)
            print(node->data);
        if (node->left)
            push_in_queue(&node->left, &head_of_queue, &tail_of_queue);
        if (node->right)
            push_in_queue(&node->right, &head_of_queue, &tail_of_queue);
    }
    printf("\n");
}
void level_order_traversal_avl(tree *root)
{
    stack_avl *head_of_queue = NULL;
    stack_avl *tail_of_queue = NULL;
    if (root)
        push_in_queue_avl(&root, &head_of_queue, &tail_of_queue);
    int count = count_nodes_avl(root);
    for (int i = 0; i < count; i++)
    {
        tree **temp = pop_from_queue_avl(&head_of_queue, &tail_of_queue);
        tree *node = *(temp);
        if (exists_avl(node) == 1)
            printf("%d ", node->data);
        if (exists_avl(node->left) == 1)
            push_in_queue_avl(&node->left, &head_of_queue, &tail_of_queue);
        if (exists_avl(node->right))
            push_in_queue_avl(&node->right, &head_of_queue, &tail_of_queue);
    }
    printf("\n");
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void lowest_common_ancestor(node *root)
{
    int i, j;
    scanf("%d %d", &i, &j);
    if (i > j)
    {
        swap(&i, &j);
    }
    if (present(root, i) == 0 || present(root, j) == 0)
    {
        printf("-1\n");
        return;
    }
    while (1)
    {
        if (i < root->data && j < root->data)
        {
            root = root->left;
        }
        else if (i > root->data && j > root->data)
        {
            root = root->right;
        }
        else if (i <= root->data && j >= root->data)
        {
            printf("%d\n", root->data);
            return;
        }
    }
}
void lowest_common_ancestor_avl(tree *root)
{
    int i, j;
    scanf("%d %d", &i, &j);
    if (i > j)
    {
        swap(&i, &j);
    }
    if (present_avl(root, i) == 0 || present_avl(root, j) == 0)
    {
        printf("-1\n");
        return;
    }
    while (1)
    {
        if (i < root->data && j < root->data)
        {
            root = root->left;
        }
        else if (i > root->data && j > root->data)
        {
            root = root->right;
        }
        else if (i <= root->data && j >= root->data)
        {
            printf("%d\n", root->data);
            return;
        }
    }
}
int height_root(tree *root)
{
    if (!root)
        return -1;

    return root->height;
}
int height_diff(tree *root)
{
    if (!root)
    {
        return 0;
    }
    return height_root(root->left) - height_root(root->right);
}
int get_height(tree *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int a = height_root(root->left);
    int b = height_root(root->right);
    root->height = max(a, b);
    root->height = root->height + 1;
    return root->height;
}
tree *right_rotate(tree *root)
{
    tree *lefta = root->left;
    tree *leftarighta = root->left->right;
    root->left = leftarighta;
    lefta->right = root;
    get_height(root);
    get_height(lefta);
    return lefta;
}
tree *left_rotate(tree *root)
{
    tree *righta = root->right;
    tree *rightalefta = root->right->left;
    root->right = rightalefta;
    righta->left = root;
    get_height(root);
    get_height(righta);
    return righta;
}
tree *avl_insertion(tree **root_ref, int a)
{
    tree *root = *(root_ref);
    if (!root)
    {
        tree *new_root = (tree *)malloc(sizeof(tree));
        new_root->data = a;
        new_root->left = NULL;
        new_root->right = NULL;
        new_root->height = 0;
        return new_root;
    }
    else
    {
        int shift = 0;
        if (greater(root->data, a))
        {
            shift = 1;
        }
        else if (less(root->data, a))
        {
            shift = 2;
        }
        switch (shift)
        {
        case 1:
        {
            root->left = avl_insertion(&root->left, a);
            get_height(root);
            break;
        }
        case 2:
        {
            root->right = avl_insertion(&root->right, a);
            get_height(root);
            break;
        }
        }
    }
    int balance = height_diff(root);
    int shift;
    if (balance == 0 || abs(balance) == 1)
    {
        shift = 0;
    }
    else if (balance < -1 && a > root->right->data)
    {
        shift = 1;
    }
    else if (balance > 1 && a < root->left->data)
    {
        shift = 2;
    }
    else if (balance > 1 && a > root->left->data)
    {
        shift = 3;
    }
    else if (balance < -1 && a < root->right->data)
    {
        shift = 4;
    }
    switch (shift)
    {
    case 1:
    {
        root = left_rotate(root);
        break;
    }
    case 2:
    {
        root = right_rotate(root);
        break;
    }
    case 3:
    {
        root->left = left_rotate(root->left);
        root = right_rotate(root);
        break;
    }
    case 4:
    {
        root->right = right_rotate(root->right);
        root = left_rotate(root);
        break;
    }
    }
    return root;
}
tree *avl_deletion(tree **root_ref, int a)
{
    tree *root = *(root_ref);
    tree *to_be_deleted;

    if (!root)
    {
        return root;
    }
    else if (root->data > a)
    {
        root->left = avl_deletion(&root->left, a);
    }
    else if (root->data < a)
    {
        root->right = avl_deletion(&root->right, a);
    }
    else if (root->data == a)
    {
        if (no_children_avl(root) == 1)
        {
            to_be_deleted = root;
            root = NULL;
            free(to_be_deleted);
        }
        else if (left_children_only_avl(root) == 1)
        {
            to_be_deleted = root;
            root = root->left;
            free(to_be_deleted);
        }
        else if (right_children_only_avl(root) == 1)
        {
            to_be_deleted = root;
            root = root->right;
            free(to_be_deleted);
        }
        else if (both_children_avl(root) == 1)
        {
            root->data = find_left_deepest_node_avl(&root);
            root->left = avl_deletion(&root->left, root->data);
        }
    }
    if (!root)
    {
        return root;
    }
    get_height(root);
    int balance = height_diff(root);
    int left_balance = height_diff(root->left);
    int right_balance = height_diff(root->right);
    int shift = 0;
    if (balance > 1 && left_balance >= 0)
    {
        shift = 1;
    }
    else if (balance < -1 && right_balance <= 0)
    {
        shift = 2;
    }
    else if (balance > 1 && left_balance < 0)
    {
        shift = 3;
    }
    else if (balance < -1 && right_balance > 0)
    {
        shift = 4;
    }
    if (balance == 0)
    {
        return root;
    }
    else if (balance == 1)
    {
        return root;
    }
    else if (balance == -1)
    {
        return root;
    }
    else
    {
        if (shift == 1)
        {
            root = right_rotate(root);
            return root;
        }
        else if (shift == 2)
        {
            root = left_rotate(root);
            return root;
        }
        else if (shift == 3)
        {
            root->left = left_rotate(root->left);
            root = right_rotate(root);
            return root;
        }
        else if (shift == 4)
        {
            root->right = right_rotate(root->right);
            root = left_rotate(root);
            return root;
        }
    }
    return root;
}
void avl_queries(tree **root_ref)
{
    tree *root = *(root_ref);
    char space;
    int a;
    char number[20];
    while (1)
    {
        if (scanf("%c", &space) == EOF)
        {
            eof_found = 1;
            break;
        }
        if (space == '\n')
        {
            break;
        }
        scanf("%s", number);
        a = atoi(number);
        if (a > 0)
        {
            root = avl_insertion(root_ref, a);
            *(root_ref) = root;
        }
        else if (a < 0)
        {
            root = avl_deletion(root_ref, -a);
            *(root_ref) = root;
        }
    }
    *(root_ref) = root;
}
int max_width(node *root, int i)
{
    int res = 1;
    if (!root)
    {
        res = 0;
        return res;
    }
    else if (i == 1)
        return res;
    res = max_width(root->left, i - 1);
    res += max_width(root->right, i - 1);
    return res;
}
int max_width_avl(tree *root, int i)
{
    int res = 1;
    if (!root)
    {
        res = 0;
        return res;
    }
    else if (i == 1)
        return res;
    res = max_width_avl(root->left, i - 1);
    res += max_width_avl(root->right, i - 1);
    return res;
}
int get_width(node *root)
{
    int heighta = height(root);
    int widtha = 0;
    int max_widtha = 0;
    int i = 1;
    while (1)
    {
        if (i > heighta + 1)
        {
            break;
        }
        int width = max_width(root, i);
        max_widtha = max(width, max_widtha);
        i++;
    }
    return max_widtha;
}
int get_width_avl(tree *root)
{
    if (exists_avl(root) == 0)
    {
        return 0;
    }
    int heighta = root->height;
    int widtha = 0;
    int max_widtha = 0;
    int i = 1;
    while (1)
    {
        if (i > heighta + 1)
        {
            break;
        }
        int width = max_width_avl(root, i);
        max_widtha = max(width, max_widtha);
        i++;
    }
    return max_widtha;
}
void print_route(node *root)
{
    int i, j;
    scanf("%d %d", &i, &j);
    int a = present(root, i);
    int b = present(root, j);
    if (a == 0)
    {
        printf("Source does not exist\n");
        return;
    }
    if (b == 0)
    {
        printf("Destination does not exist\n");
        return;
    }
    if (i == j)
    {
        printf("%d\n", i);
        return;
    }
    while (1)
    {
        if (i > root->data)
        {
            root = root->right;
        }
        else if (i < root->data)
        {
            root = root->left;
        }
        else if (i == root->data)
        {
            int reachable = present(root, j);
            if (reachable == 0)
            {
                printf("Unreachable\n");
                return;
            }

            while (1)
            {
                if (j > root->data)
                {
                    printf("%d R ", root->data);
                    root = root->right;
                }
                else if (j < root->data)
                {
                    printf("%d L ", root->data);
                    root = root->left;
                }
                else if (j == root->data)
                {
                    printf("%d", root->data);
                    printf("\n");
                    return;
                }
            }
            break;
        }
    }
}
void print_route_avl(tree *root)
{
    int i, j;
    scanf("%d %d", &i, &j);
    int a = present_avl(root, i);
    int b = present_avl(root, j);
    if (a == 0)
    {
        printf("Source does not exist\n");
        return;
    }
    if (b == 0)
    {
        printf("Destination does not exist\n");
        return;
    }
    if (i == j)
    {
        printf("%d\n", i);
        return;
    }
    while (1)
    {
        if (i > root->data)
        {
            root = root->right;
        }
        else if (i < root->data)
        {
            root = root->left;
        }
        else if (i == root->data)
        {
            int reachable = present_avl(root, j);
            if (reachable == 0)
            {
                printf("Unreachable\n");
                return;
            }

            while (1)
            {
                if (j > root->data)
                {
                    printf("%d R ", root->data);
                    root = root->right;
                }
                else if (j < root->data)
                {
                    printf("%d L ", root->data);
                    root = root->left;
                }
                else if (j == root->data)
                {
                    printf("%d", root->data);
                    printf("\n");
                    return;
                }
            }
            break;
        }
    }
}
void a_query(node **root_ref)
{
    char space;
    while (scanf("%c", &space) != EOF && space != '\n')
    {
        char numarray[20];
        scanf("%s", numarray);
        int no = atoi(numarray);
        if (no > 0)
            add_node(root_ref, no);
    }
}
tree *a_query_avl(tree *root)
{
    char space;
    while (scanf("%c", &space) != EOF && space != '\n')
    {
        char numarray[20];
        scanf("%s", numarray);
        int no = atoi(numarray);
        if (no > 0)
            root = avl_insertion(&root, no);
    }
    return root;
}
tree *u_query_avl(tree *root)
{
    char space;
    while (scanf("%c", &space) != EOF && space != '\n')
    {
        char numarray[20];
        scanf("%s", numarray);
        int no = atoi(numarray);
        // add_node(root_ref,no);
        root = avl_deletion(&root, no);
    }
    return root;
}
void u_query(node **root_ref)
{
    char space;
    while (scanf("%c", &space) != EOF && space != '\n')
    {
        char numarray[20];
        scanf("%s", numarray);
        int no = atoi(numarray);
        delete_node(root_ref, no);
    }
}
int diameter(node **root_ref)
{
    node *root = *(root_ref);
    int longest_path = 0;
    if (exists(root) == 0)
    {

        return longest_path;
    }
    longest_path = max(diameter(&root->left), diameter(&root->right));
    longest_path = max(longest_path, height(root->left) + height(root->right) + 3);
    return longest_path;
}
int diameter_avl(tree **root_ref)
{
    tree *root = *(root_ref);
    int longest_path = 0;
    if (exists_avl(root) == 0)
    {

        return longest_path;
    }
    longest_path = max(diameter_avl(&root->left), diameter_avl(&root->right));
    longest_path = max(longest_path, height_avl(root->left) + height_avl(root->right) + 3);
    return longest_path;
}
void insert_beginning(stack_data **head_reference, int data)
{

    stack_data *newnode = (stack_data *)malloc(sizeof(stack_data));
    newnode->data = data;
    newnode->next = (*head_reference);
    (*head_reference) = newnode;
}
void delete_front(stack_data **head_reference)
{
    stack_data *temp = *(head_reference);
    if (temp == NULL)
    {
        printf("\tCannot delete as NO nodes in the linked-list\n");
    }
    else if (temp->next == NULL)
    {

        free(temp);
        *(head_reference) = NULL;
    }
    else
    {
        *(head_reference) = temp->next;
        temp->next = NULL;
        free(temp);
    }
}
int printleaves(node *root, int arr[])
{
    // stack_data *stack=*(stack_ref);
    if (exists(root) == 0)
    {
        return 0;
    }
    int res = 0;
    res += printleaves(root->left, arr);
    if (exists(root->left) == 0 && exists(root->right) == 0)
    {
        res += root->data;
        // printf("%d ",root->data);
        // insert_beginning(&stack, root->data);
        arr[++top] = root->data;
    }
    res += printleaves(root->right, arr);
    return res;
}
int printleaves_avl(tree *root, int arr[])
{
    if (exists_avl(root) == 0)
    {
        return 0;
    }
    int res = 0;
    res += printleaves_avl(root->left, arr);
    if (exists_avl(root->left) == 0 && exists_avl(root->right) == 0)
    {
        res += root->data;
        arr[++top] = root->data;
    }
    res += printleaves_avl(root->right, arr);
    return res;
}
int give_perimeter(node *root, int arr[], int queue[])
{
    if (is_root_null(root) == 1)
    {
        return 0;
    }
    int res = root->data;
    // printf("%d ",root->data);
    node *temp = root;
    root = root->left;
    while (exists(root) == 1)
    {
        if (left_children(root) == 1)
        {
            res += root->data;
            arr[++top] = root->data;
            root = root->left;
            continue;
        }
        else if (exists(root->right) == 1)
        {
            res += root->data;
            arr[++top] = root->data;
            root = root->right;
            continue;
        }
        else
        {
            break;
        }
    }
    root = temp;
    res = res + printleaves(root->left, arr) + printleaves(root->right, arr);
    temp = temp->right;
    while (exists(temp) == 1)
    {
        if (exists(temp->right) == 1)
        {
            res += temp->data;
            // arr[++top] = temp->data;
            queue[++queue_top] = temp->data;
            temp = temp->right;

            continue;
        }
        else if (exists(temp->left) == 1)
        {
            res += temp->data;
            // arr[++top] = temp->data;
            queue[++queue_top] = temp->data;
            temp = temp->left;
            continue;
        }
        else
        {
            break;
        }
    }

    arr[++top] = root->data;
    return res;
}
int give_perimeter_avl(tree *root, int arr[], int queue[])
{
    if (exists_avl(root) == 0)
    {
        return 0;
    }
    int res = root->data;
    tree *temp = root;
    root = root->left;
    while (exists_avl(root) == 1)
    {
        if (left_children_avl(root) == 1)
        {
            res += root->data;
            arr[++top] = root->data;
            root = root->left;
            continue;
        }
        else if (exists_avl(root->right) == 1)
        {
            res += root->data;
            arr[++top] = root->data;
            root = root->right;
            continue;
        }
        else
        {
            break;
        }
    }
    root = temp;
    res = res + printleaves_avl(root->left, arr) + printleaves_avl(root->right, arr);
    temp = temp->right;
    while (exists_avl(temp) == 1)
    {
        if (exists_avl(temp->right) == 1)
        {
            res += temp->data;
            // arr[++top] = temp->data;
            queue[++queue_top] = temp->data;
            temp = temp->right;

            continue;
        }
        else if (exists_avl(temp->left) == 1)
        {
            res += temp->data;
            // arr[++top] = temp->data;
            queue[++queue_top] = temp->data;
            temp = temp->left;
            continue;
        }
        else
        {
            break;
        }
    }
    arr[++top] = root->data;
    return res;
}
void Y_query(node **root_ref)
{
    node *root = *(root_ref);
    stack_data *stack = NULL;
    int arr[count_nodes(root)];
    int queue[count_nodes(root)];
    top = -1;
    queue_top = -1;
    int peri = give_perimeter(root, arr, queue);
    if (peri != 0)
        printf("%d ", peri);
    if (top != -1)
    {
        int theta = arr[top--];
        printf("%d ", theta);
    }
    int i = -1;
    while (i < queue_top)
    {
        int theta = queue[++i];
        printf("%d ", theta);
    }
    while (top != -1)
    {
        int theta = arr[top--];
        printf("%d ", theta);
    }
    printf("\n");
}
void Y_query_avl(tree **root_ref)
{
    tree *root = *(root_ref);
    stack_data *stack = NULL;
    int arr[count_nodes_avl(root)];
    int queue[count_nodes_avl(root)];
    top = -1;
    queue_top = -1;

    int peri = give_perimeter_avl(root, arr, queue);
    if (peri != 0)
        printf("%d ", peri);
    if (top != -1)
    {
        int theta = arr[top--];
        printf("%d ", theta);
    }
    int i = -1;
    while (i < queue_top)
    {
        int theta = queue[++i];
        printf("%d ", theta);
    }
    while (top != -1)
    {
        int theta = arr[top--];
        printf("%d ", theta);
    }
    printf("\n");
}
int main()
{
    char query;
    int a;
    node *root = NULL;
    tree *tree_node = NULL;
    int z;
    scanf("%d", &z);
    int bst = 0;
    int avl = 0;
    while (z-- && eof_found == 0 && scanf(" %c", &query) != EOF && query != '\n')
    {
        if (query == 'T')
        {
            avl = 0;
            bst = 1;
            free_tree(&root);
            free_tree_avl(&tree_node);
            t_query(&root);
        }
        else if (query == 'H')
        {
            bst = 0;
            avl = 1;
            free_tree(&root);
            free_tree_avl(&tree_node);
            avl_queries(&tree_node);
        }
        else
        {
            if (bst == 1)
            {
                if (query == 'A')
                {
                    a_query(&root);
                }
                else if (query == 'U')
                {
                    u_query(&root);
                }
                else if (query == 'F')
                {
                    int x;
                    scanf("%d", &x);
                    int present_or_not = present(root, x);
                    if (present_or_not == 1)
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }
                }
                else if (query == 'Q')
                {
                    int no_of_leaves = leaves(root);
                    printf("%d\n", no_of_leaves);
                }
                else if (query == 'N')
                {
                    int no_of_nodes = count_nodes(root);
                    printf("%d\n", no_of_nodes);
                }
                else if (query == 'P')
                {
                    pre_order(root);
                }
                else if (query == 'I')
                {
                    inorder(root);
                    printf("\n");
                }
                else if (query == 'S')
                {
                    post_order(root);
                    printf("\n");
                }
                else if (query == 'L')
                {
                    level_order_traversal(root);
                }
                else if (query == 'D')
                {
                    int h = height(root);
                    printf("%d\n", h);
                }
                else if (query == 'W')
                {
                    int width = get_width(root);
                    printf("%d\n", width);
                }
                else if (query == 'C')
                {
                    lowest_common_ancestor(root);
                }
                else if (query == 'R')
                {
                    print_route(root);
                }
                else if (query == 'X')
                {
                    int dia = diameter(&root);
                    printf("%d\n", dia);
                }
                else if (query == 'Y')
                {
                    Y_query(&root);
                }
            }
            else if (avl == 1)
            {
                if (query == 'A')
                {
                    tree_node = a_query_avl(tree_node);
                }
                else if (query == 'U')
                {
                    tree_node = u_query_avl(tree_node);
                }
                else if (query == 'F')
                {
                    int x;
                    scanf("%d", &x);
                    int present_or_not = present_avl(tree_node, x);
                    if (present_or_not == 1)
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }
                }
                else if (query == 'Q')
                {
                    int no_of_leaves = leaves_avl(tree_node);
                    printf("%d\n", no_of_leaves);
                }
                else if (query == 'N')
                {
                    int no_of_nodes = count_nodes_avl(tree_node);
                    printf("%d\n", no_of_nodes);
                }
                else if (query == 'P')
                {
                    pre_order_avl(tree_node);
                }
                else if (query == 'I')
                {
                    inorder_tree(tree_node);
                    printf("\n");
                }
                else if (query == 'S')
                {
                    post_order_avl(tree_node);
                    printf("\n");
                }
                else if (query == 'L')
                {
                    level_order_traversal_avl(tree_node);
                }
                else if (query == 'D')
                {
                    int h = height_avl(tree_node);
                    printf("%d\n", h);
                }
                else if (query == 'W')
                {
                    int width = get_width_avl(tree_node);
                    printf("%d\n", width);
                }
                else if (query == 'C')
                {
                    lowest_common_ancestor_avl(tree_node);
                }
                else if (query == 'R')
                {
                    print_route_avl(tree_node);
                }
                else if (query == 'X')
                {
                    int dia = diameter_avl(&tree_node);
                    printf("%d\n", dia);
                }
                else if (query == 'Y')
                {
                    Y_query_avl(&tree_node);
                }
            }
        }
    }
    free_tree(&root);
    free_tree_avl(&tree_node);
}