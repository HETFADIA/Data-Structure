#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    //in this struct node we are going to save coefficient and power
    int coefficient;
    int power;
    struct node *next;
}(node);
char sign(int x)
{
    if (x >= 0)
    {
        return '+';
    }
    return '-';
}
int abs(int x)
{
    if (x >= 0)
    {
        return x;
    }
    return -x;
}
void insert_at_end(node **head_reference, int coefficient, int power)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->coefficient = coefficient;
    newnode->power = power;
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
void printlist(node **head_ref, int whichnode)
{
    node *temp = *(head_ref);
    if (whichnode <= 2)
        printf("P%d(x) : ", whichnode);
    else if (whichnode == 3)
        printf("P3(x) = P1(x) + P2(x) : ");
    else if (whichnode == 4)
        printf("P4(x) = P1(x) - P2(x) : ");
    if (temp)
    {
        while (temp)
        {
            if (temp == *(head_ref))
            {
                if (sign(temp->coefficient) == '-')
                {
                    if (temp->power != 0)
                        printf("%c %dx^%d", sign(temp->coefficient), abs(temp->coefficient), temp->power);
                    else if (temp->power == 0)
                        printf("%c %d", sign(temp->coefficient), abs(temp->coefficient));
                }
                else
                {
                    if (temp->power != 0)
                        printf("%dx^%d", abs(temp->coefficient), temp->power);
                    else if (temp->power == 0)
                        printf("%d", abs(temp->coefficient));
                }
                temp = temp->next;
                continue;
            }
            if (temp->power != 0)
                printf(" %c %dx^%d", sign(temp->coefficient), abs(temp->coefficient), temp->power);
            else if (temp->power == 0)
                printf(" %c %d", sign(temp->coefficient), abs(temp->coefficient));
            temp = temp->next;
        }
    }
    else
    {
        printf("0");
    }
    printf("\n");
}
void add(node **head_ref1, node **head_ref2, node **head_ref3)
{
    //this function calculates P3(x) ie P1(x)+P2(x)
    node *temp1 = *(head_ref1);
    node *temp2 = *(head_ref2);
    node *temp3 = NULL;
    while (temp1 && temp2)
    {
        if (temp1->power > temp2->power)
        {
            insert_at_end(&temp3, temp1->coefficient, temp1->power);
            temp1 = temp1->next;
        }
        else if (temp2->power > temp1->power)
        {
            insert_at_end(&temp3, temp2->coefficient, temp2->power);
            temp2 = temp2->next;
        }
        else
        {
            if (temp1->coefficient + temp2->coefficient)
                insert_at_end(&temp3, temp1->coefficient + temp2->coefficient, temp1->power);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    if (temp1)
    {
        while (temp1)
        {
            insert_at_end(&temp3, temp1->coefficient, temp1->power);
            temp1 = temp1->next;
        }
    }
    if (temp2)
    {
        while (temp2)
        {
            insert_at_end(&temp3, temp2->coefficient, temp2->power);
            temp2 = temp2->next;
        }
    }
    *(head_ref3) = temp3;
}
void subtract(node **head_ref1, node **head_ref2, node **head_ref4)
{
    //this function calculates P4(x) ie P1(x)-P2(x)
    node *temp1 = *(head_ref1);
    node *temp2 = *(head_ref2);
    node *temp4 = NULL;
    while (temp1 && temp2)
    {
        if (temp1->power > temp2->power)
        {
            insert_at_end(&temp4, temp1->coefficient, temp1->power);
            temp1 = temp1->next;
        }
        else if (temp2->power > temp1->power)
        {
            insert_at_end(&temp4, -temp2->coefficient, temp2->power);
            temp2 = temp2->next;
        }
        else
        {
            if (temp1->coefficient - temp2->coefficient)
                insert_at_end(&temp4, temp1->coefficient - temp2->coefficient, temp1->power);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    if (temp1)
    {
        while (temp1)
        {
            insert_at_end(&temp4, temp1->coefficient, temp1->power);
            temp1 = temp1->next;
        }
    }
    if (temp2)
    {
        while (temp2)
        {
            insert_at_end(&temp4, -temp2->coefficient, temp2->power);
            temp2 = temp2->next;
        }
    }
    *(head_ref4) = temp4;
}
int power(int x, int y)
{
    //binary exponent function
    int result = 1;
    while (y)
    {
        if (y & 1)
            result = result * x;
        y = y >> 1;
        x = x * x;
    }
    return result;
}
int findvalue(node **head_ref, int x)
{
    //this function finds the values of all the polynomials
    int res = 0;
    node *temp = NULL;

    temp = *(head_ref);
    while (temp)
    {
        res = res + temp->coefficient * power(x, temp->power);
        temp = temp->next;
    }
    return res;
}
void printvalues(node **head_ref1, node **head_ref2, node **head_ref3, node **head_ref4, int x)
{
    printf("P1(%d) = %d\n", x, findvalue(head_ref1, x));
    printf("P2(%d) = %d\n", x, findvalue(head_ref2, x));
    printf("P3(%d) = %d\n", x, findvalue(head_ref3, x));
    printf("P4(%d) = %d\n", x, findvalue(head_ref4, x));
}
void freelinkedlists(node **head_ref)
{
    //finally we will free all the linkedlists
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
    //i have checked this code using FC on all input files and output files and codechef online ide
    int k, n, coefficient, x;
    scanf("%d", &k);
    while (k--)
    {
        node *head1 = NULL, *head2 = NULL, *head3 = NULL, *head4 = NULL;
        scanf("%d", &n);
        for (int i = n; i >= 0; i--)
        {
            scanf("%d", &coefficient);
            if (coefficient != 0)
                insert_at_end(&head1, coefficient, i);
        }
        scanf("%d", &n);
        for (int i = n; i >= 0; i--)
        {
            scanf("%d", &coefficient);
            if (coefficient != 0)
                insert_at_end(&head2, coefficient, i);
        }
        scanf("%d", &x);
        add(&head1, &head2, &head3);
        subtract(&head1, &head2, &head4);
        printlist(&head1, 1);
        printlist(&head2, 2);
        printlist(&head3, 3);
        printlist(&head4, 4);
        printvalues(&head1, &head2, &head3, &head4, x);
        freelinkedlists(&head1);
        freelinkedlists(&head2);
        freelinkedlists(&head3);
        freelinkedlists(&head4);
    }
}