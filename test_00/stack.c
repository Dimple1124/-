#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;
Node *initStack()//初始化
{
    Node *S = (Node *)malloc(sizeof(Node));
    S->data = 0;
    S->next = NULL;
    return S;
}
int isempty(Node *s)
{
    if(s->data ==0 || s->next==NULL)
    {
        return 1;
    }
    else
        return 0;
}
int get_pop(Node *s)
{
    if(isempty(s))
        return -1;
    else
    {
        return s->next->data;
    }
}
void pop(Node *s)
{
    if(isempty(s))
    {
        return ;
    }
    else
    {
        Node *node = s->next;
        s->next = node->next;
        free(node);
    }
}
void push(Node *s,int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = s->next;
    s->next = node;
    s->data++;
}
void printstack(Node *s)//输出遍历
{
    Node *node = s -> next;
    while(node)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
int main()
{
    Node *s = initStack();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    printstack(s);
    int ans = get_pop(s);
    pop(s);
    printf("top=%d\n", ans);
    printstack(s);
    return 0;
}//yoxi!

