#include <iostream>
using namespace std;

int main()
{
	cout << "命题如下：" << endl;
	cout << "（1）营业员A或B偷了手表" << endl;
	cout << "（2）若A作案，则作案不在营业时间" << endl;
	cout << "（3）若B提供的证据正确，则货柜未上锁" << endl;
	cout << "（4）若B提供的证据不正确，则作案发生在营业时间" << endl;
	cout << "（5）货柜上了锁" << endl;

	cout << endl;
	cout << "用命题变元表示如下：" << endl;
	cout << "A : 营业员A偷了手表" << endl;
	cout << "B : 营业员B偷了手表" << endl;
	cout << "C : 作案不在营业时间" << endl;
	cout << "D : B提供的证据正确" << endl;
	cout << "E : 货柜未上锁" << endl;

	cout << endl;
	cout << "命题与命题变元的对应表示为：" << endl;
	cout << "（1）营业员A或B偷了手表                         ->   A  | B " << endl;
	cout << "（2）若A作案，则作案不在营业时间                ->   A -> C" << endl;
	cout << "（3）若B提供的证据正确，则货柜未上锁            ->   D -> E" << endl;
	cout << "（4）若B提供的证据不正确，则作案发生在营业时间  ->   !D->!C" << endl;
	cout << "（5）货柜上了锁                                 ->   !E" << endl;

	for (int A = 0; A <= 1; A++)
		for (int B = 0; B <= 1; B++)
			for (int C = 0; C <= 1; C++)
				for (int D = 0; D <= 1; D++)
					for (int E = 0; E <= 1; E++)
						if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E)  // 在计算时，a->b转换为!a|b
						{
							cout << endl << "A=" << A << "，B=" << B << "时，满足以上全部条件" << endl;
							cout << endl;
							cout << "根据以上推理：";
							A ? cout << "A偷了手表" : cout << "A没有偷手表";  // 若a！=0,则A偷了手表，否则A没有偷
							cout << "    ";
							B ? cout << "B偷了手表" : cout << "B没有偷手表";  // 若b！=0,则B偷了手表，否则B没有偷
							cout << endl;
						}
	return 0;
}