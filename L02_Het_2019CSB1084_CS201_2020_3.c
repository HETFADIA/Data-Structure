#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define lld long long
char space, query;
int z;
bool error;
int length_of_a;
lld catalan[31];
lld fun[31][31];
typedef struct node
{
    int data;
    struct node *next;
}(node);
int no_of_elements(node **head_ref)
{
    int count = 0;
    node *temp = *(head_ref);

    while (temp)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

void push(node **head_ref, int no)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = no;
    newnode->next = *(head_ref);
    *(head_ref) = newnode;
}
void is_node_empty(node **head_ref)
{
    if (no_of_elements(head_ref) == 0)
    {
        printf("E ");
    }
    else
    {
        printf("NE ");
    }
}
void pop(node **head_ref)
{
    node *temp = *(head_ref);
    if (temp == NULL)
    {
        printf("E ");
        return;
    }
    *(head_ref) = temp->next;
    printf("%d ", temp->data);
    temp->next = NULL;
    free(temp);
}
int pop_operator(node **head_ref)
{
    int res;
    node *temp = *(head_ref);
    if (temp == NULL)
    {
        printf("E ");
        return -1;
    }
    *(head_ref) = temp->next;
    res = temp->data;
    temp->next = NULL;
    free(temp);
    return res;
}
int top_operator(node **head_ref)
{
    int res;
    node *temp = *(head_ref);
    if (temp == NULL)
    {
        printf("E ");
        return -1;
    }
    res = temp->data;
    return res;
}
void is_node_full()
{
    printf("NF ");
}

