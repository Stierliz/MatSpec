#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int value;
    struct Node *next;
} node;

node *head = NULL, *tail = NULL;

//creating stack
int *stack;
bool *visited;
int top;
//creating stack functions
//-----------------------------------------------------
void push(int x)
{
    *(stack + top) = x;
    top++;
}

void pop()
{
    top--;
}

int showTop()
{
    return *(stack + (top - 1));
}

bool isEmpty()
{
    if (top <= 0)
        return true;
    return false;
}
//------------------------------------------------------
//creating queue 
int *queue;
int front = 0, rear = 0;

//creating queue functions
void enqueue(int element)
{
    *(queue + rear) = element;
    ++rear;
}

void dequeue()
{
    front++;
}

int showRear()
{
    return *(queue + front);
}

bool queueIsEmpty()
{
    if(front == rear)
        return true;
    return false;
}
//------------------------------------------------------

node *Insert(int element)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->value = element;
    tmp->next = NULL;
    if (head == NULL)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tmp;
    }
    return head;
}

void adjListInit(node **arrOfNodes, int vertex) //adjacency list input
{
    int element;
    for (int i = 0; i < vertex;)
    {
        printf("Введите %d лист: ", i + 1);
        while (1)
        {
            scanf("%d", &element);
            *(arrOfNodes + i) = Insert(element);
            if (element == 0)
            {
                i++;
                head = NULL;
                break;
            }
        }
    }

}

void SS_to_MS(int *MS, node **arrOfNodes, int vertex)
{
    node *tmp;
    for (int i = 0; i < vertex; i++)
    {
        tmp = *(arrOfNodes + i);
        while (tmp->value != 0)
        {
            *(MS + i * vertex + (tmp->value - 1)) = 1;
            tmp = tmp->next;
        }
    }
}

void printList(node *arrOfNodes)
{
    node *tmp = arrOfNodes;
    while (tmp != NULL)
    {
        printf("%3d", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void printM(int *MS, int vertex, int edge)
{
    for (int i = 0; i < edge; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            printf("%3d", *(MS + i * vertex + j));
        }
        printf("\n");
    }
    printf("\n");
}

void destroy(node *arrOfNodes)
{
    node *tmp;
    while (arrOfNodes)
    {
        tmp = arrOfNodes;
        arrOfNodes = arrOfNodes->next;
        free(tmp);
    }
    printf("It WAS DEEESTROOYED, dude\n");
}

void DFT(int *MS, int element, int vertex)
{
    printf("%d ", element);
    push(element);
    *(visited + (element - 1)) = true;//so the 1 element is marked too
    while (!isEmpty())
    {//going through the matrix row, if there is 1 - that`s the next element for the stack
        for (int i = 0; i < vertex; i++)
        {
            if (*(MS + (showTop() - 1) * vertex + i) == 1 && !*(visited + i))
            {
                //DFT(MS, i + 1, vertex); recursion version
                printf("%d ", i+1);
                *(visited + i) = true;
                push(i+1);
                break;
            }
            else if (i == vertex - 1)//if no 1`s in the row or all ones are marked
                pop();              // delete the element from the stack
        }
    }
}

void BFT(int *MS, int element, int vertex)
{
    printf("%d ", element);
    *(visited + (element - 1)) = true;
    enqueue(element);
    while (!queueIsEmpty())
    {
        for (int i = 0; i < vertex; i++)
        {
            if (*(MS + (showRear() - 1) * vertex + i) == 1 && !*(visited + i))
            {
                //BFT(MS, i + 1, vertex);
                printf("%d ", i + 1);
                enqueue(i + 1);
                *(visited + i) = true;
                break;
            }
            else if (i == vertex - 1)
                dequeue();
        }
    }
}

int main()
{
    node **arrOfNodes;
    int *MS;
    int vertex, element;

    printf("Введите количество вершин: ");
    scanf("%d", &vertex);

    //readList
    arrOfNodes = (node **)malloc(vertex * sizeof(node *));
    adjListInit(arrOfNodes, vertex);

    //printList
    for (int i = 0; i < vertex; i++)
    {
        printf("%d: ", i + 1);
        printList(*(arrOfNodes + i));
    }
    printf("\n");

    //tranfformation of SS to MS
    MS = (int *)calloc(vertex * vertex, sizeof(int));
    SS_to_MS(MS, arrOfNodes, vertex);
    printM(MS, vertex, vertex);

    int choice;
    while (1)
    {
        printf("Для завершения программы нажмите  0\n");
        printf("Для прохода в глубину нажмите 1\n");
        printf("Для прохода в ширину нажмите 2\n");
        visited = (bool *)malloc(vertex * sizeof(bool));
        for(int i = 0; i < vertex; i++)
        {
            *(visited + i) = false;
        }
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("Завершение программы\n");
            free(visited);
            return 0;
            //Depth First Traversal
        case 1:
            printf("Проход в глубину: ");
            stack = (int *)malloc(vertex * sizeof(int));
            DFT(MS, 1, vertex);
            free(stack);
            free(visited);
            printf("\n");
            break;
            //Breadth First Traversal
        case 2:
            printf("Проход в ширину: ");
            queue = (int *)malloc(vertex * sizeof(int));
            BFT(MS, 1, vertex);
            free(queue);
            free(visited);
            printf("\n");
            break;
        }
    }

    //destroy
    for (int i = 0; i < vertex; i++)
        destroy(*(arrOfNodes + i));
    free(arrOfNodes);
    free(MS);

    return 0;
}