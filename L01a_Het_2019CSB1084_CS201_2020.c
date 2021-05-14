#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node
{
    int data;
    struct node *next;
}(node);
//the size of the linkedlist is stored in sizeoflinkedlist
int sizeoflinkedlist = 0;
//insert beginning function add node at the start of the linkedlist
void insert_beginning(node **head_reference, int data)
{
    sizeoflinkedlist++;
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = (*head_reference);
    (*head_reference) = newnode;
}
void insert_at_end(node **head_reference, int data)
{
    sizeoflinkedlist++;
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    node *temp = *(head_reference);
    if (temp == NULL)
    {
        *(head_reference) = newnode;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}
void delete_front(node **head_reference)
{
    node *temp = *(head_reference);
    if (temp == NULL)
    {
        printf("\tCannot delete as NO nodes in the linked-list\n");
    }
    else if (temp->next == NULL)
    {
        sizeoflinkedlist--;
        free(temp);
        *(head_reference) = NULL;
    }
    else
    {
        sizeoflinkedlist--;
        *(head_reference) = temp->next;
        temp->next = NULL;
        free(temp);
    }
}
void delete_end(node **head_ref)
{
    node *temp = *(head_ref);
    if (temp == NULL)
    {
        printf("\tCannot delete as NO nodes in the linked-list\n");
    }
    else if (temp->next == NULL)
    {
        sizeoflinkedlist--;
        free(temp);
        *(head_ref) = NULL;
    }
    else
    {
        sizeoflinkedlist--;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }
}
void delete_node_with_val(node **head_ref, int data)
{
    node *temp = *(head_ref);
    node *head = *(head_ref);
    bool deleted = 0;
    if (temp == NULL)
    {
        deleted = 0;
    }
    else if (temp->next == NULL)
    {
        if (temp->data == data)
        {
            temp->next = NULL;
            free(temp);
            head = NULL;
            deleted = 1;
        }
    }
    else
    {
        if (temp->data == data)
        {
            // delete_front(&temp);
            head = head->next;
            temp->next = NULL;
            free(temp);
            deleted = 1;
        }
        else
        {
            while (temp->next != NULL)
            {
                if (temp->next->data == data)
                {
                    node *tobedelted = temp->next;
                    temp->next = temp->next->next;
                    tobedelted->next = NULL;
                    free(tobedelted);
                    deleted = 1;
                    break;
                }
                temp = temp->next;
            }
        }
    }
    if (deleted == 0)
    {
        printf("\tCannot delete as no such node in the linked-list\n");
    }
    else
    {
        *(head_ref) = head;
        sizeoflinkedlist--;
    }
}
void find_node(node **head_ref, int data)
{
    int position = 1;
    int found = 0;
    node *temp = *(head_ref);
    if (temp == NULL)
    {
        found = 0;
    }

    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                printf("\tValue %d node is at position %d in the linked list.\n\tDifference in its allocated memory to that of current head : %ld\n", data, position, temp - *(head_ref));
                found = 1;
                break;
            }
            temp = temp->next;
            position++;
        }
        if (temp->data == data && found == 0)
        {
            printf("\tValue %d node is at position %d in the linked list.\n\tDifference in its allocated memory to that of current head : %ld\n", data, position, temp - *(head_ref));
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("\tCannot find any such node in the linked-list\n");
    }
}
void size(node **head_ref)
{
    int count = 0;
    node *temp = *(head_ref);
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    printf("\tSize of the linked list = %d\n", count);
}
void display(node **head_reference)
{
    node *temp = *(head_reference);

    if (temp == NULL)
    {
        printf("\tEmpty\n");
        return;
    }

    else
    {
        printf("\tLinked list: ");
        while (temp->next != NULL)
        {

            printf("%d => ", temp->data);

            temp = temp->next;
        }
        printf("%d\n", temp->data);
    }
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
int main()
{
    //I have checked my code using FC(automatic checker in windows terminal) and codechef online ide
    node *head = NULL;
    int choice;
    int data;
    bool wronginput = 0;
    while (1)
    {
        if (wronginput == 1)
        {
            //if the entered input was incorrect
            printf("Enter your choice again:\n");
            wronginput = 0;
        }
        else
        {
            printf("Enter the choice:\n");
        }
        scanf("%d", &choice);
        if (choice == 0)
        {
            freelinkedlist(&head);
            break;
        }
        else if (choice == 1)
        {
            printf("Enter the data value:\n");
            scanf("%d", &data);
            insert_beginning(&head, data);
        }
        else if (choice == 2)
        {
            printf("Enter the data value:\n");
            scanf("%d", &data);
            insert_at_end(&head, data);
        }
        else if (choice == 3)
        {
            delete_front(&head);
        }
        else if (choice == 4)
        {
            delete_end(&head);
        }
        else if (choice == 5)
        {
            printf("Enter the data value:\n");
            scanf("%d", &data);
            delete_node_with_val(&head, data);
        }
        else if (choice == 6)
        {
            printf("Enter the data value:\n");
            scanf("%d", &data);
            find_node(&head, data);
        }
        else if (choice == 7)
        {
            size(&head);
        }
        else if (choice == 8)
        {
            display(&head);
        }
        else
        {
            //when woring input is entered
            printf("\tWrong Input.\n");
            wronginput = 1;
        }
    }
    display(&head);
    // Sample test case 7 8 3 4 0
    // sample test case(ii) 2 2 1 199 199 7 4 4 4 0
    // sample test case (iii) 1 2 2 5 2 9 6 5 2 7 3 4 0
}