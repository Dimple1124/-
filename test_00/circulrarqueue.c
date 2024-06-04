#include <stdio.h>
#include <stdlib.h>
#define maxsize 6
typedef struct Node
{
    int data[maxsize];
    // struct Node *next;
    int front;
    int rear;
} Node;
Node *initque()
{
    Node *q = (Node *)malloc(sizeof(Node));
    q->front = q->rear = 0;
    return q;
}
int isfull(Node *q)
{
    if ((q->rear + 1) % maxsize == q->front)
    {
        return 1;
    }
    else
        return 0;
}
void inque(Node *q, int data)
{
    if (isfull(q))
        return;
    else
    {
        q->data[q->rear] = data;
        q->rear = (q->rear + 1) % maxsize;
    }
}
int isempty(Node *q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}
void pop(Node *q)
{
    if (isempty(q))
        return;
    else
    {
        int data = q->data[q->front];
        q->front = (q->front + 1) % maxsize;
    }
}
void printque(Node *q)
{
    int length = (q->rear - q->front + maxsize) % maxsize;
    int index = q->front;
    for (int i = 0; i < length; i++)
    {
        printf("%d->", q->data[index]);
        index = (index + 1) % maxsize;
    }
    printf("NULL\n");
}
int main()
{
    Node *q = initque();
    inque(q, 1);
    inque(q, 2);
    inque(q, 3);
    inque(q, 4);
    inque(q, 5);
    printque(q);
    pop(q);
    printque(q);
    return 0;
}