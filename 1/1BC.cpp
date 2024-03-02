#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <windows.h>
#include <limits.h>
using namespace std;

typedef map<char, int> Map_ci;
typedef map<int, char> Map_ic;
typedef map<int, int> Map_ii;

Map_ci priority;

/***************************************************************************
  �������ƣ�findProposition
  ��    �ܣ��ж�һ����������Ƿ񱻱�����
  ���������Map_ic pSet�����⼯�ϣ��±�-�ַ���
			char p���������������
  �� �� ֵ��int��-1��ʾ�����������δ��������������˵������������ѱ�������������ָ�����������±�
***************************************************************************/
int findProposition(Map_ic pSet, char p)
{
	Map_ic::iterator it = pSet.begin();
	while (it != pSet.end())
	{
		if (it->second == p)
		{
			return it->first;
		}
		it++;
	}
	return -1;
}

/***************************************************************************
  �������ƣ�getProposition
  ��    �ܣ�ͳ�ƹ�ʽ�е������������
  ���������string formula����ͳ�ƵĹ�ʽ
  �� �� ֵ��Map_ic�����⼯�ϣ��±�-�ַ���
***************************************************************************/
Map_ic getProposition(string formula)
{
	Map_ic proposition;
	int n_proposition = 0;
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//���������������
			int r = findProposition(proposition, c);
			if (r == -1)
			{
				//˵�������������δ��������
				proposition[n_proposition] = c;
				n_proposition++;
			}
		}
		//���ַǷ��ַ���ֱ�ӱ����˳�
		else if (!priority.count(c))  
		{
			cout << c << " is undefined!" << endl;
			exit(2);
		}
	}
	return proposition;
}

/***************************************************************************
  �������ƣ�toBinary
  ��    �ܣ���һ����ת��Ϊnλ�Ķ�����
  ���������int n_proposition��λ��
			int index����ת������
  �� �� ֵ��Map_ii��ȡֵ���ϣ�λ��-ȡֵ��
***************************************************************************/
Map_ii toBinary(int n_proposition, int index)
{
	Map_ii result;
	for (int i = 0; i < n_proposition; i++)
	{
		int r = index % 2;
		result[n_proposition - 1 - i] = r;
		index = index / 2;
	}
	return result;
}

/***************************************************************************
  �������ƣ�pow2
  ��    �ܣ�����2��n�η�
  ���������int n��ָ��
  �� �� ֵ��int��2��n�η�
***************************************************************************/
int pow2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

/***************************************************************************
  �������ƣ�check
  ��    �ܣ����ݲ��������������ջ�����ݣ�������Ӧ������һ��
  ���������stack<int>& value�����������ջ
			stack<char>& opter�����������ջ
  �� �� ֵ����
***************************************************************************/
void check(stack<int>& value, stack<char>& opter)
{
	int p, q, result;
	/*ȡջ���������������������Ҫȡ1��������������
	  ������ɺ����Ż�ջ�С�ջ���������ջ*/
	char opt = opter.top();  

	switch (opt)
	{
		//������
		case '&':  
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();
			result = p && q;
			value.push(result);
			opter.pop();
			break;
		//������
		case '|':  
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();
			result = p || q;
			value.push(result);
			opter.pop();
			break;
		//������
		case '!':  
			p = value.top();
			value.pop();
			result = !p;
			value.push(result);
			opter.pop();
			break;
		//�̺�����
		case '^':  
			q = value.top();
			value.pop();
			p = value.top();
			value.pop();
			result = !p || q;
			value.push(result);
			opter.pop();
			break;
			//�ȼ�����
		case '~':  
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();
			result = (!p || q) && (p || !q);
			value.push(result);
			opter.pop();
			break;

		case '#':
			break;

		case '(':
			break;

		case ')':
			opter.pop();
			//��������ֱ����һ�������ų���
			while (opter.top() != '(')  
			{
				check(value, opter);
			}
			//����һ��������ѹ��ջ��
			if (opter.top() == '(')  
			{
				opter.pop();
			}
			break;

		default:
			break;
	}
}

