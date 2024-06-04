#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *initlist()
{
    Node *list = (Node *)malloc(sizeof(Node));
    list->data = 0;
    list->next = NULL;
    return list;
}

void hi(Node *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = list->next;
    list->next = node;
    list->data++;
}

void el(Node *list, int data)
{
    Node *head = list;
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    list = list->next;
    while (list->next)
    {
        list = list->next;
    }
    list->next = node;
    head->data++;
}

void delete(Node *list, int data)
{
    Node *pre = list;
    Node *cur = list->next;

    while (cur)
    {
        if (cur->data == data)
        {
            pre->next = cur->next;
            free(cur);
            list->data--;
            cur = pre->next; // Move to the next node after deletion
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
    }
}

void print(Node *list)
{
    list = list->next;
    while (list)
    {
        printf("%d", list->data);
        list = list->next;
    }
    printf("\n");
}

int main()
{
    Node *list = initlist();
    hi(list, 1);
    hi(list, 2);
    hi(list, 3);
    el(list, 3);
    el(list, 5);
    el(list, 6);
    print(list);
    delete (list, 3);
    print(list);
    return 0;
}