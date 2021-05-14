#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}(node);

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
void printlist(node **head_reference)
{
    node *head = *(head_reference);
    if (head)
    {
        printf("%d ", head->data);
        printlist(&head->next);
    }
}
node *insert(node **head_ref, int data)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    node *head = *(head_ref);

    if (!head)
    {

        return newnode;
    }
    if (head->data < data)
    {
        newnode->next = head;
        *(head_ref) = newnode;
        return newnode;
    }
    else
    {
        head->next = insert(&head->next, data);
        return head;
    }

    return head;
}
void insertion_sort()
{
    node *head = NULL;

    char space;
    // char a[20];
    // for(int i=0;i<20;i++){
    //     a[i]='\n';
    // }
    // int no=atoi(a);
    int no;
    scanf("%d", &no);
    head = insert(&head, no);

    while (scanf("%c", &space) != EOF && space != '\n')
    {
        // char a[20];
        // for(int i=0;i<20;i++){
        //     a[i]='\n';
        // }
        // int no=atoi(a);
        int no;
        scanf("%d", &no);
        head = insert(&head, no);
    }

    printlist(&head);
    printf("\n");
    freelinkedlist(&head);
}
int main()
{
    int t;
    scanf("%d\n", &t);
    while (t--)
    {
        insertion_sort();
    }
}
