#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *pre;
    struct Node *next;
} Node;

Node *initList() // 初始化
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = 0;
    node->pre = NULL;
    node->next = NULL;
    return node;
}

void headInsert(Node *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    if (list->data == 0)
    {
        // 链表为空
        node->next = list->next;
        node->pre = list;
        list->next = node;
    }
    else
    {
        node->pre = list;
        node->next = list->next;
        list->next->pre = node;
        list->next = node;
    }
}

void trailInsert(Node *list, int data)
{
    Node *node = list;
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    while (node->next)
    {
        node = node->next;
    }
    n->next = NULL;
    node->next = n;
    n->pre = node;
}

void printfList(Node *list)
{
    Node *node = list->next;
    while (node)
    {
        printf("%d ->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void delete(Node *list, int data)
{
    Node *node = list; // 此处node代表上一个节点
    Node *cur = list->next;

    while (cur)
    {
        if (cur->data == data)
        {
            node->next = cur->next;
            cur->next->pre = node;
            free(cur);
            list->data--;
            cur = node->next;
        }
        else
        {
            node = cur;
            cur = cur->next;
        }
    }
}

int main()
{
    Node *list = initList();
    headInsert(list, 1);
    headInsert(list, 2);
    headInsert(list, 3);
    headInsert(list, 4);
    trailInsert(list, 1);
    trailInsert(list, 2);
    trailInsert(list, 3);
    trailInsert(list, 4);
    printfList(list);
    delete (list, 4);
    printfList(list);
    return 0;
}