void node_parameter(node **head_ref, int n)
{
    if (n >= 1)
    {
        push(head_ref, n);
    }
    else if (n == 0)
    {
        is_node_empty(head_ref);
    }
    else if (n == -1)
    {
        pop(head_ref);
    }
    else if (n == -2)
    {
        is_node_full();
    }
    else if (n == -3)
    {
        int theta = no_of_elements(head_ref);
        printf("%d ", theta);
    }
}
void free_linkedlist(node **head_ref)
{
    node *temp = *(head_ref);
    node *next = *(head_ref);
    while (temp)
    {
        next = temp->next;
        temp->next = NULL;
        free(temp);
        temp = next;
    }
    *(head_ref) = NULL;
}
void stack_queries()
{
    node *root = NULL;
    bool garbage = 0;
    error = 0;
    while (1)
    {
        if (garbage == 1)
        {
            while (!(scanf("%c", &space) == EOF || space == '\n'))
            {
            }
            free_linkedlist(&root);
            break;
        }

        if (scanf("%c", &space) == EOF || space == '\n')
        {
            free_linkedlist(&root);
            break;
        }
        else if (space != ' ')
        {
            error = 1;
        }
        char number[12];
        scanf("%s", number);
        int no = atoi(number);
        if (no <= -4)
        {
            garbage = 1;
        }
        if (garbage == 0 && error == 0)
        {

            node_parameter(&root, no);
        }
    }
    if (error == 1)
    {
        printf("Error");
        error = 0;
    }
    free_linkedlist(&root);
}
void push_in_queue(node **head_ref, node **tail_ref, int n)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = n;
    newnode->next = NULL;
    if (*(tail_ref) == NULL)
    {
        *(head_ref) = newnode;
        *(tail_ref) = newnode;
        return;
    }
    node *tail = *(tail_ref);
    tail->next = newnode;
    *(tail_ref) = newnode;
}
void pop_from_queue(node **head_ref, node **tail_ref, int n)
{
    node *head = *(head_ref);
    if (head == NULL)
    {
        printf("E ");
        return;
    }
    printf("%d ", head->data);
    node *head_next = head->next;
    head->next = NULL;
    free(head);
    *(head_ref) = head_next;
    if (head_next == NULL)
    {
        *(tail_ref) = NULL;
    }
}
int pop_from_queue_with_return(node **head_ref, node **tail_ref)
{
    node *head = *(head_ref);
    if (head == NULL)
    {
        printf("E ");
        return -1;
    }

    int res = head->data;
    node *head_next = head->next;
    head->next = NULL;
    free(head);
    *(head_ref) = head_next;
    if (head_next == NULL)
    {
        *(tail_ref) = NULL;
    }
    return res;
}
void queue_parameter(node **head_ref, node **tail_ref, int n)
{
    if (n >= 1)
    {
        push_in_queue(head_ref, tail_ref, n);
    }
    else if (n == 0)
    {
        is_node_empty(head_ref);
    }
    else if (n == -1)
    {
        pop_from_queue(head_ref, tail_ref, n);
    }
    else if (n == -2)
    {
        is_node_full();
    }
    else if (n == -3)
    {
        int theta = no_of_elements(head_ref);
        printf("%d ", theta);
    }
}
void queue_queries()
{
    node *root = NULL;
    node *tail = NULL;
    bool garbage = 0;
    error = 0;
    while (1)
    {
        if (garbage == 1)
        {
            while (!(scanf("%c", &space) == EOF || space == '\n'))
            {
            }
            free_linkedlist(&root);
            tail = NULL;
            break;
        }

        if (scanf("%c", &space) == EOF || space == '\n')
        {
            free_linkedlist(&root);
            tail = NULL;
            break;
        }
        else if (space != ' ')
        {
            error = 1;
        }
        char number[12];
        scanf("%s", number);
        int no = atoi(number);

        if (no <= -4)
        {
            garbage = 1;
        }
        if (garbage == 0 && error == 0)
        {
            queue_parameter(&root, &tail, no);
        }
    }
    if (error == 1)
    {
        printf("Error");
    }
    free_linkedlist(&root);
    tail = NULL;
}
int length_of_a_finder(char *a)
{
    int length = 0;
    for (int i = 0; i < 6; i++)
    {
        if (a[i] != '\0' && a[i] && a[i] != ' ')
        {
            length++;
        }
    }
    return length;
}
void check_error(char *a)
{

    int noerrorfound = 1;

    if (a[0] == '<' && a[1] == '<')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '<' && a[1] == '=')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '>' && a[1] == '=')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '=' && a[1] == '=')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '!' && a[1] == '=')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '>' && a[1] == '>')
    {
        noerrorfound = 1;
    }

    else if (a[0] == '<' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '>' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '*' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '/' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '+' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '-' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '&' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '|' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '^' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '%' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else if (a[0] == '=' && a[1] == '\0')
    {
        noerrorfound = 1;
    }
    else
    {
        error = 1;
    }
}
int hashing(char *a)
{
    if (a[0] == '<' && a[1] == '<')
    {
        return 1000 + (int)',';
    }
    else if (a[0] == '>' && a[1] == '>')
    {
        return 1000 + (int)'.';
    }
    else if (a[0] == '<' && a[1] == '=')
    {
        return 1000 + (int)'[';
    }
    else if (a[0] == '>' && a[1] == '=')
    {
        return 1000 + (int)']';
    }
    else if (a[0] == '=' && a[1] == '=')
    {
        return 1000 + (int)'{';
    }
    else if (a[0] == '!' && a[1] == '=')
    {
        return 1000 + (int)'}';
    }

    return 1000 + (int)a[0];
}
char dehashing(int n)
{
    return (char)(n - 1000);
}
void inverse_hashing(char *a, int n)
{
    for (int i = 0; i < 2; i++)
    {
        a[i] = '\0';
    }
    char b = dehashing(n);

    if (b == ',')
    {
        a[0] = '<';
        a[1] = '<';
    }
    else if (b == '.')
    {
        a[0] = '>';
        a[1] = '>';
    }
    else if (b == '[')
    {
        a[0] = '<';
        a[1] = '=';
    }
    else if (b == ']')
    {
        a[0] = '>';
        a[1] = '=';
    }
    else if (b == '{')
    {
        a[0] = '=';
        a[1] = '=';
    }
    else if (b == '}')
    {
        a[0] = '!';
        a[1] = '=';
    }
    else
    {
        a[0] = b;
    }
}
int precedence(char a)
{
    if (a == '|')
    {
        return 0;
    }
    if (a == '^')
    {
        return 1;
    }
    if (a == '&')
    {
        return 2;
    }
    if (a == '{' || a == '}')
    {
        return 3;
    }
    if (a == '<' || a == '>' || a == '[' || a == ']')
    {
        return 4;
    }
    if (a == ',' || a == '.')
    {
        return 5;
    }
    if (a == '+' || a == '-')
    {
        return 6;
    }
    if (a == '*' || a == '/' || a == '%')
    {
        return 7;
    }
    return 7;
}
void print_char_array(char *a)
{
    for (int i = 0; i < 2; i++)
    {
        if (a[i] != '\0')
        {
            printf("%c", a[i]);
        }
    }
    printf(" ");
}
void post_fix_founder()
{
    node *post_fix_expression = NULL;
    node *tail_of_post_fix = NULL;
    node *stack_operators = NULL;
    bool hash_symbol_came = 0;
    error = 0;
    int t = 0;
    while (1)
    {
        if (hash_symbol_came == 1 || error == 1)
        {
            if (t % 2 == 0)
            {
                error = 1;
            }
            int stack_operators_size = no_of_elements(&stack_operators);
            while (stack_operators_size--)
            {
                int theta = pop_operator(&stack_operators);
                push_in_queue(&post_fix_expression, &tail_of_post_fix, theta);
            }
            while (!(scanf("%c", &space) == EOF || space == '\n'))
            {
            }
            break;
        }
        if (scanf("%c", &space) == EOF || space == '\n')
        {
            if (t % 2 == 0)
            {
                error = 1;
            }
            int stack_operators_size = no_of_elements(&stack_operators);
            while (stack_operators_size--)
            {
                int theta = pop_operator(&stack_operators);
                push_in_queue(&post_fix_expression, &tail_of_post_fix, theta);
            }
            break;
        }
        if (t % 2 == 0)
        {

            char a[6];
            for (int i = 0; i < 5; i++)
            {
                a[i] = '\0';
            }
            scanf("%s", a);
            if (a[0] == '#')
            {
                hash_symbol_came = 1;
            }
            if (!(0 <= a[0] - '0' && a[0] - '0' <= 9))
            {
                error = 1;
            }
            for (int i = 1; i < 5; i++)
            {
                if (a[i] != '\0')
                {
                    if (!(0 <= a[i] - '0' && a[i] - '0' <= 9))
                    {
                        error = 1;
                    }
                }
            }
            if (hash_symbol_came == 0 && error == 0)
            {
                t++;
                int number = atoi(a);
                if (number > 1000 || number < 0)
                {
                    error = 1;
                }
                if (error == 0)
                {
                    push_in_queue(&post_fix_expression, &tail_of_post_fix, number);
                }
            }
        }
        else
        {

            char a[6];
            for (int i = 0; i < 5; i++)
            {
                a[i] = '\0';
            }
            scanf("%s", a);
            if (a[0] == '#')
            {
                hash_symbol_came = 1;
            }
            if (hash_symbol_came == 0)
            {
                t++;
                check_error(a);

                if (error == 0)
                {
                    int no = hashing(a);
                    while (no_of_elements(&stack_operators) > 0 && precedence(dehashing(no)) <= precedence(dehashing(top_operator(&stack_operators))))
                    {
                        int theta = pop_operator(&stack_operators);
                        push_in_queue(&post_fix_expression, &tail_of_post_fix, theta);
                    }

                    push(&stack_operators, no);
                }
            }
        }
    }
    if (error == 0)
    {
        int length = no_of_elements(&post_fix_expression);
        for (int i = 0; i < length; i++)
        {

            int theta = pop_from_queue_with_return(&post_fix_expression, &tail_of_post_fix);
            if (theta <= 1000)
            {

                printf("%d ", theta);
            }
            else
            {
                char a[3];
                inverse_hashing(a, theta);
                print_char_array(a);
            }
        }
    }
    else
    {
        printf("Error");
    }
    printf("\n");
    free_linkedlist(&post_fix_expression);
    tail_of_post_fix = NULL;
    free_linkedlist(&stack_operators);
}
int pop_out(node **head_ref)
{
    node *temp = *(head_ref);
    if (temp == NULL)
    {

        return -1;
    }
    *(head_ref) = temp->next;
    int res = temp->data;

    temp->next = NULL;
    free(temp);
    return res;
}
int evaluate_the_first_two_popped_numbers(int beta, char *a, int alpha)
{
    int res;
    if (a[0] == '<' && a[1] == '<')
    {
        return beta << alpha;
    }
    if (a[0] == '>' && a[1] == '>')
    {
        return beta >> alpha;
    }
    if (a[0] == '<' && a[1] == '=')
    {
        return beta <= alpha;
    }
    if (a[0] == '>' && a[1] == '=')
    {
        return beta >= alpha;
    }
    if (a[0] == '!' && a[1] == '=')
    {
        return beta != alpha;
    }
    if (a[0] == '=' && a[1] == '=')
    {
        return beta == alpha;
    }

    if (a[0] == '+' && a[1] == '\0')
    {
        return beta + alpha;
    }
    if (a[0] == '-' && a[1] == '\0')
    {
        return beta - alpha;
    }
    if (a[0] == '%' && a[1] == '\0')
    {
        if (alpha == 0)
        {
            error = 1;
            return -5;
        }
        return beta % alpha;
    }
    if (a[0] == '*' && a[1] == '\0')
    {
        return beta * alpha;
    }
    if (a[0] == '/' && a[1] == '\0')
    {
        if (alpha == 0)
        {
            error = 1;
            return -5;
        }
        return beta / alpha;
    }
    if (a[0] == '<' && a[1] == '\0')
    {
        return beta < alpha;
    }
    if (a[0] == '>' && a[1] == '\0')
    {
        return beta > alpha;
    }
    if (a[0] == '&' && a[1] == '\0')
    {
        return beta & alpha;
    }
    if (a[0] == '|' && a[1] == '\0')
    {
        return beta | alpha;
    }
    if (a[0] == '^' && a[1] == '\0')
    {
        return beta ^ alpha;
    }

    return -10;
}
void evaluator()
{
    node *post_fix_expression = NULL;
    node *tail_of_post_fix = NULL;
    node *stack_operators = NULL;
    bool hash_symbol_came = 0;
    error = 0;
    int t = 0;
    while (1)
    {
        if (hash_symbol_came == 1 || error == 1)
        {
            if (t % 2 == 0)
            {
                error = 1;
            }
            int stack_operators_size = no_of_elements(&stack_operators);
            while (stack_operators_size--)
            {
                int theta = pop_operator(&stack_operators);
                push_in_queue(&post_fix_expression, &tail_of_post_fix, theta);
            }
            while (!(scanf("%c", &space) == EOF || space == '\n'))
            {
            }
            break;
        }
        if (scanf("%c", &space) == EOF || space == '\n')
        {
            if (t % 2 == 0)
            {
                error = 1;
            }
            int stack_operators_size = no_of_elements(&stack_operators);
            while (stack_operators_size--)
            {
                int theta = pop_operator(&stack_operators);
                push_in_queue(&post_fix_expression, &tail_of_post_fix, theta);
            }
            break;
        }
        else if (space != ' ' && hash_symbol_came == 0)
        {
            error = 1;
        }
        if (t % 2 == 0)
        {

            char a[6];
            for (int i = 0; i < 5; i++)
            {
                a[i] = '\0';
            }
            scanf("%s", a);
            if (a[0] == '#')
            {
                hash_symbol_came = 1;
            }
            if (!(0 <= a[0] - '0' && a[0] - '0' <= 9) && a[0] != '-')
            {
                error = 1;
            }
            for (int i = 1; i < 5; i++)
            {
                if (a[i] != '\0')
                {
                    if (!(0 <= a[i] - '0' && a[i] - '0' <= 9))
                    {
                        error = 1;
                    }
                }
            }
            if (hash_symbol_came == 0 && error == 0)
            {
                t++;
                int number = atoi(a);
                if (number > 1000 || number < -1000)
                {
                    error = 1;
                }
                if (error == 0)
                {
                    push_in_queue(&post_fix_expression, &tail_of_post_fix, number);
                }
            }
        }
        else
        {

            char a[6];
            for (int i = 0; i < 5; i++)
            {
                a[i] = '\0';
            }
            scanf("%s", a);
            if (a[0] == '#')
            {
                hash_symbol_came = 1;
            }
            if (hash_symbol_came == 0)
            {
                t++;

                check_error(a);

                if (error == 0)
                {
                    int no = hashing(a);
                    while (no_of_elements(&stack_operators) > 0 && precedence(dehashing(no)) <= precedence(dehashing(top_operator(&stack_operators))))
                    {
                        int theta = pop_operator(&stack_operators);
                        push_in_queue(&post_fix_expression, &tail_of_post_fix, theta);
                    }

                    push(&stack_operators, no);
                }
            }
        }
    }
    if (error == 0)
    {

        node *head = NULL;
        int length = no_of_elements(&post_fix_expression);

        for (int i = 0; i < length; i++)
        {
            int theta = pop_from_queue_with_return(&post_fix_expression, &tail_of_post_fix);
            if (theta <= 1000)
            {
                push(&head, theta);
            }
            else
            {
                char a[3];
                inverse_hashing(a, theta);
                int alpha = pop_out(&head);
                int beta = pop_out(&head);
                int gamma = evaluate_the_first_two_popped_numbers(beta, a, alpha);
                push(&head, gamma);
            }
        }
        if (error == 1)
        {
            printf("Error\n");
            free_linkedlist(&post_fix_expression);
            tail_of_post_fix = NULL;
            free_linkedlist(&stack_operators);
            return;
        }
        int answer = pop_out(&head);
        printf("%d", answer);
        free_linkedlist(&head);
    }
    else
    {
        printf("Error");
    }
    printf("\n");
    free_linkedlist(&post_fix_expression);
    tail_of_post_fix = NULL;
    free_linkedlist(&stack_operators);
}
void initialize_catalan_array()
{
    for (int i = 0; i < 31; i++)
    {
        catalan[i] = 0;
    }
    catalan[0] = 1;
    for (int i = 1; i < 31; i++)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }

    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 31; j++)
        {
            if (i == 0)
            {
                fun[i][j] = 1;
            }
            else if (j == 0)
            {
                fun[i][j] = catalan[i];
            }
            else
            {
                fun[i][j] = 0;
            }
        }
    }
    for (int a = 1; a < 31; a++)
    {
        for (int b = 1; b < 31; b++)
        {
            if (a + b <= 30)
            {
                fun[a][b] = fun[a][b - 1] + fun[a - 1][b + 1];
            }
        }
    }
}
lld funct(int a, int b)
{
    return fun[a][b];
}
void clear(node **head_ref, int i, int n)
{
    //this function pushes the remaining elements and pops them to print the largest stack permutation possible
    node *head = *(head_ref);

    while (i <= n)
    {
        push(&head, i);

        i++;
    }
    while (head)
    {
        pop(&head);
    }
    *(head_ref) = NULL;
}
void stack_permutation()
{
    node *head = NULL;
    int n;
    lld k;
    error = 0;
    space = getchar();
    if (space != ' ')
    {
        error = 1;
    }
    if (error == 1)
    {
        while (!(scanf("%c", &space) == EOF || space == '\n'))
        {
        }
        printf("Error\n");
        error = 0;
        return;
    }
    char narray[20], karray[20];
    for (int i = 0; i < 20; i++)
    {
        narray[i] = '\0';
        karray[i] = '\0';
    }
    scanf("%s", narray);
    scanf("%s", karray);
    n = atoi(narray);
    k = karray[0] - '0';
    int iterator = 1;
    while (karray[iterator] != '\0')
    {
        k = k * 10 + karray[iterator] - '0';
        iterator++;
    }
    int i = 1, a = n, b = 0;
    if (k > catalan[n])
    {
        error = 1;
    }
    if (error == 1)
    {
        while (!(scanf("%c", &space) == EOF || space == '\n'))
        {
        }
        printf("Error\n");
        error = 0;
        return;
    }
    printf("%lld ", catalan[n]);
    while (i <= n)
    {
        if (b == 0 && a == 0)
        { // if stack is empty and there are no elements left then we clear
            clear(&head, i, n);
            i = n + 1;

            break;
        }
        else if (b == 0 && a > 0)
        { // if the stack is empty then we push an element
            push(&head, i);
            b++;
            a--;
            i++;
        }
        else if (b > 0 && a == 0)
        { //else if the elements are only in stack(a==0) we call clear function
            clear(&head, i, n);
            i = n + 1;
            break;
        }
        else if (k == funct(a, b))
        { //if we find the right permutation we call clear;
            clear(&head, i, n);
            i = n + 1;
            break;
        }
        else if (k > funct(a, b - 1))
        { // if k is greater that means the permutation is not starting through top element of stack so we push next element
            push(&head, i);
            k -= funct(a, b - 1);

            a--;
            b++;
            i++;
        }
        else
        { // if it is less we pop the element
            if (head)
            {

                pop(&head);
                b--;
            }
            else
            { // if head is null that means we want largest permutation
                clear(&head, i, n);
                i = n + 1;
                break;
            }
        }
    }
    clear(&head, i, n);
    printf("\n");
    free_linkedlist(&head);
}

