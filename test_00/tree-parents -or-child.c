#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点
typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新节点
TreeNode *createNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 插入节点
TreeNode *insertNode(TreeNode *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// 前序遍历输出树
void preorder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// 查找节点的双亲
TreeNode *findParent(TreeNode *root, TreeNode *node)
{
    if (root == NULL || root == node)
    {
        return NULL;
    }
    if (root->left == node || root->right == node)
    {
        return root;
    }
    TreeNode *parent = findParent(root->left, node);
    if (parent != NULL)
    {
        return parent;
    }
    return findParent(root->right, node);
}

// 查找某个值的节点
TreeNode *findNode(TreeNode *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == data)
    {
        return root;
    }
    TreeNode *foundNode = findNode(root->left, data);
    if (foundNode != NULL)
    {
        return foundNode;
    }
    return findNode(root->right, data);
}

// 释放内存
void freeTree(TreeNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// 主函数
int main()
{
    TreeNode *root = NULL;
    int nodes[] = {10, 5, 1, 7, 40, 50};
    int size = sizeof(nodes) / sizeof(nodes[0]);

    // 创建二叉树
    for (int i = 0; i < size; i++)
    {
        root = insertNode(root, nodes[i]);
    }

    // 输出树的前序遍历
    printf("Tree in preorder: ");
    preorder(root);
    printf("\n");

    // 查找某个值的双亲节点
    int target = 7;
    TreeNode *targetNode = findNode(root, target);
    if (targetNode != NULL)
    {
        TreeNode *parent = findParent(root, targetNode);
        if (parent != NULL)
        {
            printf("Parent of node %d: %d\n", target, parent->data);
        }
        else
        {
            printf("Node %d has no parent (it is the root).\n", target);
        }
    }
    else
    {
        printf("Node %d not found in the tree.\n", target);
    }

    // 查找某个值的孩子节点
    if (targetNode != NULL)
    {
        if (targetNode->left != NULL)
        {
            printf("Left child of node %d: %d\n", target, targetNode->left->data);
        }
        else
        {
            printf("Node %d has no left child.\n", target);
        }
        if (targetNode->right != NULL)
        {
            printf("Right child of node %d: %d\n", target, targetNode->right->data);
        }
        else
        {
            printf("Node %d has no right child.\n", target);
        }
    }

    // 释放内存
    freeTree(root);
    return 0;
}
