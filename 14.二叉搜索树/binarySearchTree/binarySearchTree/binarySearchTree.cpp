// binarySearchTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "binarySearchTree.h"
#include <iostream>
int _tmain(int argc, _TCHAR* argv[])
{
	binarySearchTree bst;
   bst.insert(pair<int, int>(30, 30));
	bst.insert(pair<int, int>(35, 35));
	bst.insert(pair<int, int>(29, 29));
	bst.insert(pair<int, int>(28, 28));
    bst.insert(pair<int, int>(34, 34));
	bst.insert(pair<int, int>(38, 38));
	bst.insert(pair<int, int>(37, 37));
	bst.insert(pair<int, int>(40, 40));
	bst.insert(pair<int, int>(36, 36));
	bst.insert(pair<int, int>(6, 6));
	bst.insert(pair<int, int>(80, 80));
	bst.insert(pair<int, int>(60, 60));
	bst.insert(pair<int, int>(85, 85));
	bst.insert(pair<int, int>(32, 32));
	bst.insert(pair<int, int>(31, 31));
	bst.insert(pair<int, int>(33, 33));
//	bst.insert(pair<int, int>(35, 35));
	//bst.insert(pair<int, int>(34, 34));
     bst.erase(33);
	// bst.find(34);
	 cout << bst;
//	for (int i = 1; i <= bst.getsize();i++)
//	bst.findByIndex(i);
	 float x = 0.300;
	 cout <<( x );
	system("pause");
	return 0;
}

