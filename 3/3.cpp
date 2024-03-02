#include<iostream>
#include<climits>
#include<conio.h>
#include<stdlib.h>

using namespace std;

//���ܣ�����һ����������Ϊnum�Ķ�ά����
void Create(bool**& Matrix, const int num)
{
	//����һάָ�������
	Matrix = (bool**) new bool* [num];  

	if (Matrix == NULL)
	{
		cerr << "�ڴ����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		//Ϊÿһ��һάָ�뿪�ٿռ�
		Matrix[i] = new bool[num]; 

		if (Matrix[i] == NULL) 
		{
			cerr << "�ڴ����ʧ�ܣ�" << endl;
			exit(1);
		}
	}
}

//���ܣ�����һ����������Ϊnum�Ķ�ά���飬ͬʱ����һ����ά���������г�ʼ��
void Create(bool**& Matrix, bool** data, const int num)
{
	//����һάָ�������
	Matrix = (bool**) new bool* [num];

	if (Matrix == NULL) 
	{
		cerr << "�ڴ����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++)
	{
		//Ϊÿһ��һάָ�뿪�ٿռ�
		Matrix[i] = new bool[num]; 

		if (Matrix[i] == NULL)
		{
			cerr << "�ڴ����ʧ�ܣ�" << endl;
			exit(1);
		}

		for (int j = 0; j < num; j++)
			Matrix[i][j] = data[i][j];
	}
}

//���ܣ�ɾ��һ����������Ϊnum�Ķ�ά����
void Delete(bool**& Matrix, const int num)
{
	for (int i = 0; i < num; i++)
		delete[] Matrix[i];
}

//���ܣ�չʾһ����������Ϊnum�Ķ�ά����
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

//���ܣ�����num��Ԫ�ع�ϵ���Է��հ�
void Reflexive(bool** Matrix, const int num)
{
	cout << "�Է��հ�:" << endl;
	//�Խ�����Ԫ�ض���Ϊ1
	for (int i = 0; i < num; i++)
		Matrix[i][i] = true;
}

//���ܣ�����num��Ԫ�ع�ϵ�ĶԳƱհ�
void Symmetric(bool** Matrix, const int num)
{
	bool** rev;
	Create(rev, num);
	cout << "�ԳƱհ�" << endl;
	//ȡԭ�����ת��
	for (int i = 0; i < num; i++) 
	{
		for (int j = 0; j < num; j++) 
		{
			rev[i][j] = Matrix[j][i];
		}
	}

	//ԭ������ת�����
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			Matrix[i][j] = Matrix[i][j] || rev[i][j];
		}
	}

	Delete(rev, num);
}

//���ܣ�����num��Ԫ�ع�ϵ�Ĵ��ݱհ���һ���󷨣�
void Transitive(bool** Matrix, const int num)
{
	//ԭ����
	bool** Default;
	Create(Default, num);

	//ԭ�����n�η�
	bool** Current;
	Create(Current, num);

	//����ԭ����n�η�ʱ�������ʱ���
	bool** Result;
	Create(Result, num);
	cout << "���ݱհ�" << endl;
	//��Default��Current��ֵ��ʹ��Default��ԭ����Current�ǵ�λ��
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
		//Current��Default��ˣ��õ�M��n�η�
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

		//����Current��ֵ
		for (int i = 0; i < num; i++) 
		{
			for (int j = 0; j < num; j++) 
			{
				Current[i][j] = Result[i][j];
			}
		}

		//Matrix��Current��ӣ��õ����
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
		cout << "��������������";
		cin >> num;
		cout << endl;
		if (cin.good() && num > 0 && num <= INT_MAX)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "�����������������" << endl;
	}

	bool** data;
	Create(data, num);

	for (int i = 0; i < num; i++)
	{
		//����ÿ��Ԫ��
		cout << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�):";
		for (int j = 0; j < num; j++) 
		{
			while (1)
			{
				cin >> data[i][j];
				
				if (cin.good() && (data[i][j] == true || data[i][j] == false))
					break;

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "����ĵ�" << i << "�У���" << j << "��Ԫ������������������:";
			}
		}
		cout << endl;
	}

	while (isContinue) 
	{
		cout << endl;
		cout << "**********************************" << endl;
		cout << "**     �����Ӧ���ѡ���㷨     **" << endl;
		cout << "**********************************" << endl;
		cout << "**           1.�Է��հ�         **" << endl;
		cout << "**           2.�ԳƱհ�         **" << endl;
		cout << "**           3.���ݱհ�         **" << endl;
		cout << "**           4.�˳�             **" << endl;
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
/*�������ݣ�
			1 0 1 1

			0 1 0 1

			0 0 0 0

			1 0 0 0
*/