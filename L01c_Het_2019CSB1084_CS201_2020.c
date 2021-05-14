#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define llu unsigned long long
typedef struct node
{
    int data;
    struct node *next;
}(node);
void printlist(node *head)
{
    //recursive function to print the linked list in reverse order;
    if (head)
    {
        if (head->next)
        {
            //if there is next node then we go to that node;
            printlist(head->next);
        }

        printf("%d", head->data);
    }
    else
    {
        //if head is null then we will return;
        return;
    }
}
void multiply(node **head_ref, llu multiplier)
{
    node *temp = *(head_ref);
    node *lastnode = temp;
    llu previouscarry = 0;
    llu val = 0;
    while (temp)
    {
        val = temp->data * multiplier + previouscarry;
        temp->data = val % 10;
        previouscarry = val / 10;
        lastnode = temp;
        temp = temp->next;
    }
    while (previouscarry > 0)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->data = previouscarry % 10;
        newnode->next = NULL;
        lastnode->next = newnode;
        lastnode = newnode;
        previouscarry = previouscarry / 10;
    }
}
llu power7(llu x, llu y)
{
    llu result = x * x;            //result =pow(x,2);
    llu result2 = result * result; //result2 =pow(x,4);
    return result2 * result * x;   //return result will be pow(x,7);
}
llu power(llu x, llu y)
{
    //here we will use power function to calculate no of zeros;
    llu result = 1; //we initialize the answer with one
    if (y == 0)
    {
        // if y is 0 then we have to return result=1
        return 1;
    }
    while (y > 0)
    {
        //if y is odd then we have to multiply result with x;
        if (y % 2 == 1)
        {
            result *= x;
            x = x * x;
            y /= 2;
        }
        else
        {
            x = x * x;
            y /= 2;
        }
    }
    return result;
}
void countzeros(int n)
{
    int res = 0;
    int step = 1;
    while (n)
    {
        n = n / 5;
        res += power(5, step) * (n * (n + 1)) / 2;
        step++;
    }
    printf("%d ", res);
}
void nooftimeskappears(int n, node *head, int *b, int count)
{
    node *temp = head;
    node *next = temp;

    int res = 0;
    while (temp)
    {
        next = temp;
        for (int i = 0; i < count; i++)
        {
            if (next)
            {
                if (next->data == (b[i]))
                {

                    if (i == count - 1)
                    {
                        res++;
                    }
                }
                else
                {
                    break;
                }
                next = next->next;
            }
        }
        temp = temp->next;
    }
    printf("%d ", res);
}
void freelinkedlists(node **head_ref)
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

    int t, n;
    llu powerto7; //used to store the number raised to seven;
    scanf("%d", &t);
    while (t--)
    {
        char a[10]; //this array is used to store characters of k;
        for (int i = 0; i < 9; i++)
        {
            a[i] = '\0';
        }
        //head is the head node of the linked list which stores n#;
        node *head = (node *)malloc(sizeof(node));
        head->data = 1;
        head->next = NULL;
        scanf("%d", &n);
        scanf("%s", a);
        int count = 0; //count is used to store the length of k; the value of count lies between 1 and three;
        for (int i = 0; i < 3; i++)
        {
            if (a[i])
            {
                count++;
            }
        }

        int b[count + 1]; //this array is used to store k
        for (int i = 0; i < count; i++)
        {
            //now we convert the character array a to b in reversed form
            b[i] = a[count - i - 1] - '0';
        }
        for (int i = 1; i <= n; i++)
        {
            powerto7 = power7(i, 7);
            for (int j = 1; j <= i / 7; j++)
            {
                //instead of multiplying with a same number i times we multiply the ll with a num raised to 7 i/7 times and then we multiply with the same number i%7 times;
                multiply(&head, powerto7);
            }
            for (int j = 1; j <= i % 7; j++)
            {
                multiply(&head, i);
            }
        }
        countzeros(n);
        nooftimeskappears(n, head, b, count);
        printlist(head);
        printf("\n");
        freelinkedlists(&head);
        //i have checked my code using FC(windows) and codechef ide
    }
}