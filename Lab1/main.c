#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//осталось только добавить лист смежности
typedef struct Node
{
    int number;
    struct Node *next;
}node;

node *head = NULL, *tail = NULL;

void MSread();
void MIread();
void SSread();

void Mprint(int *, int, int);//печатает матрицу
void *Insert(int);  // считывает лист
void printNode(node *); // печатает лист

void MS_to_MI(int *, int *, int);
void MI_to_MS(int *, int *, int, int);
void MS_to_SS(int*, node**, int);


int main()
{
    int move;
    printf("Внимание, данная программа является бесконечной. ");
    printf("Для ее завершения выберите в главном меню вариант 0\n");
    printf("Приятного использования)))\n\n");
    while(1)
    {
        printf("\t\t\t__Главное меню__\n");
        printf("Как будем вводить матрицу:\n");
        printf("1-Матрица смежности:\n");
        printf("2-Матрица инцидентности:\n");
        printf("3-Список смежности:\n");
        printf("0-завершить программу:\n");

        printf("Введите число от 0 до 3:\n");
        scanf("%d", &move);
        switch(move)
        {
            case 0 : return 0;
            case 1 : MSread(); break;
            case 2 : MIread(); break;
            case 3 : SSread(); break;
            default:
                printf("Неверно введенные данные, попробуйте заново\n\n");
                break;
        }

    }
    return 0;
}

void MSread()
{
    int *MS, *MI, vertex, arc = 0, move;
    node **arrOfNodes;
    printf("Вы ввводите матрицу смежности:\n\n");
    printf("\tВведите кол-во вершин графа: ");
    scanf("%d", &vertex);
    printf("\tВыделение памяти для матрицы смежности!\n");
    MS = (int *)malloc(vertex * vertex * sizeof(int));
    for(int i=0; i<vertex; i++)
    {
        printf("\tВведите %d строку: ", i + 1);
        for(int j=0; j<vertex; j++)
        {
            scanf("%d",(MS + i * vertex + j));
            if(*(MS + i * vertex + j) == 1)//нахождение дуг графа
                arc++;
        }
    }
    printf("\tВведенная матрица:\n");
    Mprint(MS, vertex, vertex);
    printf("---------------------------------\n");
    printf("Как будем выводить матрицу:\n");
    printf("1-Список смежности:\n");
    printf("2-Матрица инцидентности:\n");
    scanf("%d", &move);
    switch(move)
    {
        case 1:
            arrOfNodes = (node**)malloc(sizeof(node*));
            MS_to_SS(MS, arrOfNodes, vertex);
            
            for(int i=0; i<vertex; i++)
	        {
		        printf("\t%d:", i+1);
		        printNode(*(arrOfNodes+i));
	        }
            break;
        case 2: 
            printf("\tВыделение памяти для матрицы инцидентности!\n");
            MI = (int *)calloc(arc*vertex,sizeof(int));
            MS_to_MI(MS, MI, vertex);
            printf("\tПолученная матрица инцидентности:\n");
            Mprint(MI, vertex, arc);
            free(MI);
            break;
    }
    free(MS);
    printf("\n");
}

// читает матрицу инцидентности
void MIread()
{
    int vertex, arc;
    int *MI, *MS;
    printf("Введите кол-во дуг графа и кол-во его вершин\n");
    scanf("%d%d", &arc, &vertex);
    printf("Выведение памяти для матрицы инцидентности!\n");
    MI = (int *)malloc(arc * vertex * sizeof(int));//выделение памяти для матрицы
    for(int i=0; i<arc; i++)
    {
        printf("Введите %d строку: ",i + 1);
        for(int j=0; j<vertex; j++)
            scanf("%d",(MI + i * vertex + j));
    }
    printf("\n");
    printf("Введенная матрица:\n");
    Mprint(MI, vertex, arc);


    printf("Выведение памяти для матрицы смежности!\n");
    MS = (int *)calloc(vertex * vertex, sizeof(int));
    MI_to_MS(MI, MS, vertex, arc);
    printf("Полученная матрица смежности:\n");
    Mprint(MS, vertex, vertex);

    free(MI);
    free(MS);

    printf("\n");
}

