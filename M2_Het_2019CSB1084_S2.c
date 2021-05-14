#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
int size_of_heap = 0;
typedef struct node
{
    int data;
    struct node *next;
}(node);
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void pop(node **head_reference)
{
    node *temp = *(head_reference);
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
void push(node **head_reference, int data)
{

    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = (*head_reference);
    (*head_reference) = newnode;
}
int top(node **head_reference)
{
    node *head = *(head_reference);
    if (head)
    {
        return head->data;
    }
    return -1;
}
void freelinkedlist(node **head_ref)
{
    node *temp = *(head_ref);
    node *next = NULL;
    while (temp)
    {
        next = temp->next;
        temp->next = NULL;
        free(temp);
        temp = next;
    }
    free(next);
    *(head_ref) = NULL;
}
int fun()
{
    int k;
    scanf("%d", &k);
    node *odd = NULL;
    node *even = NULL;
    int oddcount = 0;
    int evencount = 0;
    char arr[100];
    for (int i = 0; i < 100; i++)
    {
        arr[i] = '\n';
    }
    char space;
    int no = 0;
    int last = 0;
    int lastpopped = 0;
    int answer = 1;
    while (scanf("%c", &space) != EOF && space != '\n')
    {
        scanf("%s", arr);
        no = atoi(arr);

        if (no % 2 == 0)
        {
            if (lastpopped < no)
            {
                while (lastpopped < no)
                {
                    lastpopped++;
                    if (lastpopped % 2 == 0)
                    {
                        push(&even, lastpopped);
                    }
                    else
                    {
                        push(&odd, lastpopped);
                    }
                }
            }
            if (lastpopped == no)
            {
                pop(&even);
            }
            else if (lastpopped > no)
            {
                if (top(&even) == no)
                {
                    pop(&even);
                }
                else
                {
                    answer = 0;
                }
            }
        }
        else
        {
            if (lastpopped < no)
            {
                while (lastpopped < no)
                {
                    lastpopped++;
                    if (lastpopped % 2 == 0)
                    {
                        push(&even, lastpopped);
                    }
                    else
                    {
                        push(&odd, lastpopped);
                    }
                }
            }
            if (lastpopped == no)
            {
                pop(&odd);
            }
            else if (lastpopped > no)
            {
                if (top(&odd) == no)
                {
                    pop(&odd);
                }
                else
                {
                    answer = 0;
                }
            }
        }
    }
    freelinkedlist(&odd);
    freelinkedlist(&even);
    return answer;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int answer = fun();
        if (answer == 1)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
}