#include <iostream>
#include <limits.h>

using namespace std;

//��ʾ��ӭ��Ϣ
void WelInfoShow()
{
    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**        ��ӭ�����߼��������       **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl;
    cout << endl;
}

//���봦��
int GetInput(char c)
{
    int i = -1;
    cout << "������" << c << "��ֵ��0��1��,�Իس�����:";
    cin >> i;
    if ((i != 0 && i != 1) || cin.fail())
    {
        cout << "\n  " << c << "��ֵ��������,����������!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        return GetInput(c);
    }
    cin.ignore(INT_MAX, '\n'); //��ֹ�����һ�����ֺ󷽵�����Ӱ����������
    return i;
}

//�ж��Ƿ����
bool WheContinue()
{
    bool flag;
    char s;
    cout << "\n�Ƿ��������y/n��:";
    cin >> s;
    if (s == 'y' || s == 'n')
    {
        if (s == 'y')
            flag = true; //����
        else
        {
            cout << "��ӭ�´��ٴ�ʹ��!" << endl;  // �˳�
            flag = false;
        }
    }
    else
    {
        cout << "�������,����������!" << endl; // ����У��
        return WheContinue();
    }
    cin.ignore(INT_MAX, '\n'); //��ֹ�����һ����ĸ�󷽵�����Ӱ����������
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

        a[0] = P && Q;                     //������
        a[1] = P || Q;                     //������
        a[2] = (!P) || Q;                  //�̺����㣬����ת��Ϊ������ʽ
        a[3] = ((!P) || Q) && ((!Q) || P); //��ֵ���㣬����ת��Ϊ������ʽ

        cout << "\n\n  ��ȡ:\n       P/\\Q = " << a[0] << endl; //������
        cout << "  ��ȡ:\n       P\\/Q = " << a[1] << endl;
        cout << "  ����:\n       P->Q = " << a[2] << endl;
        cout << "  ˫����:\n       P<->Q = " << a[3] << endl;
        if (!WheContinue())
            break;
    }
    return 0;
}