// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string s[5] = {"abc","def","ghi"};
	cout << *(&s+1) << endl;//	string (*ps)[5] = &s;指向含有五个字符串的指针
	cout << *(s + 1) << endl;//def
	system("pause");
}

