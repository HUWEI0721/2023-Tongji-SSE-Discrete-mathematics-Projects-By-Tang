#include<iostream>
#include<climits>
#include<conio.h>
#include<stdlib.h>
using namespace std;

// ����һ����������Ϊnum�Ķ�ά����
void CreateMatrix(bool**& matrix, const int num)
{
	matrix = (bool**) new bool* [num];  /*����һάָ�������*/

	if (matrix == NULL) 
	{
		cerr << "�ڴ����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		matrix[i] = new bool[num];  /*Ϊÿһ��һάָ�뿪�ٿռ�*/

		if (matrix[i] == NULL) {
			cerr << "�ڴ����ʧ�ܣ�" << endl;
			exit(1);
		}
	}
}

// ɾ��һ����������Ϊnum�Ķ�ά����
void DeleteMatrix(bool**& matrix, const int num)
{
	for (int i = 0; i < num; i++)
		delete[] matrix[i];
}

// չʾһ����������Ϊnum�Ķ�ά����
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

// ����num��Ԫ�ع�ϵ�Ĵ��ݱհ���Warshall�㷨��
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
			cout << "��������������";
			cin >> num;
			if (cin.good() && num > 0 && num <= INT_MAX)
			{
				break;
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "�����������������" << endl;
		} 
		bool** matrix;
		CreateMatrix(matrix, num);
		for (int i = 0; i < num; ++i)
		{
			cout << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�):";
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
					cout << "����ĵ�" << i << "�У���" << j << "��Ԫ������������������:";
				}
			}
		}
		cout << "��ϵ�Ĵ��ݱհ���" << endl;
		TransitiveClosureWarshall(matrix, num);
		ShowMatrix(matrix, num);
		DeleteMatrix(matrix, num);
		cout << "�Ƿ����ִ�г���?(Y/N,Y/y ������N/n �˳�)";
		char ch = '0';
		cin >> ch;
		if (ch == 'Y' || ch == 'y')
			continue;
		else if (ch == 'N' || ch == 'n')
			break;
	}
	return EXIT_SUCCESS;
}