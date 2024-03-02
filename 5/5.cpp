#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <limits.h>

const int N = 13;
int n;
// �������ڵ�ṹ��
struct TreeNode
{
    int num;
    std::shared_ptr<TreeNode> Lnode; // ����
    std::shared_ptr<TreeNode> Rnode; // �Һ���
};

std::vector<std::shared_ptr<TreeNode>> fp(N); // ����ڵ�
std::vector<char> s(2 * N); // �洢ǰ׺��

// ��ʼ���ڵ㺯������������Ҷ�ӽڵ�
void init_node(const std::vector<int>& f)
{
    for (size_t i = 0; i < f.size(); ++i)
    {
        auto pt = std::make_shared<TreeNode>(); // ����һ��Ҷ�ӽڵ�
        pt->num = f[i];
        fp[i] = pt;
    }
}

// ������������ N-n ������뵽�������������
void sort(std::vector<std::shared_ptr<TreeNode>>& array)
{
    for (int i = 0; i < n - 1; ++i)
    {
        if (array[i]->num > array[i + 1]->num)
        {
            std::swap(array[i], array[i + 1]);
        }
    }
}

// �������ĺ���
std::shared_ptr<TreeNode> construct_tree(std::vector<int>& f)
{
    if (f.size() == 1)
    {
        // ���ֻ��һ���ڵ㣬ֱ�ӷ�������ڵ�
        return std::make_shared<TreeNode>(TreeNode{ f[0], nullptr, nullptr });
    }
    init_node(f); // ��ʼ��Ҷ�ӽڵ�
    for (int i = 1; i < n; ++i)
    {
        auto pt = std::make_shared<TreeNode>(); // ����һ����Ҷ�ӽڵ�
        pt->num = fp[i - 1]->num + fp[i]->num;
        pt->Lnode = fp[i - 1];
        pt->Rnode = fp[i];
        fp[i] = pt; // ���½ڵ�
        sort(fp); // ����
    }
    return fp[n - 1]; // �������ĸ��ڵ�
}

// ǰ���������
void preorder(const std::shared_ptr<TreeNode>& p, int k, char c)
{
    if (!p)
        return;
    if (p)
    {
        s[k] = (c == '1' ? '0' : '1');
        if (!p->Lnode)
        { // Ҷ�ӽڵ�
            std::cout << std::left << std::setw(2) << p->num << ": ";
            for (int j = 0; j <= k; ++j)
                std::cout << s[j];
            std::cout << '\n';
        }
        if (p->Lnode)
            preorder(p->Lnode, k + 1, '1');
        if (p->Rnode)
            preorder(p->Rnode, k + 1, 'r');
    }
}

int main()
{
    std::cout << "������ڵ����(������������): ";
    while (1)
    {
        std::cin >> n;
        if (n <= 0 || n > N || std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n'); // ���Դ�������ֱ����һ�����з�
            std::cout << "�ڵ����������Ч,���������룺";
            continue;
        }
        break;
    }


    std::vector<int> f(n);
    std::cout << "������ڵ�(�Կո�ָ�): ";

    for (int i = 0; i < n; ++i)
    {
        while (!(std::cin >> f[i]))
        {
            if (std::cin.fail())
            {
                std::cin.clear(); // ���cin�Ĵ����־
                std::cin.ignore(INT_MAX, '\n'); // ���Դ�������ֱ����һ�����з�
                std::cout << "���������ӵ�" << i + 1 << "���ڵ㿪ʼ�������룺";
            }
        }
    }


    auto head = construct_tree(f); // ������
    s[0] = '0'; // ��ʼ��ǰ׺��
    preorder(head, 0, '1'); // ǰ�������
    return 0;
}