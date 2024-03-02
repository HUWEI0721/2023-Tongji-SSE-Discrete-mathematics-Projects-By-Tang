#include<iostream>
#include<climits>
#include<conio.h>
#include<stdlib.h>
using namespace std;

// 生成一个行列数都为num的二维数组
void CreateMatrix(bool**& matrix, const int num)
{
	matrix = (bool**) new bool* [num];  /*开辟一维指针的数组*/

	if (matrix == NULL) 
	{
		cerr << "内存分配失败！" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		matrix[i] = new bool[num];  /*为每一个一维指针开辟空间*/

		if (matrix[i] == NULL) {
			cerr << "内存分配失败！" << endl;
			exit(1);
		}
	}
}

// 删除一个行列数都为num的二维数组
void DeleteMatrix(bool**& matrix, const int num)
{
	for (int i = 0; i < num; i++)
		delete[] matrix[i];
}

// 展示一个行列数都为num的二维数组
void ShowMatrix(bool** matrix, const int num)
{
	for (int i = 0; i < num; i++) 
	{
		for (int j = 0; j < num; j++) 
		{
			if (j == num - 1)
				cout << matrix[i][j] << endl;
			else
				cout << matrix[i][j] << ' ';
		}
	}
}

// 求有num个元素关系的传递闭包（Warshall算法）
void TransitiveClosureWarshall(bool** matrix, int size)
{
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++) 
		{
			for (int j = 0; j < size; j++) 
			{
				if (i != k && j != k && !matrix[i][j]) 
				{  
					matrix[i][j] = matrix[i][k] && matrix[k][j]; 
				}
			}
		}
	}
}

int main()
{
	int num = 0;
	bool flag = true;
	while (flag)
	{
		while (true)
		{
			cout << "请输入矩阵阶数：";
			cin >> num;
			if (cin.good() && num > 0 && num <= INT_MAX)
			{
				break;
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "输入错误！请重新输入" << endl;
		} 
		bool** matrix;
		CreateMatrix(matrix, num);
		for (int i = 0; i < num; ++i)
		{
			cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
			for (int j = 0; j < num; ++j)
			{
				while (true)
				{
					cin >> matrix[i][j];
					if (cin.good())
					{
						break;
					}
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "矩阵的第" << i << "行，第" << j << "列元素输入错误，请继续输入:";
				}
			}
		}
		cout << "关系的传递闭包：" << endl;
		TransitiveClosureWarshall(matrix, num);
		ShowMatrix(matrix, num);
		DeleteMatrix(matrix, num);
		cout << "是否继续执行程序?(Y/N,Y/y 继续，N/n 退出)";
		char ch = '0';
		cin >> ch;
		if (ch == 'Y' || ch == 'y')
			continue;
		else if (ch == 'N' || ch == 'n')
			break;
	}
	return EXIT_SUCCESS;
}