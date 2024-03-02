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
  函数名称：findProposition
  功    能：判断一个命题变项是否被遍历过
  输入参数：Map_ic pSet：命题集合（下标-字符）
			char p：待检查的命题变项
  返 回 值：int：-1表示该命题变项尚未被遍历过；否则说明该命题变项已被遍历过，返回指定命题变项的下标
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
  函数名称：getProposition
  功    能：统计公式中的所有命题变项
  输入参数：string formula：待统计的公式
  返 回 值：Map_ic：命题集合（下标-字符）
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
			//遍历所有命题变项
			int r = findProposition(proposition, c);
			if (r == -1)
			{
				//说明该命题变项尚未被遍历过
				proposition[n_proposition] = c;
				n_proposition++;
			}
		}
		//出现非法字符则直接报错退出
		else if (!priority.count(c))  
		{
			cout << c << " is undefined!" << endl;
			exit(2);
		}
	}
	return proposition;
}

/***************************************************************************
  函数名称：toBinary
  功    能：将一个数转换为n位的二进制
  输入参数：int n_proposition：位数
			int index：待转换的数
  返 回 值：Map_ii：取值集合（位数-取值）
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
  函数名称：pow2
  功    能：返回2的n次方
  输入参数：int n：指数
  返 回 值：int：2的n次方
***************************************************************************/
int pow2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

/***************************************************************************
  函数名称：check
  功    能：根据操作数和运算符两栈的内容，进行相应的运算一次
  输入参数：stack<int>& value：存操作数的栈
			stack<char>& opter：存运算符的栈
  返 回 值：无
***************************************************************************/
void check(stack<int>& value, stack<char>& opter)
{
	int p, q, result;
	/*取栈顶的运算符，根据运算需要取1或两个操作数，
	  运算完成后结果放回栈中。栈顶运算符出栈*/
	char opt = opter.top();  

	switch (opt)
	{
		//与运算
		case '&':  
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();
			result = p && q;
			value.push(result);
			opter.pop();
			break;
		//或运算
		case '|':  
			p = value.top();
			value.pop();
			q = value.top();
			value.pop();
			result = p || q;
			value.push(result);
			opter.pop();
			break;
		//非运算
		case '!':  
			p = value.top();
			value.pop();
			result = !p;
			value.push(result);
			opter.pop();
			break;
		//蕴含运算
		case '^':  
			q = value.top();
			value.pop();
			p = value.top();
			value.pop();
			result = !p || q;
			value.push(result);
			opter.pop();
			break;
			//等价运算
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
			//继续运算直到下一个左括号出现
			while (opter.top() != '(')  
			{
				check(value, opter);
			}
			//将下一个左括号压入栈中
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
  函数名称：calculate
  功    能：根据公式，命题集合（下标-字符）和取值集合（位数-取值），算出公式的真值
  输入参数：string formula：公式
			Map_ic pSet：命题集合（下标-字符）
			Map_ii value：取值集合（位数-取值）
  返 回 值：运算结果
***************************************************************************/
int calculate(string formula, Map_ic pSet, Map_ii value)
{
	//存运算符的栈
	stack<char> opter; 
	//存操作数的栈
	stack<int> pvalue;  
	opter.push('#');
	formula = formula + "#";
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//将某个命题变项的取值找到，放入栈中
			pvalue.push(value[findProposition(pSet, c)]);  
		}
		//遍历运算符
		else
		{
			
			//取栈顶运算符
			char tmp = opter.top();  
			//若栈顶优先级高，则运算到栈顶优先级低于c或者有括号出现
			if (priority[tmp] > priority[c])  
			{
				while (priority[tmp] > priority[c] && tmp != '(')
				{
					check(pvalue, opter);
					tmp = opter.top();
					//若遇到#，则说明运算完成，返回结果
					if (tmp == '#' && c == '#')  
					{
						return pvalue.top();
					}
				}
				//栈顶优先级低于c，c进栈
				opter.push(c);  
			}
			else
				//栈顶优先级低于c，c进栈
				opter.push(c);  
		}
	}
	return -1;
}

