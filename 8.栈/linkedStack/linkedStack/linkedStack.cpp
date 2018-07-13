// linkedStack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "linkedStack.h"

int _tmain(int argc, _TCHAR* argv[])
{
	linkedStack ls(2);
	ls.push(3);
	ls.push(4);
	ls << cout<<ls.top()<< endl;
	ls.pop();
	cout << ls.top();
	system("pause");
	return 0;
}