/***************************************************************************
  �������ƣ�calculate
  ��    �ܣ����ݹ�ʽ�����⼯�ϣ��±�-�ַ�����ȡֵ���ϣ�λ��-ȡֵ���������ʽ����ֵ
  ���������string formula����ʽ
			Map_ic pSet�����⼯�ϣ��±�-�ַ���
			Map_ii value��ȡֵ���ϣ�λ��-ȡֵ��
  �� �� ֵ��������
***************************************************************************/
int calculate(string formula, Map_ic pSet, Map_ii value)
{
	//���������ջ
	stack<char> opter; 
	//���������ջ
	stack<int> pvalue;  
	opter.push('#');
	formula = formula + "#";
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//��ĳ����������ȡֵ�ҵ�������ջ��
			pvalue.push(value[findProposition(pSet, c)]);  
		}
		//���������
		else
		{
			
			//ȡջ�������
			char tmp = opter.top();  
			//��ջ�����ȼ��ߣ������㵽ջ�����ȼ�����c���������ų���
			if (priority[tmp] > priority[c])  
			{
				while (priority[tmp] > priority[c] && tmp != '(')
				{
					check(pvalue, opter);
					tmp = opter.top();
					//������#����˵��������ɣ����ؽ��
					if (tmp == '#' && c == '#')  
					{
						return pvalue.top();
					}
				}
				//ջ�����ȼ�����c��c��ջ
				opter.push(c);  
			}
			else
				//ջ�����ȼ�����c��c��ջ
				opter.push(c);  
		}
	}
	return -1;
}

/***************************************************************************
  �������ƣ�isOp
  ��    �ܣ��ж�һ���ַ��Ƿ��������
  ���������const char ch����������������ֻ����
  �� �� ֵ��bool�����ַ��Ƿ��������
  ˵    ���������������ڼӼ��˳����ж�
***************************************************************************/
bool isOp(const char ch)
{
	switch (ch) {
		case '&':
		case '|':
		case '!':
		case '^':
		case '~':
			return true;
			break;
		default:
			return false;
	}
}

/***************************************************************************
  �������ƣ�formulaCheck
  ��    �ܣ��ж�һ�����ʽ�Ƿ�Ϸ�
  ���������const String& str��������ı��ʽ��ֻ����
  �� �� ֵ��bool���ñ��ʽ�Ƿ�Ϸ�
  ˵    �������������ڱ��ʽ��Ԥ���������жϣ�ȥ���ո���Ե�Ŀ������Ĵ���
***************************************************************************/
bool formulaCheck(const string& str)
{
	//�α����
	string::const_iterator it = str.begin();
	//��¼���������ջ
	stack<char> brackets;  
	//����������Ŀ��˫Ŀ�����������ָ���
	int op1Num = 0, op2Num = 0, numNum = 0;  

	while (it != str.end()) {
		//��ɨ�赽�ַ���ʾ���⣬����м���
		if (((*it) >= 'a' && (*it) <= 'z') || ((*it) >= 'A' && (*it) <= 'Z'))
			//һ������ɨ����ɣ����м���
			numNum++;  
		//�����������ţ�ѹ��ջ��
		if (*it == '(')  
			brackets.push(*it);
		else if (*it == ')') 
		{
			/*�����������ţ�ջ��Ϊ���򵯳�һ��Ԫ�أ�
			  ջΪ����˵�������Ŷ��࣬�Ƿ�*/
			if (!brackets.empty())
				brackets.pop();

			else {
				cout << "���Ų�ƥ��" << endl;
				return false;
			}
		}
		else if (isOp(*it)) 
		{
			//�����������������м���
			if (*it == '!')
				op1Num++;
			else
				op2Num++;
		}

		if (it != str.end())
			it++;
		else
			break;
	}

	if (!brackets.empty()) 
	{
		//��ɨ�����ջ�Բ�Ϊ�գ��������Ŷ��࣬�Ƿ�
		cout << "���Ų�ƥ��" << endl;
		return false;
	}

	if (numNum != op2Num + 1) 
	{ 
		//��˫Ŀ������������������ָ���+1����ƥ�䣬�Ƿ�
		cout << "�������������������ƥ��" << endl;
		return false;
	}
	//���б�׼�����ϣ�����ʽ�Ϸ�
	return true;  
}

