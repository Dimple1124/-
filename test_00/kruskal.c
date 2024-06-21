#include <stdio.h>
#include <stdlib.h>

// 定义最大顶点数和最大边数
#define MAXV 100
#define MAXE 100

// 边结构体
typedef struct
{
    int u, v, w;
} Edge;

// 全局变量
Edge edges[MAXE];  // 存储所有边
int nodeset[MAXV]; // 并查集
int n, m;          // n为顶点数, m为边数

// 合并集合的函数
int merge(int a, int b)
{
    int p = nodeset[a];
    int q = nodeset[b];
    if (p == q)
        return 0;
    for (int i = 0; i < n; i++)
    {
        if (nodeset[i] == q)
            nodeset[i] = p; // a的集合号赋值给b的集合号
    }
    return 1;
}

// Kruskal 算法
int kruskal()
{
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        if (merge(edges[i].u, edges[i].v))
        {
            ans += edges[i].w;
            n--;
            if (n == 1)
                return ans;
        }
    }
    return ans;
}

// 比较边的权值，用于排序
int compare(const void *a, const void *b)
{
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main()
{
    n = 5; // 顶点数
    m = 7; // 边数

    // 初始化边
    edges[0] = (Edge){0, 1, 2};
    edges[1] = (Edge){0, 3, 6};
    edges[2] = (Edge){1, 2, 3};
    edges[3] = (Edge){1, 3, 8};
    edges[4] = (Edge){1, 4, 5};
    edges[5] = (Edge){2, 4, 7};
    edges[6] = (Edge){3, 4, 9};

    // 初始化并查集
    for (int i = 0; i < n; i++)
    {
        nodeset[i] = i;
    }

    // 对边按权值进行排序
    qsort(edges, m, sizeof(Edge), compare);

    // 运行 Kruskal 算法
    int result = kruskal();

    // 输出结果
    printf("Minimum cost: %d\n", result);

    return 0;
}
