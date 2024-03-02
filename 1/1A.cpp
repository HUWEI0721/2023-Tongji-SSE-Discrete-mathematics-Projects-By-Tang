#include <iostream>
#include <limits.h>

using namespace std;

//显示欢迎消息
void WelInfoShow()
{
    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        欢迎进入逻辑运算程序       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl;
    cout << endl;
}

//输入处理
int GetInput(char c)
{
    int i = -1;
    cout << "请输入" << c << "的值（0或1）,以回车结束:";
    cin >> i;
    if ((i != 0 && i != 1) || cin.fail())
    {
        cout << "\n  " << c << "的值输入有误,请重新输入!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        return GetInput(c);
    }
    cin.ignore(INT_MAX, '\n'); //防止读入第一个数字后方的输入影响下面输入
    return i;
}

//判断是否继续
bool WheContinue()
{
    bool flag;
    char s;
    cout << "\n是否继续？（y/n）:";
    cin >> s;
    if (s == 'y' || s == 'n')
    {
        if (s == 'y')
            flag = true; //继续
        else
        {
            cout << "欢迎下次再次使用!" << endl;  // 退出
            flag = false;
        }
    }
    else
    {
        cout << "输入错误,请重新输入!" << endl; // 错误校验
        return WheContinue();
    }
    cin.ignore(INT_MAX, '\n'); //防止读入第一个字母后方的输入影响下面输入
    return flag;
}

int main()
{
    WelInfoShow();
    int a[4];
    int P, Q;

    while (1)
    {
        P = GetInput('P');
        Q = GetInput('Q');

        a[0] = P && Q;                     //与运算
        a[1] = P || Q;                     //或运算
        a[2] = (!P) || Q;                  //蕴含运算，将其转化为与或非形式
        a[3] = ((!P) || Q) && ((!Q) || P); //等值运算，将其转化为与或非形式

        cout << "\n\n  合取:\n       P/\\Q = " << a[0] << endl; //输出结果
        cout << "  析取:\n       P\\/Q = " << a[1] << endl;
        cout << "  条件:\n       P->Q = " << a[2] << endl;
        cout << "  双条件:\n       P<->Q = " << a[3] << endl;
        if (!WheContinue())
            break;
    }
    return 0;
}