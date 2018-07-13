// linearTable.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ArrayList.h"
#include "linearList.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	linearList<double> *x = new ArrayList<double>(20);
	cout << x->getsize()<<endl;
	linearList<int> *l = new ArrayList<int>({ 2, 3, 4, 5, 6 });
	l->erase(3);
	l->erase(4);
	l->insert(1, 7);
	l->output(cout);
	cout << l->getsize()<<endl;
	cout << l->get(3) << endl;
	cout << l->indexOf(7) << endl;
	system("pause");
	return 0;
}

