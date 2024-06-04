#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *initlist()
{
    Node *list = (Node *)malloc(sizeof(Node));
    list->data = 0;
    list->next = list;
    return list;
}

void headInsert(Node *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = list->next;
    list->next = node;
    list->data++;
}

void trailInsert(Node *list, int data)
{
    Node *pre = list; // 这里实际上是找结尾
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    while (pre->next != list)
    {
        pre = pre->next;
    }
    node->next = list;
    pre->next = node;
}

void delete(Node *list, int data)
{
    Node *pre = list;
    Node *cur = list->next;
    while (cur != list)
    {
        if (cur->data == data)
        {
            pre->next = cur->next;
            free(cur);
            list->data--;
            cur = pre->next; // Move to the next node after deletion
            // return true;
        }
        else
        {
            pre = cur;
            cur = cur->next;
            // return false;
        }
    }
}

void printList(Node *list)
{
    Node *node = list->next;
    while (node != list)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main()
{
    Node *list = initlist();
    headInsert(list, 1);
    headInsert(list, 2);
    headInsert(list, 3);
    headInsert(list, 4);
    printList(list);
    delete (list, 2);
    printList(list);
    return 0;
}