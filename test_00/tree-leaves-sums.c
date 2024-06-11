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

// 计算叶子节点个数
int countLeafNodes(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
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

    // 计算并输出叶子节点个数
    int leafCount = countLeafNodes(root);
    printf("Number of leaf nodes: %d\n", leafCount);

    // 释放内存
    freeTree(root);
    return 0;
}
