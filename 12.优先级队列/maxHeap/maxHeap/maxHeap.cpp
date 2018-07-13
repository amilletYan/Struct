// maxHeap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "maxHeap.h"

int _tmain(int argc, _TCHAR* argv[])
{
	maxHeap mh;//这里写成mh()，又没加参数，会被当成一个函数声明
	//若把默认构造函数加上，写成mh()，会有多个匹配的构造函数
	int i[10] = { 20, 12, 35, 15, 10, 80, 30, 17, 2, 1 };
	mh.initialize(i, 10);
	mh.push(90);
	mh.pop();
	int *a = new int[10];
	mh.heapSort(a);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << ends;
	}
	system("pause");
	return 0;
}

