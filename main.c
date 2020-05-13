#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OS_TYPE linux
#ifdef OS_TYPE
#define maxlen 256
#endif // OS_TYPE

typedef struct numb
{
    int num;
    struct numb *next;
}numb;

void push(numb **head, int num)
{
    numb *p = (numb*)malloc(sizeof(numb));
    if (p != NULL)
    {
        p -> next = *head;
        p -> num = num;
        *head = p;
    }
    else
        puts("Error!");
}

numb *pop(numb **head)
{
    numb *p;
    if ((*head) != NULL)
    {
        p = *head;
        *head = (*head) -> next;
        return p;
    }
    else
        puts("Error!");
}

int main()
{
    numb *head = NULL;
    numb *p;
    FILE *df, *mf;
    char *s1;
    int n, k, zn;
    float aver;
    aver = 0;
    n = 0;
    k = 0;

    df = fopen("stek.txt", "r");
    mf = fopen("res.txt", "w");
    if (df != NULL)
    {
        n = 0;
        while ((fgets(s1, maxlen, df)) != NULL)
        {
            zn = atoi(s1);
            printf("%d\n", zn);
            push(&head, zn);
            if (zn % 2 == 1)
            {
                k++;
                aver += zn;
                fprintf(mf, "%d\n", zn);
            }

        }
        p = pop(&head);
    }
    rewind(df);
    aver = aver/k;
    printf("\nOdd average - %f", aver);
    return 0;
}
