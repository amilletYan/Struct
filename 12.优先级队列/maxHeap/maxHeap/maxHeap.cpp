// maxHeap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "maxHeap.h"

int _tmain(int argc, _TCHAR* argv[])
{
	maxHeap mh;//����д��mh()����û�Ӳ������ᱻ����һ����������
	//����Ĭ�Ϲ��캯�����ϣ�д��mh()�����ж��ƥ��Ĺ��캯��
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

