#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <limits.h>

const int N = 13;
int n;
// 定义树节点结构体
struct TreeNode
{
    int num;
    std::shared_ptr<TreeNode> Lnode; // 左孩子
    std::shared_ptr<TreeNode> Rnode; // 右孩子
};

std::vector<std::shared_ptr<TreeNode>> fp(N); // 保存节点
std::vector<char> s(2 * N); // 存储前缀码

// 初始化节点函数，用于生成叶子节点
void init_node(const std::vector<int>& f)
{
    for (size_t i = 0; i < f.size(); ++i)
    {
        auto pt = std::make_shared<TreeNode>(); // 创建一个叶子节点
        pt->num = f[i];
        fp[i] = pt;
    }
}

// 排序函数，将第 N-n 个点插入到已排序的序列中
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

// 构建树的函数
std::shared_ptr<TreeNode> construct_tree(std::vector<int>& f)
{
    if (f.size() == 1)
    {
        // 如果只有一个节点，直接返回这个节点
        return std::make_shared<TreeNode>(TreeNode{ f[0], nullptr, nullptr });
    }
    init_node(f); // 初始化叶子节点
    for (int i = 1; i < n; ++i)
    {
        auto pt = std::make_shared<TreeNode>(); // 创建一个非叶子节点
        pt->num = fp[i - 1]->num + fp[i]->num;
        pt->Lnode = fp[i - 1];
        pt->Rnode = fp[i];
        fp[i] = pt; // 更新节点
        sort(fp); // 排序
    }
    return fp[n - 1]; // 返回树的根节点
}

// 前序遍历函数
void preorder(const std::shared_ptr<TreeNode>& p, int k, char c)
{
    if (!p)
        return;
    if (p)
    {
        s[k] = (c == '1' ? '0' : '1');
        if (!p->Lnode)
        { // 叶子节点
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
    std::cout << "请输入节点个数(必须是正整数): ";
    while (1)
    {
        std::cin >> n;
        if (n <= 0 || n > N || std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n'); // 忽略错误输入直到下一个换行符
            std::cout << "节点个数输入无效,请重新输入：";
            continue;
        }
        break;
    }


    std::vector<int> f(n);
    std::cout << "请输入节点(以空格分隔): ";

    for (int i = 0; i < n; ++i)
    {
        while (!(std::cin >> f[i]))
        {
            if (std::cin.fail())
            {
                std::cin.clear(); // 清除cin的错误标志
                std::cin.ignore(INT_MAX, '\n'); // 忽略错误输入直到下一个换行符
                std::cout << "输入错误，请从第" << i + 1 << "个节点开始重新输入：";
            }
        }
    }


    auto head = construct_tree(f); // 构建树
    s[0] = '0'; // 初始化前缀码
    preorder(head, 0, '1'); // 前序遍历树
    return 0;
}