// tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "linkedBinaryTree.h"
#include <iostream>
#include<queue>

void theVisit(binaryTreeNode<char>* node)
{
	cout << node->element << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<char> v = { '/', '+', '*', '-','+', '+', '*', '#' ,'a','x','y','#','b','c','a'};
	vector<char> v1 = { '+', '+', 'd', '+', 'c', '#', '#', 'a', '#', '#', '#','b' };
	vector<char> v2= { '+', '*', '/', 'a', 'b', 'c', 'd' };
	linkedBinaryTree<char> lbt(v2);
	linkedBinaryTree<char> lbt1(lbt);
	//lbt1.preOrder(theVisit);

	//linkedBinaryTree<char> lbt1;
	//lbt1.copyTree(lbt);
	//lbt1.postOrder(theVisit);
	lbt1.breadthFistSearch(theVisit);
	//cout << lbt1.height(lbt1.getroot());
	cout << lbt1.height();
	//lbt1.unrecursivePostOrder(theVisit);
	//vector<char> v3 = { '+', '*', 'a', '#', '#', 'b','#', '#', '/', 'c', '#', '#','d','#','#' };
	vector<char> v3 = { 'A', 'B', 'D', 'H', '#', '#', 'I', '#', '#', 'E', '#', '#', 'C', 'F', '#', 'J', '#', '#', 'G' };
	system("pause");
	return 0;
}

