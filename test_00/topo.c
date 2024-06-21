#include <stdio.h>
#include <stdlib.h>

#define MAXV 100

// 邻接表中的节点结构
typedef struct AdjNode
{
    int v;
    struct AdjNode *next;
} AdjNode;

// 图结构
typedef struct
{
    AdjNode *first;
} VertexNode;

typedef struct
{
    VertexNode vex[MAXV];
    int vexnum, edgenum;
} ALGraph;

// 栈结构
typedef struct
{
    int data[MAXV];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s)
{
    s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// 进栈
void push(Stack *s, int v)
{
    if (s->top < MAXV - 1)
    {
        s->data[++(s->top)] = v;
    }
}

// 出栈
int pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->data[(s->top)--];
    }
    return -1; // 栈空返回-1
}

// 计算入度
void findIndegree(ALGraph *g, int indegree[])
{
    for (int i = 0; i < g->vexnum; i++)
    {
        indegree[i] = 0; // 初始化入度为0
    }
    for (int i = 0; i < g->vexnum; i++)
    {
        AdjNode *p = g->vex[i].first;
        while (p != NULL)
        {
            indegree[p->v]++;
            p = p->next;
        }
    }
}

// 拓扑排序算法
int topo1(ALGraph *g, int topo[])
{
    int indegree[MAXV];
    findIndegree(g, indegree); // 求出每个顶点的入度

    Stack s;
    initStack(&s);
    for (int i = 0; i < g->vexnum; i++)
    {
        if (indegree[i] == 0)
        { // 入度为0的点进栈
            push(&s, i);
        }
    }

    int m = 0; // 对输出顶点计数
    while (!isEmpty(&s))
    {
        int i = pop(&s);
        topo[m++] = i;
        AdjNode *p = g->vex[i].first; // p指向i的第一个邻接点
        while (p)
        {
            int k = p->v;
            if (--indegree[k] == 0)
            {
                push(&s, k);
            }
            p = p->next;
        }
    }

    if (m < g->vexnum)
    {
        return 0; // 图中有回路
    }
    else
    {
        return 1; // 无回路，拓扑排序成功
    }
}

// 添加边
void addEdge(ALGraph *g, int u, int v)
{
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    node->v = v;
    node->next = g->vex[u].first;
    g->vex[u].first = node;
}

// 初始化图
void initGraph(ALGraph *g, int vexnum)
{
    g->vexnum = vexnum;
    g->edgenum = 0;
    for (int i = 0; i < vexnum; i++)
    {
        g->vex[i].first = NULL;
    }
}

int main()
{
    ALGraph g;
    initGraph(&g, 6);

    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);
    addEdge(&g, 4, 5);

    int topo[MAXV];
    int result = topo1(&g, topo); // 调用拓扑排序算法

    if (result)
    {
        printf("拓扑排序结果: ");
        for (int i = 0; i < g.vexnum; i++)
        {
            printf("%d ", topo[i]);
        }
        printf("\n");
    }
    else
    {
        printf("图中存在回路，无法进行拓扑排序\n");
    }

    return 0;
}
