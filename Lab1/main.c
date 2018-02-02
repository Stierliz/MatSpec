#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//осталось только добавить лист смежности

void MSread();
void MIread();
void Mprint(int *, int, int);//печатает матрицу
void MS_to_MI(int *, int *, int);
void MI_to_MS(int *, int *, int, int);

int main()
{
    int move;
    while(1)
    {
        printf("Как будем вводить матрицу:\n");
        printf("1-Матрица смежности:\n");
        printf("2-Матрица инцидентности:\n");
        printf("3-Список смежности:\n");
        printf("0-завершить программу:\n");

        printf("Введите число от 0 до 3:\n");
        scanf("%d",&move);
        switch(move)
        {
            case 0 : return 0;
            case 1 : MSread(); break;
            case 2: MIread(); break;
            default:
                printf("Неверно введенные данные, попробуйте заново\n\n");
                break;
        }

    }
    return 0;
}

void MSread()
{
    int *MS, *MI, vertex, arc = 0;
    printf("Введите кол-во вершин графа:\n");
    scanf("%d",&vertex);
    printf("Выведение памяти для матрицы смежности!\n");
    MS = (int*)malloc(vertex*vertex*sizeof(int));
    for(int i=0; i<vertex; i++)
    {
        printf("Введите %d строку: ",i+1);
        for(int j=0; j<vertex; j++)
        {
            scanf("%d",(MS+i*vertex+j));
            if(*(MS+i*vertex+j) == 1)//нахождение дуг графа
                arc++;
        }
    }
    printf("Введенная матрица:\n");
    Mprint(MS, vertex, vertex);
    printf("---------------------------------\n");
    printf("Выведение памяти для матрицы инцидентности!\n");
    MI = (int*)calloc(arc*vertex,sizeof(int));
    MS_to_MI(MS, MI, vertex);
    printf("Полученная матрица инцидентности:\n");
    Mprint(MI,vertex,arc);
    free(MS);
    free(MI);
    printf("\n");
}

// читает матрицу инцидентности
void MIread()
{
    int vertex,arc;
    int *MI,*MS;
    printf("Введите кол-во дуг графа и кол-во его вершин\n");
    scanf("%d%d",&arc,&vertex);
    printf("Выведение памяти для матрицы инцидентности!\n");
    MI = (int *)malloc(arc*vertex*sizeof(int));//выделение памяти для матрицы
    for(int i=0; i<arc; i++)
    {
        printf("Введите %d строку: ",i+1);
        for(int j=0; j<vertex; j++)
            scanf("%d",(MI+i*vertex+j));
    }
    printf("\n");
    printf("Введенная матрица:\n");
    Mprint(MI,vertex,arc);


    printf("Выведение памяти для матрицы смежности!\n");
    MS = (int *)calloc(vertex*vertex,sizeof(int));
    MI_to_MS(MI, MS, vertex, arc);
    printf("Полученная матрица смежности:\n");
    Mprint(MS,vertex,vertex);

    free(MI);
    free(MS);

    printf("\n");
}

void MS_to_MI(int *MS, int *MI, int vertex)
{
    int p=0, check, i, j;
    for(i=0; i<vertex; i++)
    {
        check = 0;
        for(j=0; j<vertex; j++)
        {
            if(*(MS+i*vertex+j)==1)
            {
                check++;
                *(MI+p*vertex+i)= -1;
                *(MI+p*vertex+j) =1;
                p++;
            }
        }
        if(check == 1)
            {
                *(MI+(p-1)*vertex+i) =2;
            }
    }

}

void MI_to_MS(int *MI, int *MS, int vertex, int arc)
{
    int p, d;
    for(int i=0; i<arc; i++)
    {
        for(int j=0; j<vertex; j++)
        {
            if(*(MI + i * vertex + j) == -1)
                p = j;
            else if(*(MI + i * vertex + j) == 1)
                d = j;
            else if(*(MI + i * vertex + j) == 2)
                p = d = j;
        }
        *(MS + p * vertex + d) = 1;
    }
}

void Mprint(int *M, int vertex, int arc)
{
    for(int i=0; i<arc; i++)
    {
        for(int j=0; j<vertex; j++)
            printf("%3d",*(M + i * vertex + j));
        printf("\n");
    }
}