/***************************************************************************
  �������ƣ�PrintMenu
  ��    �ܣ�����˵���
  �����������
  �� �� ֵ����
***************************************************************************/
void PrintMenu()
{
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "������Ϸ������⹫ʽ: ";
}


/***************************************************************************
  �������ƣ�main
  ��    �ܣ�������
  �����������
  �� �� ֵ��0
***************************************************************************/
int main()
{
	//��������ȼ�
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;

	while (1)
	{
		PrintMenu();
		string formula;
		//���빫ʽ
		cin >> formula;
		//��鹫ʽ�Ƿ�Ϸ�
		if (!formulaCheck(formula))
		{
			cout << "���빫ʽ���Ϸ�������������" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			Sleep(5000);
			system("cls");
			continue;
		}
		//ͳ���������
		Map_ic proposition_set = getProposition(formula);
		cout << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl << "�����ֵ�����£�" << endl;
		for (unsigned int i = 0; i < proposition_set.size(); i++)
		{
			//������е��������
			cout << proposition_set[i] << "\t";
		}
		cout << formula << endl;
		int* m;
		//���������δ�����⹫ʽ�ĸ���(0��1)����������ֵ
		m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));
		//��2^n��ȡֵ������һ��
		for (int i = 0; i < pow2(proposition_set.size()); i++)
		{
			//��ȡֵת��Ϊ������
			Map_ii bina_set = toBinary(proposition_set.size(), i);
			for (unsigned int j = 0; j < bina_set.size(); j++)
			{
				//������������ֵ��ӡ����
				cout << bina_set[j] << "\t";
			}
			//���㹫ʽ��ֵ
			int result = calculate(formula, proposition_set, bina_set);
			//��¼��һ�ε���ֵ
			*(m + i) = result;
			//��ӡ��һ�εļ�����
			cout << result << endl;
		}
		int n_m = 0, n_M = 0;
		cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
		//ͳ�Ƴ��渳ֵ����ӡ����ȡ��ʽ
		for (int i = 0; i < pow2(proposition_set.size()); i++)
		{
			if (*(m + i) == 1)
			{
				if (n_m == 0)
					cout << "m<" << i << ">";
				else
					cout << " \\/ m<" << i << "> ";
				n_m++;
			}
		}
		//�޳��渳ֵ���
		if (n_m == 0)
			cout << "0";
		cout << endl;
		cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
		//ͳ�Ƴɼٸ�ֵ����ӡ����ȡ��ʽ
		for (int i = 0; i < pow2(proposition_set.size()); i++)
		{
			if (*(m + i) == 0)
			{
				if (n_M == 0)
					cout << "M<" << i << ">";
				else
					cout << " /\\ M<" << i << "> ";
				n_M++;
			}
			//�޳ɼٸ�ֵ���
			if (n_M == 0)
				cout << "0";
		}
		cout << endl << endl;
		//�Ƿ��ٴν��������������ʽ
		cout << "�Ƿ��������(Y/N)�� Y������� N�����˳� ��Сд������" << endl;
		char ch;
		while (1)
		{
			cin >> ch;
			if (ch == 'Y' || ch == 'y')
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				break;
			}
			else if (ch == 'N' || ch == 'n')
			{
				return 0;
			}
			else
			{
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(CHAR_MAX, '\n');
				continue;
			}
		}
		continue;
	}
}