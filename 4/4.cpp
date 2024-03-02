#include <iostream>
#include <limits.h>
#include <algorithm>
using namespace std;

void GetVertexAndEdgeCounts(int& vertexCount, int& edgeCount)
{
    // ѭ��ֱ�����յ���Ч�Ķ������ͱ���
    while (true)
    {
        cin >> vertexCount >> edgeCount;
        cin.ignore(INT_MAX, '\n'); // ������ĩ�Ļ��з�
        if (vertexCount == 0 && edgeCount == 0) // ����Ƿ�Ϊ�˳�����
        {
            exit(1);
        }
        else if (!cin || vertexCount < 2 || edgeCount < vertexCount - 1 || edgeCount > vertexCount * (vertexCount - 1) / 2)
        {
            cout << "��������������!" << endl; // ���������Ч��
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
    int vertexCount;   // ������
    int edgeCount;     // ����
    int* vertices;     // ��������
    int** edges;       // ������
    int** adjMatrix;   // �ڽӾ���

    int minTotalCost;  // ��С�ܳɱ�

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
    cout << "�����붥�����ͱ�����";
    GetVertexAndEdgeCounts(vertexCount, edgeCount);

    vertices = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        vertices[i] = i;
    }

    edges = new int* [edgeCount];
    for (int i = 0; i < edgeCount; i++)
    {
        edges[i] = new int[3]; // �洢��㡢�յ㡢��Ȩ��
    }

    adjMatrix = new int* [vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        adjMatrix[i] = new int[vertexCount];
        for (int j = 0; j < vertexCount; j++)
        {
            adjMatrix[i][j] = INT_MAX; // ��ʼ��Ϊ���ֵ
        }
    }

    cout << "����������ÿ���ߵ���㡢�յ��Ȩ�� (�ÿո����)" << endl;
    for (int i = 0; i < edgeCount; i++)
    {
        int startVertex, endVertex, weight;
        cout << "�������" << i + 1 << "���ߵ���Ϣ��";
        cin >> startVertex >> endVertex >> weight;
        cin.ignore(INT_MAX, '\n');

        if (!cin || startVertex < 1 || startVertex > vertexCount || endVertex < 1 || endVertex > vertexCount || weight < 0)
        {
            cout << "�������������!" << endl;
            cin.clear();
            i--; // �ظ��˴�����
            continue;
        }

        edges[i][0] = startVertex - 1; // ����Ϊ��0��ʼ������
        edges[i][1] = endVertex - 1;
        edges[i][2] = weight;

        // �����ڽӾ���
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
    cout << "ִ��Prim�㷨����С������:" << endl;
    minTotalCost = 0;

    int* visited = new int[vertexCount](); // �ѷ��ʶ�������
    visited[0] = 1; // �ӵ�һ�����㿪ʼ

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
        cout << "���Ӷ��� " << start + 1 << " �� " << end + 1 << " �ı߱�ѡ��, Ȩ��: " << minWeight << endl;
    }

    delete[] visited;
}

void Graph::Kruskal()
{
    cout << "ִ��Kruskal�㷨����С������:" << endl;
    minTotalCost = 0;

    // ��ʼ�����鼯
    int* parent = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        parent[i] = i; // ÿ�������ʼʱ�����Լ��ļ���
    }

    // �Ա߰�Ȩ�ؽ�������
    sort(edges, edges + edgeCount, [](const int* a, const int* b) { return a[2] < b[2]; });

    // �����߼���
    for (int i = 0; i < edgeCount; i++)
    {
        int startVertex = edges[i][0];
        int endVertex = edges[i][1];
        int weight = edges[i][2];

        // ���ߵ����������Ƿ����ڲ�ͬ����
        if (FindSet(parent, startVertex) != FindSet(parent, endVertex))
        {
            UnionSets(parent, startVertex, endVertex); // �ϲ�����
            minTotalCost += weight;
            cout << "���Ӷ��� " << startVertex + 1 << " �� " << endVertex + 1 << " �ı߱�ѡ��, Ȩ��: " << weight << endl;
        }
    }

    delete[] parent;
}

int Graph::FindSet(int* parent, int vertex)
{
    if (vertex != parent[vertex])
    {
        parent[vertex] = FindSet(parent, parent[vertex]); // ·��ѹ��
    }
    return parent[vertex];
}

void Graph::UnionSets(int* parent, int vertex1, int vertex2)
{
    int root1 = FindSet(parent, vertex1);
    int root2 = FindSet(parent, vertex2);
    if (root1 != root2)
    {
        parent[root2] = root1; // ��һ�����ϵĸ��ϲ�����һ�����ϵĸ�
    }
}


int main()
{
    Graph g;

    g.Prim();
    cout << "Prim�㷨�������С�������ܳɱ�Ϊ��" << g.GetMinTotalCost() << endl;

    cout << endl;

    g.Kruskal();
    cout << "Kruskal�㷨�������С�������ܳɱ�Ϊ��" << g.GetMinTotalCost() << endl;

    return 0;
}
