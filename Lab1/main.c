#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int number;
    struct Node *next;
}node;

node *head, *tail = NULL;

void MSread();
void MIread();
void SSread();

void Mprint(int *, int, int);//печатает матрицу

node *Insert(int);  // считывает лист
void printNode(node *); // печатает лист

void MI_to_MS(int *, int *, int, int);
void MS_to_SS(int*, node**, int);
void SS_to_MI(node**, int*, int);

void destroy(node*);


int main()
{
    int move;
    printf("Внимание, данная программа является бесконечной. ");
    printf("Для ее завершения выберите в главном меню вариант 0\n\n");
    while(1)
    {
        printf("\t\t\t_-_Главное меню_-_\n");
        printf("Как будем вводить матрицу:\n");
        printf("1-Матрица смежности:\n");
        printf("2-Матрица инцидентности:\n");
        printf("3-Список смежности:\n");
        printf("0-завершить программу:\n");

        printf("Введите число от 0 до 3: ");
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
            printf("\tВыводим как список смежности!\n");
            printf("\tВыделение памяти для списка смежности\n");
            arrOfNodes = (node**)malloc(vertex * sizeof(node*));
            MS_to_SS(MS, arrOfNodes, vertex);
            for(int i=0; i<vertex; i++)
	        {
		        printf("\t%d:", i+1);
		        printNode(*(arrOfNodes+i));
	        }
            // освобождение памяти
            for(int i=0; i<vertex; i++) destroy(*(arrOfNodes+i));
            free(arrOfNodes);
            break;
        case 2: 
            printf("\tВыводим как матрицу инцидентности!\n");
            arrOfNodes = (node**)malloc(vertex * sizeof(node*));
            MS_to_SS(MS, arrOfNodes, vertex);
            printf("\tВыделение памяти для матрицы инцидентности!\n");
            MI = (int *)calloc(arc*vertex,sizeof(int));
            SS_to_MI(arrOfNodes, MI, vertex);
            printf("\tПолученная матрица инцидентности:\n");
            Mprint(MI, vertex, arc);
            for(int i=0; i<vertex; i++) destroy(*(arrOfNodes + i));
            free(arrOfNodes);
            free(MI);
            break;
    }
    free(MS);
    printf("\n");
}

void MIread()
{
    int vertex, arc, move;
    int *MI, *MS;
    node **arrOfNodes;
    printf("Введите кол-во дуг графа и кол-во его вершин\n");
    scanf("%d%d", &arc, &vertex);
    printf("\tВыведение памяти для матрицы инцидентности!\n");
    MI = (int *)malloc(arc * vertex * sizeof(int));//выделение памяти для матрицы
    for(int i=0; i<arc; i++)
    {
        printf("\tВведите %d строку: ",i + 1);
        for(int j=0; j<vertex; j++)
            scanf("%d",(MI + i * vertex + j));
    }
    printf("\n");
    printf("\tВведенная матрица:\n");
    Mprint(MI, vertex, arc);

    printf("\nКак будем выводить матрицу:\n");
    printf("1-Матрица смежности:\n");
    printf("2-Список смежности:\n");
    scanf("%d", &move);
    switch(move)
    {
        case 1: 
            printf("Выведение памяти для матрицы смежности!\n");
            MS = (int *)calloc(vertex * vertex, sizeof(int));
            MI_to_MS(MI, MS, vertex, arc);
            printf("Полученная матрица смежности:\n");
            Mprint(MS, vertex, vertex);   
            free(MS);
            break;
        case 2:
            MS = (int *)calloc(vertex * vertex, sizeof(int));
            MI_to_MS(MI, MS, vertex, arc);
            printf("\tВыводим как список смежности!\n");
            printf("\tВыделение памяти для списка смежности\n");
            arrOfNodes = (node**)malloc(vertex * sizeof(node*));
            MS_to_SS(MS, arrOfNodes, vertex);
            for(int i=0; i<vertex; i++)
	        {
		        printf("\t%d:", i+1);
		        printNode(*(arrOfNodes+i));
	        }
            free(MS);
            for(int i=0; i<vertex; i++) destroy(*(arrOfNodes+i));
            free(arrOfNodes);
            break;
    }
    free(MI);
    printf("\n");
}

void SSread()
{
    int vertex, value, move, arc = 0;
    int *MS, *MI;
    head = 0;
    node **arrOfNodes; // создаем массив узлов
    printf("Введите количество вершин: ");
    scanf("%d", &vertex);
    arrOfNodes = (node**)malloc(vertex * sizeof(node*));//выделяем для него память

    //считываем списки
    for(int i=0; i<vertex;)
    {
        printf("\tВведите %d строку: ", i+1);
        while(1)
        {
            scanf("%d", &value);
            *(arrOfNodes+i) = Insert(value);
            if(value == 0)
            {
                i++;
                head = NULL; // если значение листа равно 0, присваем значение NULL,
                break;       // чтобы создать новый список 
            }
            else
                arc++; // считает количество дуг для МИ
        }
    }
    // выводит список на экран
    printf("\nВведенный список: \n");
    for(int i=0; i<vertex; i++)
	{
		printf("\t\t%d:", i+1);
		printNode(*(arrOfNodes+i));
	}

    printf("\nКак будем выводить матрицу:\n");
    printf("1-Матрица смежности:\n");
    printf("2-Матрица инцидентности:\n");
    scanf("%d",&move);
    switch(move)
    {
        case 1 :
            printf("\tВыводим как матрицу смежности!\n");
            MI = (int*)calloc(vertex * arc, sizeof(int));
            SS_to_MI(arrOfNodes, MI, vertex);
            printf("\tВыделение памяти для матрицы смежности\n");
            MS = (int*)malloc(vertex * vertex * sizeof(int));
            MI_to_MS(MI, MS, vertex, arc);
            Mprint(MS, vertex, vertex);
            free(MI);
            free(MS);
            break;

        case 2 :
            printf("\tВыводим как матрицу инцидентности!\n");
            printf("\tВыделение памяти для матрицы инцидентности\n");
            MI = (int*)calloc(vertex * arc, sizeof(int));
            SS_to_MI(arrOfNodes, MI, vertex);
            Mprint(MI, vertex, arc);
            free(MI);
            break;
    }
    // освобождение памяти
    for(int i=0; i<vertex; i++) destroy(*(arrOfNodes+i));
    free(arrOfNodes);
    
}

node *Insert(int x) // ставит список в конец
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
    while(current)
    {
        printf("%2d ",current->number);
        current = current->next;
    }
    printf("\n\n");
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

void SS_to_MI(node **arrOfNodes, int *MI, int vertex)
{
    node *tmp;
    int j;
    int row = 0;
    for(int i = 0; i<vertex; i++)
        {
            tmp = *(arrOfNodes + i);
            while(tmp != NULL && tmp->number != 0)
            {
                j = tmp->number;
                if(j-1 == i)
                    *(MI + row * vertex + i) = 2;
                else
                {
                    *(MI + row * vertex + i) = -1;
                    *(MI + row * vertex + j-1) = 1;
                }
                tmp = tmp->next;
                row++;
            }
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

void destroy(node *arrOfNodes)
{
   node *tmp;
   while(arrOfNodes)
	{
		tmp=arrOfNodes;
        arrOfNodes=arrOfNodes->next;
		free(tmp);
	}
}
