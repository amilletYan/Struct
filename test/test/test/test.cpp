// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string s[5] = {"abc","def","ghi"};
	cout << *(&s+1) << endl;//	string (*ps)[5] = &s;ָ��������ַ�����ָ��
	cout << *(s + 1) << endl;//def
	system("pause");
}