/***************************************************************************
  函数名称：isOp
  功    能：判断一个字符是否是运算符
  输入参数：const char ch：待处理的运算符（只读）
  返 回 值：bool：该字符是否是运算符
  说    明：本函数仅限于加减乘除的判断
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
  函数名称：formulaCheck
  功    能：判断一个表达式是否合法
  输入参数：const String& str：待处理的表达式（只读）
  返 回 值：bool：该表达式是否合法
  说    明：本函数仅在表达式被预处理后进行判断（去除空格与对单目运算符的处理）
***************************************************************************/
bool formulaCheck(const string& str)
{
	//游标对象
	string::const_iterator it = str.begin();
	//记录括号情况的栈
	stack<char> brackets;  
	//操作符（单目、双目）个数，数字个数
	int op1Num = 0, op2Num = 0, numNum = 0;  

	while (it != str.end()) {
		//若扫描到字符表示命题，则进行计数
		if (((*it) >= 'a' && (*it) <= 'z') || ((*it) >= 'A' && (*it) <= 'Z'))
			//一个数字扫描完成，进行计数
			numNum++;  
		//若遇到左括号，压入栈中
		if (*it == '(')  
			brackets.push(*it);
		else if (*it == ')') 
		{
			/*若遇到右括号，栈不为空则弹出一个元素；
			  栈为空则说明右括号多余，非法*/
			if (!brackets.empty())
				brackets.pop();

			else {
				cout << "括号不匹配" << endl;
				return false;
			}
		}
		else if (isOp(*it)) 
		{
			//若遇到操作符，进行计数
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
		//若扫描完成栈仍不为空，则左括号多余，非法
		cout << "括号不匹配" << endl;
		return false;
	}

	if (numNum != op2Num + 1) 
	{ 
		//若双目运算符个数不等于数字个数+1，则不匹配，非法
		cout << "操作符与操作数数量不匹配" << endl;
		return false;
	}
	//所有标准均符合，则表达式合法
	return true;  
}

/***************************************************************************
  函数名称：PrintMenu
  功    能：输出菜单栏
  输入参数：无
  返 回 值：空
***************************************************************************/
void PrintMenu()
{
	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "请输入合法的命题公式: ";
}


/***************************************************************************
  函数名称：main
  功    能：主函数
  输入参数：无
  返 回 值：0
***************************************************************************/
int main()
{
	//运算符优先级
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
		//输入公式
		cin >> formula;
		//检查公式是否合法
		if (!formulaCheck(formula))
		{
			cout << "输入公式不合法，请重新输入" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			Sleep(5000);
			system("cls");
			continue;
		}
		//统计命题变项
		Map_ic proposition_set = getProposition(formula);
		cout << "该式子中的变量个数为：" << proposition_set.size() << endl << "输出真值表如下：" << endl;
		for (unsigned int i = 0; i < proposition_set.size(); i++)
		{
			//输出所有的命题变项
			cout << proposition_set[i] << "\t";
		}
		cout << formula << endl;
		int* m;
		//该数组依次存放命题公式的各行(0或1)的运算结果的值
		m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));
		//有2^n种取值，遍历一遍
		for (int i = 0; i < pow2(proposition_set.size()); i++)
		{
			//将取值转换为二进制
			Map_ii bina_set = toBinary(proposition_set.size(), i);
			for (unsigned int j = 0; j < bina_set.size(); j++)
			{
				//将各命题变项的值打印出来
				cout << bina_set[j] << "\t";
			}
			//计算公式真值
			int result = calculate(formula, proposition_set, bina_set);
			//记录这一次的真值
			*(m + i) = result;
			//打印这一次的计算结果
			cout << result << endl;
		}
		int n_m = 0, n_M = 0;
		cout << "该命题公式的主析取范式：" << endl;
		//统计成真赋值并打印主析取范式
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
		//无成真赋值情况
		if (n_m == 0)
			cout << "0";
		cout << endl;
		cout << "该命题公式的主合取范式：" << endl;
		//统计成假赋值并打印主合取范式
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
			//无成假赋值情况
			if (n_M == 0)
				cout << "0";
		}
		cout << endl << endl;
		//是否再次进行运算其它表达式
		cout << "是否继续运算(Y/N)？ Y代表继续 N代表退出 大小写不敏感" << endl;
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
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(CHAR_MAX, '\n');
				continue;
			}
		}
		continue;
	}
}