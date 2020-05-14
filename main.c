#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxlen 256

typedef struct numb
{
    int num;
    struct numb *next;
}numb;

void push(numb **head, int num)//функция добавляющая элемент стека
{
    numb *p = (numb*)malloc(sizeof(numb));
    if (p != NULL)
    {
        p -> next = *head;
        p -> num = num;
        *head = p;//элемент становится головой, тем самым занимая первое место и сдвигая предыдущую голову вперёд на шаг
    }
    else
        puts("Error!");
}

void pop(numb **head)//функция "удаляющая" элемент стека
{
    if ((*head) != NULL)
        *head = (*head) -> next;//двигаем голову списка вперёд на 1
    else
        puts("Error!");
}

int main()
{
    numb *head = NULL;
    FILE *df, *mf;
    char s1[maxlen];
    int k, zn;
    float aver;
    aver = 0;
    k = 0;

    df = fopen("stek.txt", "r");//считываем файл из чисел которого формируется стек
    mf = fopen("res.txt", "w");//создаём файл в который будут записаны нечётные числа
    if (df != NULL)
    {
        zn = 0;
        while ((fgets(s1, maxlen, df)) != NULL)//считываем построчно каждое число
        {
            zn = atoi(s1);//преобразуем строку в число
            printf("%d\n", zn);
            push(&head, zn);//добавляем элемент в стек
            if (zn % 2 == 1)
            {
                k++;
                aver += zn;
                fprintf(mf, "%d\n", zn);//проверяем на нечётность, и если это так то записываем число в файл
            }

        }
        pop(&head);//удаляем элемент стека(для проверки работы функции)
    }
    rewind(df);//переводим указатель для красоты
    if(aver)
    {
        aver = aver/k;
        printf("\nOdd average - %f", aver);
    }
    else
        puts("No odd elements!");
    return 0;
}
