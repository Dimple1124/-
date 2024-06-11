#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} treenode;

typedef struct hftree
{
    treenode *data;
    int len;
} hftree;

hftree *inittree(int *weight, int len)
{
    hftree *t = (hftree *)malloc(sizeof(hftree));
    t->data = (treenode *)malloc(sizeof(treenode) * (2 * len - 1));
    t->len = len;
    for (int i = 0; i < len; i++)
    {
        t->data[i].weight = weight[i];
        t->data[i].parent = -1;
        t->data[i].lchild = -1;
        t->data[i].rchild = -1;
    }
    for (int i = len; i < 2 * len - 1; i++)
    {
        t->data[i].weight = 0;
        t->data[i].parent = -1;
        t->data[i].lchild = -1;
        t->data[i].rchild = -1;
    }
    return t;
}

void selectmin(hftree *t, int *f_min, int *s_min)
{
    int min1 = 99999, min2 = 99999;
    *f_min = -1;
    *s_min = -1;
    for (int i = 0; i < t->len; i++)
    {
        if (t->data[i].parent == -1)
        {
            if (t->data[i].weight < min1)
            {
                min2 = min1;
                *s_min = *f_min;
                min1 = t->data[i].weight;
                *f_min = i;
            }
            else if (t->data[i].weight < min2)
            {
                min2 = t->data[i].weight;
                *s_min = i;
            }
        }
    }
}

void createhftree(hftree *t)
{
    int min, se_min;
    int original_len = t->len; // 原始叶节点数
    for (int i = 0; i < original_len - 1; i++)
    {
        selectmin(t, &min, &se_min);
        t->data[t->len].weight = t->data[min].weight + t->data[se_min].weight;
        t->data[t->len].lchild = min;
        t->data[t->len].rchild = se_min;
        t->data[min].parent = t->len;
        t->data[se_min].parent = t->len;
        t->len++;
    }
}

void preorder(hftree *t, int index)
{
    if (index != -1)
    {
        printf("%d ", t->data[index].weight);
        preorder(t, t->data[index].lchild);
        preorder(t, t->data[index].rchild);
    }
}

int main()
{
    int weight[4] = {1, 2, 3, 4};
    hftree *t = inittree(weight, 4);
    createhftree(t);
    preorder(t, t->len - 1); // 从根节点开始
    free(t->data);
    free(t);
    return 0;
}
