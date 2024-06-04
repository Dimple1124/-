#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;
Node *initque()
{
    Node *q = (Node *)malloc(sizeof(Node));
    q->data = 0;
    q->next = NULL;
    return q;
}
void inque(Node *q, int data)
{
    Node *t = q;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    for (int i = 0; i < q->data; i++)
    {
        t = t->next;
    }
    node->next = t->next;
    t->next = node;
    q->data++;
}
int isempty(Node *s)
{
    if (s->data == 0 || s->next == NULL)
        return 1;
    else
        return 0;
}
void pop(Node *q)
{
    if (isempty(q))
    {
        return;
    }
    else
    {
        Node *node = q->next;
        q->next = node->next;
        free(node);
        q->data--;
    }
}
int get_pop(Node *q)
{
    if (isempty(q))
    {
        return -1;
    }
    else
    {
        Node *node = q->next;
        return node->data;
    }
}
void printque(Node *q)
{
    Node *node = q->next;
    while (node)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
int main()
{
    Node *s = initque();
    inque(s, 1);
    inque(s, 2);
    inque(s, 3);
    inque(s, 4);
    printque(s);
    int ans = get_pop(s);
    printf("top=%d\n", ans);
    pop(s);
    printque(s);
    ans = get_pop(s);
    printf("top=%d\n", ans);
    return 0;
}