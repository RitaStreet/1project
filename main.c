#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OS_TYPE linux
#define maxlen 256

typedef struct stroka
{
    char *str;
    struct stroka *next;
}stroka;

stroka *push(stroka *head, char *s1, int slen)//функция добавляющая элемент стека
{
    stroka *p = NULL;
    p = (stroka*)malloc(sizeof(stroka));
    p -> str = (char*)malloc((slen+1) * sizeof(char));
    if (p != NULL)
    {
        p -> next = head;
        strcpy(p -> str, s1);
        head = p;//элемент становится головой, тем самым занимая первое место и сдвигая предыдущую голову вперёд на шаг
    }
    else
        puts("Error!");
    return head;
}

stroka *pop(stroka *head)//функция "удаляющая" элемент стека
{
    if (head != NULL)
        head = head -> next;//двигаем голову списка вперёд на 1
    else
        puts("Error!");

    return head;
}

int main()
{
    stroka *head = NULL;
    FILE *df, *mf;
    int sumstr, n, i, slen, *a = NULL;
    char s1[maxlen];
    sumstr = 0;

    df = fopen("csv.txt", "r");//считываем файл из чисел которого формируется стек
    mf = fopen("res.txt", "w");//создаём файл в который будут записаны нечётные числа
    if (df != NULL)
    {
        n = 0;
        while ((fgets(s1, maxlen, df)) != NULL) n++;
        rewind(df);
        a = malloc(n * sizeof(int));

        for (i = 0; i < n; i++)
        {
            fgets(s1, maxlen, df);
            slen = strlen(s1);
            s1[slen - 1] = '\0';
            slen = strlen(s1);
            a[i] = slen;
            sumstr += slen;
            head = push(head, s1, slen);//добавляем элемент в стек
            printf("%s\n", head -> str);

        }
        head = pop(head);
        head = pop(head);//удаляем 2 элемента по заданию
        while(head != NULL)
        {
            fprintf(mf, "%s\n", head -> str);
            head = pop(head);
        }
    }
    sumstr = sumstr - a[n - 1] - a[n - 2];
    printf("Dlina strok tekushego steka = %d", sumstr);
    rewind(df);//переводим указатель для красоты
    return 0;
}
