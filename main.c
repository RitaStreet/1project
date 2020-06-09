
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OS_TYPE linux
#define maxlen 256

typedef struct numb
{
    int cnt;
    struct numb *next;
}numb;

typedef struct Head
{
    struct numb *first;
}Head;

numb *create_node(int num)
{
    numb *node = NULL;
    node = (numb*)malloc(sizeof(numb*));
    node -> cnt = num;
    node -> next = NULL;

    return node;
}

Head *make_head()
{
    Head *ddd = NULL;
    ddd = (Head *) malloc(sizeof(Head));

    if (ddd != NULL)
    {
        ddd -> first = NULL;
    }
    return ddd;
}

int main()
{
    Head *head = NULL;
    FILE *df, *mf;
    numb *temp = NULL, *node = NULL;
    int n, i;

    df = fopen("csv.txt", "r");
    mf = fopen("res.txt", "w");
    head = make_head();
    if (df != NULL)
    {
        i = 0;
        n = 0;

        while(fscanf(df, "%d", &n) != EOF)
        {
            printf("%d\n", n);
            temp = create_node(n);
            if (i != 0 )
                node -> next = temp;
            else
            {
                head -> first = temp;
            }

            node = temp;
            i++;
        }
    }
    else puts("File error!");
    i = 0;
    node = head -> first;
    while (node != NULL)
    {
        if (node -> next -> cnt % 3 == 0 && i < 1)
        {
            temp = node -> next -> next;
            node -> next = temp;
            i++;
        }
        if (node -> next -> cnt == 5)
        {
            temp = create_node(25);
            temp -> next = node -> next;
            node -> next = temp;
        }
        node = node -> next;
    }
    //node = head -> first
    rewind(df);
    return 0;
}
