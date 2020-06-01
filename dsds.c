#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OS_TYPE windows
#ifdef OS_TYPE
    #define CLS system("cls")
#else
    #define CLS system("clear")
#endif

struct st
{
    char *name;// имя
    struct LNode *fac;// факультет
    int prop;// количество пропусков
    int dolg;// количество долгов
    float average;// средняя оценка по всем предметам
    float exs;// средняя оценка по экзаменам
    int ege[3];// баллы егэ
};

typedef struct st STUD;

/*---------------------------------------------------------*/
struct LNode {
    int   id;
    char  *info;
    struct LNode  *next;
    struct LNode *prev;
};

struct LHead {
    int cnt;
    struct LNode *first;
    struct LNode *last;
};

typedef struct LHead Head;
typedef struct LNode Node;

Head *make_head()
{
    Head *ph=NULL;

    ph=(Head*)malloc(sizeof(Head));
    if(ph)
    {
        ph->cnt=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}

Node *create_node(char *inf)
{
    Node *new_node=NULL;
    char *information=NULL;

    new_node = (Node*)malloc(sizeof(Node));
    information=(char*)malloc(sizeof(char));
    if(new_node&&information)
    {
        new_node->id = 1;
        information=inf;
        new_node->info=information;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
}

void add_first(Head *my_head, Node *new_node)
{
    if(my_head&&new_node)
    {
        my_head->first = new_node;
        my_head->last = new_node;
        my_head->cnt++;
    }
}


void clear_str_array(char **str, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;

}


char **simple_split(char *str, int length, char sep)
{
    char **str_array=NULL;
    int i,j,k,m;
    int key,count;
    for(j=0,m=0;j<length;j++)
    {
        if(str[j]==sep) m++;
    }

    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]!=NULL) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else
                {
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
            str_array[m][j-k]='\0';
        }
        else
        {
            clear_str_array(str_array,count);
        }
     }
     return str_array;
}

void struct_out(STUD *str0, char *info)
{
    printf("|%20s | %5s | %6d | %3d | %10f | %10f | %d %d %d |\n",
         str0->name,info,str0->prop,str0->dolg,str0->average,str0->exs,str0->ege[0],str0->ege[1],str0->ege[2]);
}

STUD *fill_stud(char **str)
{
    STUD *str0=NULL;
    int t;
    t=0;
    str0=(STUD*)malloc(sizeof(STUD));
    if((str0!=NULL))
    {
        str0->name=str[0];
        str0->prop=atoi(str[2]);
        str0->dolg=atoi(str[3]);
        str0->average=atof(str[4]);
        str0->exs=atof(str[5]);
        str0->ege[0]=atoi(str[6]);
        str0->ege[1]=atoi(str[7]);
        str0->ege[2]=atoi(str[8]);
    }
    return str0;
}


void new_gets(char *s, int lim)
{
    char c;
    int i;
    i=0;
    while(((c=getchar())!='\n')&&(i<lim-1))
    {
        s[i]=c;
        i++;
    }
    s[i]='\0';
}



/*-------------------------------------------------------------------*/

int main()
{
    enum {maxlen=128, M=100};
    STUD **STUD1=NULL;
    int slen,i,n,count, key;
    char **s2=NULL;
    char s1[maxlen];
    char sep;
    Head *p0;
    Node *p,*pp1,*my_node=NULL;
    Node *pp;

    FILE *df;
    sep=';';
    key = 1;
    df=fopen("csv.txt","r");
    if(df!=NULL)
    {
        n=0;
        while((fgets(s1,maxlen,df))!=NULL) n++;
        rewind(df);
        STUD1=(STUD**)malloc(M*sizeof(STUD*));
        if(STUD1!=NULL)
        {
            fgets(s1,maxlen,df);
            slen=strlen(s1);
            s1[slen-1]='\0';
            slen=strlen(s1);
            s2=simple_split(s1,slen,sep);
            p0=make_head();
            p=create_node(s2[1]);
            add_first(p0,p);
            for(i=1,count=0;i<n;i++,count++)
            {
                fgets(s1,maxlen,df);
                slen=strlen(s1);
                s1[slen-1]='\0';
                slen=strlen(s1);
                s2=simple_split(s1,slen,sep);
                if(s2!=NULL)
                {
                    key=1;
                    pp=p0->first;
                    while (pp!=NULL)
                    {
                        if (strcmp(pp->info,s2[1])==0) key=0;
                        pp=pp->next;
                    }
                    if(key==1)
                    {
                        p=create_node(s2[1]);
                        insert_after(p0,p,p0->last);
                    }
                }
            }
            printf("HERE IS YOUR LINKED LIST OF FACULTIES:\n");
            p=p0->first;
            while(p!=NULL)
            {
                printf("| %3d | %7s |\n",p->id, p->info);
                p=p->next;
            }
            rewind(df);
            for(i=0,count=0;i<n;i++,count++)
            {
                fgets(s1,maxlen,df);
                slen=strlen(s1);
                s1[slen-1]='\0';
                slen=strlen(s1);
                s2=simple_split(s1,slen,sep);
                if(s2!=NULL)
                {
                    STUD1[i]=fill_stud(s2);
                    pp=p0->first;
                    while (strcmp(pp->info,s2[1])!=0)
                    {
                        pp=pp->next;
                    }
                    STUD1[i]->fac=pp;
                }
            }
        }
        fclose(df);

        printf("\nHERE IS AN ARRAY OF STRUCTURES WHICH USE DATA FROM THE LINKED LIST:\n");
        for (i=0; i<n; i++)
        {
            struct_out(STUD1[i], STUD1[i]->fac->info);
        }
        copy(s2, p0, p);


    }
    else puts("there is no csv file");
    return 0;
}

