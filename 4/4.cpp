#include <iostream>
#include <limits.h>
#include <algorithm>
using namespace std;

void GetVertexAndEdgeCounts(int& vertexCount, int& edgeCount)
{
    // 循环直到接收到有效的顶点数和边数
    while (true)
    {
        cin >> vertexCount >> edgeCount;
        cin.ignore(INT_MAX, '\n'); // 忽略行末的换行符
        if (vertexCount == 0 && edgeCount == 0) // 检查是否为退出条件
        {
            exit(1);
        }
        else if (!cin || vertexCount < 2 || edgeCount < vertexCount - 1 || edgeCount > vertexCount * (vertexCount - 1) / 2)
        {
            cout << "输入有误，请重试!" << endl; // 检查输入有效性
            cin.clear();
        }
        else
        {
            break;
        }
    }
}

class Graph
{
private:
    int vertexCount;   // 顶点数
    int edgeCount;     // 边数
    int* vertices;     // 顶点数组
    int** edges;       // 边数组
    int** adjMatrix;   // 邻接矩阵

    int minTotalCost;  // 最小总成本

public:
    Graph();
    ~Graph();

    void Prim();
    void Kruskal();

    int FindSet(int* parent, int vertex);
    void UnionSets(int* parent, int vertex1, int vertex2);

    int GetMinTotalCost() const { return minTotalCost; }
};

Graph::Graph()
{
    cout << "请输入顶点数和边数：";
    GetVertexAndEdgeCounts(vertexCount, edgeCount);

    vertices = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        vertices[i] = i;
    }

    edges = new int* [edgeCount];
    for (int i = 0; i < edgeCount; i++)
    {
        edges[i] = new int[3]; // 存储起点、终点、边权重
    }

    adjMatrix = new int* [vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        adjMatrix[i] = new int[vertexCount];
        for (int j = 0; j < vertexCount; j++)
        {
            adjMatrix[i][j] = INT_MAX; // 初始化为最大值
        }
    }

    cout << "请依次输入每条边的起点、终点和权重 (用空格隔开)" << endl;
    for (int i = 0; i < edgeCount; i++)
    {
        int startVertex, endVertex, weight;
        cout << "请输入第" << i + 1 << "条边的信息：";
        cin >> startVertex >> endVertex >> weight;
        cin.ignore(INT_MAX, '\n');

        if (!cin || startVertex < 1 || startVertex > vertexCount || endVertex < 1 || endVertex > vertexCount || weight < 0)
        {
            cout << "输入错误，请重试!" << endl;
            cin.clear();
            i--; // 重复此次输入
            continue;
        }

        edges[i][0] = startVertex - 1; // 调整为从0开始的索引
        edges[i][1] = endVertex - 1;
        edges[i][2] = weight;

        // 更新邻接矩阵
        adjMatrix[startVertex - 1][endVertex - 1] = weight;
        adjMatrix[endVertex - 1][startVertex - 1] = weight;
    }
}

Graph::~Graph()
{
    delete[] vertices;
    for (int i = 0; i < edgeCount; i++)
    {
        delete[] edges[i];
    }
    delete[] edges;

    for (int i = 0; i < vertexCount; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

void Graph::Prim()
{
    cout << "执行Prim算法求最小生成树:" << endl;
    minTotalCost = 0;

    int* visited = new int[vertexCount](); // 已访问顶点数组
    visited[0] = 1; // 从第一个顶点开始

    for (int i = 0; i < vertexCount - 1; i++)
    {
        int minWeight = INT_MAX;
        int start = 0, end = 0;

        for (int j = 0; j < vertexCount; j++)
        {
            if (visited[j])
            {
                for (int k = 0; k < vertexCount; k++)
                {
                    if (!visited[k] && adjMatrix[j][k] < minWeight)
                    {
                        minWeight = adjMatrix[j][k];
                        start = j;
                        end = k;
                    }
                }
            }
        }

        visited[end] = 1;
        minTotalCost += minWeight;
        cout << "连接顶点 " << start + 1 << " 和 " << end + 1 << " 的边被选中, 权重: " << minWeight << endl;
    }

    delete[] visited;
}

void Graph::Kruskal()
{
    cout << "执行Kruskal算法求最小生成树:" << endl;
    minTotalCost = 0;

    // 初始化并查集
    int* parent = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        parent[i] = i; // 每个顶点初始时代表自己的集合
    }

    // 对边按权重进行排序
    sort(edges, edges + edgeCount, [](const int* a, const int* b) { return a[2] < b[2]; });

    // 遍历边集合
    for (int i = 0; i < edgeCount; i++)
    {
        int startVertex = edges[i][0];
        int endVertex = edges[i][1];
        int weight = edges[i][2];

        // 检查边的两个顶点是否属于不同集合
        if (FindSet(parent, startVertex) != FindSet(parent, endVertex))
        {
            UnionSets(parent, startVertex, endVertex); // 合并集合
            minTotalCost += weight;
            cout << "连接顶点 " << startVertex + 1 << " 和 " << endVertex + 1 << " 的边被选中, 权重: " << weight << endl;
        }
    }

    delete[] parent;
}

int Graph::FindSet(int* parent, int vertex)
{
    if (vertex != parent[vertex])
    {
        parent[vertex] = FindSet(parent, parent[vertex]); // 路径压缩
    }
    return parent[vertex];
}

void Graph::UnionSets(int* parent, int vertex1, int vertex2)
{
    int root1 = FindSet(parent, vertex1);
    int root2 = FindSet(parent, vertex2);
    if (root1 != root2)
    {
        parent[root2] = root1; // 将一个集合的根合并到另一个集合的根
    }
}


int main()
{
    Graph g;

    g.Prim();
    cout << "Prim算法计算的最小生成树总成本为：" << g.GetMinTotalCost() << endl;

    cout << endl;

    g.Kruskal();
    cout << "Kruskal算法计算的最小生成树总成本为：" << g.GetMinTotalCost() << endl;

    return 0;
}
