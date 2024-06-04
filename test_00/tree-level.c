#include <stdlib.h>
#include <stdio.h>

typedef struct treenode
{
    char data;
    struct treenode *lchild;
    struct treenode *rchild;
} treenode;

typedef struct quetree
{
    treenode *data;
    struct quetree *pre;
    struct quetree *next;

} quenode;

void createtree(treenode **t)
{
    char data;
    scanf(" %c", &data);
    if (data == '#')
        *t = NULL;
    else
    {
        *t = (treenode *)malloc(sizeof(treenode));
        (*t)->data = data;
        // 创建左右子树，逻辑一致，进行递归
        createtree(&((*t)->lchild));
        createtree(&((*t)->rchild));
    }
}
void preorder(treenode *t)
{
    if (t == NULL)
        return;
    else
    {
        printf("%c ", t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}
quenode *initque()
{
    quenode *q = (quenode *)malloc(sizeof(quenode));
    q->data = NULL;
    q->next = q;
    q->pre = q;
    return q;
}
void enque(treenode *data, quenode *q) // 双向循环队列,入队
{
    quenode *node = (quenode *)malloc(sizeof(quenode));
    quenode *tail = q->pre;
    node->data = data;
    node->pre = tail;
    node->next = q;
    tail->next = node;
    q->pre = node;
}
int isempty(quenode *q)
{
    if (q->next == q)
        return 1;
    else
        return 0;
}

quenode *deque(quenode *q) // 出队
{
    if (isempty(q))
        return NULL;
    else
    {
        quenode *node = q->next;
        q->next->next->pre = q;
        q->next = q->next->next;
        return node;
    }
}

void leveltra(quenode *q, treenode *t)
{
    enque(t, q);
    while (!isempty(q))
    {
        quenode *node = deque(q);
        printf("%c ", node->data->data);
        if (node->data->lchild)
        {
            enque(node->data->lchild, q);
        }
        if (node->data->rchild)
        {
            enque(node->data->rchild, q);
        }
        free(node);
    }
    printf("\n");
}
int main()
{
    treenode *t;
    createtree(&t);
    quenode *q = initque();
    preorder(t);
    printf("\n");
    leveltra(q, t);
    return 0;
}