int main()
{
    int t;

    scanf("%d %d\n", &t, &z);
    initialize_catalan_array();
    while (t--)
    {
        scanf(" %c", &query);

        if (query == 'S')
        {
            stack_queries();
            printf("\n");
        }
        else if (query == 'Q')
        {
            queue_queries();
            printf("\n");
        }
        else if (query == 'I')
        {
            post_fix_founder();
        }
        else if (query == 'E')
        {
            evaluator();
        }
        else if (query == 'P')
        {
            stack_permutation();
        }
        else
        {

            printf("Error\n");
            while (!(scanf("%c", &space) == EOF || space == '\n'))
            {
            }
        }
    }
    //SELF DECLARATION: I have done this assignment by myself.
    // i have used knowledge of ge103 cs201 and cs101
    /* sample input i have run my code and got successful output
    29 20
    S 6 7 -1 -4
    S 6 7 -1 -4
    Q 6 7 -1 -4
    P 3 4
    P 3 5
    P 30 380000000
    Q 5 7 -1 -2 -3 -4
    I 1 + 2 + 3 + 4 #
    I 1 + 2 + 3 + 4 #
    E 1 + 2 + 3 + 4 #
    E 1 + 2 + 3 + 4 #
    S 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4
    Q 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4
    S -1 -1 -1 -1 -1 -4
    Q -1 -1 -1 -1 -1 -4
    I 1000 >> 3 #
    E 1000 >> 3 #
    I 1 >= 3 #
    E 1 >= 3 #
    I 4 <= 5 #
    E 4 <= 5 #
    I 4 != 5 #
    E 4 != 5 #
    I 4 << 5 #
    E 4 << 5 #
    I 1000 == 1000 #
    E 1000 == 1000 #
    I 1 + 2 + 3 * 4 * 5 / 6 / 6 #
    E 1 + 2 + 3 * 4 * 5 / 6 / 6 #
    Output i got:
    7 
    7 
    6 
    5 2 3 1 
    5 3 2 1 
    3814986502092304 1 2 3 4 5 6 7 8 9 10 11 12 16 17 15 14 18 13 19 21 20 22 24 26 29 28 27 25 30 23 
    5 NF 1 
    1 2 + 3 + 4 + 
    1 2 + 3 + 4 + 
    10
    10
    NE 1 NF 9 
    NE 10 NF 9 
    E E E E E 
    E E E E E 
    1000 3 >> 
    125
    1 3 >= 
    0
    4 5 <= 
    1
    4 5 != 
    1
    4 5 << 
    128
    1000 1000 == 
    1
    1 2 + 3 4 * 5 * 6 / 6 / + 
    4

    */
    //i have run my code on online codechef ide tutorialspoint onlinegdb repl.it and my pc and got successful output.

    return 0;
}