// void SSread()
// {
//     int vertex, L_value;
//     node **arrOfNodes;
//     arrOfNodes = (node**)malloc(sizeof(node*));
//     printf("Введите количество вершин: ");
//     scanf("%d", &vertex);
//     int i = 0, j;
//     while(i<vertex)
//     {
//         printf("\nВведите %d строку\n",i+1);
//         j = 1;
//         while(j)
//         {
//             //printf("\nВведите элемент листа: ");
//             scanf("%d", &L_value);
//             if(L_value == 0)
//             {
//                 j = 0;
//             }
//             Insert(L_value); // сделать список не последовательным
//         }
//         i++;
//     }
// void Insert(int x) // добавить себе либо как у полякова
// {
//         node *temp = (node *)malloc(sizeof(node));
//         temp->number = x;
//         temp->next = NULL;
//         if(head == NULL)
//         {
//             head = temp;
//             tail = temp;
//             //temp = NULL;
//             printf("Занесено\n");
//         }
            
//         else
//         {
//             //node *p = head;

//             tail->next = temp;
//             tail = temp;
//             printf("Сделано\n");
//         }
// }
// void printNode()
// {
//     node *current = head;
//     int i = 1;
//     printf("The List is: \n");
//     //printf("%d : ",i);
//     while(current != NULL)
//     {
//         printf("%d ",current->number);
//         if(current->number == 0)
//         {
//             printf("\n");
//             i++;
//         }
//         current = current->next;
//     }
//     //printf("Checking\n");
// }

void SSread()
{
    int vertex, i, value, move;
    node **arrOfNodes; // создаем массив узлов
    arrOfNodes = (node**)malloc(sizeof(node*));//выделяем для него память
    printf("Введите количество вершин: ");
    scanf("%d", &vertex);

    for(i=0; i<vertex;)
    {
        printf("Введите %d строку: ", i+1);
        while(1)
        {
            scanf("%d", &value);
            *(arrOfNodes+i) = Insert(value);
            if(value == 0)
            {
                i++;
                head = NULL; // если значение листа равно 0, присваем значение,
                break;       // чтобы создать новый список 
            }
        }
    }

        // printf("\nКак будем выводить матрицу:\n");
        // printf("1-Матрица смежности:\n");
        // printf("2-Матрица инцидентности:\n");
        // scanf("%d",&move);
        // switch(move)
        // {
        //     case 2 : SS_to_MI();
        // }

    // выводит список на экран
    for(i=0; i<vertex; i++)
	{
		printf("%d:", i+1);
		printNode(*(arrOfNodes+i));
	}
}

void *Insert(int x) // ставит список в конец
{
        node *temp = (node *)malloc(sizeof(node));
        temp->number = x;
        temp->next = NULL;
        if(head == NULL) // если лист пустой ставим адресс начала(head) и конца(tail) в tmp
        {
            head = temp; // head, tail - глобальные переменные
            tail = temp;
        }   
        else // если нет, ставим адресс конца в tmp
        {
            tail->next = temp;
            tail = temp;
        }
        return head; // вохвращаем head, так как оно всегда показывает на начало списка 
}

void printNode(node *current) // печатает лист
{
    while(current != NULL)
    {
        printf("%2d ",current->number);
        current = current->next;
    }
    printf("\n");
}

void MS_to_MI(int *MS, int *MI, int vertex)
{
    int p=0, i, j;
    for(i=0; i<vertex; i++)
    {
        for(j=0; j<vertex; j++)
        {
            if(*(MS + i * vertex + j) == 1)
            {
                if(i == j)
                {
                   *(MI + p * vertex + j) = 2;
                   p++;
                   continue;
                }
                *(MI + p * vertex + i) = -1;
                *(MI + p * vertex + j) = 1;
                p++;
            }
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

void MS_to_SS(int *MS, node **arrOfNodes, int vertex)
{
    int i, j;
    for(i=0; i<vertex; i++)
    {
        head = NULL;
        for(j=0; j<vertex; j++)
        {
            if(*(MS + i * vertex +j) == 1)
                *(arrOfNodes + i) = Insert(j+1);
        }
        *(arrOfNodes + i) = Insert(0);
    }
}

void Mprint(int *M, int vertex, int arc)
{
    printf("\n");
    for(int i=0; i<arc; i++)
    {
        printf("\t\t");
        for(int j=0; j<vertex; j++)
            printf("%3d",*(M + i * vertex + j));
        printf("\n");
    }
}
