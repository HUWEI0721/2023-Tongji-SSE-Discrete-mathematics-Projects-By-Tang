#include<iostream>
#include<climits>
#include<conio.h>
#include<stdlib.h>

using namespace std;

//功能：生成一个行列数都为num的二维数组
void Create(bool**& Matrix, const int num)
{
	//开辟一维指针的数组
	Matrix = (bool**) new bool* [num];  

	if (Matrix == NULL)
	{
		cerr << "内存分配失败！" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		//为每一个一维指针开辟空间
		Matrix[i] = new bool[num]; 

		if (Matrix[i] == NULL) 
		{
			cerr << "内存分配失败！" << endl;
			exit(1);
		}
	}
}

//功能：生成一个行列数都为num的二维数组，同时用另一个二维数组对其进行初始化
void Create(bool**& Matrix, bool** data, const int num)
{
	//开辟一维指针的数组
	Matrix = (bool**) new bool* [num];

	if (Matrix == NULL) 
	{
		cerr << "内存分配失败！" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		//为每一个一维指针开辟空间
		Matrix[i] = new bool[num]; 

		if (Matrix[i] == NULL)
		{
			cerr << "内存分配失败！" << endl;
			exit(1);
		}

		for (int j = 0; j < num; j++)
			Matrix[i][j] = data[i][j];
	}
}

//功能：删除一个行列数都为num的二维数组
void Delete(bool**& Matrix, const int num)
{
	for (int i = 0; i < num; i++)
		delete[] Matrix[i];
}

//功能：展示一个行列数都为num的二维数组
void show(bool** Matrix, const int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << "         ";
		for (int j = 0; j < num; j++)
		{
			if (j == num - 1)
				cout << Matrix[i][j] << endl;
			else
				cout << Matrix[i][j] << ' ';
		}
	}
}

//功能：求有num个元素关系的自反闭包
void Reflexive(bool** Matrix, const int num)
{
	cout << "自反闭包:" << endl;
	//对角线上元素都置为1
	for (int i = 0; i < num; i++)
		Matrix[i][i] = true;
}

//功能：求有num个元素关系的对称闭包
void Symmetric(bool** Matrix, const int num)
{
	bool** rev;
	Create(rev, num);
	cout << "对称闭包" << endl;
	//取原矩阵的转置
	for (int i = 0; i < num; i++) 
	{
		for (int j = 0; j < num; j++) 
		{
			rev[i][j] = Matrix[j][i];
		}
	}

	//原矩阵与转置相加
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			Matrix[i][j] = Matrix[i][j] || rev[i][j];
		}
	}

	Delete(rev, num);
}

//功能：求有num个元素关系的传递闭包（一般求法）
void Transitive(bool** Matrix, const int num)
{
	//原矩阵
	bool** Default;
	Create(Default, num);

	//原矩阵的n次方
	bool** Current;
	Create(Current, num);

	//运算原矩阵n次方时，存放临时结果
	bool** Result;
	Create(Result, num);
	cout << "传递闭包" << endl;
	//给Default和Current赋值，使得Default是原矩阵，Current是单位阵
	for (int i = 0; i < num; i++) 
	{
		for (int j = 0; j < num; j++)
		{
			Default[i][j] = Matrix[i][j];

			if (i == j)
				Current[i][j] = true;
			else
				Current[i][j] = false;
		}
	}

	for (int times = 0; times < num; times++)
	{
		//Current和Default相乘，得到M的n次方
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				bool* primes = new bool[num];

				for (int k = 0; k < num; k++)
					primes[k] = Current[i][k] && Default[k][j];

				Result[i][j] = false;

				for (int k = 0; k < num; k++)
					Result[i][j] = Result[i][j] || primes[k];

				delete[] primes;
			}
		}

		//更新Current的值
		for (int i = 0; i < num; i++) 
		{
			for (int j = 0; j < num; j++) 
			{
				Current[i][j] = Result[i][j];
			}
		}

		//Matrix和Current相加，得到结果
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++) 
			{
				Matrix[i][j] = Matrix[i][j] || Current[i][j];
			}
		}
	}

	Delete(Default, num);
	Delete(Current, num);
	Delete(Result, num);
}


int main()
{
	int num = 0;
	bool isContinue = true;

	while (1) 
	{  
		cout << "请输入矩阵阶数：";
		cin >> num;
		cout << endl;
		if (cin.good() && num > 0 && num <= INT_MAX)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "输入错误！请重新输入" << endl;
	}

	bool** data;
	Create(data, num);

	for (int i = 0; i < num; i++)
	{
		//输入每个元素
		cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
		for (int j = 0; j < num; j++) 
		{
			while (1)
			{
				cin >> data[i][j];
				
				if (cin.good() && (data[i][j] == true || data[i][j] == false))
					break;

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "矩阵的第" << i << "行，第" << j << "列元素输入错误，请继续输入:";
			}
		}
		cout << endl;
	}

	while (isContinue) 
	{
		cout << endl;
		cout << "**********************************" << endl;
		cout << "**     输入对应序号选择算法     **" << endl;
		cout << "**********************************" << endl;
		cout << "**           1.自反闭包         **" << endl;
		cout << "**           2.对称闭包         **" << endl;
		cout << "**           3.传递闭包         **" << endl;
		cout << "**           4.退出             **" << endl;
		cout << "**********************************" << endl;

		char choice = '\0';

		while (1) 
		{
			choice = _getch();

			if (choice >= '1' && choice <= '4')
			{
				cout << choice << endl;
				break;
			}
		}

		bool** Matrix;
		Create(Matrix, data, num);

		switch (choice) 
		{
			case '1':
				Reflexive(Matrix, num);
				show(Matrix, num);
				Delete(Matrix, num);
				break;
			case '2':
				Symmetric(Matrix, num);
				show(Matrix, num);
				Delete(Matrix, num);
				break;
			case '3':
				Transitive(Matrix, num);
				show(Matrix, num);
				Delete(Matrix, num);
				break;
			case '4':
				isContinue = false;
				Delete(Matrix, num);
				break;
		}
	}

	return 0;
}
/*测试数据：
			1 0 1 1

			0 1 0 1

			0 0 0 0

			1 0 0 0
*/