#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5
#define INF 9999

// 全局变量
int lowcost[N]; // 存储最小权值
int closest[N]; // 存储对应的顶点
bool s[N];      // 标记顶点是否加入最小生成树

void prim(int n, int u0, int c[N][N])
{
    s[u0] = true;
    for (int i = 0; i < n; i++)
    {
        if (i != u0)
        {
            lowcost[i] = c[u0][i];
            closest[i] = u0;
            s[i] = false;
        }
        else
        {
            lowcost[i] = 0;
        }
    }

    for (int i = 1; i < n; i++)
    {
        int tmp = INF;
        int t = -1;
        for (int j = 0; j < n; j++)
        {
            if (!s[j] && lowcost[j] < tmp)
            {
                t = j;
                tmp = lowcost[j];
            }
        }

        if (t == -1)
        {
            break; // 找不到t，跳出循环
        }

        s[t] = true; // 将t加入集合

        // 输出当前选择的边及其权重
        printf("Edge: %d - %d, Weight: %d\n", closest[t], t, c[closest[t]][t]);

        for (int j = 0; j < n; j++)
        {
            if (!s[j] && c[t][j] < lowcost[j])
            {
                lowcost[j] = c[t][j];
                closest[j] = t;
            }
        }
    }
}

int main()
{
    int n = 5;  // 顶点数
    int u0 = 0; // 起始顶点
    int c[N][N] = {
        {0, 2, INF, 6, INF},
        {2, 0, 3, 8, 5},
        {INF, 3, 0, INF, 7},
        {6, 8, INF, 0, 9},
        {INF, 5, 7, 9, 0}};

    prim(n, u0, c);

    return 0;
}
