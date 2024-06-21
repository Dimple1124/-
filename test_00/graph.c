#include <stdio.h>
#include <stdlib.h>

#define maxsize 5

typedef struct graph
{
    char *vexs; // 顶点
    int **arcs; // 边
    int vexnum; // 顶点数量
    int arcnum; // 边的数量
} graph;

graph *init(int vexnum)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->vexs = (char *)malloc(sizeof(char) * vexnum);
    g->arcs = (int **)malloc(sizeof(int *) * vexnum);
    for (int i = 0; i < vexnum; i++)
    {
        g->arcs[i] = (int *)malloc(sizeof(int) * vexnum);
        for (int j = 0; j < vexnum; j++)
        {
            g->arcs[i][j] = 0; // 初始化邻接矩阵
        }
    }
    g->vexnum = vexnum;
    g->arcnum = 0;
    return g;
}

void creategraph(graph *g, char *vexs, int *arcs)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        g->vexs[i] = vexs[i];
        for (int j = 0; j < g->vexnum; j++)
        {
            g->arcs[i][j] = *(arcs + i * g->vexnum + j);
            if (g->arcs[i][j] != 0)
                g->arcnum++;
        }
    }
    g->arcnum /= 2;
}

void dfs(graph *g, int *visited, int index)
{
    printf("%c", g->vexs[index]);
    visited[index] = 1; // 标记节点为已访问
    int has_child = 0;
    for (int i = 0; i < g->vexnum; i++)
    {
        if (g->arcs[index][i] == 1 && !visited[i])
        {
            has_child = 1;
            dfs(g, visited, i);
        }
    }
    if (!has_child)
    {
        printf("#");
    }
    for (int i = 0; i < g->vexnum; i++)
    {
        if (g->arcs[index][i] == 1 && !visited[i])
        {
            dfs(g, visited, i);
        }
    }
}

typedef struct queue
{
    int data[maxsize];
    int front;
    int rear;
} queue;

queue *initque()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = q->rear = 0;
    return q;
}

int isfull(queue *q)
{
    return (q->rear + 1) % maxsize == q->front;
}

void inque(queue *q, int data)
{
    if (isfull(q))
        return;
    q->data[q->rear] = data;
    q->rear = (q->rear + 1) % maxsize;
}

int isempty(queue *q)
{
    return q->front == q->rear;
}

int pop(queue *q)
{
    if (isempty(q))
        return -1;
    int data = q->data[q->front];
    q->front = (q->front + 1) % maxsize;
    return data;
}

void bfs(graph *g, int *visited, int index)
{
    queue *q = initque();
    printf("%c\t", g->vexs[index]);
    visited[index] = 1;
    inque(q, index);
    while (!isempty(q))
    {
        int i = pop(q);
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] == 1 && !visited[j])
            {
                printf("%c\t", g->vexs[j]);
                visited[j] = 1;
                inque(q, j);
            }
        }
    }
    free(q); // 释放队列内存
}

void freegraph(graph *g)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        free(g->arcs[i]);
    }
    free(g->arcs);
    free(g->vexs);
    free(g);
}

int main()
{
    graph *g = init(5);
    int *visited = (int *)malloc(sizeof(int) * g->vexnum);
    for (int i = 0; i < g->vexnum; i++)
    {
        visited[i] = 0;
    }

    int arcs[5][5] = {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 1, 0}};

    creategraph(g, "ABCDE", (int *)arcs);

    bfs(g, visited, 0);
    printf("\n");

    for (int i = 0; i < g->vexnum; i++)
    {
        visited[i] = 0;
    }

    dfs(g, visited, 0);
    printf("\n");

    free(visited);
    freegraph(g);
    return 0;
}
